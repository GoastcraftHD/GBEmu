project("GBEmuTests")
kind("ConsoleApp")
language("C++")
cppdialect("C++23")
staticruntime("on")
systemversion("latest")

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files({
	"src/**.h",
	"src/**.cpp",
	"%{wks.location}/external/googletest/googletest/**.h",
	"%{wks.location}/external/googletest/googletest/src/gtest-all.cc"
})

includedirs({
	"src/",
	"%{wks.location}/GBEmu/Emulator/src",
	"%{wks.location}/GBEmu/Common/src",
	"%{wks.location}/external/googletest/googletest",
	"%{wks.location}/external/googletest/googletest/include"
})

links({
	"Emulator",
	"Common"
})

-- Linux

filter("system:linux")
defines("GBE_LINUX")
toolset("clang")
buildoptions({
	"-Wall",
})

filter({ "system:linux", "configurations:Release" })
buildoptions({
	"-Werror",
})

-- Windows

filter("system:windows")
defines("GBE_WINDOWS")

buildoptions({
	"/W4",
	"/MP",
})

filter({ "system:windows", "configurations:Release" })
kind("WindowedApp")
buildoptions({
	"/WX",
})

-- Configurations

filter("configurations:Debug")
defines("GBE_DEBUG")
runtime("Debug")
symbols("on")

filter("configurations:Release")
defines("GBE_RELEASE")
runtime("Release")
optimize("on")

filter("configurations:Tests")
defines("GBE_TESTS")
runtime("Debug")
symbols("on")