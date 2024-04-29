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

	# Motor
	method SetMotorType {} @CMo-SetMotorType
	method GetMotorType {} @CMo-GetMotorType
	method SetMotorCommand {} @CMo-SetMotorCommand
	method GetMotorCommand {} @CMo-GetMotorCommand
	method GetActiveMotorCommand {} @CMo-GetActiveMotorCommand

    }
    private {
	method _init    {} @CMo-construct
	method _destroy {} @CMo-destruct
    }
}
