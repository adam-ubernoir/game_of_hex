#include "pch.h"
#include "HiddenHex.h"
#include <vector>



HiddenHex::HiddenHex(int hexId, int groupId) 
{
	_hexId = hexId;

	_groupIds.insert(groupId);

}

void HiddenHex::addGroup(int groupId)
{
	_groupIds.insert(groupId);
}

HiddenHex::HiddenHex(int hexId, std::set<int> groupIdsSet)
{
	_hexId = hexId;

	_groupIds = groupIdsSet;
}