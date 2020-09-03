#include "pch.h"
#include "Group.h"
#include "Hexagon.h"



Group::Group(int group, std::shared_ptr<Hexagon> hex)
{
	_groupNumber = group;
	_myHexByGroup.push_back(hex);
	
}

std::vector<std::shared_ptr<Hexagon>> Group::getHexGroup()
{
	return _myHexByGroup;
}

Group::Group(int group, std::vector<std::shared_ptr<Hexagon>> myHexByGroup)
{
	_groupNumber = group;
	_myHexByGroup = myHexByGroup;
}

void Group::addHiddenHex(std::shared_ptr<HiddenHex> myHiddenHexByGroup)
{
	_myHiddenHexByGroup.push_back (myHiddenHexByGroup);
}

std::vector<std::shared_ptr<HiddenHex>> Group::getHiddenHexGroup()
{
	return _myHiddenHexByGroup;
}

void Group::setVectorHidHex(std::vector<std::shared_ptr<HiddenHex>> myHiddenHexGroup)
{
	_myHiddenHexByGroup = myHiddenHexGroup;
}