project("Editor")
kind("ConsoleApp")
language("C++")
cppdialect("C++20")
-- targetdir("Binaries/%{cfg.buildcfg}")
staticruntime("off")

files({ "Source/**.h", "Source/**.cpp" })

includedirs({
	"Source",
	"../Core/Source",
})

links {
	"Core"
}

externalincludedirs {
	"../Core/" .. IncludeDir.glfw,
	"../Core/" .. IncludeDir.glew,
	"../Core/" .. IncludeDir.glm,
}

dependson { "Core" }



-- libdirs {
-- 	"../Binaries/" .. OutputDir .. "/%{prj.name}",
-- 	"../Core/%{LibDir.glfw}",
-- 	"../Core/%{LibDir.glew}",
-- }

defines {
	"_CONSOLE"
}

targetdir("../bin/" .. OutputDir .. "/%{prj.name}")
objdir("../bin/obj/" .. OutputDir .. "/%{prj.name}")

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
