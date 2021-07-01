------------------------------------------------ Global
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

DLL_LibOutput =  (WorkingDirectory.."/bin/" ..outputdir.. "/Libs");


--Change me
GameName = "Testing"



files{
    "ProjectConfig.h",
}

------------------------------------------------ Solution
workspace "OpenGLFramework"
    configurations  { "Debug", "Release" }
    location        (WorkingDirectory)
    startproject    "2. Player"

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

        defines{
            "WIN32",
            "WIN64",
            "_WINDOWS",
        }


---------------------------------------------------- Project Configuration files
project "1. PROJECT_CONFIG"
    location (WorkingDirectory)
    kind "Utility"

    files{
        "premake5.lua",
        "PremakeGenerateBuildFiles.bat",
        ".gitignore",
    }

    targetdir (WorkingDirectory.."/bin/" ..outputdir.. "/Game")
    objdir  (WorkingDirectory.."/bin-obj/")

    --If on windows we are most likely using a visual studio project 
    --Created since I can't right click and run a bat file in vs
    filter "system:windows"
        postbuildcommands{
            "cd ..",
            "PremakeGenerateBuildFiles.bat",
        }


------------------------------------------------ Main Executable Project
project "2. Player"
    targetname  "Player"
    location    (WorkingDirectory)
    kind        "ConsoleApp"
    language    "C++"

    dependson{
        "Framework",
        (GameName),
    }
    
    includedirs {
        "Game",
        "Framework",
        "ThirdParty/include",
    }

    files {
        "main.cpp",
        "ProjectConfig.h",
    }

    targetdir (WorkingDirectory.."/bin/" ..outputdir.. "/Game")
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "ThirdParty/lib",
        (DLL_LibOutput),
    }

    links {
        "opengl32",
        "glew32s",
        "glfw3",
        "Framework",
        (GameName),
    }

    postbuildcommands{
        ("{COPY} %{prj.location}../Data %{prj.location}bin/"..outputdir.."/Game/Data"),
        ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll %{cfg.targetdir}/"),
        ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll %{cfg.targetdir}/"),
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      postbuildcommands{
        
      }

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

    filter {"configurations:Release", "system:windows"}
        kind "WindowedApp"
        entrypoint ("mainCRTStartup")

    filter {}


------------------------------------------------ Game Project
project ("3. "..GameName)
    targetname  (GameName)
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
    defines     {"GameDLLExport"}

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

    targetdir (DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "ThirdParty/lib",
        (DLL_LibOutput),
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

    filter {}


------------------------------------------------ Engine Project
project "4. Framework"
    targetname  "Framework"
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
     defines    {"FrameworkDLLExport"}

    includedirs {
        "Framework",
        "ThirdParty/include",
    }

    files {
        "Framework/**.cpp",
        "Framework/**.h",
    }

    targetdir (DLL_LibOutput)
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

      filter {}


------------------------------------------------------- Shaders project
project "5. Shaders"
    location (WorkingDirectory)
    kind "Utility"

    targetdir (WorkingDirectory.."/bin/" ..outputdir)
    objdir  (WorkingDirectory.."/bin-obj/")

    files{
        "Data/Shaders/**.vert",
        "Data/Shaders/**.frag",
    }


--A Project used to view all files
----------------------------------All files project
-- project "ALL_FILES"
--     location (WorkingDirectory)
--     kind "none"
-- 
--     files{
--         "**.*",
--     }
-- 
--     removefiles{
--         "build/**.*",
--     }