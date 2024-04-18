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

    }
    private {
	method _init    {} @CMo-construct
	method _destroy {} @CMo-destruct
    }
}
