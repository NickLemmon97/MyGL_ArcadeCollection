------------------------------------------------ Globals
-- Directoory names
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GameOutputDir = (WorkingDirectory.."/bin/" ..outputdir.. "/Game")
LibOutputDir  = (WorkingDirectory.."/bin/" ..outputdir.. "/Lib")

--Name of the current game project
GameName = "ArcadeCollection"

--Project names as a variable
WorkspaceName            = "OpenGLFramework"

ProjectConfigProjectName = "1. Project Config"
ShaderProjectName        = "2. Shaders"

--A global to show where the third party libraries are for your system
ThirdPartyIncludeFolder = "Source/ThirdParty/include"
ThirdPartyLibFolder     = "Source/ThirdParty/lib"

--All configuration settings
objdir  (WorkingDirectory.."/bin-obj/")

files{
    "Source/ProjectConfig.h",
}

-- Universal project filters
filter "system:windows"
       cppdialect "C++17"
       systemversion "latest"
       disablewarnings { "4251" }

filter "configurations:Debug"
       defines { "DEBUG", "_DEBUG", "EXECUTE_WITH_CONSOLE_VISIBLE"}
       symbols "On"

filter "configurations:Development"
       defines {"DEVELOPMENT", "EXECUTE_WITH_CONSOLE_VISIBLE"}
       optimize "On"

filter "configurations:ReleaseConsole"
       defines { "CONSOLE_RELEASE", "STANDALONE", "EXECUTE_WITH_CONSOLE_VISIBLE" }
       optimize "On"
       symbols "Off"

filter {}

------------------------------------------------ Solution
workspace (WorkspaceName)
    configurations  { "Debug", "ReleaseConsole", "Development"}
    location        (WorkingDirectory)
    startproject    (GameName)

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
        "README.md",
    }

    targetdir (GameOutputDir)

    filter "system:windows"
        postbuildcommands{
            "cd ..",
            "PremakeGenerateBuildFiles.bat",
        }


------------------------------------------------------- Shaders project
project (ShaderProjectName)
    location (WorkingDirectory)
    kind "Utility"

    targetdir (WorkingDirectory.."/bin/" ..outputdir)

    files{
        "Source/Data/Shaders/**.vert",
        "Source/Data/Shaders/**.frag",
    }


------------------------------------------------ An all in 1 project since DLLS are cool but I wanted to see 1 main exe
project (GameName)
location    (WorkingDirectory)
debugdir    "Source"
kind        "ConsoleApp"
language    "C++"
defines     {"ALLONEPROJECT"}


includedirs {
    "Source/Framework",
    "Source/Framework/ThirdParty",
    "Source/Game",
    "Source/Game/Core",
    (ThirdPartyIncludeFolder),
}

files {
    "Source/main.cpp",
    "Source/AppInitializer.*",
    "Source/Game/**.cpp",
    "Source/Game/**.h",
    "Source/Framework/**.*",
}

targetdir (GameOutputDir)

libdirs{
    (ThirdPartyLibFolder),
    (LibOutputDir),
}

links {
    "Winmm",    --For calling Playsound on windows
    
    "opengl32",
    "glew32",
    "glfw3dll",
}

postbuildcommands{
    ("{COPY} %{prj.location}../Source/Data %{prj.location}bin/"..outputdir.."/Game/Data"),
    ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glew32.dll %{cfg.targetdir}/"),
    ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glfw3.dll %{cfg.targetdir}/"),
}

filter {}
