project("Editor")
kind("ConsoleApp")
language("C++")
cppdialect("C++20")
-- targetdir("Binaries/%{cfg.buildcfg}")
staticruntime("off")

files({ "Source/**.h", "Source/**.cpp" })

includedirs({
	"Source",
	"../Core/GraphicsLib",
})


externalincludedirs {
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
	"Core",
	"opengl32",
	"glew32",
	"glfw3dll",
}

dependson { "Core" }



defines {
	"_CONSOLE"
}

targetdir("../Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("../Binaries/obj/" .. OutputDir .. "/%{prj.name}")

local glewpb = PBCmd.glew.cmd .. PBCmd.glew.Dir .. PBCmd.glew.file .. PBCmd.glew.target .. PBCmd.glew.file
local glfwpb = PBCmd.glfw.cmd .. PBCmd.glfw.Dir .. PBCmd.glfw.file .. PBCmd.glfw.target .. PBCmd.glfw.file


postbuildcommands {
	glewpb,
	glfwpb,
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
