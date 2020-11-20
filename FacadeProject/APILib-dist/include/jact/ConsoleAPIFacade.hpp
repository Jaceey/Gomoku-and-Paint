#pragma once
/*!	\file		ConsoleAPIFacade.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	ConsoleAPIFacade class declaration.
		Outer Facade.

*/
#include <jact/WindowsConsoleAPI.hpp>

#ifndef CONSOLEAPIFACADE_H
#define CONSOLEAPIFACADE_H
#endif // !CONSOLEAPIFACADE_H

class ConsoleAPIFacade {
	Console console;

public:
	ConsoleAPIFacade() {}

	void ConfigConsole()
	{
		GetConsoleMode(console.hConsoleInput, &console.originalConsoleMode);
		console.consoleMode = ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT;
		console.consoleMode |= ENABLE_EXTENDED_FLAGS;
	}

	void SaveConsole()
	{
		console.SaveTitle();
		console.SaveConsoleState();
	}

	void SetUpConsole(WORD Width, WORD Height, LPCSTR Title)
	{
		SetConsoleTitleA(Title);
		console.ResizeWindow(Width, Height);
		console.ReColourWindow();
		console.HideTheCursor();
	}

	void HideCursor()
	{
		console.HideTheCursor();
	}

	void ShowCursor()
	{
		console.ShowTheCursor();
	}

	BOOL SetConsole()
	{
		return console.SetConsole();
	}

	BOOL RestoreOriginal()
	{
		return console.RestoreOriginal();
	}

	void RestoreConsole()
	{
		console.RestoreWindow();
	}

	HANDLE GetConsoleInput()
	{
		return console.hConsoleInput;
	}

	HANDLE GetConsoleOutput()
	{
		return console.hConsoleOutput;
	}

	DWORD GetConsoleSize()
	{
		return console.consoleSize;
	}

	void SetTextAttribute(WORD colour)
	{
		console.SetConsoleColour(colour);
	}

	void ReColourTextAttribute(HANDLE hOutput, DWORD size, COORD location, WORD colour)
	{
		console.ReColourTextAttribute(hOutput, size, location, colour);
	}

	void ClearConsole()
	{
		console.ClearConsole();
	}

	COORD GetConsoleCursorPosition()
	{
		return console.GetCursorLocation();
	}

	void SetCursor(COORD coord)
	{
		console.SetCursor(coord);
	}

};