/*
* Handle dll importing and exporting defines for windows systems
* 
* On linux, it seems as though they do not need to be defined as such
* If I want to export it all as one project it doesn't need to be defined either
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

#elif defined _WINDOWS

#ifdef GameDLLExport
#define GameAPI __declspec(dllexport)
#define GameImpl
#else
#define GameAPI __declspec(dllimport)
#define GameImpl extern
#endif

#ifdef TrialGameDLLExport
#define TrialGameAPI __declspec(dllexport)
#define TrialGameImpl
#else	
#define TrialGameAPI __declspec(dllimport)
#define TrialGameImpl extern
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

#ifdef FrameworkDLLExport
#define FrameworkAPI __declspec(dllexport)
#define FrameworkImpl 
#else
#define FrameworkAPI __declspec(dllimport)
#define FrameworkImpl extern
#endif

#endif
