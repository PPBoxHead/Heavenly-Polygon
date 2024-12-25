workspace "Heavenly Polygon"
    architecture "x64"
    startproject "OpenGL_Project"

    configurations { "Debug", "Release" }

    -- Define the location dynamically based on the action
    -- if _ACTION then
    --     location ("IDEs-spec/" .. _ACTION)
    -- else
    --     location "IDEs-spec/default"
    -- end
    

outputdir = "%{cfg.buildcfg}/%{cfg.system}-%{cfg.architecture}"

project "Heavenly Polygon"
    kind "ConsoleApp"  -- Console-based application

    location "."

    language "C"
    cdialect "C99"

    targetdir ("bin/" .. outputdir)
    objdir ("bin/" .. outputdir .. "/obj_output")

    files {
        "src/**.c",
        "src/**.h",
        "third-party/glad.c",
    }

    includedirs {
        "third-party/include"
    }

    libdirs {
        "third-party/lib"
    }

    links {
        -- Link OpenGL (default Windows OpenGL library)
        "opengl32.lib",
        -- This are GLFW dependencies:
        "gdi32",
        "user32",
        "kernel32",
        "advapi32",
        "winmm",
        -- Link GLFW static library
        "glfw3.lib"
    }

        -- Organize Filters (Solution Explorer in Visual Studio)
    vpaths {
        ["Source Files/*"] = { "src/**.c" },
        ["Source Files/third-party*"] = { "third-party/*.c" },
        ["Header Files/*"] = { "src/**.h" },
        ["Header Files/third-party/*"] = { "third-party/include/**.h" },
        ["Resource Files/Shaders"] = {
            "resources/shaders/**.vert",
            "resources/shaders/**.frag"
        }
    }


    filter "system:windows"
        -- Use latest Windows SDK
        systemversion "latest"
        defines { "GLFW_STATIC" }


    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        staticruntime "off"
        symbols "on"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        staticruntime "off"
        optimize "on"
        
