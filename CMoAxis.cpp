#include <climits>
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
    long temp;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 2, objv, "velocity");
	return TCL_ERROR;
    }

    if (TCL_OK != Tcl_GetLongFromObj(interp, objv[2], &temp))
    {
	return TCL_ERROR;
    }

    // validate range
    if (temp < MININT32 || temp > MAXINT32)
    {
	Tcl_SetObjResult(interp, Tcl_NewStringObj("value out of range", -1));
	return TCL_ERROR;
    }
    else
    {
	velocity = static_cast<PMDint32>(temp);
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
    Tcl_WideInt temp;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 2, objv, "velocity");
	return TCL_ERROR;
    }

    if (TCL_OK != Tcl_GetWideIntFromObj(interp, objv[1], &temp))
    {
	return TCL_ERROR;
    }

    // validate range
    if (temp < 0 || temp > MAXUINT32)
    {
	Tcl_SetObjResult(interp, Tcl_NewStringObj("value out of range", -1));
	return TCL_ERROR;
    }
    else
    {
	velocity = static_cast<PMDuint32>(temp);
    }

    if (PMD_NOERROR != (result = ::PMDSetStartVelocity(&hAxis, velocity)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }
    return TCL_OK;
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
    PMDresult result;
    PMDuint32 acceleration;
    Tcl_WideInt temp;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 1, objv, "acceleration");
	return TCL_ERROR;
    }

    if (TCL_OK != Tcl_GetWideIntFromObj(interp, objv[1], &temp))
    {
	return TCL_ERROR;
    }

    // validate range
    if (temp < 0 || temp > MAXUINT32)
    {
	Tcl_SetObjResult(interp, Tcl_NewStringObj("value out of range", -1));
	return TCL_ERROR;
    }
    else
    {
	acceleration = static_cast<PMDuint32>(temp);
    }

    if (PMD_NOERROR != (result = ::PMDSetAcceleration(&hAxis, acceleration)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }
    return TCL_OK;
};

int
CMoAxis::PMDGetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint32 acceleration;

    if (PMD_NOERROR != (result = ::PMDGetAcceleration(&hAxis, &acceleration)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    // upcasting should fit
    Tcl_SetObjResult(interp, Tcl_NewWideIntObj(acceleration));
    return TCL_OK;
};

int
CMoAxis::PMDSetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint32 deacceleration;
    Tcl_WideInt temp;

    if (objc != 2)
    {
	Tcl_WrongNumArgs(interp, 1, objv, "deacceleration");
	return TCL_ERROR;
    }

    if (TCL_OK != Tcl_GetWideIntFromObj(interp, objv[1], &temp))
    {
	return TCL_ERROR;
    }

    // validate range
    if (temp < 0 || temp > MAXUINT32)
    {
	Tcl_SetObjResult(interp, Tcl_NewStringObj("value out of range", -1));
	return TCL_ERROR;
    }
    else
    {
	deacceleration = static_cast<PMDuint32>(temp);
    }

    if (PMD_NOERROR != (result = ::PMDSetDeceleration(&hAxis, deacceleration)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }
    return TCL_OK;
};

int
CMoAxis::PMDGetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint32 deacceleration;

    if (PMD_NOERROR != (result = ::PMDGetDeceleration(&hAxis, &deacceleration)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    // upcasting should fit
    Tcl_SetObjResult(interp, Tcl_NewWideIntObj(deacceleration));
    return TCL_OK;
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
    PMDresult result;
    PMDint32 position;

    if (PMD_NOERROR != (result = ::PMDGetCommandedPosition(&hAxis, &position)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj(position));
    return TCL_OK;
};

int
CMoAxis::PMDGetCommandedVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDint32 velocity;

    if (PMD_NOERROR != (result = ::PMDGetCommandedVelocity(&hAxis, &velocity)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj(velocity));
    return TCL_OK;
};

int
CMoAxis::PMDGetCommandedAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDint32 acceleration;

    if (PMD_NOERROR != (result = ::PMDGetCommandedAcceleration(&hAxis, &acceleration)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    Tcl_SetObjResult(interp, Tcl_NewIntObj(acceleration));
    return TCL_OK;
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


// motor 
int
CMoAxis::PMDSetMotorType(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    PMDresult result;
    PMDuint16 type;
    static const char* cmodes[] =
    {
	"brushless-DC-3ph", "brushless-DC-2ph", "microstep-3ph", "microstep-2ph", "stepping",
	"brush-DC", 0L
    };
    enum cmodes
    {
	dc3ph, dc2ph, ustep3, ustep2, step, dc
    };
    int index;

    if (TCL_OK != Tcl_GetIndexFromObj(interp, objv[1],
	(const char**)cmodes, "mode", 0, &index))
    {
	return TCL_ERROR;
    }

    switch ((enum cmodes)index)
    {
    case dc3ph:
	type = PMDMotorTypeBrushlessDC3Phase; break;
    case dc2ph:
	type = PMDMotorTypeBrushlessDC2Phase; break;
    case ustep3:
	type = PMDMotorTypeMicrostep3Phase; break;
    case ustep2:
	type = PMDMotorTypeMicrostep2Phase; break;
    case step:
	type = PMDMotorTypeStepping; break;
    case dc:
	type = PMDMotorTypeDCBrush; break;
    default:
	return TCL_ERROR;
    }

    if (PMD_NOERROR != (result = ::PMDSetMotorType(&hAxis, type)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    return TCL_OK;
};

int
CMoAxis::PMDGetMotorType(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    //PMDMotorType type;
    PMDuint16 type;
    PMDresult result;
    Tcl_Obj* mt;

    if (PMD_NOERROR != (result = ::PMDGetMotorType(&hAxis, &type)))
    {
	Tcl_SetObjResult(interp,
	    Tcl_NewStringObj(::PMDGetErrorMessage(result), -1));
	return TCL_ERROR;
    }

    switch (type)
    {
    case PMDMotorTypeBrushlessDC3Phase:
	mt = Tcl_NewStringObj("brushless-DC-3ph", -1); break;
    case PMDMotorTypeBrushlessDC2Phase:
	mt = Tcl_NewStringObj("brushless-DC-2ph", -1); break;
    case PMDMotorTypeMicrostep3Phase:
	mt = Tcl_NewStringObj("microstep-3ph", -1); break;
    case PMDMotorTypeMicrostep2Phase:
	mt = Tcl_NewStringObj("microstep-2ph", -1); break;
    case PMDMotorTypeStepping:
	mt = Tcl_NewStringObj("stepping", -1); break;
    case PMDMotorTypeDCBrush:
	mt = Tcl_NewStringObj("brush-DC", -1); break;
    default:
	Tcl_Panic("unknown motor type");
    }

    Tcl_SetObjResult(interp, mt);
    return TCL_OK;
};

int
CMoAxis::PMDSetMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

int
CMoAxis::PMDGetActiveMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};

