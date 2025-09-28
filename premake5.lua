require("external/premake/premake_extensions/ecc/ecc")

workspace("GBEmu")
architecture("x86_64")
startproject("GBEmu")

configurations({
	"Debug",
	"Release",
	"Tests"
})

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include("GBEmu/Common")
include("GBEmu/Emulator")
include("GBEmu/GBEmu")
include("GBEmu/GBEmuTests")