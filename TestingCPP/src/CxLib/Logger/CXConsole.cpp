#include "CXConsole.h"

Console::Console() :
	_hndConsole(GetStdHandle(STD_OUTPUT_HANDLE)) {}

bool Console::ChangeConsoleTitle(const std::wstring& titleName)
{
	return SetConsoleTitle(titleName.c_str());
}

bool Console::ChangeConsoleColor(const unsigned short colorCode) const
{
	return SetConsoleTextAttribute(_hndConsole, colorCode);
}
