#include "Logger.h"

Console::Console() :
	hndConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

bool Console::ChangeConsoleTitle(const std::wstring& titleName)
{
	return SetConsoleTitle(titleName.c_str());
}

bool Console::ChangeConsoleColor(int colorCode)
{
	return SetConsoleTextAttribute(hndConsole, colorCode);
}