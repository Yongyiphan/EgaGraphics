project("Editor")
kind("ConsoleApp")
language("C++")
cppdialect("C++20")
staticruntime("off")

targetdir(ProjectTargetDir .. "/%{prj.name}")
objdir(ProjectObjDir .. "/%{prj.name}")

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
	IncludeDir.imgui,
	IncludeDir.stb_image,
	IncludeDir.freetype,
}

libdirs
{
	LibDir.glfw,
	LibDir.glew,
	LibDir.freetype,
}

links {
	"ELib",
	"ImGui",
	"opengl32",
	"glew32",
	"glfw3dll",
}

dependson { "ELib", "ImGui" }



defines {
	"_CONSOLE",
}


local function CreatePostBuildCommand(CMD, p_SrcDir, p_Filename, p_isDir)
	local m_TargetDir = " %{cfg.targetdir}/"
	if p_isDir == true then
		return CMD .. " " .. p_SrcDir .. m_TargetDir .. p_Filename
	else
		return CMD .. " " .. p_SrcDir .. "/" .. p_Filename .. m_TargetDir .. p_Filename
	end
end

postbuildcommands {
	CreatePostBuildCommand("{COPYDIR}", AssetsDir.GL_Core.dir, AssetsDir.GL_Core.name, true),
	CreatePostBuildCommand("{COPYFILE}", PostLibDir.glew, "glew32.dll", false),
	CreatePostBuildCommand("{COPYFILE}", PostLibDir.glfw, "glfw3.dll", false),
	CreatePostBuildCommand("{COPYFILE}", PostLibDir.freetype, "freetype.dll", false),
}

linkoptions { '/NODEFAULTLIB:LIBCMTD' }
-- linkoptions { "/VERBOSE:LIB" }

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
