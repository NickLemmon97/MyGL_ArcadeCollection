/*
* Handle dll importing and exporting defines for windows systems
* 
* On linux, it seems as though they do not need to be defined as such
* 
* If I want to export it all as one project they need to be defined to nothing
*/

#if defined ALLONEPROJECT || defined _LINUX

#define GameAPI 
#define GameImpl 

#define AsteroidsAPI 
#define AsteroidsImpl

#define DeathRaceAPI 
#define DeathRaceImpl

#define TrialGameAPI 
#define TrialGameImpl

#define FrameworkAPI 
#define FrameworkImpl

#define BrickBreakAPI
#define BrickBreakImpl


#elif defined _WINDOWS

#define TrialGameAPI
#define TrialGameImpl

#ifdef GameDLLExport
#define GameAPI __declspec(dllexport)
#define GameImpl
#else
#define GameAPI __declspec(dllimport)
#define GameImpl extern
#endif

#ifdef DeathRaceDLLExport
#define DeathRaceAPI __declspec(dllexport)
#define DeathRaceImpl
#else
#define DeathRaceAPI __declspec(dllimport)
#define DeathRaceImpl extern
#endif

#ifdef AsteroidsDLLExport
#define AsteroidsAPI __declspec(dllexport)
#define AsteroidsImpl
#else
#define AsteroidsAPI __declspec(dllimport)
#define AsteroidsImpl extern
#endif

#ifdef BrickBreakDLLExport
#define BrickBreakAPI __declspec(dllexport)
#define BrickBreakImpl
#else
#define BrickBreakAPI __declspec(dllimport)
#define BrickBreakImpl extern
#endif

#ifdef FrameworkDLLExport
#define FrameworkAPI __declspec(dllexport)
#define FrameworkImpl 
#else
#define FrameworkAPI __declspec(dllimport)
#define FrameworkImpl extern
#endif

#endif
