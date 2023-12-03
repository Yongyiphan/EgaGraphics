project("Core")
kind("StaticLib")
language("C++")
cppdialect("C++20")
-- targetdir("Binaries/%{cfg.buildcfg}")
staticruntime("off")

pchheader "epch.h"
pchsource "GraphicsLib/epch.cpp"

files { "GraphicsLib/**.h", "GraphicsLib/**.cpp" }

includedirs {
	"GraphicsLib",
	IncludeDir.glfw,
	IncludeDir.glew,
	IncludeDir.glm,
}

-- libdirs
-- {
-- 	LibDir.glfw,
-- 	LibDir.glew,
-- }


-- links {
-- 	"glew32",
-- 	"glfw3dll",
-- 	"opengl32",
-- }


defines {
	"GLFW_DLL",
	"CRT_SECURE_NO_WARNINGS",
	"_UNICODE", "UNICODE"
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
