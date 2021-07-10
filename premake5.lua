------------------------------------------------ Globals
-- Directoory names
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

DLL_LibOutput =  ("/bin/" ..outputdir.. "/Libs")

GameOutputDir = (WorkingDirectory.."/bin/" ..outputdir.. "/Game")


--Name of the current game project
GameName = "Game"

--Project names as a variable
WorkspaceName            = "OpenGLFramework"

ProjectConfigProjectName = "1. Project Config"
ShaderProjectName        = "2. Shaders"
ApplicationProjectName   = "3. Player"
FrameworkProjectName     = "4. Framework"
GameProjectName          = ("5. "..GameName)

DeathRace = "DeathRace"
Asteroids = "Asteroids"

--A global to show where the third party libraries are for your system
ThirdPartyLibFolder = "Source/ThirdParty/lib"

--All configuration settings
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
        symbols "Off"

------------------------------------------------ Solution
workspace (WorkspaceName)
    configurations  { "Debug", "ReleaseConsole", "Development"}
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

    targetdir (GameOutputDir)
    objdir  (WorkingDirectory.."/bin-obj/")

    filter "system:windows"
        postbuildcommands{
            "cd ..",
            "PremakeGenerateBuildFiles.bat",
        }


------------------------------------------------ Main Executable Project
project (ApplicationProjectName)
    targetname  "Player"
    location    (WorkingDirectory)
    debugdir    "Source"
    kind        "ConsoleApp"
    language    "C++"
    
    includedirs {
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    includedirs {"Source/Game"}
    
    dependson{
        (FrameworkProjectName),
        (GameProjectName),
        (DeathRace),
        "TrialGame",
    }

    files {
        "Source/main.cpp",
    }

    targetdir (GameOutputDir)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
        (GameName),
        (DeathRace),
        "TrialGame",
    }

    postbuildcommands{
        ("{COPY} %{prj.location}../Source/Data %{prj.location}bin/"..outputdir.."/Game/Data"),
        ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glew32.dll %{cfg.targetdir}/"),
        ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glfw3.dll %{cfg.targetdir}/"),
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

    dependson {
        (FrameworkProjectName),
    }
    
    includedirs {
        "Source/Game",
        "Source/Game/Core",
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/Game/Core/**.cpp",
        "Source/Game/Core/**.h",
        "Source/Game/GamePCH.cpp",
        "Source/Game/GamePCH.h",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
    }

    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll bin/" ..outputdir.. "/Game"),
    }

    filter {}

------------------------------------------------ DeathRace Project
project (DeathRace)
    targetname  (DeathRace)
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
    defines     {"DeathRaceDLLExport"}

    dependson {
        (FrameworkProjectName),
    }
    
    includedirs {
        "Source/Game",
        "Source/Game/Core",
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/Game/DeathRace/**.cpp",
        "Source/Game/DeathRace/**.h",
        "Source/Game/GamePCH.cpp",
        "Source/Game/GamePCH.h",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
        "Game",
    }

    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..DeathRace..".dll bin/" ..outputdir.. "/Game"),
    }

    filter {}

    ------------------------------------------------ DeathRace Project
project "TrialGame"
    targetname  "TrialGame"
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
    defines     {"TrialGameDLLExport"}

    dependson {
        (FrameworkProjectName),
        (GameProjectName),
    }
    
    includedirs {
        "Source/Game",
        "Source/Game/Core",
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/Game/Trial/**.cpp",
        "Source/Game/Trial/**.h",
        "Source/Game/GamePCH.cpp",
        "Source/Game/GamePCH.h",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
        "Game",
    }

    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/TrialGame.dll bin/" ..outputdir.. "/Game"),
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
        (ThirdPartyLibFolder),
    }

    links {
        "opengl32",
        "glew32",
        "glfw3dll",
    }

    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll bin/"..outputdir.."/Game"),
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
