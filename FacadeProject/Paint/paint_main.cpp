/*!	\file		paint_main.cpp
	\author		Jaceey Tuck
	\date		2019-02-18

	Paint console application main.
*/
#include "Paint.hpp"

//=======================================================
// Console System
//=======================================================
#pragma region ConsoleSystem
Paint paint;
bool done = false;
#pragma endregion


//=======================================================
// Application
//=======================================================

BOOL CtrlHandler(DWORD ctrlType) {
	paint.con.RestoreConsole();

	return FALSE;
}

int main() {
	// Install a control handler to trap ^C
	if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)) {
		//cout << "Terminate program with Ctrl-C\n";
	}
	else {
		cerr << "ERROR: failed to install control handler." << endl;
		return EXIT_FAILURE;
	}

	if (!paint.con.SetConsole())
	{
		cerr << "\nERROR: could not set console mode.\n";
		return EXIT_FAILURE;
	}

	// read input buffer repeatedly
	vector<INPUT_RECORD> inBuffer(128);
	while (!done) {
		DWORD numEvents;
		if (!ReadConsoleInput(paint.con.GetConsoleInput(), inBuffer.data(), (DWORD)inBuffer.size(), &numEvents)) {
			cerr << "Failed to read console input\n";
			break;
		}

		for (size_t iEvent = 0; iEvent < numEvents; ++iEvent) {
			switch (inBuffer[iEvent].EventType) {
			case MOUSE_EVENT:
				paint.MouseEventProc(inBuffer[iEvent].Event.MouseEvent);
				break;
			case KEY_EVENT:
				paint.KeyEventProc(inBuffer[iEvent].Event.KeyEvent);
				break;
			}
		}

	}

	cout << "Finished" << endl;

	if (!paint.con.RestoreOriginal()) {
		cerr << "\nERROR: could not restore original console mode.\n";
		return EXIT_FAILURE;
	}
}