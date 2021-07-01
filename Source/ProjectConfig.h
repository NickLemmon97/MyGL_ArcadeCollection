
/*
* Export defines for exporting and importing DLL functions
*/
#ifdef GameDLLExport
#define GameAPI __declspec(dllexport)
#else
#define GameAPI __declspec(dllimport)
#endif

#ifdef FrameworkDLLExport
#define FrameworkAPI __declspec(dllexport)
#define FrameworkImpl 
#else
#define FrameworkAPI __declspec(dllimport)
#define FrameworkImpl extern
#endif
