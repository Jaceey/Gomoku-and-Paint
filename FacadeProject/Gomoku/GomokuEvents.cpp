/*!	\file		GomokuEvents.cpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Gomoku class implementation
		Contains Gomoku specific Event processing code

*/

#include "Gomoku.hpp"

void Gomoku::MouseEventProc(MOUSE_EVENT_RECORD const& mer)
{
	DWORD temp = mer.dwButtonState;
	DWORD consoleSize = con.GetConsoleSize();
	HANDLE consoleOutput = con.GetConsoleOutput();
	COORD cursorLocation;

	switch (mer.dwEventFlags) {
	case 0: // button pressed or released
	{
		if (win != "No win") break;

		auto mask = mer.dwButtonState;
		auto bufferLoc = mer.dwMousePosition;

		if (mask&FROM_LEFT_1ST_BUTTON_PRESSED)
		{
#pragma region PlayerNameClick
			// Check if click was in the Player 1 name box location
			if (bufferLoc.X > 11 && bufferLoc.X < 32 && bufferLoc.Y == 1)
			{
				if (Player1Name != "")
				{
					// Reset name on click
					Player1Name = "";
					DrawPlayerBar();
				}
				// Set cursor to beginning of box
				cursorLocation.X = 12;
				cursorLocation.Y = 1;
				con.SetCursor(cursorLocation);
				currentCursor = cursorLocation;
				con.ShowCursor();

			}
			// Check if click was in the Player 2 name box location
			else if (bufferLoc.X > 55 && bufferLoc.X < 75 && bufferLoc.Y == 1)
			{
				if (Player2Name != "")
				{
					// Reset name on click
					Player2Name = "";
					DrawPlayerBar();
				}
				// Set cursor to beginning of box
				cursorLocation.X = 56;
				cursorLocation.Y = 1;
				con.SetCursor(cursorLocation);
				currentCursor = cursorLocation;
				con.ShowCursor();
			}
#pragma endregion
			// Check if click was in the second row
			else if (bufferLoc.Y == 1)
			{
#pragma region PlayerColourClick
				con.HideCursor();
				currentCursor = { 0,0 };
				// Check locations of all Player 1 colours
				if (bufferLoc.X == 33)
				{
					PrevP1Colour = Player1Colour;
					Player1Colour = BACKGROUND_INTENSITY | BACKGROUND_RED;
					Player1Foreground = FOREGROUND_INTENSITY | FOREGROUND_RED;
				}
				else if (bufferLoc.X == 35)
				{
					PrevP1Colour = Player1Colour;
					Player1Colour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE;
					Player1Foreground = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE;
				}
				else if (bufferLoc.X == 37)
				{
					PrevP1Colour = Player1Colour;
					Player1Colour = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN;
					Player1Foreground = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN;
				}
				// Check locations of all Player 2 colours
				else if (bufferLoc.X == 77)
				{
					PrevP2Colour = Player2Colour;
					Player2Colour = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
					Player2Foreground = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
				}
				else if (bufferLoc.X == 79)
				{
					PrevP2Colour = Player2Colour;
					Player2Colour = BACKGROUND_RED | BACKGROUND_BLUE;
					Player2Foreground = FOREGROUND_RED | FOREGROUND_BLUE;
				}
				else if (bufferLoc.X == 81)
				{
					PrevP2Colour = Player2Colour;
					Player2Colour = BACKGROUND_GREEN;
					Player2Foreground = FOREGROUND_GREEN;
				}
#pragma endregion

				OutputMoves();
				OutputBoard();
			}
			else
			{
				con.HideCursor();
				currentCursor = { 0,0 };

#pragma region MoveClicks
				// Check that the click was within the Gomoku board
				if (bufferLoc.X >= 8 && bufferLoc.Y >= 7 && bufferLoc.X <= 65 && bufferLoc.Y <= 35)
				{
					for (auto it = screenLocations.begin(); it != screenLocations.end(); it++)
					{
						COORD loc = it->get_coord();
						// Check if clicked on the left half of the gomoku pieces
						if (loc.X == bufferLoc.X && loc.Y == bufferLoc.Y)
						{
							if (it->get_background() == (BACKGROUND_BLUE | BACKGROUND_GREEN))
							{
								totalPieces++;
								// Check whos turn it is
								if (Player1Turn)
								{
									con.ReColourTextAttribute(consoleOutput, 2, mer.dwMousePosition, Player1Colour);
									it->set_background(Player1Colour);
								}
								else
								{
									con.ReColourTextAttribute(consoleOutput, 2, mer.dwMousePosition, Player2Colour);
									it->set_background(Player2Colour);
								}
								// Save move information to output
								CoordLocationInfo move;
								move.set_background(it->get_background());
								COORD moveCoord = it->get_boardlocation();
								move.set_boardlocation(moveCoord.X, moveCoord.Y);
								move.set_coord(bufferLoc.X, bufferLoc.Y);
								moveLocations.push_back(move);
								// Change players turn
								Player1Turn = !Player1Turn;
								break;
							}
						}	// Check if clicked on the right half of the gomoku pieces
						else if (loc.X + 1 == bufferLoc.X && loc.Y == bufferLoc.Y)
						{
							if (it->get_background() == (BACKGROUND_BLUE | BACKGROUND_GREEN))
							{
								totalPieces++;
								bufferLoc.X -= 1;
								// Check whos turn it is
								if (Player1Turn)
								{
									con.ReColourTextAttribute(consoleOutput, 2, bufferLoc, Player1Colour);
									it->set_background(Player1Colour);
								}
								else
								{
									con.ReColourTextAttribute(consoleOutput, 2, bufferLoc, Player2Colour);
									it->set_background(Player2Colour);
								}

								// Save move information to output
								CoordLocationInfo move;
								move.set_background(it->get_background());
								COORD moveCoord = it->get_boardlocation();
								move.set_boardlocation(moveCoord.X, moveCoord.Y);
								move.set_coord(bufferLoc.X, bufferLoc.Y);
								moveLocations.push_back(move);

								// Change players turn
								Player1Turn = !Player1Turn;
								break;
							}
						}
					}
					win = IsWinner();
				}
#pragma endregion

				OutputMoves();

				if (win != "No win")
				{
					OutputWin(win);
				}
				else
					break;
			}
		}
		break;

	}
	}

}

