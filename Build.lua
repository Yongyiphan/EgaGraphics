-- premake5.lua
workspace("EgaGraphics")
-- "%{wks.location}" == sln.dir
architecture("x64")
configurations({ "Debug", "Release" })
startproject("Editor")

-- Workspace-wide build options for MSVC
filter("system:windows")
buildoptions({ "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" })

-- Relative to sln.dir
IncludeDir          = {}
IncludeDir["glfw"]  = "%{wks.location}/Vendor/Dependencies/glfw-3.3.8.bin.WIN64/include"
IncludeDir["glew"]  = "%{wks.location}/Vendor/Dependencies/glew-2.2.0/include"
IncludeDir["glm"]   = "%{wks.location}/Vendor/Dependencies/glm-0.9.9.8/glm"
IncludeDir["imgui"] = "%{wks.location}/Vendor/Dependencies/imgui"

--Relative to sln.dir
LibDir              = {}
LibDir["glfw"]      = "%{wks.location}/Vendor/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022"
LibDir["glew"]      = "%{wks.location}/Vendor/Dependencies/glew-2.2.0/lib/Release/x64"

AssetsDir           = {}
PostLibDir          = {}
PostLibDir["glfw"]  = "%{wks.location}Vendor/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022"
PostLibDir["glew"]  = "%{wks.location}Vendor/Dependencies/glew-2.2.0/bin/Release/x64"


OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "GLib"
include("ELib/Build-ELib.lua")
group ""

include "Editor/Build-Editor.lua"
