#pragma once
#include <vector>
#include <set>
#include <memory>
#include "Hexagon.h"
#include "HiddenHex.h"
class Group
{
public:
	int _groupNumber;
	std::vector<std::shared_ptr<Hexagon>> _myHexByGroup;
	std::vector<std::shared_ptr<HiddenHex>> _myHiddenHexByGroup;
	Group() = delete;
	Group(int group, std::shared_ptr<Hexagon> hex);
	Group(int group, std::vector<std::shared_ptr<Hexagon>> myHexByGroup);
	std::vector<std::shared_ptr<Hexagon>> getHexGroup();
	void addHiddenHex(std::shared_ptr<HiddenHex> myHiddenHexByGroup);
	std::vector<std::shared_ptr<HiddenHex>> getHiddenHexGroup();
	void setVectorHidHex(std::vector<std::shared_ptr<HiddenHex>> myHiddenHexGroup);
	
};

