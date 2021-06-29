------------------------------------------------ Global
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


------------------------------------------------ Solution
workspace "OpenGLFramework"
    configurations  { "Debug", "Release" }
    location        (WorkingDirectory)
    startproject    "Game"

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

        defines{
            "WIN32",
            "WIN64",
            "_WINDOWS",
        }


------------------------------------------------ Game Project
project "Game"
    location    (WorkingDirectory)
    kind        "ConsoleApp"
    language    "C++"

    dependson{
        "Framework",
    }
    
    includedirs {
        "Game",
        "Framework",
        "ThirdParty/include",
    }

    files {
        "Game/**.cpp",
        "Game/**.h",
    }

    targetdir (WorkingDirectory.."/bin/" ..outputdir.. "/%{prj.name}")
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "ThirdParty/lib",
        "Framework",
    }

    links {
        "opengl32",
        "glew32s",
        "glfw3",
        "Framework",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

    postbuildcommands{
        ("{COPY} %{prj.location}../Data %{prj.location}bin/"..outputdir.."/%{prj.name}/Data")
    }

------------------------------------------------ Engine Project
project "Framework"
    location    (WorkingDirectory)
    kind        "StaticLib"
    language    "C++"

    includedirs {
        "Framework",
        "ThirdParty/include",
    }

    files {
        "Framework/**.cpp",
        "Framework/**.h",
    }

    targetdir (WorkingDirectory.."/bin/" ..outputdir.."/%{prj.name}")
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "ThirdParty/lib",
    }

    links {
        "opengl32",
        "glew32s",
        "glfw3",
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"


---------------------------------------------------- Project Configuration files
project "PROJECT_CONFIG"
    location (WorkingDirectory)
    kind "none"

    files{
        "premake5.lua",
        "PremakeGenerateBuildFiles.bat",
        ".gitignore",
    }


------------------------------------------------------- Shaders project
project "Shaders"
    location (WorkingDirectory)
    kind "Utility"

    targetdir (WorkingDirectory.."/bin/" ..outputdir)
    objdir  (WorkingDirectory.."/bin-obj/")

    files{
        "Data/Shaders/**.vert",
        "Data/Shaders/**.frag",
        "Data/Shaders/**.bat",
    }

----------------------------------All files project
project "ALL_FILES"
    location (WorkingDirectory)
    kind "none"

    files{
        "**.*",
    }

    removefiles{
        "build/**.*",
    }