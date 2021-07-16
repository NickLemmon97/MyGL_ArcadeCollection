#pragma once
#include "Debugging.h"

//Debug logging
static const char* RED_CONSOLE_TEXT = "\33[31m";
static const char* WHITE_CONSOLE_TEXT = "\33[97m";
static const char* YELLOW_CONSOLE_TEXT = "\33[33m";
static const char* GREEN_CONSOLE_TEXT = "\33[32m";


enum class LogVerbosity
{
	Log = 0,
	Warning,
	Error,
	Success,
};

namespace Logger
{
	void LogMessage(const char* Category, LogVerbosity verbosity, const char* message);
	void LogMessage(LogVerbosity verbosity, const char* message);
};


#if defined EXECUTE_WITH_CONSOLE_VISIBLE
#define LOG_MESSAGE(type, verbosity, message) Logger::LogMessage(#type, verbosity, message);
#define quick_log(verb, message) Logger::LogMessage("QuickLog", LogVerbosity::verb, message);
#else
#define LOG_MESSAGE(type, verbosity, message);
#define quick_log(verb, message)
#endif

#ifdef DEBUG
#define DEBUG_LOG_MESSAGE(type, verbosity, message) Logger::LogMessage(#type, verbosity, message);
#else 
#define DEBUG_LOG_MESSAGE(type, verbosity, message)
#endif
