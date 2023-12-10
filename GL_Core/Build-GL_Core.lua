project("GL_Core")
kind("StaticLib")
language("C++")
cppdialect("C++20")
-- targetdir("Binaries/%{cfg.buildcfg}")
staticruntime("off")

local FilesDir = "OpenGL_E"

pchheader "epch.h"
pchsource(FilesDir .. "/epch.cpp")


files {
	FilesDir .. "/**.h",
	FilesDir .. "/**.cpp",
	FilesDir .. "/**.inl",
}

IncludeDir.GL_Core     = "%{wks.location}/GL_Core"
AssetsDir.GL_Core      = {}
AssetsDir.GL_Core.dir  = "%{wks.location}/GL_Core/GL_Assets"
AssetsDir.GL_Core.name = "GL_Assets"

includedirs {
	FilesDir,
	IncludeDir.glfw,
	IncludeDir.glew,
	IncludeDir.glm,
}



defines {
	"GLFW_DLL",
	"CRT_SECURE_NO_WARNINGS",
	"_UNICODE", "UNICODE",
	"OPENGL_E"
}





targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("../Binaries/obj/" .. OutputDir .. "/%{prj.name}")

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
