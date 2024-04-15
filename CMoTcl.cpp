

#include "cpptcl/ItclAdaptor.hpp"
#include "cpptcl/TclHash.hpp"

// forward reference for now
class CMoAPI
{
public:
    int GetCMotionVersion(void) { return 0; };
};

class ItclCMoAdaptor
    : private Itcl::IAdaptor<ItclCMoAdaptor>
{
    Tcl::Hash<CMoAPI *, TCL_ONE_WORD_KEYS> CMoHash;
    Tcl_Encoding iso8859_1;
 
    virtual void DoCleanup ()
    {
	// The adapter base class is telling us we are about to go away and it is
	// safe to use the interp pointer to do any needed cleanup.
    }

public:
    ItclCMoAdaptor(Tcl_Interp *interp)
	: Itcl::IAdaptor<ItclCMoAdaptor>(interp)
    {
	// Let [Incr Tcl] know we have some methods in here.
	NewItclCmd("CMo-construct", ConstructCmd);
	NewItclCmd("CMo-destruct",  DestructCmd);
	NewItclCmd("CMo-GetCMotionVersion", GetCMotionVersionCmd);

	iso8859_1 = Tcl_GetEncoding(interp, "iso8859-1");
    }

    ~ItclCMoAdaptor()
    {
	// Use of the interp pointer is not allowed in here.
	Tcl_FreeEncoding(iso8859_1);
    }

private:

    // The constructor method.
    int ConstructCmd (int objc, struct Tcl_Obj * const objv[])
    {
	ItclObject *ItclObj;
	CMoAPI *CMoPtr;

	if (objc != 1) {
	    Tcl_WrongNumArgs(interp, 1, objv, "");
	    return TCL_ERROR;
	}

	if (GetItclObj(&ItclObj, objv[0]) != TCL_OK) return TCL_ERROR;

	// Using the Itcl object context pointer as our key, create a new
	// CMoAPI C++ object and store the pointer in the hash table.
	try {
	    CMoPtr = new CMoAPI();
	}
	catch (char *err) {
	    // Whoop!  The house is on fire, run for the hills...
	    Tcl_SetObjResult(interp, Tcl_NewStringObj(err, -1));
	    return TCL_ERROR;
	}

	// Save the instance in the hash table associated to Itcl's object
	// context pointer.
	CMoHash.Add(ItclObj, CMoPtr);
	return TCL_OK;
    }

    // The destructor method.
    int DestructCmd (int objc, struct Tcl_Obj * const objv[])
    {
	ItclObject *ItclObj;
	CMoAPI *CMoPtr;

	if (objc != 1) {
	    Tcl_WrongNumArgs(interp, 1, objv, "");
	    return TCL_ERROR;
	}

	// retrieve the Itcl object context
	if (GetItclObj(&ItclObj, objv[0]) != TCL_OK) return TCL_ERROR;

	// grab the Py::Interp instance associated to this Itcl instance
	if (CMoHash.Extract(ItclObj, &CMoPtr) == TCL_OK) {

	    // Itcl's destructor may be called even though the Itcl class
	    // constructor returned with an error!  Thus, no Py::Interp
	    // instance exists in the hash table even though an Itcl object
	    // context exists.  Only delete what we know is there.
	    delete CMoPtr;
	}
	return TCL_OK;
    }

    int GetCMotionVersionCmd  (int objc, struct Tcl_Obj * const objv[])
    {
	ItclObject *ItclObj;
	CMoAPI *CMoPtr;

	if (objc != 1) {
	    Tcl_WrongNumArgs(interp, 1, objv, "");
	    return TCL_ERROR;
	}

	if (GetItclObj(&ItclObj, objv[0]) != TCL_OK) return TCL_ERROR;

	// grab the CMoAPI instance associated to this Itcl instance
	if (CMoHash.Find(ItclObj, &CMoPtr) != TCL_OK) {
	    Tcl_SetObjResult(interp,
		    Tcl_NewStringObj("CMoAPI instance lost!", -1));
	    return TCL_ERROR;
	}

	CMoPtr->GetCMotionVersion();

	return TCL_ERROR;
    }
}

// tell the EXTERN macro we want to declare functions for export.
#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLEXPORT

EXTERN int
Cmotcl_Init (Tcl_Interp *interp)
{
#ifdef USE_TCL_STUBS
    if (Tcl_InitStubs(interp, "8.1", 0) == 0L) {
	return TCL_ERROR;
    }
#endif
#ifdef USE_ITCL_STUBS
    if (Itcl_InitStubs(interp, "3.1", 0) == 0L) {
	return TCL_ERROR;
    }
#endif
    new ItclCMoAdaptor(interp);
    Tcl_PkgProvide(interp, "cmotion", "1.0");
    return TCL_OK;
}
