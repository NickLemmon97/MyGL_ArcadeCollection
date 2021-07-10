
/*
* Export defines for exporting and importing DLL functions on windows
*/
#ifdef _WINDOWS

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

#ifdef FrameworkDLLExport
#define FrameworkAPI __declspec(dllexport)
#define FrameworkImpl 
#else
#define FrameworkAPI __declspec(dllimport)
#define FrameworkImpl extern
#endif

#endif

/*
* In basic research, linux doesn't do the __declspec so define these as nothing 
*/
#ifdef _LINUX
#define GameAPI 
#define GameImpl 

#define FrameworkAPI 
#define FrameworkImpl
#endif
