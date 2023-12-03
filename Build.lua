-- premake5.lua
workspace("EgaGraphics")
-- "%{wks.location}" == sln.dir
--
architecture("x64")
configurations({ "Debug", "Release" })
startproject("Editor")

-- Workspace-wide build options for MSVC
filter("system:windows")
buildoptions({ "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" })

-- Relative to Core/
IncludeDir         = {}
IncludeDir["glfw"] = "../Vendor/Dependencies/glfw-3.3.8.bin.WIN64/include"
IncludeDir["glew"] = "../Vendor/Dependencies/glew-2.2.0/include"
IncludeDir["glm"]  = "../Vendor/Dependencies/glm-0.9.9.8/glm"

LibDir             = {}
LibDir["glfw"]     = "../Vendor/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022"
LibDir["glew"]     = "../Vendor/Dependencies/glew-2.2.0/lib/Release/x64"

-- Post Build Commands
PBCmd              = {}
PBCmd["glfw"]      = {
	cmd = "{COPYFILE} ",
	file = "glfw3.dll",
	Dir = "%{wks.location}/Vendor/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022/",
	target = " %{cfg.targetdir}/"
}

PBCmd["glew"]      = {
	cmd = "{COPYFILE} ",
	file = "glew32.dll",
	Dir = "%{wks.location}/Vendor/Dependencies/glew-2.2.0/bin/Release/x64/",
	target = " %{cfg.targetdir}/"
}

OutputDir          = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group("Core")
include("Core/Build-Core.lua")
group("")

include "Editor/Build-Editor.lua"
