#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

/// <summary>
/// A simple Console helper that helps with all the console stuff
/// </summary>
class Console
{
private:
	HANDLE hndConsole;

public:
	/// <summary>
	/// an end line character '\n'
	/// </summary>
	static const char endl = '\n';

public:
	Console();

	/// <summary>
	/// Logs a messages to the console
	/// </summary>
	template <typename T>
	void Log(const T& message) const
	{
		std::cout << message << std::endl;
	}

	template <typename T>
	void RawLog(const T& message) const
	{
		std::cout << message;
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
	/// Changes the console's title
	/// </summary>
	bool ChangeConsoleTitle(const std::wstring& titleName);

	/// <summary>
	/// Changes the Console's Color
	/// Returns if failed or not
	/// </summary>
	bool ChangeConsoleColor(int colorCode);

#pragma region Operation overloading

	/// <summary>
	/// Raw logs to the console
	/// </summary>
	template <typename T>
	const Console& operator<<(const T& message) const
	{
		std::cout << message;
		return *this;
	}

#pragma endregion
};