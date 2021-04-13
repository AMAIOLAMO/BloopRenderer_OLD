#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

/// <summary>
/// A simple logger that helps you log stuff pretty quick and easy
/// </summary>
class Logger
{
private:
	HANDLE hndConsole;

public:
	Logger();

	/// <summary>
	/// Logs a messages to the console
	/// </summary>
	void Log(const std::string& message) const;

	/// <summary>
	/// Logs an error to the console
	/// </summary>
	void LogError(const std::string& errorOverview, const std::string& details) const;

	/// <summary>
	/// Changes the Console's Color
	/// Returns if failed or not
	/// </summary>
	bool ChangeConsoleColor(int colorCode);

#pragma region Operation overloading

	Logger& operator<<(const std::string& message);

#pragma endregion
};