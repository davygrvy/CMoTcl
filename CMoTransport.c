// future home of the transport hook into Tcl's channel system.
// See the PMDIOTransport typedef in PMDdevice.h

#include "c-motion/PMDtypes.h"

PMDresult
TclTransport_SendCommand(void* transport_data, PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat)
{
    // notice here that reads follow writes.  The chip never talks on its own out-of-band
    return PMD_ERR_InvalidOperation;
}

PMDresult
TclTransport_Close(void* transport_data)
{
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

