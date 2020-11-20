/*!	\file		GomokuWin.cpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Gomoku class implementation
		Contains Gomoku specific code related to determining winner.

*/

#include "Gomoku.hpp"

string Gomoku::IsWinner()
{
	bool p1 = false;
	bool p2 = false;
	int redCount = 0;
	int blackCount = 0;

#pragma region HorizontalWin
	auto it = screenLocations.begin();
	for (size_t c = 0; c < 15; c++)
	{
		for (size_t x = 0; x < 15; x++)
		{
			if (it->get_background() == Player1Colour)
			{
				p1 = true;
				redCount++;

				if (redCount > Player1run)
					Player1run = redCount;

				p2 = false;
				blackCount = 0;
				if (redCount == 5)
					break;
			}
			else if (it->get_background() == Player2Colour)
			{
				p2 = true;
				blackCount++;

				if (blackCount > Player2run)
					Player2run = blackCount;

				p1 = false;
				redCount = 0;
				if (blackCount == 5)
					break;
			}
			else
			{
				p1 = false;
				p2 = false;
				redCount = 0;
				blackCount = 0;
			}
			it++;
		}
		if ((p1 == true || p2 == true) && (redCount == 5 || blackCount == 5))
			break;
		else if (c == 14)
		{
			p1 = false;
			p2 = false;
		}
	}

#pragma endregion

#pragma region VerticalWin
	it = screenLocations.begin();
	auto temp = screenLocations.begin();
	redCount = 0;
	blackCount = 0;

	if (p1 == false && p2 == false)	// Only enter loop if not Horizontal wins
	{
		// Vertical wins
		for (size_t c = 0; c < 15; c++)
		{
			it = temp++;
			for (size_t x = 0; x < 15; x++)
			{
				if (it->get_background() == Player1Colour)
				{
					p1 = true;
					redCount++;

					if (redCount > Player1run)
						Player1run = redCount;

					p2 = false;
					blackCount = 0;
					if (redCount == 5)
						break;
				}
				else if (it->get_background() == Player2Colour)
				{
					p2 = true;
					blackCount++;

					if (blackCount > Player2run)
						Player2run = blackCount;

					p1 = false;
					redCount = 0;
					if (blackCount == 5)
						break;
				}
				else
				{
					p1 = false;
					p2 = false;
					redCount = 0;
					blackCount = 0;
				}

				for (size_t i = 0; i < 15; i++)
				{
					if (it + 1 != screenLocations.end())
						it++;
					else
						break;

				}
			}

			if ((p1 == true || p2 == true) && (redCount == 5 || blackCount == 5))
				break;
			else if (c == 14)
			{
				p1 = false;
				p2 = false;
			}
		}
	}
#pragma endregion

#pragma region DiagonalWin
	it = screenLocations.begin();
	temp = screenLocations.begin();
	redCount = 0;
	blackCount = 0;

	if (p1 == false && p2 == false)	// Only enter loop if not Horizontal wins
	{
		// Diagonal wins - top left to bottom right (only does first row and 6th row..)
		for (size_t c = 0; c < 15; c++)
		{
			it = temp++;
			for (size_t x = 0; x < 15; x++)
			{
				if (it->get_background() == Player1Colour)
				{
					p1 = true;
					redCount++;

					if (redCount > Player1run)
						Player1run = redCount;

					p2 = false;
					blackCount = 0;
					if (redCount == 5)
						break;
				}
				else if (it->get_background() == Player2Colour)
				{
					p2 = true;
					blackCount++;

					if (blackCount > Player2run)
						Player2run = blackCount;

					p1 = false;
					redCount = 0;
					if (blackCount == 5)
						break;
				}
				else
				{
					p1 = false;
					p2 = false;
					redCount = 0;
					blackCount = 0;
				}

				for (size_t i = 0; i < 16; i++)
				{
					if (it + 1 != screenLocations.end())
						it++;
					else
						break;

				}
			}

			if ((p1 == true || p2 == true) && (redCount == 5 || blackCount == 5))
				break;
			else if (c == 14)
			{
				p1 = false;
				p2 = false;
			}
		}
	}
#pragma endregion

	DrawScoreboard();

	if (p1 == true)
		win = "Player 1 won";
	else if (p2 == true)
		win = "Player 2 won";
	else
		win = "No win";

	return win;
}

