/*
 * This is CMoTcl, an extension for Tcl that provides a connection to 
 * Performance Motion Devices' C-Motion API to control their range of motor 
 * controllers.
 * 
 * See: https://www.pmdcorp.com/products/development-software
 *
 * Author: David Gravereaux <davygrvy@pobox.com> April 2024
 *
 * Not only is this a Tcl extension, but it's also an [Incr Tcl] extension,
 * too.  The model looks like this..  Each Tcl interpreter that loads this
 * extension is told that Itcl can find some methods in here.  Many Itcl
 * instances of CMoAxis are possible.  So are multiple Tcl interps that
 * have multiple CMoAxis instances.
 *
 * The ItclCMoAdaptor class isn't actually Itcl's pmd::cmotion class.
 * ItclPyAdapter is the template (or go between) to Itcl's pmd::cmotion
 * instances and are directly associated to each CMoAPI C++ instance.
 *
 * Most of the dirty work is done in Itcl::IAdapter and Tcl::Adapter for the
 * duties of being an Itcl/Tcl extension.  This allows ItclCMoAdaptor to be more
 * readable and only contain the 'meat' of what it's job is.
 *
 * Consider this work under BSD license.  If you make improvements to this,
 * I would apreciate it if you could send me the patches.  This is not a
 * requirement for use of this software.
 */


#include "cpptcl/ItclAdaptor.hpp"
#include "cpptcl/TclHash.hpp"
#include "CMoAxis.hpp"
#include <string>
#include <sstream>

