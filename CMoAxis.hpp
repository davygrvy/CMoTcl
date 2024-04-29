#include "tcl.h"
#include "c-motion/c-motion.h"

class CMoAxis
{
public:
    CMoAxis(Tcl_Interp* interp);
    ~CMoAxis();
    int PMDGetVersion(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    int PMDSetProfileMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetProfileMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetStartVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetStartVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDeceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetJerk(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetJerk(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetGearRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetGearRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetGearMaster(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetGearMaster(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetStopMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetStopMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCommandedPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCommandedVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCommandedAcceleration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    int PMDSetMotorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetMotorBias(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotorBias(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPositionErrorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPositionErrorLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetSettleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSettleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetSettleWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSettleWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetTrackingWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTrackingWindow(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetMotionCompleteMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotionCompleteMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDClearPositionError(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPositionError(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetSampleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSampleTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Motor
    int PMDSetMotorType(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotorType(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActiveMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]); // same as PMDGetCurrentMotorCommand

private:
    PMDAxisHandle hAxis;
};
