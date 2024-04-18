#include "tcl.h"
#include "c-motion/c-motion.h"

class CMoAPI
{
public:
    CMoAPI(Tcl_Interp* interp);
    ~CMoAPI();
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

private:
    PMDAxisHandle hAxis;
};
