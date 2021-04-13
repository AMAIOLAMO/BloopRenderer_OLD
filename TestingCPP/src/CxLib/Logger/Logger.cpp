#include "Logger.h"

Logger::Logger() :
	//get handle in console for more control on the console
	hndConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

void Logger::Log(const std::string& message) const
{
	std::cout << message << std::endl;
}

void Logger::LogError(const std::string& errorOverview, const std::string& details) const
{
	Log(errorOverview + ": " + details);
}

bool Logger::ChangeConsoleColor(int colorCode)
{
	return SetConsoleTextAttribute(hndConsole, colorCode);
}

#pragma region Operation overloading

Logger& Logger::operator<<(const std::string& message)
{
	Log(message);
	return *this;
}

#pragma endregion
