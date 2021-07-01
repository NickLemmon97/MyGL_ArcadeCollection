#pragma once
#include "../ProjectConfig.h"

//Debug logging
constexpr char* RED_CONSOLE_TEXT = "\33[31m";
constexpr char* WHITE_CONSOLE_TEXT = "\33[97m"; 
constexpr char* YELLOW_CONSOLE_TEXT = "\33[33m";


enum class FrameworkAPI LogVerbosity
{
	Log = 0,
	Warning,
	Error,
};


#ifdef _DEBUG
#define CHECK_FOR_MEMORY_LEAKS 1
#else
#define CHECK_FOR_MEMORY_LEAKS 0
#endif

#ifdef _DEBUG
#if CHECK_FOR_MEMORY_LEAKS
#define new   new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif 

