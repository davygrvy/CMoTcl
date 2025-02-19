#include "tcl.h"
#include "c-motion/c-motion.h"

class CMoAxis
{
public:
    CMoAxis(Tcl_Interp* interp);
    ~CMoAxis();

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

    // Position Loop
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

    // Parameter Update & Breakpoints
    int PMDSetBreakpoint(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBreakpoint(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetBreakpointValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBreakpointValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetBreakpointUpdateMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBreakpointUpdateMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDUpdate(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDMultiUpdate(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Interrupt Processing
    int PMDSetInterruptMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetInterruptMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDClearInterrupt(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetInterruptAxis(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Status Register Control
    int PMDResetEventStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetEventStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActivityStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetSignalSense(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSignalSense(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSignalStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Encoder
    int PMDAdjustActualPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetActualPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActualPosition(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetActualPositionUnits(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActualPositionUnits(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCaptureSource(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCaptureSource(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetEncoderSource(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetEncoderSource(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetEncoderModulus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetEncoderModulus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetEncoderToStepRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetEncoderToStepRatio(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActualVelocity(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCaptureValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetAuxiliaryEncoderSource(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetAuxiliaryEncoderSource(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Motor
    int PMDSetMotorType(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotorType(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActiveMotorCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]); // same as PMDGetCurrentMotorCommand

    // Commutation
    int PMDSetOutputMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int	PMDGetOutputMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int	PMDSetPWMFrequency(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int	PMDGetPWMFrequency(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCommutationMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCommutationMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseInitializeMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseInitializeMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhasePrescale(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhasePrescale(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseCounts(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseCounts(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseInitializeTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseInitializeTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseOffset(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseOffset(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseAngle(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseAngle(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseCorrectionMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseCorrectionMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDInitializePhase(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseCommand(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // External Memory
    int PMDSetBufferStart(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBufferStart(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetBufferLength(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBufferLength(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDWriteBuffer(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDReadBuffer(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetBufferWriteIndex(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBufferWriteIndex(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetBufferReadIndex(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBufferReadIndex(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Trace Operations
    int PMDSetTraceMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetTracePeriod(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTracePeriod(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetTraceVariable(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceVariable(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetTraceStart(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceStart(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetTraceStop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceStop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceCount(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTraceValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Miscellaneous
    int PMDWriteIO(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDReadIO(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDReadAnalog(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDReset(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDNoOperation(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetVersion(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetVersion32(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetInstructionError(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    int PMDSetSerialPortMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSerialPortMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCANMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCANMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    int PMDSetSPIMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSPIMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTime(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetChecksum(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetStepRange(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetStepRange(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetSynchronizationMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetSynchronizationMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // ION and Atlas specific functions
    int PMDGetDriveStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPositionLoop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPositionLoop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPositionLoopValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetOperatingMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetOperatingMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetActiveOperatingMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDRestoreOperatingMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCurrentFoldback(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCurrentFoldback(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetHoldingCurrent(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetHoldingCurrent(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCurrentControlMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCurrentControlMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetAxisOutMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetAxisOutMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetEventAction(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetEventAction(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetBusVoltageLimits(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBusVoltageLimits(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetBusVoltage(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetOvertemperatureLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetOvertemperatureLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetTemperature(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDClearDriveFaultStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDriveFaultStatus(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetUpdateMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetUpdateMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCurrentLoop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCurrentLoop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCurrentLoopValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetDefault(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDefault(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetFOC(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetFOC(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetFOCValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetFaultOutMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetFaultOutMask(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // Atlas, MC5x113 and MC7x113 specific functions
    int PMDDriveNVRAM(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDReadBuffer16(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCurrent(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCurrent(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetDriveFaultParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDriveFaultParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetDrivePWM(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDrivePWM(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetFeedbackParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetFeedbackParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    // MC5x113 specific functions
    int PMDSetAnalogCalibration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetAnalogCalibration(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDriveValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDCalibrateAnalog(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

    int PMDSetLoop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetLoop(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetLoopValue(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetProfileParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetProfileParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetProductInfo(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDExecutionControl(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCommutationParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCommutationParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetPhaseParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetPhaseParameter(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetDriveCommandMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetDriveCommandMode(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetRuntimeError(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDSetCurrentLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);
    int PMDGetCurrentLimit(Tcl_Interp* interp, int objc, struct Tcl_Obj* const objv[]);

private:
    PMDAxisHandle hAxis;
};
