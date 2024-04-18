#include "tcl.h"
#include "c-motion/c-motion.h"

class CMoAPI
{
public:
    CMoAPI(Tcl_Interp* interp);
    ~CMoAPI();
    int PMDGetVersion(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
private:
    PMDAxisHandle hAxis;
};
