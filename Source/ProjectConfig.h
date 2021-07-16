/*
* Handle dll importing and exporting defines
*/

#if defined ALLONEPROJECT || defined _LINUX

#define GameAPI 
#define GameImpl 

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

#ifdef FrameworkDLLExport
#define FrameworkAPI __declspec(dllexport)
#define FrameworkImpl 
#else
#define FrameworkAPI __declspec(dllimport)
#define FrameworkImpl extern
#endif

#endif
