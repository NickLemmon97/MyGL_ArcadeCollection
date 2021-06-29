#pragma once


//Debug logging
constexpr char* RED_CONSOLE_TEXT = "\33[31m";
constexpr char* WHITE_CONSOLE_TEXT = "\33[97m"; 
constexpr char* YELLOW_CONSOLE_TEXT = "\33[33m";


enum class LogVerbosity
{
	Log = 0,
	Warning,
	Error,
};


#define CHECK_FOR_MEMORY_LEAKS 1

#ifdef _DEBUG
#if CHECK_FOR_MEMORY_LEAKS
#define new   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif 
