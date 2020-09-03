#pragma once
#include <set>
class HiddenHex
{
public:
	int _hexId;
	std::set<int> _groupIds;
	HiddenHex() = delete;
	HiddenHex(int HexId, int groupId);
	HiddenHex(int HexId, std::set<int> groupIdsSet);
	void addGroup(int groupId);
	
};

