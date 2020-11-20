#pragma once
/*!	\file		Paint.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Paint class declaration.
		Contains paint specific application code
*/
#include <jact/ConsoleAPIFacade.hpp>

#ifndef PAINT_H
#define PAINT_H
#endif // !PAINT_H

class Paint
{
public:
	WORD const FOREGROUND_BLACK = 0;
	WORD const FOREGROUND_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	WORD const BACKGROUND_BLACK = 0;
	WORD const BACKGROUND_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

	WORD background;

	//WORD const WINDOW_WIDTH = 100;
	WORD const WINDOW_WIDTH = 40;
	WORD const WINDOW_HEIGHT = 40;

	ConsoleAPIFacade con;

public:
	Paint() {
		background = (BACKGROUND_INTENSITY | BACKGROUND_RED);
		con.SaveConsole();
		con.SetUpConsole(WINDOW_WIDTH, WINDOW_HEIGHT, "Paint Application");
		DrawPalette();
		con.ConfigConsole();
	};

	void MouseEventProc(MOUSE_EVENT_RECORD const& mer);
	void KeyEventProc(KEY_EVENT_RECORD const& ker);
	void DrawPalette();
};