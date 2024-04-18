//  PMDSer.c -- serial interface command/data transfer functions
//
//  Performance Motion Devices, Inc.
//

#include <stdio.h>
#include <stdlib.h>

#include "PMDtypes.h"
#include "PMDecode.h"
#include "PMDdevice.h"
#include "PMDtrans.h"
#include "PMDsys.h"
#include "PMDw32ser.h"

// only need to include this if diagnostics mode is used
#include "PMDdiag.h"


// ------------------------------------------------------------------------
PMDuint16 PMDSerial_GetStatus(void* transport_data)
{
    return 0;
}

// ------------------------------------------------------------------------
PMDuint16 PMDSerial_IsReady(void* transport_data)
{
    return 1;
}

// ------------------------------------------------------------------------
PMDuint16 PMDSerial_HasInterrupt(void* transport_data)
{
    return 0;
}

// ------------------------------------------------------------------------
PMDuint16 PMDSerial_HasError(void* transport_data)
{
    return 0;
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_HardReset(void* transport_data)
{
    return PMD_ERR_InvalidOperation; // unsupported
}


// ------------------------------------------------------------------------
PMDuint16 PMDSerial_InitPort(void* transport_data)
{
    char szPort[10] = "\\\\.\\COM";
    char szPortNum[3];
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    itoa( SIOtransport_data->port, szPortNum, 10 );
    strcat( szPort, szPortNum );

    SIOtransport_data->hPort = CreateFile( szPort, GENERIC_READ|GENERIC_WRITE, 0, 
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

    if( SIOtransport_data->hPort == INVALID_HANDLE_VALUE )
    {
        return PMD_ERR_InvalidSerialPort;
    }

    if( !PMDSerial_SetConfig( transport_data, SIOtransport_data->baud, NOPARITY) )
    {
        CloseHandle( SIOtransport_data->hPort );
        SIOtransport_data->hPort = INVALID_HANDLE_VALUE;
        return PMD_ERR_InvalidSerialPort;
    }

    if( !PMDSerial_SetTimeout( transport_data, 100 ) )
    {
        CloseHandle( SIOtransport_data->hPort );
        SIOtransport_data->hPort = INVALID_HANDLE_VALUE;
        return PMD_ERR_InvalidSerialPort;
    }

    return PMD_ERR_OK;
}


// ------------------------------------------------------------------------
PMDresult PMDSerial_Close(void* transport_data)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    if (transport_data != NULL)
    {
        if ( SIOtransport_data->hPort!=INVALID_HANDLE_VALUE )
        {
            CloseHandle( SIOtransport_data->hPort );
            SIOtransport_data->hPort = INVALID_HANDLE_VALUE;
        }
        free(transport_data);
    }
    transport_data = NULL;

    return PMD_ERR_OK;
}

// ------------------------------------------------------------------------
BOOL PMDSerial_SetConfig(void* transport_data,PMDuint32 b,PMDuint8 p)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    DCB dcb;

    SIOtransport_data->baud   = b;
    SIOtransport_data->parity = p;
    SIOtransport_data->stop   = ONESTOPBIT;

    if( SIOtransport_data->hPort == INVALID_HANDLE_VALUE ) return FALSE;

    dcb.DCBlength         = sizeof(DCB);
    dcb.BaudRate          = b;
    dcb.fBinary           = 1;
    dcb.fParity           = TRUE;
    dcb.fOutxCtsFlow      = 0;
    dcb.fOutxDsrFlow      = 0;
    dcb.fDtrControl       = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity   = 0;
    dcb.fTXContinueOnXoff = 0;
    dcb.fOutX             = 0;
    dcb.fInX              = 0;
    dcb.fErrorChar        = 0;
    dcb.fNull             = 0;
    dcb.fRtsControl       = RTS_CONTROL_DISABLE;
    dcb.fAbortOnError     = 0;
    dcb.XonLim            = 0;
    dcb.XoffLim           = 0;
    dcb.ByteSize          = 8;
    dcb.Parity            = p;
    dcb.StopBits          = SIOtransport_data->stop;
    dcb.XonChar           = 0;
    dcb.XoffChar          = 0;
    dcb.ErrorChar         = 0;
    dcb.EofChar           = 0;
    dcb.EvtChar           = 0;

    if( !SetCommState( SIOtransport_data->hPort, &dcb ) )
        return FALSE;
    return TRUE;
}

