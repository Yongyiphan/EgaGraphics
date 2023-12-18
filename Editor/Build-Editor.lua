project("Editor")
kind("ConsoleApp")
language("C++")
cppdialect("C++20")
-- targetdir("Binaries/%{cfg.buildcfg}")
staticruntime("off")

files({ "Source/**.h", "Source/**.cpp" })

includedirs({
	"Source",
})


externalincludedirs {
	IncludeDir.Core,
	IncludeDir.GL_Core,
	IncludeDir.glfw,
	IncludeDir.glew,
	IncludeDir.glm,
}

libdirs
{
	LibDir.glfw,
	LibDir.glew,
}

links {
	"ELib",
	"opengl32",
	"glew32",
	"glfw3dll",
}

dependson { "ELib" }



defines {
	"_CONSOLE",
	"ELIB_OPENGL",
}

targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("../Binaries/obj/" .. OutputDir .. "/%{prj.name}")
debugdir("../Binaries/" .. OutputDir .. "/%{prj.name}")

local TargetDir = " %{cfg.targetdir}/"

postbuildcommands {
	"{COPYDIR}  " .. AssetsDir.GL_Core.dir .. " " .. TargetDir .. AssetsDir.GL_Core.name,
	"{COPYFILE} " .. PostLibDir.glew .. "/glew32.dll " .. TargetDir .. "glew32.dll",
	"{COPYFILE} " .. PostLibDir.glfw .. "/glfw3.dll " .. TargetDir .. "glfw3.dll",
}


filter("system:windows")
systemversion("latest")
defines({ "WINDOWS" })

filter("configurations:Debug")
defines({ "_DEBUG" })
runtime("Debug")
symbols("On")

filter("configurations:Release")
defines({ "NDEBUG" })
runtime("Release")
optimize("On")
symbols("On")

-- filter("configurations:Dist")
-- defines({ "DIST" })
-- runtime("Release")
-- optimize("On")
-- symbols("Off")
