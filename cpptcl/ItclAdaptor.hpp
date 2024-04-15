/*
 ------------------------------------------------------------------------------
 * ItclAdaptor.hpp --
 *
 *	Defines one templated class for doing the grunt work for making
 *	C++ extensions (includes some Itcl support).
 *
 * Copyright (c) 1999-2001 Tomahawk Software Group
 *
 * See the file "license.txt" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * RCS: @(#) $Id: ItclAdaptor.hpp,v 1.3 2002/08/15 09:04:10 davygrvy Exp $
 ------------------------------------------------------------------------------
 */
#ifndef INC_ItclAdaptor_hpp__
#define INC_ItclAdaptor_hpp__

#include "TclAdaptor.hpp"
#include <itclInt.h>

#ifdef _MSC_VER
    // Only do this when MSVC++ is compiling us.
#   ifdef USE_ITCL_STUBS
	// Mark this .obj as needing [Incr Tcl]'s Stubs library.
#	pragma comment(lib, "itclstub" \
	    STRINGIFY(JOIN(ITCL_MAJOR_VERSION,ITCL_MINOR_VERSION)) ".lib")
#	if !defined(_MT) || !defined(_DLL) || defined(_DEBUG)
	    // This fixes a bug with how the Stubs library was compiled.
	    // The requirement for msvcrt.lib from itclstubXX.lib should
	    // be removed.
#	    pragma comment(linker, "-nodefaultlib:msvcrt.lib")
#	endif
#   else
    // Mark this .obj needing the import library
#   pragma comment(lib, "itcl" \
	STRINGIFY(JOIN(ITCL_MAJOR_VERSION,ITCL_MINOR_VERSION)) ".lib")
#   endif
#endif


// short cut.
#define NewItclCmd(a,b) \
	Itcl_RegisterObjC(interp, (a), CmdDemux, CmdInfo((b), this), CmdDelete)


namespace Itcl {

template <class T>
    class IAdaptor : public Tcl::Adaptor<T>
{
protected:
    IAdaptor(Tcl_Interp *interp)
	: Tcl::Adaptor<T>(interp)
    {
    }

    int GetItclObj (ItclObject **contextObj, Tcl_Obj *cmd)
    {
	ItclClass *contextClass;
	
	// Get the object context we are in
	if (Itcl_GetContext(Tcl::Adaptor<T>::interp, &contextClass, contextObj) != TCL_OK
		|| !contextObj) {
	    char *token = Tcl_GetString(cmd);
	    Tcl_ResetResult(Tcl::Adaptor<T>::interp);
	    Tcl_AppendStringsToObj(Tcl_GetObjResult(Tcl::Adaptor<T>::interp),
		"cannot use \"", token, "\" without an object context",
		0L);
	    return TCL_ERROR;
	}
	return TCL_OK;
    }
};

}

#endif