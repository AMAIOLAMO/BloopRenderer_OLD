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
	template <typename T>
	void Log(const T& message) const
	{
		std::cout << message << std::endl;
	}

	/// <summary>
	/// Logs an error to the console
	/// </summary>
	template <typename T>
	void LogError(const T& errorOverview, const T& details) const
	{
		std::cout << errorOverview << ": " << details << std::endl;
	}

	/// <summary>
	/// Changes the Console's Color
	/// Returns if failed or not
	/// </summary>
	bool ChangeConsoleColor(int colorCode);

#pragma region Operation overloading

	template <typename T>
	const Logger& operator<<(const T& message) const
	{
		Log(message);
		return *this;
	}

#pragma endregion
};