------------------------------------------------ Globals
-- Directoory names
WorkingDirectory = "build"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

DLL_LibOutput =  ("/bin/" ..outputdir.. "/Libs")

GameOutputDir = (WorkingDirectory.."/bin/" ..outputdir.. "/Game")

--project flags
UseLuaGame = false;

--Name of the current game project
GameName = "Game"

--Project names as a variable
WorkspaceName            = "OpenGLFramework"
if _ACTION == "gmake2" then
ProjectConfigProjectName = "proj"
ShaderProjectName        = "shade"
ApplicationProjectName   = "Player"
FrameworkProjectName     = "Framework"
GameProjectName          = (GameName)
else --Order them for a nicer finding of projects while in VS ~
ProjectConfigProjectName = "1. Project Config"
ShaderProjectName        = "2. Shaders"
ApplicationProjectName   = "3. Player"
FrameworkProjectName     = "4. Framework"
GameProjectName          = ("5. "..GameName)
end

--A global to show where the third party libraries are for your system
ThirdPartyLibFolder = "";

--All configuration settings
files{
    "Source/ProjectConfig.h",
}

if _ACTION == "gmake2" then 
    defines {"TEMP_DONT_USE"}
end

filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        ThirdPartyLibFolder = "Source/ThirdParty/lib"

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

if _ACTION ~= "gmake2" then
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

    --If on windows we are most likely using a visual studio project 
    --Created since I can't right click and run a bat file in vs
    filter "system:windows"
        postbuildcommands{
            "cd ..",
            "PremakeGenerateBuildFiles.bat",
        }

end

------------------------------------------------ Main Executable Project
project (ApplicationProjectName)
    targetname  "Player"
    location    (WorkingDirectory)
    debugdir    (WorkingDirectory.."/bin/" ..outputdir.. "/Game")
    kind        "ConsoleApp"
    language    "C++"

    if _ACTION == gmake2 then
    dependson{
       (FrameworkProjectName),
       (GameProjectName),
    }
    end
    
    includedirs {
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    if (UseLuaGame) then includedirs {"Source/LuaGame"}
    else includedirs {"Source/Game"}
    end

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
    }
--TODO FIND SEARCH
if _ACTION ~= "gmake2" then
    postbuildcommands{
        ("{COPY} %{prj.location}../Source/Data %{prj.location}bin/"..outputdir.."/Game/Data"),
        ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glew32.dll %{cfg.targetdir}/"),
        ("{COPY} %{prj.location}../"..(ThirdPartyLibFolder).."/glfw3.dll %{cfg.targetdir}/"),
    }

    filter "configurations:Debug"
        postbuildcommands{
          ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/ %{cfg.targetdir}/"),
        }
end

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


if UseLuaGame == false then
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
        "Source/Game/**.cpp",
        "Source/Game/**.h",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
    }
if _ACTION ~= "gmake2" then
    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll bin/" ..outputdir.. "/Game"),
    }
end
    filter {}

else
------------------------------------------------ Lua Game Project
project (GameProjectName.."Lua")
    targetname  (GameName)
    location    (WorkingDirectory)
    kind        "SharedLib"
    language    "C++"
    defines     {"GameDLLExport"}
    pchheader   "GamePCH.h"
    pchsource   "Source/LuaGame/GamePCH.cpp"
    
    includedirs {
        "Source/LuaGame",
        "Source/LuaGame/Core",
        "Source/Framework",
        "Source/ThirdParty/include",
    }

    files {
        "Source/LuaGame/**.cpp",
        "Source/LuaGame/**.h",
        "Source/Data/LuaScripts/**.lua",
    }

    targetdir (WorkingDirectory..DLL_LibOutput)
    objdir  (WorkingDirectory.."/bin-obj/")

    libdirs{
        (ThirdPartyLibFolder),
        (WorkingDirectory..DLL_LibOutput),
    }

    links {
        "Framework",
        "lua54",
    }

    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/"..GameName..".dll bin/" ..outputdir.. "/Game"),
       ("{COPY} %{prj.location}../Source/ThirdParty/lib/lua54.dll bin/" ..outputdir.. "/Game"),
       ("{COPY} %{prj.location}../Source/Data/LuaScripts %{prj.location}bin/"..outputdir.."/Game/Data/LuaScripts"),
    }

    filter {}

end

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
if _ACTION ~= "gmake2" then
    postbuildcommands{
      ("{COPY} %{prj.location}bin/"..outputdir.."/Libs/Framework.dll bin/"..outputdir.."/Game"),
    }
end
    filter {}


if _ACTION ~= "gmake2" then
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
end

------------------------ Debug purpose all files project to view all files from withing VS
--project "ALL_FILES"
--    kind "none"
--    files{
--        "**.*"
--    }

GenThirdPartyWorkspace = false

if (GenThirdPartyWorkspace ) then

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

end