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
IncludeDir              = {}
IncludeDir["glfw"]      = "%{wks.location}/Vendor/Dependencies/glfw-3.3.8.bin.WIN64/include"
IncludeDir["glew"]      = "%{wks.location}/Vendor/Dependencies/glew-2.2.0/include"
IncludeDir["glm"]       = "%{wks.location}/Vendor/Dependencies/glm-0.9.9.8/glm"
IncludeDir["imgui"]     = "%{wks.location}/Vendor/Dependencies/imgui"
IncludeDir["stb_image"] = "%{wks.location}/Vendor/Dependencies/stb-master"
IncludeDir["freetype"]  = "%{wks.location}/Vendor/Dependencies/freetype-windows-binaries-2.13.1/include"

--Relative to sln.dir
LibDir                  = {}
LibDir["glfw"]          = "%{wks.location}/Vendor/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022"
LibDir["glew"]          = "%{wks.location}/Vendor/Dependencies/glew-2.2.0/lib/x64"
LibDir["freetype"]      = "%{wks.location}/Vendor/Dependencies/freetype-windows-binaries-2.13.1/release_static/win64"

AssetsDir               = {}
PostLibDir              = {}
PostLibDir["glfw"]      = "%{wks.location}Vendor/Dependencies/glfw-3.3.8.bin.WIN64/lib-vc2022"
PostLibDir["glew"]      = "%{wks.location}Vendor/Dependencies/glew-2.2.0/bin/x64"
PostLibDir["freetype"]  = "%{wks.location}Vendor/Dependencies/freetype-windows-binaries-2.13.1/release_dll/win64"

defines {
	"ELIB_OPENGL"
}

ProjectTargetDir = "%{wks.location}/Binaries/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}/"
ProjectObjDir = "%{wks.location}/Binaries/obj/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}/"

group "GLib"
include("ImGui/Build-ImGui.lua")
include("ELib/Build-ELib.lua")
group ""

dependson { "ImGui" }
-- ignoredefaultlibraries { "LIBCMTD" }

include "Editor/Build-Editor.lua"
