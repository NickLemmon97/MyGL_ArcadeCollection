------------------------------------------------ Globals
-- Directoory names
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

GameOutputDir = (WorkingDirectory.."/bin/" ..outputdir.. "/Game")

--Name of the current game project
GameName = "ArcadeCollection"

--Project names as a variable
WorkspaceName            = "OpenGLFramework"

ProjectConfigProjectName = "1. Project Config"
ShaderProjectName        = "2. Shaders"

--A global to show where the third party libraries are for your system
ThirdPartyLibFolder = "Source/ThirdParty/lib"

--All configuration settings
files{
    "Source/ProjectConfig.h",
}

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
    objdir  (WorkingDirectory.."/bin-obj/")

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
    objdir  (WorkingDirectory.."/bin-obj/")

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
    "Source/Game",
    "Source/Game/Core",
    "Source/ThirdParty/include",
}

files {
    "Source/main.cpp",
    "Source/Framework/**.cpp",
    "Source/Framework/**.h",
    "Source/Game/**.cpp",
    "Source/Game/**.h",
}

targetdir (GameOutputDir)
objdir  (WorkingDirectory.."/bin-obj/")

libdirs{
    (ThirdPartyLibFolder),
}

links {
    "opengl32",
    "glew32",
    "glfw3dll",
    "Winmm",
}

postbuildcommands{
    ("{COPY} %{prj.location}../Source/Data %{prj.location}bin/"..outputdir.."/Game/Data"),
    ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glew32.dll %{cfg.targetdir}/"),
    ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glfw3.dll %{cfg.targetdir}/"),
}

filter {}
