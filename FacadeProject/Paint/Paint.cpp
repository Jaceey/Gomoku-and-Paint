/*!	\file		Paint.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Paint class implementation
		Contains paint specific application code
*/
#include "Paint.hpp"

void Paint::MouseEventProc(MOUSE_EVENT_RECORD const& mer)
{
	DWORD temp = mer.dwButtonState;

	switch (mer.dwEventFlags) {
	case 0: // button pressed or released
	{
		auto mask = mer.dwButtonState;
		auto bufferLoc = mer.dwMousePosition;
		//if (mask&RIGHTMOST_BUTTON_PRESSED)
		//{
		//	if (background == (BACKGROUND_INTENSITY | BACKGROUND_RED))
		//		background = (BACKGROUND_INTENSITY | BACKGROUND_GREEN);
		//	else if (background == (BACKGROUND_INTENSITY | BACKGROUND_GREEN))
		//		background = (BACKGROUND_INTENSITY | BACKGROUND_BLUE);
		//	else if (background == (BACKGROUND_INTENSITY | BACKGROUND_BLUE))
		//		background = (BACKGROUND_INTENSITY | BACKGROUND_RED);
		//}

		if (mask&FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			if (bufferLoc.Y <= 2 && bufferLoc.Y != 0)
			{
				if (bufferLoc.X >= 3 && bufferLoc.X <= 6)
					background = (BACKGROUND_INTENSITY | BACKGROUND_RED);
				else if (bufferLoc.X >= 9 && bufferLoc.X <= 12)
					background = (BACKGROUND_INTENSITY | BACKGROUND_GREEN);
				else if (bufferLoc.X >= 15 && bufferLoc.X <= 18)
					background = (BACKGROUND_INTENSITY | BACKGROUND_BLUE);
				else if (bufferLoc.X >= 21 && bufferLoc.X <= 24)
					background = (BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN);
				else if (bufferLoc.X >= 27 && bufferLoc.X <= 30)
					background = (BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);
				else if (bufferLoc.X >= 33 && bufferLoc.X <= 36)
					background = (BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE);


			}
		}

		temp = mask;

	}

	case MOUSE_MOVED:
		if (temp&FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwMousePosition.Y > 3)
			con.ReColourTextAttribute(con.GetConsoleOutput(), 1, mer.dwMousePosition, background);
		break;


	}
}

void Paint::KeyEventProc(KEY_EVENT_RECORD const& ker) {

	auto ks = ker.uChar.AsciiChar;

	if (ks == 'c')
	{
		con.ClearConsole();
		DrawPalette();
	}
}

void Paint::DrawPalette()
{

	vector<WORD> colours = {
		BACKGROUND_INTENSITY | BACKGROUND_RED,		// Red
		BACKGROUND_INTENSITY | BACKGROUND_GREEN,	// Green	
		BACKGROUND_INTENSITY | BACKGROUND_BLUE,		// Blue	
		BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,	// Cyan 
		BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,	// Yellow
		BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE		// Magenta
	};

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	con.SetCursor(coord);

	con.SetTextAttribute(BACKGROUND_INTENSITY | FOREGROUND_WHITE);
	cout << setw(40) << "  ";

	con.SetTextAttribute(BACKGROUND_INTENSITY);

	for (size_t x = 0; x < 2; x++)
	{
		cout << "   ";
		for (size_t i = 0; i < 6; i++)
		{
			con.SetTextAttribute(colours.at(i));
			cout << "    ";
			// Background
			con.SetTextAttribute(BACKGROUND_INTENSITY | FOREGROUND_WHITE);
			if (i == 5)
				cout << "   ";
			else
				cout << "  ";
		}
	}

	con.SetTextAttribute(BACKGROUND_INTENSITY | FOREGROUND_WHITE);
	cout << setw(40) << "  ";

}
