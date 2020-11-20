#pragma once
/*!	\file		CoordLocationInfo.hpp
	\author		Jaceey Tuck
	\date		2019-02-18

	CoordLocationInfo class declaration.
		Used to set the X,Y coordinates and backColour of a Gomoku board piece
*/

#include <Windows.h>

#ifndef COORDLOCATIONINFO_H
#define COORDLOCATIONINFO_H
#endif // !COORDLOCATIONINFO_H

class CoordLocationInfo
{
	WORD backColour = BACKGROUND_BLUE | BACKGROUND_GREEN;
	COORD coord;
	COORD boardLocation;
public:
	void set_coord(int x, int y) { this->coord.X = x, this->coord.Y = y; };
	void set_background(WORD colour) {
		this->backColour = colour;
	};
	void set_boardlocation(int x, int y) { this->boardLocation.X = x, this->boardLocation.Y = y; }
	WORD get_background() { return this->backColour; };
	COORD get_coord() { return this->coord; };
	COORD get_boardlocation() { return this->boardLocation; }
};
