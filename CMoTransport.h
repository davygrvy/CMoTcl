#include "c-motion/PMDtypes.h"

PMDresult TclTransport_SendCommand(void* transport_data, PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat);
PMDresult TclTransport_Close(void* transport_data);
PMDuint16 TclTransport_GetStatus(void* transport_data);
PMDuint16 TclTransport_IsReady(void* transport_data);
PMDuint16 TclTransport_HasInterrupt(void* transport_data);
PMDuint16 TclTransport_HasError(void* transport_data);
PMDresult TclTransport_HardReset(void* transport_data);