// ------------------------------------------------------------------------
BOOL PMDSerial_SetTimeout(void* transport_data,long msec)
{
    COMMTIMEOUTS timeouts;

    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    if( SIOtransport_data->hPort == INVALID_HANDLE_VALUE ) return FALSE;

    timeouts.ReadIntervalTimeout         = MAXDWORD;
    timeouts.ReadTotalTimeoutMultiplier  = 0;
    timeouts.ReadTotalTimeoutConstant    = msec;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant   = 0;

    return SetCommTimeouts( SIOtransport_data->hPort, &timeouts );
}

// ------------------------------------------------------------------------
void PMDSerial_SetProtocol(void* transport_data,PMDuint16 mode)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    if (mode != Protocol_ModeAddressBit)
        PMDSerial_SetConfig( transport_data, SIOtransport_data->baud, NOPARITY );
    SIOtransport_data->protocol = mode;
}

// ------------------------------------------------------------------------
void PMDSerial_SetMultiDropAddress(void* transport_data,PMDuint16 address)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    SIOtransport_data->multiDropAddress = address;
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_Send(void* transport_data, PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    unsigned int c=0;
    unsigned int i;
    unsigned int nExpected = 2*rCt+2;
    char sum;
    DWORD bytes;
    PMDuint8 buffer[20];
    PMDuint8* pbuff = &buffer[0];
    PMDuint16 ProcessorError;

    if( SIOtransport_data->hPort == INVALID_HANDLE_VALUE ) return PMD_ERR_NotConnected;

    /* Clear address byte & checksum byte */
    buffer[ c++ ] = (char)(SIOtransport_data->multiDropAddress);
    buffer[ c++ ] = (char)(0);

    /* Add axis number and command code */
    buffer[ c++ ] = (char)(xDat[0]>>8);
    buffer[ c++ ] = (char)(xDat[0]&0xff);

    /* add data (handling byte swapping) */
    for( i=1; i<xCt; i++ )
    {
        buffer[ c++ ] = (char)(xDat[i] >> 8);
        buffer[ c++ ] = (char)(xDat[i] & 0xFF);
    }

    /* calculate checksum */
    for( sum=i=0; i<c; i++ ) 
        sum += buffer[i];
    buffer[1] = -sum;

    // Flush the receive buffer in case any unexpected bytes have been received
    PMDSerial_FlushRecv(transport_data);

    if( !WriteFile( SIOtransport_data->hPort, buffer, c, &bytes, NULL ) || bytes != c )
        return PMD_ERR_CommPortWrite;

    /* read return data */
    if (SIOtransport_data->protocol != PMDSerialProtocolMultiDropUsingIdleLineDetection)
    {
        if( !ReadFile( SIOtransport_data->hPort, buffer, nExpected, &bytes, NULL ) )
            return PMD_ERR_CommPortRead;

        if ( bytes == 0 )
            return PMD_ERR_CommTimeoutError;
    }
    else
    {
        // idle line returns an extra byte containing the slave address
        if( !ReadFile( SIOtransport_data->hPort, buffer, nExpected+1, &bytes, NULL ) )
            return PMD_ERR_CommPortRead;

        if ( bytes == 0 )
            return PMD_ERR_CommTimeoutError;

        if(buffer[0] != SIOtransport_data->multiDropAddress)
            return PMD_ERR_CommPortRead; // unexpected address  
    }

    // verify the checksum
    for( sum=i=0; i<bytes; i++ )
        sum += buffer[i];

    if (SIOtransport_data->protocol == PMDSerialProtocolMultiDropUsingIdleLineDetection)
    {
        // remove address byte from head of packet
        pbuff++; 
        bytes--;
    }

    // first byte is the error code 
    ProcessorError = pbuff[0];

    // if there was an error, don't attempt to receive any data
    if( ProcessorError && bytes==2 )
        rCt = 0;

    if( sum )
        return PMD_ERR_ChecksumError;

    /* byte swap return data */
    for( i=0, c=2; i<rCt; i++ )
    {
        rDat[i]  = (PMDuint16)((pbuff[c++])<<8);
        rDat[i] |= (PMDuint16)(pbuff[c++]);
    }


    if (ProcessorError && SIOtransport_data->bDiagnostics)
    {
        PMDprintf("Processor status: %s\r\n", PMDGetErrorMessage(ProcessorError));
        PMDprintf("C-Motion: %s ",PMDGetOpcodeText(xDat[0]));
        for(i=1; i<xCt; i++)
            PMDprintf(" TXdata%d %X ",i, xDat[i]);
        for(i=0; i<rCt; i++)
            PMDprintf(" RXdata%d %X ",i, rDat[i]);
        PMDprintf("\r\n");
    }
    // some errors require resyncing the serial port when in point-to-point serial mode.
    if (ProcessorError && bytes == 2)
    {
        // we might be out of sync if any of these error codes are returned,
        // especially if the command contains parameters.
        if (ProcessorError == PMD_ERR_HardFault ||
            ProcessorError == PMD_ERR_BadSerialChecksum ||
            ProcessorError == PMD_ERR_InvalidInstruction ||
            ProcessorError == PMD_ERR_InvalidAxis)
        {
            PMDSerial_Sync(transport_data);
        }
    }
    else
    {
        if ( bytes != (unsigned)(nExpected) )
            return PMD_ERR_CommTimeoutError;
    }

    return ( ProcessorError );
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_WriteByte(void* transport_data, PMDuint8 data)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;
    DWORD bytes;

    if( !WriteFile( SIOtransport_data->hPort, &data, 1, &bytes, NULL ) || bytes != 1 )
        return PMD_ERR_CommPortWrite;

    return PMD_ERR_OK;
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_ReadByte(void* transport_data, PMDuint8* data)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;
    DWORD bytes;

    if( !ReadFile( SIOtransport_data->hPort, data, 1, &bytes, NULL ) || bytes != 1 )
        return PMD_ERR_CommPortRead;

    return PMD_ERR_OK;
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_Sync(void* transport_data)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;
    const int maxSend = 15;
    DWORD bytes;
    int i;
    char tx = 0;
    char rx[2];

    if( SIOtransport_data->hPort == INVALID_HANDLE_VALUE ) return PMD_ERR_NotConnected;

    // sync is not required with multi-drop protocols because the command buffer resets
    // after the idle time has elapsed.
    if (SIOtransport_data->protocol != Protocol_PointToPoint)
        return PMD_ERR_InvalidOperation;

    // Flush the receive buffer in case any unexpected bytes have been received
    PMDSerial_FlushRecv(transport_data);

    for( i=0; i<maxSend; i++ )
    {
        /* write a zero character */
        if( !WriteFile( SIOtransport_data->hPort, &tx, 1, &bytes, NULL ) || bytes != 1 )
            return PMD_ERR_CommPortWrite;

        /* Attempt to read the 2 byte response */
        if( ReadFile( SIOtransport_data->hPort, rx, 2, &bytes, NULL ) && bytes==2 )
            break;
    }

    /* If no data was seen, return an error */
    if( i== maxSend ) 
        return PMD_ERR_CommTimeoutError;

    /* flush any other data read */
    PMDSerial_FlushRecv(transport_data);

    return PMD_ERR_OK;
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_FlushRecv(void* transport_data)
{
    PMDSerialIOData* SIOtransport_data = (PMDSerialIOData*)transport_data;

    if( SIOtransport_data->hPort == INVALID_HANDLE_VALUE ) return PMD_ERR_NotConnected;

    PurgeComm(SIOtransport_data->hPort, PURGE_RXCLEAR); // Windows OS specific flush function

    return PMD_ERR_OK;
}

// ------------------------------------------------------------------------
void PMDSerial_InitData(PMDSerialIOData* transport_data)
{
    // assign default values
    transport_data->multiDropAddress = 0;
    transport_data->protocol = Protocol_PointToPoint;
    transport_data->baud = 57600;

    // default port is COM1
    transport_data->port = 1;

    // by default always verify the checksum
    transport_data->bVerifyChecksum = 1;
    // by default disable diagnostics
    transport_data->bDiagnostics = 0;
}

// ------------------------------------------------------------------------
PMDresult PMDSerial_Init(PMDAxisHandle* handle)
{
    PMDAxisHandle* axis_handle = (PMDAxisHandle*) handle;

    // setup function pointers
    axis_handle->transport.SendCommand = PMDSerial_Send;

    axis_handle->transport.GetStatus = PMDSerial_GetStatus;
    axis_handle->transport.IsReady = PMDSerial_IsReady;
    axis_handle->transport.HasInterrupt = PMDSerial_HasInterrupt;
    axis_handle->transport.HasError = PMDSerial_HasError;
    axis_handle->transport.HardReset = PMDSerial_HardReset;

    axis_handle->transport.bHasDPRAM = FALSE;
    axis_handle->transport.ReadDPRAM = NULL;
    axis_handle->transport.WriteDPRAM = NULL;

    axis_handle->transport.Close = PMDSerial_Close;

    return PMDSerial_InitPort(axis_handle->transport_data);
}

// ------------------------------------------------------------------------
// Use this function to copy an existing handle to an open port 
// and set the multi-drop address and axis number.
void PMDCreateMultiDropHandle(PMDAxisHandle* dest_axis_handle, PMDAxisHandle* src_axis_handle, PMDAxis axis_number, PMDuint8 nodeID)
{
    PMDSerialIOData* transport_data;

    // copy the handle
    memcpy(dest_axis_handle, src_axis_handle, sizeof( PMDAxisHandle ) );
    // allocate a new transport_data structure because the multi-drop address will be different for each axis handle
    transport_data = (PMDSerialIOData*) malloc( sizeof( PMDSerialIOData ) );
    dest_axis_handle->transport_data = transport_data;
    memcpy(dest_axis_handle->transport_data, src_axis_handle->transport_data, sizeof(PMDSerialIOData));

    // set the axis number and multi-drop address 
    dest_axis_handle->axis = axis_number;
    transport_data->multiDropAddress = nodeID;
}   

/*****************************************************************************
Set port_number to COMn port number (1 = COM1, 0 = default)
*****************************************************************************/
PMDresult PMDSetupAxisInterface_Serial(PMDAxisHandle* axis_handle, PMDAxis axis_number, PMDuint8 port_number)
{
    PMDSerialIOData* transport_data;

    transport_data = (PMDSerialIOData*) malloc( sizeof( PMDSerialIOData ) );
    memset(transport_data, 0, sizeof(PMDSerialIOData));

    // set the axis we are talking to with this handle
    axis_handle->axis = axis_number;

    // set the interface type 
    axis_handle->InterfaceType = InterfaceSerial;

    // the transport data is initialized first to setup the defaults
    PMDSerial_InitData(transport_data);

    // assign port number that this axis handle will use
    // if 0 use default (COM1)
    if (port_number)
        transport_data->port = port_number;

    axis_handle->transport_data = (void*) transport_data;

    // initialize the transport (inits function pointers)
    return PMDSerial_Init(axis_handle);
}

