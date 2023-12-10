project("Vulkan_Core")
kind("StaticLib")
language("C++")
cppdialect("C++20")
-- targetdir("Binaries/%{cfg.buildcfg}")
staticruntime("off")

local FilesDir = "Vulkan_E"

-- pchheader "epch.h"
-- pchsource(FilesDir .. "/epch.cpp")


files {
	FilesDir .. "/**.h",
	FilesDir .. "/**.cpp",
	FilesDir .. "/**.inl",
}

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
	"VULKAN_E"
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
