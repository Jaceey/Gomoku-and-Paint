/*!	\file		Gomoku.cpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Gomoku class implementation
		Contains Gomoku specific application code.

*/

#include "Gomoku.hpp"

void Gomoku::DrawPlayerBar() {
	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	con.SetCursor(coord);
	cout << setw(100) << " ";
	cout << "  Player 1: ";
	con.SetTextAttribute(BACKGROUND_WHITE | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << setw(20) << left << Player1Name;

	// Output Player 1 colours
	con.SetTextAttribute(BACKGROUND_BLACK);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << " ";	
	con.SetTextAttribute(BACKGROUND_BLACK);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE);
	cout << " ";	
	con.SetTextAttribute(BACKGROUND_BLACK);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
	cout << " ";

	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);	
	cout << setw(8) << " ";
	cout << "Player 2: ";
	con.SetTextAttribute(BACKGROUND_WHITE | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << setw(20) << left << Player2Name;

	// Output Player 2 colours
	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_RED | BACKGROUND_BLUE);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_GREEN);
	cout << " ";
	con.SetTextAttribute(BACKGROUND_BLACK);
	cout << setw(18) << " ";
	cout << setw(100) << " ";


}

void Gomoku::OutputBoard() {

	for (size_t i = 0; i < screenLocations.size(); i++)
	{
		// Change both player previous colour to new - board pieces
		if (screenLocations[i].get_background() == PrevP1Colour)
			screenLocations[i].set_background(Player1Colour);

		if (screenLocations[i].get_background() == PrevP2Colour)
			screenLocations[i].set_background(Player2Colour);
	}

	for (size_t i = 0; i < moveLocations.size(); i++)
	{
		// Change both player previous colour to new - move output
		if (moveLocations[i].get_background() == PrevP1Colour)
			moveLocations[i].set_background(Player1Colour);

		if (moveLocations[i].get_background() == PrevP2Colour)
			moveLocations[i].set_background(Player2Colour);
	}
	// Update moves
	OutputMoves();

	con.SetTextAttribute(BACKGROUND_WHITE);
	COORD coord;
	coord.X = 0;
	coord.Y = 5;
	con.SetCursor(coord);

	// output updated board
	int count = 0;
	cout << "\n\n";
	for (size_t s = 0; s < 15; s++)
	{
		cout << '\t';
		for (size_t i = 0; i < 15; i++)
		{
			// Gomoku piece
			con.SetTextAttribute(screenLocations[count].get_background());
			cout << "  ";
			// Background
			con.SetTextAttribute(BACKGROUND_WHITE | FOREGROUND_WHITE);
			cout << "  ";

			count++;

		}
		cout << "\n\n";
	}
}

void Gomoku::DrawScoreboard()
{
	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	COORD coord;
	coord.X = 0;
	coord.Y = 3;
	con.SetCursor(coord);

	cout << setw(15) << right << "Longest Run: " << setw(2) << Player1run;
	cout << setw(27) << " ";
	cout << setw(15) << right << "Longest Run: " << setw(2) << Player2run;
	cout << setw(29) << "Pieces in Play: " << setw(2) << totalPieces;
	cout << setw(8) << " ";
}

void Gomoku::DrawControls()
{
	con.SetTextAttribute(BACKGROUND_BLACK | FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
	COORD coord;
	coord.X = 20;
	coord.Y = 38;

	con.SetCursor(coord);
	cout << "'u' to undo move   'r' to restart";
}

void Gomoku::DrawBoard()
{
#pragma region ResetVariables
	win = "No win";
	screenLocations.clear();
	moveLocations.clear();
#pragma endregion

#pragma region DrawBoard
	con.SetTextAttribute(BACKGROUND_WHITE);
	COORD coord;
	coord.X = 0;
	coord.Y = 5;
	con.SetCursor(coord);

	int x = 8;
	int y = 7;
	cout << "\n\n";
	for (size_t s = 0; s < 15; s++)
	{
		cout << '\t';
		for (size_t i = 0; i < 15; i++)
		{
			// Gomoku piece
			con.SetTextAttribute(BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_GREEN);
			cout << "  ";
			// Background
			con.SetTextAttribute(BACKGROUND_WHITE | FOREGROUND_WHITE);
			cout << "  ";

			// Save coordinate information
			CoordLocationInfo c;
			c.set_coord(x, y);
			c.set_boardlocation((int)i, (int)s);
			screenLocations.push_back(c);

			// Column goes up by 4 each piece
			x += 4;


		}
		// Row goes up by 2, column resets to 8
		x = 8;
		y += 2;
		cout << "\n\n";
	}
#pragma endregion
}