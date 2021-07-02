#pragma once
#include "Debugging.h"

//Debug logging
#if !_HAS_CXX20
constexpr char* RED_CONSOLE_TEXT = "\33[31m";
constexpr char* WHITE_CONSOLE_TEXT = "\33[97m";
constexpr char* YELLOW_CONSOLE_TEXT = "\33[33m";
//constexpr char* GREEN_CONSOLE_TEXT = "\33[33m";
#else
const char* RED_CONSOLE_TEXT = "\33[31m";
const char* WHITE_CONSOLE_TEXT = "\33[97m";
const char* YELLOW_CONSOLE_TEXT = "\33[33m";
//const char* GREEN_CONSOLE_TEXT = "\33[33m";
#endif

enum class LogVerbosity
{
	Log = 0,
	Warning,
	Error,
};

namespace Logger
{
	struct LogCategory {
	public:
		virtual const char* GetName() const = 0;
	};

	template<typename _Ty>
	struct TLogCategory : public LogCategory {};

	void FrameworkAPI LogMessage(const char* Category, LogVerbosity verbosity, const char* message);
	void FrameworkAPI LogMessage(LogVerbosity verbosity, const char* message);

	template<typename _Ty>
	void Log(LogVerbosity verbosity, const char* message)
	{
		LogMessage(_Ty::GetName(), verbosity, message);
	}
};

#ifdef DEBUG

#define DECLARE_LOG_CATEGORY(cat) struct cat : public Logger::TLogCategory<cat>			\
{																						\
	public: static const char* GetName() { return #cat; }								\
};																																		
#define DEBUG_LOG_MESSAGE(type, verbosity, message) Logger::Log<type>(verbosity, message);

#else

#define DECLARE_LOG_CATEGORY(cat) 																									
#define DEBUG_LOG_MESSAGE(type, verbosity, message) 

#endif // DEBUG