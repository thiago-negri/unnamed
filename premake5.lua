-- premake5.lua
workspace "Unnamed"
   configurations { "Debug", "Release" }

include "premake5_glfw.lua"

project "Unnamed"
    kind "ConsoleApp"
    language "C"
    targetdir "bin/%{prj.name}"
    objdir "obj/%{prj.name}"
    systemversion "latest"

    files {
	"src/**.h",
	"src/**.c",

	"src-3rd/**.h",
	"src-3rd/**.c",
    }
	
    includedirs {
	"includes",
	"glfw/include"
    }

    libdirs "libs"

    links { 
        "OpenGL32",
	"GLFW"
    }
	
    linkoptions { "/VERBOSE:LIB" }

    filter "configurations:Debug"
        defines { "GLEW_STATIC", "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "GLEW_STATIC", "NDEBUG" }
        optimize "On"