void Gomoku::OutputWin(string win)
{
	DWORD consoleSize = con.GetConsoleSize();
	HANDLE consoleOutput = con.GetConsoleOutput();

	con.ClearConsole();
	COORD coord;
	coord.X = 0;
	coord.Y = 5;
	con.SetCursor(coord);

	// WHERE WIN IS OUTPUT
	if (win == "Player 1 won")
	{
		//Player1Wins++;
		cout << setw(80) << right << "     :::::::::  :::            :::   :::   ::: :::::::::: ::::::::: " << endl;
		cout << setw(80) << right << "     :+:    :+: :+:          :+: :+: :+:   :+: :+:        :+:    :+:" << endl;
		cout << setw(80) << right << "     +:+    +:+ +:+         +:+   +:+ +:+ +:+  +:+        +:+    +:+" << endl;
		cout << setw(80) << right << "     +#++:++#+  +#+        +#++:++#++: +#++:   +#++:++#   +#++:++#: " << endl;
		cout << setw(80) << right << "     +#+        +#+        +#+     +#+  +#+    +#+        +#+    +#+" << endl;
		cout << setw(80) << right << "     #+#        #+#        #+#     #+#  #+#    #+#        #+#    #+#" << endl;
		cout << setw(80) << right << "     ###        ########## ###     ###  ###    ########## ###    ###" << endl;
		cout << "\n" << endl;
		cout << setw(45) << right << " " << "   :::   " << endl;
		cout << setw(45) << right << " " << " :+:+:   " << endl;
		cout << setw(45) << right << " " << "   +:+   " << endl;
		cout << setw(45) << right << " " << "   +#+   " << endl;
		cout << setw(45) << right << " " << "   +#+   " << endl;
		cout << setw(45) << right << " " << "   #+#   " << endl;
		cout << setw(45) << right << " " << " ####### " << endl;
		cout << "\n" << endl;
		cout << setw(75) << right << "             :::        ::: ::::::::::: ::::    :::  ::::::::  " << endl;
		cout << setw(75) << right << "             :+:        :+:     :+:     :+:+:   :+: :+:    :+: " << endl;
		cout << setw(75) << right << "             +:+        +:+     +:+     :+:+:+  +:+ +:+        " << endl;
		cout << setw(75) << right << "             +#+  +:+   +#+     +#+     +#+ +:+ +#+ +#++:++#++ " << endl;
		cout << setw(75) << right << "             +#+ +#+#+  +#+     +#+     +#+  +#+#+#        +#+ " << endl;
		cout << setw(75) << right << "              #+#+#  #+#+#      #+#     #+#   #+#+# #+#    #+# " << endl;
		cout << setw(75) << right << "               ###    ###   ########### ###    ####  ########  " << endl;
		cout << "\n" << endl;
		cout << setw(40) << right << " " << "PRESS 'r' TO PLAY AGAIN" << endl;

		for (int i = 0; i < 10; i++)
		{
			con.ReColourTextAttribute(consoleOutput, consoleSize, cursorHomeCoord, Player1Foreground | BACKGROUND_BLACK);
			Sleep(100);
			con.ReColourTextAttribute(consoleOutput, consoleSize, cursorHomeCoord, FOREGROUND_BLACK | Player1Colour);
			Sleep(100);
			con.ReColourTextAttribute(consoleOutput, consoleSize, cursorHomeCoord, Player1Foreground | BACKGROUND_BLACK);
		}
	}
	else if (win == "Player 2 won")
	{
		//Player2Wins++;
		cout << setw(80) << right << "     :::::::::  :::            :::   :::   ::: :::::::::: ::::::::: " << endl;
		cout << setw(80) << right << "     :+:    :+: :+:          :+: :+: :+:   :+: :+:        :+:    :+:" << endl;
		cout << setw(80) << right << "     +:+    +:+ +:+         +:+   +:+ +:+ +:+  +:+        +:+    +:+" << endl;
		cout << setw(80) << right << "     +#++:++#+  +#+        +#++:++#++: +#++:   +#++:++#   +#++:++#: " << endl;
		cout << setw(80) << right << "     +#+        +#+        +#+     +#+  +#+    +#+        +#+    +#+" << endl;
		cout << setw(80) << right << "     #+#        #+#        #+#     #+#  #+#    #+#        #+#    #+#" << endl;
		cout << setw(80) << right << "     ###        ########## ###     ###  ###    ########## ###    ###" << endl;
		cout << "\n" << endl;
		cout << setw(45) << right << " " << " :::::::: " << endl;
		cout << setw(45) << right << " " << ":+:    :+:" << endl;
		cout << setw(45) << right << " " << "      +:+ " << endl;
		cout << setw(45) << right << " " << "    +#+   " << endl;
		cout << setw(45) << right << " " << "  +#+     " << endl;
		cout << setw(45) << right << " " << " #+#      " << endl;
		cout << setw(45) << right << " " << "##########" << endl;
		cout << "\n" << endl;
		cout << setw(75) << right << "             :::        ::: ::::::::::: ::::    :::  ::::::::  " << endl;
		cout << setw(75) << right << "             :+:        :+:     :+:     :+:+:   :+: :+:    :+: " << endl;
		cout << setw(75) << right << "             +:+        +:+     +:+     :+:+:+  +:+ +:+        " << endl;
		cout << setw(75) << right << "             +#+  +:+   +#+     +#+     +#+ +:+ +#+ +#++:++#++ " << endl;
		cout << setw(75) << right << "             +#+ +#+#+  +#+     +#+     +#+  +#+#+#        +#+ " << endl;
		cout << setw(75) << right << "              #+#+#  #+#+#      #+#     #+#   #+#+# #+#    #+# " << endl;
		cout << setw(75) << right << "               ###    ###   ########### ###    ####  ########  " << endl;
		cout << "\n" << endl;
		cout << setw(40) << right << " " << "PRESS 'r' TO PLAY AGAIN" << endl;

		for (int i = 0; i < 10; i++)
		{
			con.ReColourTextAttribute(consoleOutput, consoleSize, cursorHomeCoord, Player2Foreground | BACKGROUND_BLACK);
			Sleep(100);
			con.ReColourTextAttribute(consoleOutput, consoleSize, cursorHomeCoord, FOREGROUND_BLACK | Player2Colour);
			Sleep(100);
			con.ReColourTextAttribute(consoleOutput, consoleSize, cursorHomeCoord, Player2Foreground | BACKGROUND_BLACK);
		}
	}
}