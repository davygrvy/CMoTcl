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

    // Boiler-plate to connect to the CMoAPI class.
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
          2    1 00001470 PMDAdjustActualPosition
          3    2 00002F70 PMDAtlasAxisOpen
          4    3 00002AE0 PMDAxisAlloc
          5    4 00002FA0 PMDAxisClose
          6    5 00002B10 PMDAxisFree
          7    6 00004610 PMDAxisOpen
          8    7 00002430 PMDCalibrateAnalog
          9    8 00002160 PMDClearDriveFaultStatus
         10    9 000013F0 PMDClearInterrupt
         11    A 00001290 PMDClearPositionError
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
         24   17 000022D0 PMDDriveNVRAM
         25   18 000025C0 PMDExecutionControl
         26   19 00001090 PMDGetAcceleration
         27   1A 00001650 PMDGetActiveMotorCommand
         28   1B 00001F80 PMDGetActiveOperatingMode
         29   1C 00001430 PMDGetActivityStatus
         30   1D 00001490 PMDGetActualPosition
         31   1E 000014B0 PMDGetActualPositionUnits
         32   1F 000015D0 PMDGetActualVelocity
         33   20 000023F0 PMDGetAnalogCalibration
         34   21 00001520 PMDGetAuxiliaryEncoderSource
         35   22 00002040 PMDGetAxisOutMask
         36   23 00001310 PMDGetBreakpoint
         37   24 00001EE0 PMDGetBreakpointUpdateMask
         38   25 00001390 PMDGetBreakpointValue
         39   26 00001830 PMDGetBufferLength
         40   27 000018F0 PMDGetBufferReadIndex
         41   28 000017F0 PMDGetBufferStart
         42   29 000018B0 PMDGetBufferWriteIndex
         43   2A 00002120 PMDGetBusVoltage
         44   2B 00002100 PMDGetBusVoltageLimits
         45   2C 00001DE0 PMDGetCANMode
         46   2D 000022C0 PMDGetCMotionVersion
         47   2E 000014D0 PMDGetCaptureSource
         48   2F 000015E0 PMDGetCaptureValue
         49   30 00001E60 PMDGetChecksum
         50   31 000011B0 PMDGetCommandedAcceleration
         51   32 00001190 PMDGetCommandedPosition
         52   33 000011A0 PMDGetCommandedVelocity
         53   34 000016B0 PMDGetCommutationMode
         54   35 00002500 PMDGetCommutationParameter
         55   36 00002330 PMDGetCurrent
         56   37 00001FF0 PMDGetCurrentControlMode
         57   38 00001FC0 PMDGetCurrentFoldback
         58   39 000011C0 PMDGetCurrentLimit
         59   3A 000021C0 PMDGetCurrentLoop
         60   3B 000021E0 PMDGetCurrentLoopValue
         61   3C 000010B0 PMDGetDeceleration
         62   3D 00002220 PMDGetDefault
         63   3E 00002570 PMDGetDriveCommandMode
         64   3F 00002100 PMDGetDriveFaultParameter
         65   40 00002170 PMDGetDriveFaultStatus
         66   41 00002370 PMDGetDrivePWM
         67   42 00001EB0 PMDGetDriveStatus
         68   43 00002410 PMDGetDriveValue
         69   44 00001580 PMDGetEncoderModulus
         70   45 000014F0 PMDGetEncoderSource
         71   46 000015B0 PMDGetEncoderToStepRatio
         72   47 000032A0 PMDGetErrorMessage
         73   48 000020C0 PMDGetEventAction
         74   49 00001420 PMDGetEventStatus
         75   4A 00002260 PMDGetFOC
         76   4B 00002280 PMDGetFOCValue
         77   4C 000022B0 PMDGetFaultOutMask
         78   4D 000023B0 PMDGetFeedbackParameter
         79   4E 00001120 PMDGetGearMaster
         80   4F 000010F0 PMDGetGearRatio
         81   50 00002330 PMDGetHoldingCurrent
         82   51 00001CE0 PMDGetInstructionError
         83   52 00001400 PMDGetInterruptAxis
         84   53 000013E0 PMDGetInterruptMask
         85   54 000010D0 PMDGetJerk
         86   55 00002460 PMDGetLoop
         87   56 00002480 PMDGetLoopValue
         88   57 00001280 PMDGetMotionCompleteMode
         89   58 000011E0 PMDGetMotorBias
         90   59 00001640 PMDGetMotorCommand
         91   5A 000011C0 PMDGetMotorLimit
         92   5B 00001600 PMDGetMotorType
         93   5C 00001F70 PMDGetOperatingMode
         94   5D 00001670 PMDGetOutputMode
         95   5E 00002140 PMDGetOvertemperatureLimit
         96   5F 00001690 PMDGetPWMFrequency
         97   60 00001770 PMDGetPhaseAngle
         98   61 000017B0 PMDGetPhaseCommand
         99   62 00001790 PMDGetPhaseCorrectionMode
        100   63 00001710 PMDGetPhaseCounts
        101   64 000016D0 PMDGetPhaseInitializeMode
        102   65 00001730 PMDGetPhaseInitializeTime
        103   66 00001750 PMDGetPhaseOffset
        104   67 00002540 PMDGetPhaseParameter
        105   68 000016F0 PMDGetPhasePrescale
        106   69 00001030 PMDGetPosition
        107   6A 000012A0 PMDGetPositionError
        108   6B 00001200 PMDGetPositionErrorLimit
        109   6C 00001F20 PMDGetPositionLoop
        110   6D 00001F40 PMDGetPositionLoopValue
        111   6E 00002580 PMDGetProductInfo
        112   6F 00001010 PMDGetProfileMode
        113   70 000024C0 PMDGetProfileParameter
        114   71 000025A0 PMDGetRuntimeError
        115   72 00001E40 PMDGetSPIMode
        116   73 000012C0 PMDGetSampleTime
        117   74 00001D40 PMDGetSerialPortMode
        118   75 00001220 PMDGetSettleTime
        119   76 00001240 PMDGetSettleWindow
        120   77 00001450 PMDGetSignalSense
        121   78 00001460 PMDGetSignalStatus
        122   79 00001070 PMDGetStartVelocity
        123   7A 00001E80 PMDGetStepRange
        124   7B 00001180 PMDGetStopMode
        125   7C 00001EA0 PMDGetSynchronizationMode
        126   7D 00002150 PMDGetTemperature
        127   7E 00001E50 PMDGetTime
        128   7F 00001B60 PMDGetTraceCount
        129   80 00001920 PMDGetTraceMode
        130   81 00001940 PMDGetTracePeriod
        131   82 00001A10 PMDGetTraceStart
        132   83 00001B50 PMDGetTraceStatus
        133   84 00001AD0 PMDGetTraceStop
        134   85 00001B70 PMDGetTraceValue
        135   86 00001980 PMDGetTraceVariable
        136   87 00001260 PMDGetTrackingWindow
        137   88 00002190 PMDGetUpdateMask
        138   89 00008150 PMDGetUserCodeFileDate
        139   8A 00008130 PMDGetUserCodeFileName
        140   8B 00008110 PMDGetUserCodeFileVersion
        141   8C 00001050 PMDGetVelocity
        142   8D 00001C10 PMDGetVersion
        143   8E 00001CD0 PMDGetVersion32
        144   8F 000017A0 PMDInitializePhase
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
        169   A8 000013C0 PMDMultiUpdate
        170   A9 00001C00 PMDNoOperation
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
        190   BD 00001BD0 PMDReadAnalog
        191   BE 00001870 PMDReadBuffer
        192   BF 000022F0 PMDReadBuffer16
        193   C0 00001BB0 PMDReadIO
        194   C1 00001BF0 PMDReset
        195   C2 00001410 PMDResetEventStatus
        196   C3 00001F90 PMDRestoreOperatingMode
        197   C4 00008A90 PMDSerial_Sync
        198   C5 00001080 PMDSetAcceleration
        199   C6 00001480 PMDSetActualPosition
        200   C7 000014A0 PMDSetActualPositionUnits
        201   C8 000023D0 PMDSetAnalogCalibration
        202   C9 00001500 PMDSetAuxiliaryEncoderSource
        203   CA 00002000 PMDSetAxisOutMask
        204   CB 000012D0 PMDSetBreakpoint
        205   CC 00001EC0 PMDSetBreakpointUpdateMask
        206   CD 00001370 PMDSetBreakpointValue
        207   CE 00001810 PMDSetBufferLength
        208   CF 000018D0 PMDSetBufferReadIndex
        209   D0 000017D0 PMDSetBufferStart
        210   D1 00001890 PMDSetBufferWriteIndex
        211   D2 000020E0 PMDSetBusVoltageLimits
        212   D3 00001DC0 PMDSetCANMode
        213   D4 000014C0 PMDSetCaptureSource
        214   D5 000016A0 PMDSetCommutationMode
        215   D6 000024E0 PMDSetCommutationParameter
        216   D7 00002310 PMDSetCurrent
        217   D8 00001FE0 PMDSetCurrentControlMode
        218   D9 00001FA0 PMDSetCurrentFoldback
        219   DA 000025B0 PMDSetCurrentLimit
        220   DB 000021A0 PMDSetCurrentLoop
        221   DC 000010A0 PMDSetDeceleration
        222   DD 00002200 PMDSetDefault
        223   DE 00002560 PMDSetDriveCommandMode
        224   DF 000020E0 PMDSetDriveFaultParameter
        225   E0 00002350 PMDSetDrivePWM
        226   E1 00001570 PMDSetEncoderModulus
        227   E2 000014E0 PMDSetEncoderSource
        228   E3 00001590 PMDSetEncoderToStepRatio
        229   E4 000020A0 PMDSetEventAction
        230   E5 00002240 PMDSetFOC
        231   E6 000022A0 PMDSetFaultOutMask
        232   E7 00002390 PMDSetFeedbackParameter
        233   E8 00001100 PMDSetGearMaster
        234   E9 000010E0 PMDSetGearRatio
        235   EA 00002310 PMDSetHoldingCurrent
        236   EB 000013D0 PMDSetInterruptMask
        237   EC 000010C0 PMDSetJerk
        238   ED 00002440 PMDSetLoop
        239   EE 00001270 PMDSetMotionCompleteMode
        240   EF 000011D0 PMDSetMotorBias
        241   F0 00001630 PMDSetMotorCommand
        242   F1 000025B0 PMDSetMotorLimit
        243   F2 000015F0 PMDSetMotorType
        244   F3 00001F60 PMDSetOperatingMode
        245   F4 00001660 PMDSetOutputMode
        246   F5 00002130 PMDSetOvertemperatureLimit
        247   F6 00001680 PMDSetPWMFrequency
        248   F7 00001760 PMDSetPhaseAngle
        249   F8 00001780 PMDSetPhaseCorrectionMode
        250   F9 00001700 PMDSetPhaseCounts
        251   FA 000016C0 PMDSetPhaseInitializeMode
        252   FB 00001720 PMDSetPhaseInitializeTime
        253   FC 00001740 PMDSetPhaseOffset
        254   FD 00002520 PMDSetPhaseParameter
        255   FE 000016E0 PMDSetPhasePrescale
        256   FF 00001020 PMDSetPosition
        257  100 000011F0 PMDSetPositionErrorLimit
        258  101 00001F00 PMDSetPositionLoop
        259  102 00001000 PMDSetProfileMode
        260  103 000024A0 PMDSetProfileParameter
        261  104 00001E30 PMDSetSPIMode
        262  105 000012B0 PMDSetSampleTime
        263  106 00001CF0 PMDSetSerialPortMode
        264  107 00001210 PMDSetSettleTime
        265  108 00001230 PMDSetSettleWindow
        266  109 00001440 PMDSetSignalSense
        267  10A 00001060 PMDSetStartVelocity
        268  10B 00001E70 PMDSetStepRange
        269  10C 00001170 PMDSetStopMode
        270  10D 00001E90 PMDSetSynchronizationMode
        271  10E 00001910 PMDSetTraceMode
        272  10F 00001930 PMDSetTracePeriod
        273  110 000019D0 PMDSetTraceStart
        274  111 00001A90 PMDSetTraceStop
        275  112 00001950 PMDSetTraceVariable
        276  113 00001250 PMDSetTrackingWindow
        277  114 00002180 PMDSetUpdateMask
        278  115 00001040 PMDSetVelocity
        279  116 00007FC0 PMDTaskGetState
        280  117 00008010 PMDTaskStart
        281  118 00008030 PMDTaskStop
        282  119 000013B0 PMDUpdate
        283  11A 00003220 PMDWaitForEvent
        284  11B 00003120 PMDWaitForEventPoll
        285  11C 00001850 PMDWriteBuffer
        286  11D 00001B90 PMDWriteIO

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
