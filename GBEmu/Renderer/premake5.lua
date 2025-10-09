project("Renderer")
kind("StaticLib")
language("C++")
cppdialect("C++23")
staticruntime("on")
systemversion("latest")

targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

files({
	"src/**.h",
	"src/**.cpp"
})

includedirs({
	"src/",
	"%{wks.location}/GBEmu/Common/src",
	"%{wks.location}/external/GLFW/include",
	"%{wks.location}/external/glad/include",
	"%{wks.location}/external/imgui"
})

links({
	"Common",
	"opengl32.lib",
    "glad",
	"GLFW",
	"imgui"
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