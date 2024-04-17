#include "CMoAPI.hpp"


CMoAPI::CMoAPI(Tcl_Interp* interp)
{
    PMDuint32 maj, min;

    PMDGetCMotionVersion(&maj, &min);
};

CMoAPI::~CMoAPI()
{
};

int
CMoAPI::PMDGetVersion(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[])
{
    return TCL_ERROR;
};
