load [file join [file dirname [info script]] CMoTcl10.dll]

itcl::class ::pmd::cmotion {
    constructor {} { _init }
    destructor { _destroy }
    public {
	method GetCMotionVersion {} @CMo-GetCMotionVersion
    }
    private {
	method _init    {} @CMo-construct
	method _destroy {} @CMo-destruct
    }
}
