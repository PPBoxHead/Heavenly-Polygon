workspace "Heavenly Polygon"
    architecture "x64"
    startproject "OpenGL_Project"

    configurations { "Debug", "Release" }

    -- Define the location dynamically based on the action
    if _ACTION then
        location ("IDEs-spec/" .. _ACTION)
    else
        location "IDEs-spec/default"
    end
    

outputdir = "%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}"

project "Heavenly Polygon"
    location "."
    kind "ConsoleApp"  -- Console-based application

    language "C"
    cdialect "C99"

    staticruntime "on" -- Statically link runtime library (makes executable self-contained)

    targetdir ("bin/" .. outputdir)
    objdir ("bin/" .. outputdir .. "/obj_output")

    files {
        "src/**.c",
        "src/**.h",
        "third-party/glad.c",
    }

    includedirs {
        "src",
        "third-party/include"
    }

    libdirs {
        "third-party/lib"
    }

    links {
        "glfw3.lib",       -- Link GLFW static library
        "opengl32.lib"     -- Link OpenGL (default Windows OpenGL library)
    }

        -- Organize Filters (Solution Explorer in Visual Studio)
    vpaths {
        ["Source Files/*"] = { "src/**.c" },
        ["Source Files/third-party*"] = { "third-party/*.c" },
        ["Header Files/*"] = { "src/**.h" },
        ["Header Files/third-party/*"] = { "third-party/include/**.h" },
        ["Resource Files/Shaders"] = {  "resources/shaders/**.vert", "resources/shaders/**.frag"  }
    }


    filter "system:windows"
        systemversion "latest" -- Use latest Windows SDK


    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "on"
