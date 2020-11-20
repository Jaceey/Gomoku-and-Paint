#pragma once
/*!	\file		WindowsConsoleAPI.cpp
	\author		Jaceey Tuck
	\date		2019-02-18

	WindowsConsoleAPI class implementation
*/
#include <jact\WindowsConsoleAPI.hpp>

Console::Console()
{
	SaveConsoleState();
	originalTitle.resize(GetConsoleTitleA(originalTitle.data(), (DWORD)originalTitle.size()) + 1);	// +1 because theres always a null at the end of a C string
	originalTitle.shrink_to_fit();

	//hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	//hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(hConsoleOutput, &originalCSBI));

	originalColour = originalCSBI.wAttributes;

	// save the desktop
	originalBuffer.resize(originalCSBI.dwSize.X * originalCSBI.dwSize.Y);
	originalBufferCoord = COORD{ 0 };
	bufferRect.Right = originalCSBI.dwSize.X - 1;
	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(ReadConsoleOutputA(hConsoleOutput, originalBuffer.data(),
		originalCSBI.dwSize, originalBufferCoord, &bufferRect));

	THROW_IF_CONSOLE_ERROR(GetConsoleCursorInfo(hConsoleOutput, &originalCCI));

	consoleSize = sbi.dwSize.X*sbi.dwSize.Y;
}

void Console::SaveTitle()
{
	originalTitle.resize(GetConsoleTitleA(originalTitle.data(), (DWORD)originalTitle.size()) + 1);	// +1 because theres always a null at the end of a C string
	originalTitle.shrink_to_fit();
}

void Console::SaveConsoleState()
{
	hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(hConsoleOutput, &originalCSBI));

	// save the desktop
	originalBuffer.resize(originalCSBI.dwSize.X * originalCSBI.dwSize.Y);
	originalBufferCoord = COORD{ 0 };
	bufferRect.Right = originalCSBI.dwSize.X - 1;
	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(ReadConsoleOutputA(hConsoleOutput, originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, &bufferRect));

	THROW_IF_CONSOLE_ERROR(GetConsoleCursorInfo(hConsoleOutput, &originalCCI));
}

void Console::ResizeWindow(WORD width, WORD height)
{
	SMALL_RECT sr{ 0 };	// sets all four fields to 0
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hConsoleOutput, TRUE, &sr));

	COORD bufferSize;
	bufferSize.X = width;
	bufferSize.Y = height;
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(hConsoleOutput, bufferSize));

	THROW_IF_CONSOLE_ERROR(GetConsoleScreenBufferInfo(hConsoleOutput, &sbi));
	sr.Top = sr.Left = 0;
	width = std::min((SHORT)width, sbi.dwMaximumWindowSize.X);
	height = std::min((SHORT)height, sbi.dwMaximumWindowSize.Y);
	sr.Right = width - 1;
	sr.Bottom = height - 1;

	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hConsoleOutput, TRUE, &sr));
	currentConsoleWidth = sr.Right = sr.Left - 1;
	consoleSize = sbi.dwSize.X*sbi.dwSize.Y;
}

void Console::HideTheCursor()
{
	auto newCCI = originalCCI;
	newCCI.bVisible = FALSE;
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hConsoleOutput, &newCCI));
}

void Console::ShowTheCursor()
{
	auto newCCI = originalCCI;
	newCCI.bVisible = TRUE;
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hConsoleOutput, &newCCI));
}

void Console::ReColourWindow()
{
	FillConsoleOutputCharacterA(hConsoleOutput, ' ', consoleSize, cursorHomeCoord, &charsWritten);
	FillConsoleOutputAttribute(hConsoleOutput, BACKGROUND_WHITE, consoleSize, cursorHomeCoord, &charsWritten);
}

void Console::RestoreWindow()
{
	// Restore the original settings/size
	SMALL_RECT sr{ 0 };
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hConsoleOutput, TRUE, &sr));
	THROW_IF_CONSOLE_ERROR(SetConsoleScreenBufferSize(hConsoleOutput, originalCSBI.dwSize));
	THROW_IF_CONSOLE_ERROR(SetConsoleWindowInfo(hConsoleOutput, TRUE, &originalCSBI.srWindow));
	// Restore the desktop contents
	bufferRect = SMALL_RECT{ 0 };
	bufferRect.Right = originalCSBI.dwSize.X - 1;
	bufferRect.Bottom = originalCSBI.dwSize.Y - 1;
	THROW_IF_CONSOLE_ERROR(WriteConsoleOutputA(hConsoleOutput, originalBuffer.data(), originalCSBI.dwSize, originalBufferCoord, &bufferRect));
	SetConsoleTitleA(originalTitle.data());

	// Restore the cursor
	THROW_IF_CONSOLE_ERROR(SetConsoleCursorInfo(hConsoleOutput, &originalCCI));
	SetConsoleTextAttribute(hConsoleOutput, originalColour);
}

void Console::SetCursor(COORD coord)
{
	SetConsoleCursorPosition(hConsoleOutput, coord);
}

bool Console::SetConsole()
{
	return SetConsoleMode(hConsoleInput, consoleMode);
}

bool Console::RestoreOriginal()
{
	return SetConsoleMode(hConsoleInput, originalConsoleMode);
}

COORD Console::GetCursorLocation()
{;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &sbi))
	{
		return sbi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void Console::SetConsoleColour(WORD colour)
{
	SetConsoleTextAttribute(hConsoleOutput, colour);
}

void Console::ReColourTextAttribute(HANDLE hOutput, DWORD size, COORD location, WORD colour)
{
	FillConsoleOutputAttribute(hOutput, colour, size, location, &charsWritten);
}

void Console::ClearConsole()
{
	FillConsoleOutputCharacterA(hConsoleOutput, ' ', consoleSize, cursorHomeCoord, &charsWritten);
	FillConsoleOutputAttribute(hConsoleOutput, BACKGROUND_WHITE, consoleSize, cursorHomeCoord, &charsWritten);
}