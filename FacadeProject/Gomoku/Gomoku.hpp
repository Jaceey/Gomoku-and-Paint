#pragma once
/*!	\file		Gomoku.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Gomoku class declaration.
		Contains Gomoku specific application code.

*/
#include "CoordLocation.hpp"
#include <jact/ConsoleAPIFacade.hpp>

#ifndef GOMOKU_H
#define GOMOKU_H
#endif // !GOMOKU_H

class Gomoku
{
public:
	WORD const FOREGROUND_BLACK = 0;
	WORD const FOREGROUND_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	WORD const BACKGROUND_BLACK = 0;
	WORD const BACKGROUND_WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

	WORD background;

	WORD const WINDOW_WIDTH = 100;
	WORD const WINDOW_HEIGHT = 40;

	ConsoleAPIFacade con;
	vector<CoordLocationInfo> screenLocations;
	vector<CoordLocationInfo> moveLocations;

	string win;
	int Player1run = 0;
	int Player2run = 0;
	int totalPieces = 0;

	string Player1Name = "";
	string Player2Name = "";

	bool Player1Turn = true;

	WORD PrevP1Colour = BACKGROUND_RED;
	WORD PrevP2Colour = BACKGROUND_BLACK;
	WORD Player1Colour = BACKGROUND_RED;
	WORD Player2Colour = BACKGROUND_BLACK;

	WORD Player1Foreground = FOREGROUND_RED;
	WORD Player2Foreground = FOREGROUND_GREEN;

	DWORD charsWritten;
	COORD cursorHomeCoord{ 0,0 };
	COORD currentCursor;

public:
	Gomoku() {
		background = BACKGROUND_RED;
		win = "No win";
		con.SaveConsole();
		con.SetUpConsole(WINDOW_WIDTH, WINDOW_HEIGHT, "Gomoku Application");
		DrawPlayerBar();
		DrawScoreboard();
		DrawBoard();
		DrawMoveScroll();
		DrawControls();
		con.ConfigConsole();
	};

	string IsWinner();
	void OutputWin(string win);
	void MouseEventProc(MOUSE_EVENT_RECORD const& mer);
	void KeyEventProc(KEY_EVENT_RECORD const& ker);
	void DrawBoard();
	void DrawPlayerBar();
	void DrawMoveScroll();
	void DrawControls();
	void OutputMoves();
	void DrawScoreboard();
	void OutputBoard();
	void RemoveLastMove();
};