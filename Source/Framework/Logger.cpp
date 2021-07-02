#include <FrameworkPCH.h>
#include <Logger.h>

std::ostream& operator<<(std::ostream& stream, const Logger::LogCategory& other)
{
	stream << other.GetName();
	return stream;
}

void Logger::LogMessage(const char* Category, LogVerbosity verbosity, const char* message)
{
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
	}

	std::cout << Category << ": " << message << WHITE_CONSOLE_TEXT << std::endl;
}

void FrameworkAPI Logger::LogMessage(LogVerbosity verbosity, const char* message)
{
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
	}

	std::cout << message << WHITE_CONSOLE_TEXT << std::endl;
}
