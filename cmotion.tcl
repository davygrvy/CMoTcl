load [file join [file dirname [info script]] CMoTcl10.[info sharedlibextension]]

itcl::class ::pmd::cmotion {
    constructor {} { _init }
    destructor { _destroy }
    public {
	method GetCMotionVersion {} @CMo-GetCMotionVersion

	# Profile Generation
	method SetProfileMode {} @CMo-SetProfileMode
	method GetProfileMode {} @CMo-GetProfileMode
	method SetPosition {} @CMo-SetPosition
	method GetPosition {} @CMo-GetPosition
	method SetVelocity {} @CMo-SetVelocity
	method GetVelocity {} @CMo-GetVelocity
	method SetStartVelocity {} @CMo-SetStartVelocity
	method GetStartVelocity {} @CMo-GetStartVelocity
	method SetAcceleration {} @CMo-SetAcceleration
	method GetAcceleration {} @CMo-GetAcceleration
	method SetDeceleration {} @CMo-SetDeceleration
	method GetDeceleration {} @CMo-GetDeceleration
	method SetJerk {} @CMo-SetJerk
	method GetJerk {} @CMo-GetJerk
	method SetGearRatio {} @CMo-SetGearRatio
	method GetGearRatio {} @CMo-GetGearRatio
	method SetGearMaster {} @CMo-SetGearMaster
	method GetGearMaster {} @CMo-GetGearMaster
	method SetStopMode {} @CMo-SetStopMode
	method GetStopMode {} @CMo-GetStopMode
	method GetCommandedPosition {} @CMo-GetCommandedPosition
	method GetCommandedVelocity {} @CMo-GetCommandedVelocity
	method GetCommandedAcceleration {} @CMo-GetCommandedAcceleration

	# Position Loop
	method SetMotorLimit {} @CMo-SetMotorLimit
	method GetMotorLimit {} @CMo-GetMotorLimit
	method SetMotorBias {} @CMo-SetMotorBias
	method GetMotorBias {} @CMo-GetMotorBias
	method SetPositionErrorLimit {} @CMo-SetPositionErrorLimit
	method GetPositionErrorLimit {} @CMo-GetPositionErrorLimit
	method SetSettleTime {} @CMo-SetSettleTime
	method GetSettleTime {} @CMo-GetSettleTime
	method SetSettleWindow {} @CMo-SetSettleWindow
	method GetSettleWindow {} @CMo-GetSettleWindow
	method SetTrackingWindow {} @CMo-SetTrackingWindow
	method GetTrackingWindow {} @CMo-GetTrackingWindow
	method SetMotionCompleteMode {} @CMo-SetMotionCompleteMode
	method GetMotionCompleteMode {} @CMo-GetMotionCompleteMode
	method ClearPositionError {} @CMo-ClearPositionError
	method GetPositionError {} @CMo-GetPositionError
	method SetSampleTime {} @CMo-SetSampleTime
	method GetSampleTime {} @CMo-GetSampleTime

	# Parameter Update & Breakpoints
	method SetBreakpoint {} @CMo-SetBreakpoint
	method GetBreakpoint {} @CMo-GetBreakpoint
	method SetBreakpointValue {} @CMo-SetBreakpointValue
	method GetBreakpointValue {} @CMo-GetBreakpointValue
	method SetBreakpointUpdateMask {} @CMo-SetBreakpointUpdateMask
	method GetBreakpointUpdateMask {} @CMo-GetBreakpointUpdateMask
	method Update {} @CMo-Update
	method MultiUpdate {} @CMo-MultiUpdate

	# Interrupt Processing
	method SetInterruptMask {} @CMo-SetInterruptMask
	method GetInterruptMask {} @CMo-GetInterruptMask
	method ClearInterrupt {} @CMo-ClearInterrupt
	method GetInterruptAxis {} @CMo-GetInterruptAxis

	# Status Register Control
	method ResetEventStatus {} @CMo-ResetEventStatus
	method GetEventStatus {} @CMo-GetEventStatus
	method GetActivityStatus {} @CMo-GetActivityStatus
	method SetSignalSense {} @CMo-SetSignalSense
	method GetSignalSense {} @CMo-GetSignalSense
	method GetSignalStatus {} @CMo-GetSignalStatus

	# Encoder
	method AdjustActualPosition {} @CMo-AdjustActualPosition
	method SetActualPosition {} @CMo-SetActualPosition
	method GetActualPosition {} @CMo-GetActualPosition
	method SetActualPositionUnits {} @CMo-SetActualPositionUnits
	method GetActualPositionUnits {} @CMo-GetActualPositionUnits
	method SetCaptureSource {} @CMo-SetCaptureSource
	method GetCaptureSource {} @CMo-GetCaptureSource
	method SetEncoderSource {} @CMo-SetEncoderSource
	method GetEncoderSource {} @CMo-GetEncoderSource
	method SetEncoderModulus {} @CMo-SetEncoderModulus
	method GetEncoderModulus {} @CMo-GetEncoderModulus
	method SetEncoderToStepRatio {} @CMo-SetEncoderToStepRatio
	method GetEncoderToStepRatio {} @CMo-GetEncoderToStepRatio
	method GetActualVelocity {} @CMo-GetActualVelocity
	method GetCaptureValue {} @CMo-GetCaptureValue
	method SetAuxiliaryEncoderSource {} @CMo-SetAuxiliaryEncoderSource
	method GetAuxiliaryEncoderSource {} @CMo-GetAuxiliaryEncoderSource

	# Motor
	method SetMotorType {} @CMo-SetMotorType
	method GetMotorType {} @CMo-GetMotorType
	method SetMotorCommand {} @CMo-SetMotorCommand
	method GetMotorCommand {} @CMo-GetMotorCommand
	method GetActiveMotorCommand {} @CMo-GetActiveMotorCommand

	# Commutation
	method SetOutputMode {} @CMo-SetOutputMode
	method GetOutputMode {} @CMo-GetOutputMode
	method SetPWMFrequency {} @CMo-SetPWMFrequency
	method GetPWMFrequency {} @CMo-GetPWMFrequency
	method SetCommutationMode {} @CMo-SetCommutationMode
	method GetCommutationMode {} @CMo-GetCommutationMode
	method SetPhaseInitializeMode {} @CMo-SetPhaseInitializeMode
	method GetPhaseInitializeMode {} @CMo-GetPhaseInitializeMode
	method SetPhasePrescale {} @CMo-SetPhasePrescale
	method GetPhasePrescale {} @CMo-GetPhasePrescale
	method SetPhaseCounts {} @CMo-SetPhaseCounts
	method GetPhaseCounts {} @CMo-GetPhaseCounts
	method SetPhaseInitializeTime {} @CMo-SetPhaseInitializeTime
	method GetPhaseInitializeTime {} @CMo-GetPhaseInitializeTime
	method SetPhaseOffset {} @CMo-SetPhaseOffset
	method GetPhaseOffset {} @CMo-GetPhaseOffset
	method SetPhaseAngle {} @CMo-SetPhaseAngle
	method GetPhaseAngle {} @CMo-GetPhaseAngle
	method SetPhaseCorrectionMode {} @CMo-SetPhaseCorrectionMode
	method GetPhaseCorrectionMode {} @CMo-GetPhaseCorrectionMode
	method InitializePhase {} @CMo-InitializePhase
	method GetPhaseCommand {} @CMo-GetPhaseCommand

	# External Memory
	method SetBufferStart {} @CMo-SetBufferStart
	method GetBufferStart {} @CMo-GetBufferStart
	method SetBufferLength {} @CMo-SetBufferLength
	method GetBufferLength {} @CMo-GetBufferLength
	method WriteBuffer {} @CMo-WriteBuffer
	method ReadBuffer {} @CMo-ReadBuffer
	method SetBufferWriteIndex {} @CMo-SetBufferWriteIndex
	method GetBufferWriteIndex {} @CMo-GetBufferWriteIndex
	method SetBufferReadIndex {} @CMo-SetBufferReadIndex
	method GetBufferReadIndex {} @CMo-GetBufferReadIndex

	# Trace Operations
	method SetTraceMode {} @CMo-SetTraceMode
	method GetTraceMode {} @CMo-GetTraceMode
	method SetTracePeriod {} @CMo-SetTracePeriod
	method GetTracePeriod {} @CMo-GetTracePeriod
	method SetTraceVariable {} @CMo-SetTraceVariable
	method GetTraceVariable {} @CMo-GetTraceVariable
	method SetTraceStart {} @CMo-SetTraceStart
	method GetTraceStart {} @CMo-GetTraceStart
	method SetTraceStop {} @CMo-SetTraceStop
	method GetTraceStop {} @CMo-GetTraceStop
	method GetTraceStatus {} @CMo-GetTraceStatus
	method GetTraceCount {} @CMo-GetTraceCount
	method GetTraceValue {} @CMo-GetTraceValue

	# Miscellaneous
	method WriteIO {} @CMo-WriteIO
	method ReadIO {} @CMo-ReadIO
	method ReadAnalog {} @CMo-ReadAnalog
	method Reset {} @CMo-Reset
	method NoOperation {} @CMo-NoOperation
	method GetVersion {} @CMo-GetVersion
	method GetVersion32 {} @CMo-GetVersion32
	method GetInstructionError {} @CMo-GetInstructionError

	method SetSerialPortMode {} @CMo-SetSerialPortMode
	method GetSerialPortMode {} @CMo-GetSerialPortMode
	method SetCANMode {} @CMo-SetCANMode
	method GetCANMode {} @CMo-GetCANMode
	
	method SetSPIMode {} @CMo-SetSPIMode
	method GetSPIMode {} @CMo-GetSPIMode
	method GetTime {} @CMo-GetTime
	method GetChecksum {} @CMo-GetChecksum
	method SetStepRange {} @CMo-SetStepRange
	method GetStepRange {} @CMo-GetStepRange
	method SetSynchronizationMode {} @CMo-SetSynchronizationMode
	method GetSynchronizationMode {} @CMo-GetSynchronizationMode

	# ION and Atlas specific functions
	method GetDriveStatus {} @CMo-GetDriveStatus
	method SetPositionLoop {} @CMo-SetPositionLoop
	method GetPositionLoop {} @CMo-GetPositionLoop
	method GetPositionLoopValue {} @CMo-GetPositionLoopValue
	method SetOperatingMode {} @CMo-SetOperatingMode
	method GetOperatingMode {} @CMo-GetOperatingMode
	method GetActiveOperatingMode {} @CMo-GetActiveOperatingMode
	method RestoreOperatingMode {} @CMo-RestoreOperatingMode
	method SetCurrentFoldback {} @CMo-SetCurrentFoldback
	method GetCurrentFoldback {} @CMo-GetCurrentFoldback
	method SetHoldingCurrent {} @CMo-SetHoldingCurrent
	method GetHoldingCurrent {} @CMo-GetHoldingCurrent
	method SetCurrentControlMode {} @CMo-SetCurrentControlMode
	method GetCurrentControlMode {} @CMo-GetCurrentControlMode
	method SetAxisOutMask {} @CMo-SetAxisOutMask
	method GetAxisOutMask {} @CMo-GetAxisOutMask
	method SetEventAction {} @CMo-SetEventAction
	method GetEventAction {} @CMo-GetEventAction
	method SetBusVoltageLimits {} @CMo-SetBusVoltageLimits
	method GetBusVoltageLimits {} @CMo-GetBusVoltageLimits
	method GetBusVoltage {} @CMo-GetBusVoltage
	method SetOvertemperatureLimit {} @CMo-SetOvertemperatureLimit
	method GetOvertemperatureLimit {} @CMo-GetOvertemperatureLimit
	method GetTemperature {} @CMo-GetTemperature
	method ClearDriveFaultStatus {} @CMo-ClearDriveFaultStatus
	method GetDriveFaultStatus {} @CMo-GetDriveFaultStatus
	method SetUpdateMask {} @CMo-SetUpdateMask
	method GetUpdateMask {} @CMo-GetUpdateMask
	method SetCurrentLoop {} @CMo-SetCurrentLoop
	method GetCurrentLoop {} @CMo-GetCurrentLoop
	method GetCurrentLoopValue {} @CMo-GetCurrentLoopValue
	method SetDefault {} @CMo-SetDefault
	method GetDefault {} @CMo-GetDefault
	method SetFOC {} @CMo-SetFOC
	method GetFOC {} @CMo-GetFOC
	method GetFOCValue {} @CMo-GetFOCValue
	method SetFaultOutMask {} @CMo-SetFaultOutMask
	method GetFaultOutMask {} @CMo-GetFaultOutMask

	# Atlas, MC5x113 and MC7x113 specific functions
	method DriveNVRAM {} @CMo-DriveNVRAM
	method ReadBuffer16 {} @CMo-ReadBuffer16
	method SetCurrent {} @CMo-SetCurrent
	method GetCurrent {} @CMo-GetCurrent
	method SetDriveFaultParameter {} @CMo-SetDriveFaultParameter
	method GetDriveFaultParameter {} @CMo-GetDriveFaultParameter
	method SetDrivePWM {} @CMo-SetDrivePWM
	method GetDrivePWM {} @CMo-GetDrivePWM
	method SetFeedbackParameter {} @CMo-SetFeedbackParameter
	method GetFeedbackParameter {} @CMo-GetFeedbackParameter

	# MC5x113 specific functions
	method SetAnalogCalibration {} @CMo-SetAnalogCalibration
	method GetAnalogCalibration {} @CMo-GetAnalogCalibration
	method GetDriveValue {} @CMo-GetDriveValue
	method CalibrateAnalog {} @CMo-CalibrateAnalog

	# MC7x113 specific functions
	method SetLoop {} @CMo-SetLoop
	method GetLoop {} @CMo-GetLoop
	method GetLoopValue {} @CMo-GetLoopValue
	method SetProfileParameter {} @CMo-SetProfileParameter
	method GetProfileParameter {} @CMo-GetProfileParameter
	method GetProductInfo {} @CMo-GetProductInfo
	method ExecutionControl {} @CMo-ExecutionControl
	method SetCommutationParameter {} @CMo-SetCommutationParameter
	method GetCommutationParameter {} @CMo-GetCommutationParameter
	method SetPhaseParameter {} @CMo-SetPhaseParameter
	method GetPhaseParameter {} @CMo-GetPhaseParameter
	method SetDriveCommandMode {} @CMo-SetDriveCommandMode
	method GetDriveCommandMode {} @CMo-GetDriveCommandMode
	method GetRuntimeError {} @CMo-GetRuntimeError
	method SetCurrentLimit {} @CMo-SetCurrentLimit
	method GetCurrentLimit {} @CMo-GetCurrentLimit
    }
    private {
	method _init    {} @CMo-construct
	method _destroy {} @CMo-destruct
    }
}
