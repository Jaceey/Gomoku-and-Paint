#pragma once
/*!	\file		WindowsConsoleAPI.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Console class declaration.
		Contains all of the Console information - original and current
*/
#include <jact\XError.hpp>
#undef min
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#ifndef WINDOWSCONSOLEAPI_H
#define WINDOWSCONSOLEAPI_H
#endif // !WINDOWSCONSOLEAPI_H
using namespace std;
class Console
{
	//// System Data
public:
	WORD const FOREGROUND_BLACK = 0;
	WORD const FOREGROUND_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	WORD const BACKGROUND_BLACK = 0;
	WORD const BACKGROUND_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

	HANDLE hConsoleInput, hConsoleOutput;
	CONSOLE_SCREEN_BUFFER_INFO	originalCSBI;
	CONSOLE_CURSOR_INFO			originalCCI;
	vector<CHAR_INFO>			originalBuffer;
	COORD						originalBufferCoord;
	DWORD						originalConsoleMode;
	WORD						currentConsoleWidth = 0;
	SMALL_RECT bufferRect{ 0 };
	vector<char> originalTitle;

	WORD originalColour;

	DWORD consoleMode;
	DWORD numEvents;
	DWORD charsWritten;
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	DWORD consoleSize;
	COORD cursorHomeCoord{ 0,0 };

public:
	Console();
	void ResizeWindow(WORD width, WORD height);
	void SaveTitle();
	void SaveConsoleState();
	void HideTheCursor();
	void ShowTheCursor();
	void ReColourWindow();
	void RestoreWindow();

	void SetCursor(COORD coord);
	bool SetConsole();
	bool RestoreOriginal();
	COORD GetCursorLocation();

	void SetConsoleColour(WORD colour);
	void ReColourTextAttribute(HANDLE hOutput, DWORD size, COORD location, WORD colour);
	void ClearConsole();

};