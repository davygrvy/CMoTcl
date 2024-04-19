#include "CMoAPI.hpp"

#ifdef WIN32
#   ifdef _MSC_VER
#	pragma comment (lib, "C-Motion.lib")
#   endif
#endif

// The transport in use is considered to be an external hook.
// We will use the native Win32 method for now until I write
// a Tcl one that, will of course, be universal.  Even more
// fun will be the oppertunity to write some new SPI/CAN/etc
// channel driver(s) for Tcl for use when embedded on ARM. 
//
#define PMD_W32SERIAL_INTERFACE
#include "c-motion/PMDW32Ser.h"

CMoAPI::CMoAPI (Tcl_Interp* interp)
{
    PMDuint32 Maj, Min;

    // Does compile-time C-Motion API match the loaded DLL?
    //
    PMDGetCMotionVersion(&Maj, &Min);
    if ((Maj != CMOTION_MAJOR_VERSION) || (Min != CMOTION_MINOR_VERSION))
    {
	throw "C-Motion version mismatch of DLL! Got " << Maj << "." << Min <<
	    " but needed " << CMOTION_MAJOR_VERSION << "." << CMOTION_MINOR_VERSION;
    }

#if defined PMD_CAN_INTERFACE
    // open the CAN interface at 20,000 baud and NodeID=0
    PMDSetupAxisInterface_CAN(&hAxis1, PMDAxis, PMDCANBaud20000, 0);
#elif defined PMD_W32SERIAL_INTERFACE
    // Open the serial interface (57600 baud and point-to-point protocol)
    // The third parameter represents the COM port number (0=default of COM1)
    PMDSetupAxisInterface_Serial(&hAxis, PMDAxis1, 1);
#elif defined PMD_SPI_INTERFACE
    // Open the SPI interface
    // The third parameter represents the device number (0=first NI device found)
    PMDSetupAxisInterface_SPI(&hAxis1, PMDAxis, 0);
#endif

};

CMoAPI::~CMoAPI()
{
};

int
CMoAPI::PMDGetVersion(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetProfileMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetProfileMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetStartVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetStartVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetJerk(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetJerk(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetGearRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetGearRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetGearMaster(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetGearMaster(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDSetStopMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetStopMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetCommandedPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetCommandedVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAPI::PMDGetCommandedAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

