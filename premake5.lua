------------------------------------------------ Global
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

DLL_LibOutput =  ("/bin/" ..outputdir.. "/Libs");


--Name of the current game project
GameName = "Game"


--Project names as a variable
WorkspaceName            = "OpenGLFramework"

ProjectConfigProjectName = "1. Project Config"
ShaderProjectName        = "2. Shaders"
ApplicationProjectName   = "3. Player"
FrameworkProjectName     = "4. Framework"
GameProjectName          = ("5. "..GameName)


files{
    "Source/ProjectConfig.h",
}

filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

filter "configurations:Debug"
       defines { "DEBUG", "_DEBUG", "EXECUTE_WITH_CONSOLE_VISIBLE"}
       symbols "On"

filter "configurations:Development"
       defines {"DEVELOPMENT", "EXECUTE_WITH_CONSOLE_VISIBLE"}
       optimize "On"

filter "configurations:Release"
       defines { "RELEASE", "STANDALONE" }
       optimize "On"

filter "configurations:ReleaseConsole"
       defines { "CONSOLE_RELEASE", "STANDALONE", "EXECUTE_WITH_CONSOLE_VISIBLE" }
       optimize "On"

filter "configurations:Publish"
        defines {"RELEASE", "STANDALONE"}
        optimize "On"

------------------------------------------------ Solution
workspace (WorkspaceName)
    configurations  { "Debug", "Release", "ReleaseConsole", "Development", "Publish" }
    location        (WorkingDirectory)
    startproject    (ApplicationProjectName)

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

        defines{
            "WIN32",
            "WIN64",
            "_WINDOWS",
        }


---------------------------------------------------- Project Configuration files
project (ProjectConfigProjectName)
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
project (ApplicationProjectName)
    targetname  "Player"
    location    (WorkingDirectory)
    debugdir    (WorkingDirectory.."/bin/" ..outputdir.. "/Game")
    kind        "ConsoleApp"
    language    "C++"

    dependson{
        (GameProjectName),
        (FrameworkProjectName),
    }
    
    includedirs {
        "Source/Game",
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/main.cpp",
    }

    targetdir (WorkingDirectory.."/bin/" ..outputdir.. "/Game")
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "Source/ThirdParty/lib",
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
        (GameName),
    }

    postbuildcommands{
        ("{COPY} %{prj.location}../Source/Data %{prj.location}bin/"..outputdir.."/Game/Data"),
        ("{COPY} %{prj.location}../Source/ThirdParty/lib/glew32.dll %{cfg.targetdir}/"),
        ("{COPY} %{prj.location}../Source/ThirdParty/lib/glfw3.dll %{cfg.targetdir}/"),
    }

    filter "configurations:Debug"
        postbuildcommands{
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/ %{cfg.targetdir}/"),
        }

    filter "configurations:Development"
        postbuildcommands{
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll %{cfg.targetdir}/"),
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll %{cfg.targetdir}/"),
        }

    filter "configurations:Release"
        postbuildcommands{
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll %{cfg.targetdir}/"),
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll %{cfg.targetdir}/"),
        }

    filter "configurations:ReleaseConsole"
        postbuildcommands{
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll %{cfg.targetdir}/"),
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll %{cfg.targetdir}/"),
        }

    filter "configurations:Publish"
        postbuildcommands{
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll %{cfg.targetdir}/"),
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll %{cfg.targetdir}/"),
        }

    filter {"configurations:Release", "system:windows"}
        kind "WindowedApp"
        entrypoint ("mainCRTStartup")

    filter {"configurations:Publish", "system:windows"}
        kind "WindowedApp"
        entrypoint ("mainCRTStartup")

    filter {}



------------------------------------------------ Game Project
project (GameProjectName)
    targetname  (GameName)
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
    defines     {"GameDLLExport"}
    pchheader   "GamePCH.h"
    pchsource   "Source/Game/GamePCH.cpp"

    dependson{
       (FrameworkProjectName),
    }
    
    includedirs {
        "Source/Game",
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/Game/**.cpp",
        "Source/Game/**.h",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "Source/ThirdParty/lib",
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
    }

    filter {}



------------------------------------------------ Framework Project
project (FrameworkProjectName)
    targetname  "Framework"
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
    defines     {"FrameworkDLLExport"}
    pchheader   "FrameworkPCH.h"
    pchsource   "Source/Framework/FrameworkPCH.cpp"

    includedirs {
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/Framework/**.cpp",
        "Source/Framework/**.h",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        "Source/ThirdParty/lib",
    }

    links {
        "opengl32",
        "glew32",
        "glfw3dll",
    }

      filter {}


------------------------------------------------------- Shaders project
project (ShaderProjectName)
    location (WorkingDirectory)
    kind "Utility"

    targetdir (WorkingDirectory.."/bin/" ..outputdir)
    objdir  (WorkingDirectory.."/bin-obj/")

    files{
        "Source/Data/Shaders/**.vert",
        "Source/Data/Shaders/**.frag",
    }


------------------------ Debug purpose all files project to view all files from withing VS
--project "ALL_FILES"
--    kind "none"
--    files{
--        "**.*"
--    }


-------------------------ThirdParty workspace to view ThirdParty code
workspace "ThirdParty"
    configurations  { "Debug", "Release" }
    location        (WorkingDirectory)
    startproject    "ThirdParty"

    filter "system:windows"
        platforms       { "x64" }
        characterset    "MBCS"

        defines{
            "WIN32",
            "WIN64",
            "_WINDOWS",
        }

project "ThirdParty"
    location (WorkingDirectory)
    kind "Utility"

    targetdir (WorkingDirectory.."/bin/" ..outputdir)
    objdir  (WorkingDirectory.."/bin-obj/")

    files{
        "Source/ThirdParty/**.h",
        "Source/ThirdParty/**.cpp",
    }