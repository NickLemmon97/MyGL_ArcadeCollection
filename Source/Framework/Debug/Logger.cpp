#include <FrameworkPCH.h>
#include "Logger.h"

std::ostream& operator<<(std::ostream& stream, const Logger::LogCategory& other)
{
	stream << other.GetName();
	return stream;
}

void Logger::LogMessage(const char* Category, LogVerbosity verbosity, const char* message)
{
#if defined _WINDOWS
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (verbosity)
	{
	case LogVerbosity::Log:
		SetConsoleTextAttribute(hConsole, 15);
		break;

	case LogVerbosity::Warning:
		SetConsoleTextAttribute(hConsole, 14);
		break;

	case LogVerbosity::Error:
		SetConsoleTextAttribute(hConsole, 12);
		break;

	case LogVerbosity::Success:
		SetConsoleTextAttribute(hConsole, 10);
		break;
	}
#else
	switch (verbosity)
	{
	case LogVerbosity::Log:
		std::cout << WHITE_CONSOLE_TEXT;
		break;

	case LogVerbosity::Warning:
		std::cout << YELLOW_CONSOLE_TEXT;
		break;

	case LogVerbosity::Error:
		std::cout << RED_CONSOLE_TEXT;
		break;
	case LogVerbosity::Success:
		std::cout << GREEN_CONSOLE_TEXT;
		break;
	}
#endif

	std::cout << Category << ": " << message << std::endl;

#if defined _WINDOWS
		SetConsoleTextAttribute(hConsole, 15);
#else
	std::cout << WHITE_CONSOLE_TEXT;
#endif

}

void FrameworkAPI Logger::LogMessage(LogVerbosity verbosity, const char* message)
{
	LogMessage("", verbosity, message);
}
