#pragma once

#include <iostream>
#include <string>
#include <Windows.h>
#include <wincon.h>

/// <summary>
/// A simple Console helper that helps with all the console stuff
/// </summary>
class Console
{
private:
	HANDLE _hndConsole;

public:
	/// <summary>
	/// an end line character '\n'
	/// </summary>
	static const char endl = '\n';
	/// <summary>
	/// an tab character '\t'
	/// </summary>
	static const char tab =  '\t';

	static const int BLUE          = 0x0001;
	static const int GREEN         = 0x0002;
	static const int RED           = 0x0003;

	static const int INTENSITY     = 0x0080;

	static const int REVERSE_VIDEO = 0x4000;
	static const int UNDERSCORE    = 0x8000;

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

	/// <summary>
	/// Raw logs to the console
	/// </summary>
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
