#pragma once
#include "Debugging.h"

//Debug logging
#if !_HAS_CXX20
constexpr char* RED_CONSOLE_TEXT = "\33[31m";
constexpr char* WHITE_CONSOLE_TEXT = "\33[97m";
constexpr char* YELLOW_CONSOLE_TEXT = "\33[33m";
constexpr char* GREEN_CONSOLE_TEXT = "\33[32m";
#else
static const char* RED_CONSOLE_TEXT = "\33[31m";
static const char* WHITE_CONSOLE_TEXT = "\33[97m";
static const char* YELLOW_CONSOLE_TEXT = "\33[33m";
static const char* GREEN_CONSOLE_TEXT = "\33[32m";
#endif

enum class LogVerbosity
{
	Log = 0,
	Warning,
	Error,
	Success,
};

namespace Logger
{
	struct LogCategory {
	public:
		virtual const char* GetName() const = 0;
	};

	void FrameworkAPI LogMessage(const char* Category, LogVerbosity verbosity, const char* message);
	void FrameworkAPI LogMessage(LogVerbosity verbosity, const char* message);

	template<typename _Ty>
	void Log(LogVerbosity verbosity, const char* message)
	{
		LogMessage(_Ty::GetName(), verbosity, message);
	}

	template<typename _Ty>
	struct TLogCategory : public LogCategory {};
};


#if defined DEBUG
#define DECLARE_LOG_CATEGORY(cat) struct cat : public Logger::TLogCategory<cat>			\
{																						\
	public: static const char* GetName() { return #cat; }								\
};																						
#define DEFINE_LOG_CATEGORY(cat) struct cat : public Logger::TLogCategory<cat>;
#define DEBUG_LOG_MESSAGE(type, verbosity, message) Logger::Log<type>(verbosity, message);
#else
#define DECLARE_LOG_CATEGORY(cat) 																									
#define DEBUG_LOG_MESSAGE(type, verbosity, message)
#endif 

#if defined DEBUG
#define LOG_MESSAGE(type, verbosity, message) Logger::Log<type>(verbosity, message);
#else
#if defined EXECUTE_WITH_CONSOLE_VISIBLE
#define LOG_MESSAGE(type, verbosity, message) Logger::LogMessage(#type, verbosity, message);
#else
#define LOG_MESSAGE(type, verbosity, message);
#endif
#endif

