#include "CMoAxis.hpp"
#include "c-motion/PMDdiag.h"

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

CMoAxis::CMoAxis(Tcl_Interp* interp)
{

#if defined PMD_CAN_INTERFACE
    // open the CAN interface at 20,000 baud and NodeID=0
    PMDSetupAxisInterface_CAN(&hAxis, PMDAxis, PMDCANBaud20000, 0);
#elif defined PMD_W32SERIAL_INTERFACE
    // Open the serial interface (57600 baud and point-to-point protocol)
    // The third parameter represents the COM port number (0=default of COM1)
    PMDSetupAxisInterface_Serial(&hAxis, PMDAxis1, 1);
#elif defined PMD_SPI_INTERFACE
    // Open the SPI interface
    // The third parameter represents the device number (0=first NI device found)
    PMDSetupAxisInterface_SPI(&hAxis, PMDAxis, 0);
#endif

};

CMoAxis::~CMoAxis()
{
};

int
CMoAxis::PMDGetVersion(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetProfileMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint16 mode;
    static const char* cmodes[] =
    {
	"trapezoidial", "velocity", "s-curve", "electronic-gear", 0L
    };
    enum cmodes
    {
	trapezoidial, velocity, scurve, electronicgear
    };
    int index;

    if (TCL_OK != Tcl_GetIndexFromObj(interp, objv[1],
	(const char**)cmodes, "mode", 0, &index))
    {
	return TCL_ERROR;
    }

    switch ((enum cmodes)index)
    {
    case trapezoidial:
	mode = PMDProfileModeTrapezoidal; break;
    case velocity:
	mode = PMDProfileModeVelocity; break;
    case scurve:
	mode = PMDProfileModeSCurve; break;
    case electronicgear:
	mode = PMDProfileModeElectronicGear; break;
    default:
	return TCL_ERROR;
    }

    if (PMD_NOERROR != (result = ::PMDSetProfileMode(&hAxis, mode)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    return TCL_OK;
};

int
CMoAxis::PMDGetProfileMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint16 mode;
    Tcl_Obj* pm;

    if (PMD_NOERROR != (result = ::PMDGetProfileMode(&hAxis, &mode)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    switch (mode)
    {
	case PMDProfileModeTrapezoidal:
	    pm = Tcl_NewStringObj("trapezoidial", -1); break;
	case PMDProfileModeVelocity:
	    pm = Tcl_NewStringObj("velocity", -1); break;
	case PMDProfileModeSCurve:
	    pm = Tcl_NewStringObj("s-curve", -1); break;
	case PMDProfileModeElectronicGear:
	    pm = Tcl_NewStringObj("electronic-gear", -1); break;
	default:
	    Tcl_Panic("unknown profile mode");
    }

    Tcl_SetObjResult(interp, pm);
    return TCL_OK;
};

int
CMoAxis::PMDSetPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDint32 position;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 2, objv, "position");
	return TCL_ERROR;
    }

    if (TCL_OK != Tcl_GetLongFromObj(interp, objv[2], &position))
    {
	return TCL_ERROR;
    }

    if (PMD_NOERROR != (result = ::PMDSetPosition(&hAxis, position)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    return TCL_OK;
};

int
CMoAxis::PMDGetPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDint32 position;

    if (PMD_NOERROR != (result = ::PMDGetPosition(&hAxis, &position)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }
    
    Tcl_SetObjResult(interp, Tcl_NewIntObj(position));
    return TCL_OK;
};

int
CMoAxis::PMDSetVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDint32 velocity;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 2, objv, "velocity");
	return TCL_ERROR;
    }

    if (TCL_OK != Tcl_GetLongFromObj(interp, objv[2], &velocity))
    {
	return TCL_ERROR;
    }

    if (PMD_NOERROR != (result = ::PMDSetVelocity(&hAxis, velocity)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    return TCL_OK;
};

int
CMoAxis::PMDGetVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDint32 velocity;

    if (PMD_NOERROR != (result = ::PMDGetVelocity(&hAxis, &velocity)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj(velocity));
    return TCL_OK;
};

int
CMoAxis::PMDSetStartVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint32 velocity;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 2, objv, "velocity");
	return TCL_ERROR;
    }

    // upcasting unsigned int should fit
    if (TCL_OK != Tcl_GetLongFromObj(interp, objv[1],
	    reinterpret_cast<long *>(&velocity)))
    {
	return TCL_ERROR;
    }

    if (PMD_NOERROR != (result = ::PMDSetStartVelocity(&hAxis, velocity)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }
    return TCL_ERROR;
};

int
CMoAxis::PMDGetStartVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint32 velocity;

    if (PMD_NOERROR != (result = ::PMDGetStartVelocity(&hAxis, &velocity)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    // upcasting should fit
    Tcl_SetObjResult(interp, Tcl_NewLongObj(velocity));
    return TCL_OK;
};

int
CMoAxis::PMDSetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetJerk(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetJerk(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetGearRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetGearRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetGearMaster(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetGearMaster(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetStopMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetStopMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetCommandedPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetCommandedVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetCommandedAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetMotorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetMotorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetMotorBias(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetMotorBias(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetPositionErrorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetPositionErrorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetSettleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetSettleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetSettleWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetSettleWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetTrackingWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetTrackingWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetMotionCompleteMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetMotionCompleteMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDClearPositionError(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetPositionError(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDSetSampleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetSampleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};