class ItclCMoAdaptor
    : private Itcl::IAdaptor<ItclCMoAdaptor>
{
    Tcl::Hash<CMoAxis *, TCL_ONE_WORD_KEYS> CMoHash;
    Tcl_Encoding iso8859_1;
 
    virtual void DoCleanup ()
    {
	// The Tcl::Adaptor base class is telling us we are about to go away and it is
	// safe to use the interp pointer to do any needed cleanup.
    }

public:
    ItclCMoAdaptor(Tcl_Interp *interp)
	: Itcl::IAdaptor<ItclCMoAdaptor>(interp)
    {

	// Let [Incr Tcl] know we have some methods in here.
	NewItclCmd("CMo-construct", &ItclCMoAdaptor::ConstructCmd);
	NewItclCmd("CMo-destruct",  &ItclCMoAdaptor::DestructCmd);

#define NewItclAPICmd(a) \
     NewItclCmd(STRINGIFY(JOIN(CMo-,a)), &ItclCMoAdaptor::PMD##a##Cmd)

	// **** Begin API connections ****

	// Profile Generation
	NewItclAPICmd(SetProfileMode);
	NewItclAPICmd(GetProfileMode);
	NewItclAPICmd(SetPosition);
	NewItclAPICmd(GetPosition);
	NewItclAPICmd(SetVelocity);
	NewItclAPICmd(GetVelocity);
	NewItclAPICmd(SetStartVelocity);
	NewItclAPICmd(GetStartVelocity);
	NewItclAPICmd(SetAcceleration);
	NewItclAPICmd(GetAcceleration);
	NewItclAPICmd(SetDeceleration);
	NewItclAPICmd(GetDeceleration);
	NewItclAPICmd(SetJerk);
	NewItclAPICmd(GetJerk);
	NewItclAPICmd(SetGearRatio);
	NewItclAPICmd(GetGearRatio);
	NewItclAPICmd(SetGearMaster);
	NewItclAPICmd(GetGearMaster);
	NewItclAPICmd(SetStopMode);
	NewItclAPICmd(GetStopMode);
	NewItclAPICmd(GetCommandedPosition);
	NewItclAPICmd(GetCommandedVelocity);
	NewItclAPICmd(GetCommandedAcceleration);

	// Position Loop
	NewItclAPICmd(SetMotorLimit);
	NewItclAPICmd(GetMotorLimit);
	NewItclAPICmd(SetMotorBias);
	NewItclAPICmd(GetMotorBias);
	NewItclAPICmd(SetPositionErrorLimit);
	NewItclAPICmd(GetPositionErrorLimit);
	NewItclAPICmd(SetSettleTime);
	NewItclAPICmd(GetSettleTime);
	NewItclAPICmd(SetSettleWindow);
	NewItclAPICmd(GetSettleWindow);
	NewItclAPICmd(SetTrackingWindow);
	NewItclAPICmd(GetTrackingWindow);
	NewItclAPICmd(SetMotionCompleteMode);
	NewItclAPICmd(GetMotionCompleteMode);
	NewItclAPICmd(ClearPositionError);
	NewItclAPICmd(GetPositionError);
	NewItclAPICmd(SetSampleTime);
	NewItclAPICmd(GetSampleTime);
	
	// Parameter Update & Breakpoints
	NewItclAPICmd(SetBreakpoint);
	NewItclAPICmd(GetBreakpoint);
	NewItclAPICmd(SetBreakpointValue);
	NewItclAPICmd(GetBreakpointValue);
	NewItclAPICmd(SetBreakpointUpdateMask);
	NewItclAPICmd(GetBreakpointUpdateMask);
	NewItclAPICmd(Update);
	NewItclAPICmd(MultiUpdate);

	// Interrupt Processing
	NewItclAPICmd(SetInterruptMask);
	NewItclAPICmd(GetInterruptMask);
	NewItclAPICmd(ClearInterrupt);
	NewItclAPICmd(GetInterruptAxis);

	// Status Register Control
	NewItclAPICmd(ResetEventStatus);
	NewItclAPICmd(GetEventStatus);
	NewItclAPICmd(GetActivityStatus);
	NewItclAPICmd(SetSignalSense);
	NewItclAPICmd(GetSignalSense);
	NewItclAPICmd(GetSignalStatus);

	// Encoder
	NewItclAPICmd(AdjustActualPosition);
	NewItclAPICmd(SetActualPosition);
	NewItclAPICmd(GetActualPosition);
	NewItclAPICmd(SetActualPositionUnits);
	NewItclAPICmd(GetActualPositionUnits);
	NewItclAPICmd(SetCaptureSource);
	NewItclAPICmd(GetCaptureSource);
	NewItclAPICmd(SetEncoderSource);
	NewItclAPICmd(GetEncoderSource);
	NewItclAPICmd(SetEncoderModulus);
	NewItclAPICmd(GetEncoderModulus);
	NewItclAPICmd(SetEncoderToStepRatio);
	NewItclAPICmd(GetEncoderToStepRatio);
	NewItclAPICmd(GetActualVelocity);
	NewItclAPICmd(GetCaptureValue);
	NewItclAPICmd(SetAuxiliaryEncoderSource);
	NewItclAPICmd(GetAuxiliaryEncoderSource);

	// Motor
	NewItclAPICmd(SetMotorType);
	NewItclAPICmd(GetMotorType);
	NewItclAPICmd(SetMotorCommand);
	NewItclAPICmd(GetMotorCommand);
	NewItclAPICmd(GetActiveMotorCommand); // same as PMDGetCurrentMotorCommand

	// Commutation
	NewItclAPICmd(SetOutputMode);
	NewItclAPICmd(GetOutputMode);
	NewItclAPICmd(SetPWMFrequency);
	NewItclAPICmd(GetPWMFrequency);
	NewItclAPICmd(SetCommutationMode);
	NewItclAPICmd(GetCommutationMode);
	NewItclAPICmd(SetPhaseInitializeMode);
	NewItclAPICmd(GetPhaseInitializeMode);
	NewItclAPICmd(SetPhasePrescale);
	NewItclAPICmd(GetPhasePrescale);
	NewItclAPICmd(SetPhaseCounts);
	NewItclAPICmd(GetPhaseCounts);
	NewItclAPICmd(SetPhaseInitializeTime);
	NewItclAPICmd(GetPhaseInitializeTime);
	NewItclAPICmd(SetPhaseOffset);
	NewItclAPICmd(GetPhaseOffset);
	NewItclAPICmd(SetPhaseAngle);
	NewItclAPICmd(GetPhaseAngle);
	NewItclAPICmd(SetPhaseCorrectionMode);
	NewItclAPICmd(GetPhaseCorrectionMode);
	NewItclAPICmd(InitializePhase);
	NewItclAPICmd(GetPhaseCommand);

	// External Memory
	NewItclAPICmd(SetBufferStart);
	NewItclAPICmd(GetBufferStart);
	NewItclAPICmd(SetBufferLength);
	NewItclAPICmd(GetBufferLength);
	NewItclAPICmd(WriteBuffer);
	NewItclAPICmd(ReadBuffer);
	NewItclAPICmd(SetBufferWriteIndex);
	NewItclAPICmd(GetBufferWriteIndex);
	NewItclAPICmd(SetBufferReadIndex);
	NewItclAPICmd(GetBufferReadIndex);

	// Trace Operations
	NewItclAPICmd(SetTraceMode);
	NewItclAPICmd(GetTraceMode);
	NewItclAPICmd(SetTracePeriod);
	NewItclAPICmd(GetTracePeriod);
	NewItclAPICmd(SetTraceVariable);
	NewItclAPICmd(GetTraceVariable);
	NewItclAPICmd(SetTraceStart);
	NewItclAPICmd(GetTraceStart);
	NewItclAPICmd(SetTraceStop);
	NewItclAPICmd(GetTraceStop);
	NewItclAPICmd(GetTraceStatus);
	NewItclAPICmd(GetTraceCount);
	NewItclAPICmd(GetTraceValue);

	// Miscellaneous
	NewItclAPICmd(WriteIO);
	NewItclAPICmd(ReadIO);
	NewItclAPICmd(ReadAnalog);
	NewItclAPICmd(Reset);
	NewItclAPICmd(NoOperation);
	NewItclAPICmd(GetVersion);
	NewItclAPICmd(GetVersion32);
	NewItclAPICmd(GetInstructionError); //was GetHostIOError

	NewItclAPICmd(SetSerialPortMode);
	NewItclAPICmd(GetSerialPortMode);
	NewItclAPICmd(SetCANMode);
	NewItclAPICmd(GetCANMode);
	
	NewItclAPICmd(SetSPIMode);
	NewItclAPICmd(GetSPIMode);
	NewItclAPICmd(GetTime);
	NewItclAPICmd(GetChecksum);
	NewItclAPICmd(SetStepRange);
	NewItclAPICmd(GetStepRange);
	NewItclAPICmd(SetSynchronizationMode);
	NewItclAPICmd(GetSynchronizationMode);

	// ION and Atlas specific functions
	NewItclAPICmd(GetDriveStatus);
	NewItclAPICmd(SetPositionLoop);
	NewItclAPICmd(GetPositionLoop);
	NewItclAPICmd(GetPositionLoopValue);
	NewItclAPICmd(SetOperatingMode);
	NewItclAPICmd(GetOperatingMode);
	NewItclAPICmd(GetActiveOperatingMode);
	NewItclAPICmd(RestoreOperatingMode);
	NewItclAPICmd(SetCurrentFoldback);
	NewItclAPICmd(GetCurrentFoldback);
	NewItclAPICmd(SetHoldingCurrent);
	NewItclAPICmd(GetHoldingCurrent);
	NewItclAPICmd(SetCurrentControlMode);
	NewItclAPICmd(GetCurrentControlMode);
	NewItclAPICmd(SetAxisOutMask);
	NewItclAPICmd(GetAxisOutMask);
	NewItclAPICmd(SetEventAction);
	NewItclAPICmd(GetEventAction);
	NewItclAPICmd(SetBusVoltageLimits);
	NewItclAPICmd(GetBusVoltageLimits);
	NewItclAPICmd(GetBusVoltage);
	NewItclAPICmd(SetOvertemperatureLimit);
	NewItclAPICmd(GetOvertemperatureLimit);
	NewItclAPICmd(GetTemperature);
	NewItclAPICmd(ClearDriveFaultStatus);
	NewItclAPICmd(GetDriveFaultStatus);
	NewItclAPICmd(SetUpdateMask);
	NewItclAPICmd(GetUpdateMask);
	NewItclAPICmd(SetCurrentLoop);
	NewItclAPICmd(GetCurrentLoop);
	NewItclAPICmd(GetCurrentLoopValue);
	NewItclAPICmd(SetDefault);
	NewItclAPICmd(GetDefault);
	NewItclAPICmd(SetFOC);
	NewItclAPICmd(GetFOC);
	NewItclAPICmd(GetFOCValue);
	NewItclAPICmd(SetFaultOutMask);
	NewItclAPICmd(GetFaultOutMask);

	// Atlas, MC5x113 and MC7x113 specific functions
	NewItclAPICmd(DriveNVRAM);
	NewItclAPICmd(ReadBuffer16);
	NewItclAPICmd(SetCurrent);
	NewItclAPICmd(GetCurrent);
	NewItclAPICmd(SetDriveFaultParameter);
	NewItclAPICmd(GetDriveFaultParameter);
	NewItclAPICmd(SetDrivePWM);
	NewItclAPICmd(GetDrivePWM);
	NewItclAPICmd(SetFeedbackParameter);
	NewItclAPICmd(GetFeedbackParameter);

	// MC5x113 specific functions
	NewItclAPICmd(SetAnalogCalibration);
	NewItclAPICmd(GetAnalogCalibration);
	NewItclAPICmd(GetDriveValue);
	NewItclAPICmd(CalibrateAnalog);

	// MC7x113 specific functions
	NewItclAPICmd(SetLoop);
	NewItclAPICmd(GetLoop);
	NewItclAPICmd(GetLoopValue);
	NewItclAPICmd(SetProfileParameter);
	NewItclAPICmd(GetProfileParameter);
	NewItclAPICmd(GetProductInfo);
	NewItclAPICmd(ExecutionControl);
	NewItclAPICmd(SetCommutationParameter);
	NewItclAPICmd(GetCommutationParameter);
	NewItclAPICmd(SetPhaseParameter);
	NewItclAPICmd(GetPhaseParameter);
	NewItclAPICmd(SetDriveCommandMode);
	NewItclAPICmd(GetDriveCommandMode);
	NewItclAPICmd(GetRuntimeError);
	NewItclAPICmd(SetCurrentLimit);
	NewItclAPICmd(GetCurrentLimit);

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
	CMoAxis *CMoPtr;

	if (objc != 1) {
	    Tcl_WrongNumArgs(interp, 1, objv, "");
	    return TCL_ERROR;
	}

	if (GetItclObj(&ItclObj, objv[0]) != TCL_OK) return TCL_ERROR;

	// Using the Itcl object context pointer as our key, create a new
	// CMoAPI C++ object and store the pointer in the hash table.
	try {
	    CMoPtr = new CMoAxis(interp);
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
	CMoAxis *CMoPtr;

	if (objc != 1) {
	    Tcl_WrongNumArgs(interp, 1, objv, "");
	    return TCL_ERROR;
	}

	// retrieve the Itcl object context
	if (GetItclObj(&ItclObj, objv[0]) != TCL_OK) return TCL_ERROR;

	// grab the CMoAPI instance associated to this Itcl instance
	if (CMoHash.Extract(ItclObj, &CMoPtr) == TCL_OK) {

	    // Itcl's destructor may be called even though the Itcl class
	    // constructor returned with an error!  Thus, no CMoAPI
	    // instance exists in the hash table even though an Itcl object
	    // context exists.  Only delete what we know is there.
	    delete CMoPtr;
	}
	return TCL_OK;
    }

    // Boiler-plate to connect to the CMoAxis class.
#define NewAPICmd(a) \
	int a##Cmd (int objc, struct Tcl_Obj * const objv[]) \
    { \
	ItclObject* ItclObj; \
	CMoAxis* CMoPtr; \
	if (GetItclObj(&ItclObj, objv[0]) != TCL_OK) return TCL_ERROR; \
	if (CMoHash.Find(ItclObj, &CMoPtr) != TCL_OK) { \
	    Tcl_SetObjResult(interp, Tcl_NewStringObj("CMoAPI instance lost!", -1)); \
	    return TCL_ERROR; \
	} \
	return CMoPtr->a(interp,objc,objv); \
    }

    // Profile Generation
    NewAPICmd(PMDSetProfileMode);
    NewAPICmd(PMDGetProfileMode);
    NewAPICmd(PMDSetPosition);
    NewAPICmd(PMDGetPosition);
    NewAPICmd(PMDSetVelocity);
    NewAPICmd(PMDGetVelocity);
    NewAPICmd(PMDSetStartVelocity);
    NewAPICmd(PMDGetStartVelocity);
    NewAPICmd(PMDSetAcceleration);
    NewAPICmd(PMDGetAcceleration);
    NewAPICmd(PMDSetDeceleration);
    NewAPICmd(PMDGetDeceleration);
    NewAPICmd(PMDSetJerk);
    NewAPICmd(PMDGetJerk);
    NewAPICmd(PMDSetGearRatio);
    NewAPICmd(PMDGetGearRatio);
    NewAPICmd(PMDSetGearMaster);
    NewAPICmd(PMDGetGearMaster);
    NewAPICmd(PMDSetStopMode);
    NewAPICmd(PMDGetStopMode);
    NewAPICmd(PMDGetCommandedPosition);
    NewAPICmd(PMDGetCommandedVelocity);
    NewAPICmd(PMDGetCommandedAcceleration);

    // Position Loop
    NewAPICmd(PMDSetMotorLimit);
    NewAPICmd(PMDGetMotorLimit);
    NewAPICmd(PMDSetMotorBias);
    NewAPICmd(PMDGetMotorBias);
    NewAPICmd(PMDSetPositionErrorLimit);
    NewAPICmd(PMDGetPositionErrorLimit);
    NewAPICmd(PMDSetSettleTime);
    NewAPICmd(PMDGetSettleTime);
    NewAPICmd(PMDSetSettleWindow);
    NewAPICmd(PMDGetSettleWindow);
    NewAPICmd(PMDSetTrackingWindow);
    NewAPICmd(PMDGetTrackingWindow);
    NewAPICmd(PMDSetMotionCompleteMode);
    NewAPICmd(PMDGetMotionCompleteMode);
    NewAPICmd(PMDClearPositionError);
    NewAPICmd(PMDGetPositionError);
    NewAPICmd(PMDSetSampleTime);
    NewAPICmd(PMDGetSampleTime);

    // Parameter Update & Breakpoints
    NewAPICmd(PMDSetBreakpoint);
    NewAPICmd(PMDGetBreakpoint);
    NewAPICmd(PMDSetBreakpointValue);
    NewAPICmd(PMDGetBreakpointValue);
    NewAPICmd(PMDSetBreakpointUpdateMask);
    NewAPICmd(PMDGetBreakpointUpdateMask);
    NewAPICmd(PMDUpdate);
    NewAPICmd(PMDMultiUpdate);

    // Interrupt Processing
    NewAPICmd(PMDSetInterruptMask);
    NewAPICmd(PMDGetInterruptMask);
    NewAPICmd(PMDClearInterrupt);
    NewAPICmd(PMDGetInterruptAxis);

    // Status Register Control
    NewAPICmd(PMDResetEventStatus);
    NewAPICmd(PMDGetEventStatus);
    NewAPICmd(PMDGetActivityStatus);
    NewAPICmd(PMDSetSignalSense);
    NewAPICmd(PMDGetSignalSense);
    NewAPICmd(PMDGetSignalStatus);

    // Encoder
    NewAPICmd(PMDAdjustActualPosition);
    NewAPICmd(PMDSetActualPosition);
    NewAPICmd(PMDGetActualPosition);
    NewAPICmd(PMDSetActualPositionUnits);
    NewAPICmd(PMDGetActualPositionUnits);
    NewAPICmd(PMDSetCaptureSource);
    NewAPICmd(PMDGetCaptureSource);
    NewAPICmd(PMDSetEncoderSource);
    NewAPICmd(PMDGetEncoderSource);
    NewAPICmd(PMDSetEncoderModulus);
    NewAPICmd(PMDGetEncoderModulus);
    NewAPICmd(PMDSetEncoderToStepRatio);
    NewAPICmd(PMDGetEncoderToStepRatio);
    NewAPICmd(PMDGetActualVelocity);
    NewAPICmd(PMDGetCaptureValue);
    NewAPICmd(PMDSetAuxiliaryEncoderSource);
    NewAPICmd(PMDGetAuxiliaryEncoderSource);
    
    // Motor
    NewAPICmd(PMDSetMotorType);
    NewAPICmd(PMDGetMotorType);
    NewAPICmd(PMDSetMotorCommand);
    NewAPICmd(PMDGetMotorCommand);
    NewAPICmd(PMDGetActiveMotorCommand); // same as PMDGetCurrentMotorCommand

    // Commutation
    NewAPICmd(PMDSetOutputMode);
    NewAPICmd(PMDGetOutputMode);
    NewAPICmd(PMDSetPWMFrequency);
    NewAPICmd(PMDGetPWMFrequency);
    NewAPICmd(PMDSetCommutationMode);
    NewAPICmd(PMDGetCommutationMode);
    NewAPICmd(PMDSetPhaseInitializeMode);
    NewAPICmd(PMDGetPhaseInitializeMode);
    NewAPICmd(PMDSetPhasePrescale);
    NewAPICmd(PMDGetPhasePrescale);
    NewAPICmd(PMDSetPhaseCounts);
    NewAPICmd(PMDGetPhaseCounts);
    NewAPICmd(PMDSetPhaseInitializeTime);
    NewAPICmd(PMDGetPhaseInitializeTime);
    NewAPICmd(PMDSetPhaseOffset);
    NewAPICmd(PMDGetPhaseOffset);
    NewAPICmd(PMDSetPhaseAngle);
    NewAPICmd(PMDGetPhaseAngle);
    NewAPICmd(PMDSetPhaseCorrectionMode);
    NewAPICmd(PMDGetPhaseCorrectionMode);
    NewAPICmd(PMDInitializePhase);
    NewAPICmd(PMDGetPhaseCommand);

    // External Memory
    NewAPICmd(PMDSetBufferStart);
    NewAPICmd(PMDGetBufferStart);
    NewAPICmd(PMDSetBufferLength);
    NewAPICmd(PMDGetBufferLength);
    NewAPICmd(PMDWriteBuffer);
    NewAPICmd(PMDReadBuffer);
    NewAPICmd(PMDSetBufferWriteIndex);
    NewAPICmd(PMDGetBufferWriteIndex);
    NewAPICmd(PMDSetBufferReadIndex);
    NewAPICmd(PMDGetBufferReadIndex);

    // Trace Operations
    NewAPICmd(PMDSetTraceMode);
    NewAPICmd(PMDGetTraceMode);
    NewAPICmd(PMDSetTracePeriod);
    NewAPICmd(PMDGetTracePeriod);
    NewAPICmd(PMDSetTraceVariable);
    NewAPICmd(PMDGetTraceVariable);
    NewAPICmd(PMDSetTraceStart);
    NewAPICmd(PMDGetTraceStart);
    NewAPICmd(PMDSetTraceStop);
    NewAPICmd(PMDGetTraceStop);
    NewAPICmd(PMDGetTraceStatus);
    NewAPICmd(PMDGetTraceCount);
    NewAPICmd(PMDGetTraceValue);

    // Miscellaneous
    NewAPICmd(PMDWriteIO);
    NewAPICmd(PMDReadIO);
    NewAPICmd(PMDReadAnalog);
    NewAPICmd(PMDReset);
    NewAPICmd(PMDNoOperation);
    NewAPICmd(PMDGetVersion);
    NewAPICmd(PMDGetVersion32);
    NewAPICmd(PMDGetInstructionError); //was GetHostIOError

    NewAPICmd(PMDSetSerialPortMode);
    NewAPICmd(PMDGetSerialPortMode);
    NewAPICmd(PMDSetCANMode);
    NewAPICmd(PMDGetCANMode);

    NewAPICmd(PMDSetSPIMode);
    NewAPICmd(PMDGetSPIMode);
    NewAPICmd(PMDGetTime);
    NewAPICmd(PMDGetChecksum);
    NewAPICmd(PMDSetStepRange);
    NewAPICmd(PMDGetStepRange);
    NewAPICmd(PMDSetSynchronizationMode);
    NewAPICmd(PMDGetSynchronizationMode);

    // ION and Atlas specific functions
    NewAPICmd(PMDGetDriveStatus);
    NewAPICmd(PMDSetPositionLoop);
    NewAPICmd(PMDGetPositionLoop);
    NewAPICmd(PMDGetPositionLoopValue);
    NewAPICmd(PMDSetOperatingMode);
    NewAPICmd(PMDGetOperatingMode);
    NewAPICmd(PMDGetActiveOperatingMode);
    NewAPICmd(PMDRestoreOperatingMode);
    NewAPICmd(PMDSetCurrentFoldback);
    NewAPICmd(PMDGetCurrentFoldback);
    NewAPICmd(PMDSetHoldingCurrent);
    NewAPICmd(PMDGetHoldingCurrent);
    NewAPICmd(PMDSetCurrentControlMode);
    NewAPICmd(PMDGetCurrentControlMode);
    NewAPICmd(PMDSetAxisOutMask);
    NewAPICmd(PMDGetAxisOutMask);
    NewAPICmd(PMDSetEventAction);
    NewAPICmd(PMDGetEventAction);
    NewAPICmd(PMDSetBusVoltageLimits);
    NewAPICmd(PMDGetBusVoltageLimits);
    NewAPICmd(PMDGetBusVoltage);
    NewAPICmd(PMDSetOvertemperatureLimit);
    NewAPICmd(PMDGetOvertemperatureLimit);
    NewAPICmd(PMDGetTemperature);
    NewAPICmd(PMDClearDriveFaultStatus);
    NewAPICmd(PMDGetDriveFaultStatus);
    NewAPICmd(PMDSetUpdateMask);
    NewAPICmd(PMDGetUpdateMask);
    NewAPICmd(PMDSetCurrentLoop);
    NewAPICmd(PMDGetCurrentLoop);
    NewAPICmd(PMDGetCurrentLoopValue);
    NewAPICmd(PMDSetDefault);
    NewAPICmd(PMDGetDefault);
    NewAPICmd(PMDSetFOC);
    NewAPICmd(PMDGetFOC);
    NewAPICmd(PMDGetFOCValue);
    NewAPICmd(PMDSetFaultOutMask);
    NewAPICmd(PMDGetFaultOutMask);

    // Atlas, MC5x113 and MC7x113 specific functions
    NewAPICmd(PMDDriveNVRAM);
    NewAPICmd(PMDReadBuffer16);
    NewAPICmd(PMDSetCurrent);
    NewAPICmd(PMDGetCurrent);
    NewAPICmd(PMDSetDriveFaultParameter);
    NewAPICmd(PMDGetDriveFaultParameter);
    NewAPICmd(PMDSetDrivePWM);
    NewAPICmd(PMDGetDrivePWM);
    NewAPICmd(PMDSetFeedbackParameter);
    NewAPICmd(PMDGetFeedbackParameter);

    // MC5x113 specific functions
    NewAPICmd(PMDSetAnalogCalibration);
    NewAPICmd(PMDGetAnalogCalibration);
    NewAPICmd(PMDGetDriveValue);
    NewAPICmd(PMDCalibrateAnalog);

    // MC7x113 specific functions
    NewAPICmd(PMDSetLoop);
    NewAPICmd(PMDGetLoop);
    NewAPICmd(PMDGetLoopValue);
    NewAPICmd(PMDSetProfileParameter);
    NewAPICmd(PMDGetProfileParameter);
    NewAPICmd(PMDGetProductInfo);
    NewAPICmd(PMDExecutionControl);
    NewAPICmd(PMDSetCommutationParameter);
    NewAPICmd(PMDGetCommutationParameter);
    NewAPICmd(PMDSetPhaseParameter);
    NewAPICmd(PMDGetPhaseParameter);
    NewAPICmd(PMDSetDriveCommandMode);
    NewAPICmd(PMDGetDriveCommandMode);
    NewAPICmd(PMDGetRuntimeError);
    NewAPICmd(PMDSetCurrentLimit);
    NewAPICmd(PMDGetCurrentLimit);


/*

The following is a listing of exports *NOT* listed in c-motion.h
and are possibly for internal use only.

 Dump of file C-Motion.dll

File Type: DLL

  Section contains the following exports for C-Motion.dll

    00000000 characteristics
    5C3CF476 time date stamp Mon Jan 14 12:43:34 2019
        0.00 version
           1 ordinal base
         286 number of functions
         286 number of names

    ordinal hint RVA      name

          1    0 00002B30 DllMain
          3    2 00002F70 PMDAtlasAxisOpen
          4    3 00002AE0 PMDAxisAlloc
          5    4 00002FA0 PMDAxisClose
          6    5 00002B10 PMDAxisFree
          7    6 00004610 PMDAxisOpen
         12    B 00002A80 PMDDeviceAlloc
         13    C 00003010 PMDDeviceClose
         14    D 00002B10 PMDDeviceFree
         15    E 00008170 PMDDeviceGetDefault
         16    F 00003060 PMDDeviceGetEvent
         17   10 00008290 PMDDeviceGetResetCause
         18   11 00007F10 PMDDeviceGetVersion
         19   12 00007F80 PMDDeviceNoOperation
         20   13 00007FA0 PMDDeviceReset
         21   14 00008250 PMDDeviceSetConsole
         22   15 00008210 PMDDeviceSetDefault
         23   16 00008050 PMDDeviceStoreUserCode
         46   2D 000022C0 PMDGetCMotionVersion
         72   47 000032A0 PMDGetErrorMessage
        138   89 00008150 PMDGetUserCodeFileDate
        139   8A 00008130 PMDGetUserCodeFileName
        140   8B 00008110 PMDGetUserCodeFileVersion
        145   90 000040E0 PMDMBClearResetCause
        146   91 00004000 PMDMBGetAmplifierEnable
        147   92 00004060 PMDMBGetDACOutputEnable
        148   93 000040B0 PMDMBGetResetCause
        149   94 00004170 PMDMBGetSSIAbsolutePosition
        150   95 00004110 PMDMBGetSSIRegister
        151   96 00004210 PMDMBGetSSIVersion
        152   97 00004090 PMDMBReadCardID
        153   98 00003F70 PMDMBReadDigitalInput
        154   99 00003FA0 PMDMBReadDigitalOutput
        155   9A 00004220 PMDMBResetSSI
        156   9B 000041E0 PMDMBSetActualPositionToSSIPosition
        157   9C 00003FE0 PMDMBSetAmplifierEnable
        158   9D 00004030 PMDMBSetDACOutputEnable
        159   9E 000040F0 PMDMBSetSSIRegister
        160   9F 000040A0 PMDMBSetWatchdog
        161   A0 00003FD0 PMDMBWriteDigitalOutput
        162   A1 00004710 PMDMPDeviceOpen
        163   A2 00002B20 PMDMemoryAlloc
        164   A3 00002FC0 PMDMemoryClose
        165   A4 00002B10 PMDMemoryFree
        166   A5 00004650 PMDMemoryOpen
        167   A6 00003240 PMDMemoryRead
        168   A7 00003270 PMDMemoryWrite
        171   AA 00002AB0 PMDPeriphAlloc
        172   AB 00002E70 PMDPeriphClose
        173   AC 00002EE0 PMDPeriphFlush
        174   AD 00002B10 PMDPeriphFree
        175   AE 00004390 PMDPeriphOpenCAN
        176   AF 00008470 PMDPeriphOpenCME
        177   B0 00004230 PMDPeriphOpenCOM
        178   B1 00004480 PMDPeriphOpenISA
        179   B2 00004530 PMDPeriphOpenMultiDrop
        180   B3 000044F0 PMDPeriphOpenPCI
        181   B4 00004410 PMDPeriphOpenPIO
        182   B5 000042B0 PMDPeriphOpenTCP
        183   B6 00004320 PMDPeriphOpenUDP
        184   B7 00002E40 PMDPeriphRead
        185   B8 00002D60 PMDPeriphReceive
        186   B9 00002D00 PMDPeriphReceiveEvent
        187   BA 00002DD0 PMDPeriphSend
        188   BB 00002E10 PMDPeriphWrite
        189   BC 000082C0 PMDRPDeviceOpen
        197   C4 00008A90 PMDSerial_Sync
        263  106 00001CF0 PMDSetSerialPortMode
        279  116 00007FC0 PMDTaskGetState
        280  117 00008010 PMDTaskStart
        281  118 00008030 PMDTaskStop
        283  11A 00003220 PMDWaitForEvent
        284  11B 00003120 PMDWaitForEventPoll

*/
};

// tell the EXTERN macro we want to declare functions for export.
#undef TCL_STORAGE_CLASS
#define TCL_STORAGE_CLASS DLLEXPORT

// This is Tcl's entry point

EXTERN int Cmotcl_Init (Tcl_Interp *interp)
{
    PMDuint32 Maj, Min;

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

    // Does the compile-time C-Motion API match the implicitly loaded DLL?
    //
    PMDGetCMotionVersion(&Maj, &Min);
    if ((Maj != CMOTION_MAJOR_VERSION) || (Min != CMOTION_MINOR_VERSION))
    {
	std::ostringstream msg;
	msg << "C-Motion version mismatch of DLL! Got " << Maj << "." << Min <<
	    " but needed " << CMOTION_MAJOR_VERSION << "." << CMOTION_MINOR_VERSION;
	Tcl_SetObjResult(interp, Tcl_NewStringObj(msg.str().c_str(), -1));
	return TCL_ERROR;
    }

    new ItclCMoAdaptor(interp);
    Tcl_PkgProvide(interp, "cmotion", "1.0");
    return TCL_OK;
}