void Gomoku::KeyEventProc(KEY_EVENT_RECORD const& ker) {
	con.SetTextAttribute(BACKGROUND_WHITE | FOREGROUND_BLUE | FOREGROUND_GREEN);
	auto ks = ker.uChar.AsciiChar;

	COORD cursorPos = con.GetConsoleCursorPosition();

	if (cursorPos.Y == 1 && cursorPos.X > 11 && cursorPos.X < 22)
	{
		if (ker.bKeyDown)
		{
			if (ks == 8 && cursorPos.X != 12)
			{
				// \b to backspace - replace with a space, and go back
				cout << "\b";
				cout << " ";
				cout << "\b";
				Player1Name.pop_back();
			}
			// Only output letter on key down
			else if ((ks >= 'a' && ks <= 'z') || (ks >= 'A' && ks <= 'Z'))
			{
				cout << ks;
				Player1Name += ks;
			}
		}
	}
	else if (cursorPos.Y == 1 && cursorPos.X == 22)
	{
		if (ker.bKeyDown)
		{
			if (ks == 8)
			{
				// \b to backspace - replace with a space, and go back
				cout << "\b";
				cout << " ";
				cout << "\b";
				Player1Name.pop_back();
			}
		}
	}
	else if (cursorPos.X > 54 && cursorPos.X < 66 && cursorPos.Y == 1)
	{
		if (ker.bKeyDown)
		{
			if (ks == 8 && cursorPos.X != 56)
			{
				// \b to backspace - replace with a space, and go back
				cout << "\b";
				cout << " ";
				cout << "\b";
				Player2Name.pop_back();
			}
			// Only output letter on key down
			else if ((ks >= 'a' && ks <= 'z') || (ks >= 'A' && ks <= 'Z'))
			{
				cout << ks;
				Player2Name += ks;
			}
		}
	}
	else if (cursorPos.Y == 1 && cursorPos.X == 66)
	{
		if (ker.bKeyDown)
		{
			if (ks == 8)
			{
				// \b to backspace - replace with a space, and go back
				cout << "\b";
				cout << " ";
				cout << "\b";
				Player2Name.pop_back();
			}
		}
	}
	else if (ks == 'r' && currentCursor.X == 0 && currentCursor.Y == 0)
	{
		if (ker.bKeyDown)
		{
			Player1run = 0;
			Player2run = 0;
			totalPieces = 0;
			con.ClearConsole();
			DrawPlayerBar();
			DrawScoreboard();
			DrawBoard();
			DrawMoveScroll();
			DrawControls();
			Player1Turn = true;
		}
	}
	else if (ks == 'u' && currentCursor.X == 0 && currentCursor.Y == 0)
	{
		if (ker.bKeyDown)
		{
			RemoveLastMove();
		}
	}
}