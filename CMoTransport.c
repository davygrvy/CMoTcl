// future home of the transport hook into Tcl's channel system.
// See the PMDIOTransport typedef in PMDdevice.h

#include "CMoTransport.h"
#include "tcl.h"

// notice here that reads follow writes.  The chip never talks on its own out-of-band
PMDresult
TclTransport_SendCommand(void* transport_data, PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat)
{
    Tcl_Channel chan = *(Tcl_Channel*)transport_data;
    Tcl_Write(chan, (const char*)xDat, (xCt*2));   //???  TODO: lots of proper error handling. An array of words is double in bytes?
    Tcl_Read(chan, (char*)rDat, (rCt*2));
    return PMD_ERR_InvalidOperation;
}

PMDresult
TclTransport_Close(void* transport_data)
{
    int result;
    Tcl_Channel chan = *(Tcl_Channel*)transport_data;

    if (chan != NULL)
    {
	result = Tcl_Close(0L, chan);
	chan = NULL;
    }

    return PMD_ERR_InvalidOperation;
}

PMDuint16
TclTransport_GetStatus(void* transport_data)
{
    return 0;
}

PMDuint16
TclTransport_IsReady(void* transport_data)
{
    return 0;
}

PMDuint16
TclTransport_HasInterrupt(void* transport_data)
{
    return 0;
}

PMDuint16
TclTransport_HasError(void* transport_data)
{
    return 0;
}

PMDresult
TclTransport_HardReset(void* transport_data)
{
    return PMD_ERR_InvalidOperation;
}

