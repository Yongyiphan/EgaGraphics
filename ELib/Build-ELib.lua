project("ELib")
kind("StaticLib")
language("C++")
cppdialect("C++20")
staticruntime("off")

targetdir(ProjectTargetDir .. "/%{prj.name}")
objdir(ProjectObjDir .. "/%{prj.name}")

filter "action:vs*"
removefiles { "*.filters" }

warnings "Extra"

local FilesDir = "OpenGL_E"

pchheader "epch.h"
pchsource("Core/epch.cpp")


files {
	"Core/**.h",
	"Core/**.hpp",
	"Core/**.inl",
	"Core/**.cpp",
	FilesDir .. "/**.h",
	FilesDir .. "/**.cpp",
	FilesDir .. "/**.inl",
	FilesDir .. "/**.hpp",
}



IncludeDir.Core        = "%{wks.location}/ELib/Core"
IncludeDir.GL_Core     = "%{wks.location}/ELib/" .. FilesDir

AssetsDir.GL_Core      = {}
AssetsDir.GL_Core.dir  = "%{wks.location}/ELib/GL_Assets"
AssetsDir.GL_Core.name = "GL_Assets"

includedirs {
	FilesDir,
	IncludeDir.Core,
	IncludeDir.glfw,
	IncludeDir.glew,
	IncludeDir.glm,
	IncludeDir.imgui
}


defines {
	"GLFW_DLL",
	"CRT_SECURE_NO_WARNINGS",
	"_UNICODE", "UNICODE",
}


filter("system:windows")
systemversion("latest")
defines {}


filter("configurations:Debug")
defines { "DEBUG" }
runtime("Debug")
symbols("On")

filter("configurations:Release")
defines { "RELEASE" }
runtime("Release")
optimize("On")
symbols("On")



-- filter("configurations:Dist")
-- defines { "DIST" }
-- runtime("Release")
-- optimize("On")
-- symbols("Off")
