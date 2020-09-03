#include "pch.h"
#include "Hexagon.h"
#include <string>

Hexagon::Hexagon(int id, int colour, int groupNumber, int timeStep)
{
	_id = id;
	_colour = colour;
	_groupNumber = groupNumber;
	_timeStep = timeStep;
}
