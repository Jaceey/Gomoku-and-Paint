/*!	\file		GomokuMoves.cpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Gomoku class implementation
		Contains Gomoku specific code related to player moves

*/

#include "Gomoku.hpp"


void Gomoku::DrawMoveScroll()
{
	con.SetTextAttribute(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	COORD coord;
	coord.X = 70;
	coord.Y = 5;
	con.SetCursor(coord);

	int y = 5;

	while (y != 38)
	{
		if (y == 6)
		{
			// Output title
			cout << setw(21) << right << "List Of Moves" << setw(7) << " " << endl;
		}
		else if (y == 5 || y == 7)
		{
			// Output background for title
			con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			cout << setw(28) << " ";
		}
		else
		{
			// Output the rest of move board
			con.SetTextAttribute(BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
			cout << setw(28) << " ";
		}
		y++;

		coord.Y = y;
		con.SetCursor(coord);
	}

}

void Gomoku::OutputMoves()
{
	COORD coord;
	coord.X = 71;
	coord.Y = 8;
	COORD move;
	WORD colour;
	int size = 0;

	vector<CoordLocationInfo> output15Moves;

	// store and reverse - to grab the 15 most recent moves
	vector<CoordLocationInfo> temp = moveLocations;
	reverse(temp.begin(), temp.end());

	// Add 15 moves 
	for (size_t i = 0; i < temp.size(); i++)
	{
		output15Moves.push_back(temp[i]);
		if (i == 14)
			break;
	}
	// reverse to output in order
	reverse(output15Moves.begin(), output15Moves.end());

	con.SetTextAttribute(BACKGROUND_INTENSITY);
	for (size_t i = 0; i < 15; i++)
	{
		con.SetCursor(coord);
		cout << setw(25) << " ";
		coord.Y += 2;
	}

	coord.Y = 8;

	for (size_t i = 0; i < output15Moves.size(); i++)
	{
		colour = output15Moves[i].get_background();
		con.SetTextAttribute(colour | FOREGROUND_WHITE);
		con.SetCursor(coord);
		move = output15Moves[i].get_boardlocation();

		if (colour == Player1Colour)
		{
			con.SetTextAttribute(Player1Colour | FOREGROUND_BLACK);
			cout << Player1Name << " X:" << setw(2) << left << move.X << " Y:" << setw(2) << left << move.Y << setw(14 - Player1Name.length()) << " " << endl;
		}
		else if (colour == Player2Colour)
		{
			con.SetTextAttribute(Player2Colour | FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			cout << Player2Name << " X:" << setw(2) << left << move.X << " Y:" << setw(2) << left << move.Y << setw(14 - Player2Name.length()) << " " << endl;
		}

		coord.Y += 2;

		if (coord.Y > 37)
			break;
	}
}

void Gomoku::RemoveLastMove()
{
	if (moveLocations.size() > 0)
	{
		CoordLocationInfo c = moveLocations.back();
		moveLocations.pop_back();

		COORD coord = c.get_coord();
		int x = coord.X;
		int y = coord.Y;

		for (size_t i = 0; i < screenLocations.size(); i++)
		{
			COORD co = screenLocations[i].get_coord();

			if (co.X == x && co.Y == y)
			{
				screenLocations[i].set_background(BACKGROUND_BLUE | BACKGROUND_GREEN);
			}
		}

		// Redraw moves and board after removing
		OutputMoves();
		OutputBoard();

		// Reset longest run
		Player1run = 0;
		Player2run = 0;
		IsWinner();

		// Reset turn
		Player1Turn = !Player1Turn;

		// Decrease every time a move is removed
		totalPieces--;

		// Update scoreboard
		DrawScoreboard();

	}
}