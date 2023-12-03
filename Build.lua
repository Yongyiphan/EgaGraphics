-- premake5.lua
workspace("EgaGraphics")
architecture("x64")
configurations({ "Debug", "Release" })
startproject("Core")

-- Workspace-wide build options for MSVC
filter("system:windows")
buildoptions({ "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" })

-- Relative to Core/
IncludeDir         = {}
IncludeDir["glfw"] = "Dependencies/glfw-3.3.8.bin.WIN64/include"
IncludeDir["glew"] = "Dependencies/glew-2.2.0/include"
IncludeDir["glm"]  = "Dependencies/glm-0.9.9.8/glm"

LibDir             = {}
LibDir["glfw"]     = "Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022"
LibDir["glew"]     = "Dependencies/glew-2.2.0/lib/Release/x64"



OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group("Core")
include("Core/Build-Core.lua")
group("")

include "Editor/Build-Editor.lua"
