#include "pch.h"
#include "Board.h"
#include <vector>
#include <set>
#include <algorithm>
#include <memory>
#include "Hexagon.h"

#include "Group.h"

Board::Board()
{}

Board::Board(int boardGridEdgeSize)
{
	boardSize = boardGridEdgeSize;
	setUp();
}

void Board::setUp()
{
	topLeft = 1;
	topRight = boardSize;

	// for a 11*11 board (10*11)+1 = 111
	bottomLeft = ((boardSize - 1) * boardSize) + 1;

	// for a 11*11 board 11*11 = 121
	bottomRight = boardSize * boardSize;

	hiddenWhite1 = bottomRight + 1;
	hiddenWhite2 = bottomRight + 2;
	hiddenBlack1 = bottomRight + 3;
	hiddenBlack2 = bottomRight + 4;
	white = 1;
	black = 2;

	createdHiddenWhite1 = false;
	createdHiddenWhite2 = false;
	createdHiddenBlack1 = false;
	createdHiddenBlack2 = false;
	win = false;
	moveId = 0;
	winBlack = false;
	winWhite = false;

	for (int i = 1; i < bottomRight + 1; i++)
	{
		legalMoves.insert(i);
	}
}

int Board::addMoveToBoard(const int hexId, const int turn)
{
	int positionCode = checkPositionNumber(hexId);
	int returnedEdgeGroup = 0;
	int groupNumber = 0;
	int test = 0;
	moveId++;
	std::vector<int> myEdgeCollection;
	
	
	switch (positionCode)
	{
	case 1:
		// top left corner
		//checkEdgeTwo(hexId);
		//checkEdgeThree(hexId);
		returnedEdgeGroup = checkEdge(hexId, turn, 2);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		returnedEdgeGroup = checkEdge(hexId, turn, 3);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);
		
		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 2:
		// top right corner
		//checkEdgeThree(hexId);
		//checkEdgeFour(hexId);
		//checkEdgeFive(hexId);
		returnedEdgeGroup = checkEdge(hexId, turn, 3);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		returnedEdgeGroup = checkEdge(hexId, turn, 4);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		returnedEdgeGroup = checkEdge(hexId, turn, 5);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 3:
		// bottom left corner
		//checkEdgeOne(hexId);
		//checkEdgeTwo(hexId);
		//checkEdgeSix(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 1);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		returnedEdgeGroup = checkEdge(hexId, turn, 2);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		returnedEdgeGroup = checkEdge(hexId, turn, 6);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 4:
		// bottom right corner
		//checkEdgeFive(hexId);
		//checkEdgeSix(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 5);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		returnedEdgeGroup = checkEdge(hexId, turn, 6);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 5:
		// top edge without corners
		//checkEdgeTwo(hexId);
		//checkEdgeThree(hexId);
		//checkEdgeFour(hexId);
		//checkEdgeFive(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 2);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 3);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 4);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 5);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 6:
		// left edge without corners
		//checkEdgeOne(hexId);
		//checkEdgeTwo(hexId);
		//checkEdgeThree(hexId);
		//checkEdgeSix(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 1);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 2);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 3);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 6);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 7:
		// right edge without corners
		//checkEdgeThree(hexId);
		//checkEdgeFour(hexId);
		//checkEdgeFive(hexId);
		//checkEdgeSix(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 3);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 4);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 5);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 6);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 8:
		// bottom edge without corners
		//checkEdgeOne(hexId);
		//checkEdgeTwo(hexId);
		//checkEdgeFive(hexId);
		//checkEdgeSix(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 1);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 2);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 5);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 6);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	case 9:
		// internal
		//checkEdgeOne(hexId);
		//checkEdgeTwo(hexId);
		//checkEdgeThree(hexId);
		//checkEdgeFour(hexId);
		//checkEdgeFive(hexId);
		//checkEdgeSix(hexId);

		returnedEdgeGroup = checkEdge(hexId, turn, 1);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 2);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 3);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 4);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 5);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);


		returnedEdgeGroup = checkEdge(hexId, turn, 6);
		checkGroupIds(returnedEdgeGroup, myEdgeCollection);

		//groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);
		break;
	default:
		throw - 1;
	}

	groupNumber = checkEdgeCollection(hexId, turn, myEdgeCollection);

	if (groupNumber == -1)
	{
		if (win == true)
		{
			return 1;
		}
		return 0;
	}

	if (groupNumber == -2)
	{
		if (win == true)
		{
			return 1;
		}
		return 0;
	}
	auto hex = std::make_shared <Hexagon>(hexId, turn, groupNumber, 0);


	
	if (turn == white)
	{
		
		Group myGroup = Group::Group(groupNumber, hex);
	
		myGroupCollectionWhite.push_back(myGroup);
		playerWhiteHexCollection.push_back(hex);
	}
	else
	{
		Group myGroup = Group::Group(groupNumber, hex);
		myGroupCollectionBlack.push_back(myGroup);
		playerBlackHexCollection.push_back(hex);
	}
	win = winQuestion(turn);
	if (win == true)
	{
		return 1;
	}
	return 0;
	
}


int Board::checkEdge(int hexId, int turn, int edge)
{
	int edgeToCheck = 0;
	if (edge == 1)
	{
		edgeToCheck = -10;
	}

	if (edge == 2)
	{
		edgeToCheck = 1;
	}

	if (edge == 3)
	{
		edgeToCheck = 11;
	}

	if (edge == 4)
	{
		edgeToCheck = 10;
	}

	if (edge == 5)
	{
		edgeToCheck = -1;
	}

	if (edge == 6)
	{
		edgeToCheck = -11;
	}

	int checkHex = hexId + edgeToCheck;

	if (turn == white)
	{
		
		for (const auto& hex : playerWhiteHexCollection)
		{
			if (hex->_id == checkHex)
			{
				return checkHex;
			}
		}
	}
	else
	{
		
		for (const auto& hex : playerBlackHexCollection)
		{
			if (hex->_id == checkHex)
			{
				return checkHex;
			}
		}
	}
	return 0;
}

void Board::checkGroupIds(int returnedEdgeGroupId, std::vector<int>& myEdgeCollection)
{
	if (returnedEdgeGroupId != 0)
	{
		myEdgeCollection.push_back(returnedEdgeGroupId);
	}

}

int Board::checkEdgeCollection(int hexId, int turn, std::vector<int>& myEdgeCollection)
{
	if (myEdgeCollection.empty() && turn == white)
	{
		
		return moveId ;
	}
	else
	{
		if (myEdgeCollection.empty())
		{
			return moveId;
		}
	}
	std::set<int> myEdgeSet;
	bool bridgingHere = false;

	for (std::vector<int>::iterator it = myEdgeCollection.begin(); it != myEdgeCollection.end(); ++it)
	{
		std::pair<std::set<int>::iterator, bool> ret = myEdgeSet.insert(*it);

		if (ret.second == true && it != myEdgeCollection.begin())
		{
			bridgingHere = true;
		}
	}

	if (bridgingHere == false)
	{
		int newGroupId;
		if (turn == white)
		{
			newGroupId = resetGroupIdLinking(hexId, turn, myEdgeSet);
		}
		else
		{
			newGroupId = resetGroupIdLinking(hexId, turn, myEdgeSet);
		}
		return newGroupId;
		
	}
	else
	{
		
		int newGroupId = resetGroupId(hexId, turn, myEdgeSet);
		return newGroupId;
	}
	return -1;
}

int Board::resetGroupIdLinking(int hexId, int turn, std::set<int>& myEdgeSet)
{
	int groupTemp = moveId;
	int swapVal = 0;
	bool hello = false;
	std::vector<int> sameGroup;
	std::vector<std::shared_ptr<Hexagon>> sameHexGroup;

	if (turn == white)
	{
		for (auto itForSet : myEdgeSet)
		{			
			for (auto& hex : playerWhiteHexCollection)
			{
			if (itForSet == hex->_id)
				{
					sameHexGroup.push_back(hex);
					sameGroup.push_back(hex->_groupNumber);
				}
			}
		}

		std::vector<std::vector<std::shared_ptr<Hexagon>>> mergeCollection;
		
		int groupTempMerge = moveId;
		int swapValMerge = 0;

		for (auto& hexGroup : sameGroup)
		{		
			for (auto& GroupCollection : myGroupCollectionWhite)
			{
				if (GroupCollection._groupNumber == hexGroup)
				{
					Group myGroup = GroupCollection;
					mergeCollection.push_back(myGroup._myHexByGroup);
				}
			}
		}	
	std::vector<std::shared_ptr<Hexagon>> mergedHex;
	for (auto& mergeOutside : mergeCollection)
		{
			for (auto& mergeInside : mergeOutside)
				{
					if (mergeInside->_groupNumber != groupTempMerge)
							{
								mergeInside->_groupNumber = groupTempMerge;
							}
							mergedHex.push_back(mergeInside);

				}
		}

					
	auto hex = std::make_shared <Hexagon>(hexId, turn, groupTempMerge, 0);
	mergedHex.push_back(hex);
	playerWhiteHexCollection.push_back(hex);
	Group myGroup = Group::Group(groupTempMerge, mergedHex);
	myGroupCollectionWhite.push_back(myGroup);
	win = winQuestion(turn);
	groupTemp = -2;

	}
	else
		{
			for (auto itForSet : myEdgeSet)
				{
					for (auto& hex : playerBlackHexCollection)
						{
							if (itForSet == hex->_id)
							{
								sameHexGroup.push_back(hex);
								sameGroup.push_back(hex->_groupNumber);
							}
						}
				}

		std::vector<std::vector<std::shared_ptr<Hexagon>>> mergeCollection;		
		int groupTempMerge = moveId;
		int swapValMerge = 0;
		for (auto& hexGroup : sameGroup)
			{
				for (auto& GroupCollection : myGroupCollectionBlack)
					{
							if (GroupCollection._groupNumber == hexGroup)
							{
								Group myGroup = GroupCollection;
								mergeCollection.push_back(myGroup._myHexByGroup);
							}
					}
			}

	std::vector<std::shared_ptr<Hexagon>> mergedHex;

								
	for (auto& mergeOutside : mergeCollection)
		{
									
			for (auto& mergeInside : mergeOutside)
				{
					if (mergeInside->_groupNumber != groupTempMerge)
						{
							mergeInside->_groupNumber = groupTempMerge;
						}
					mergedHex.push_back(mergeInside);

				}
		}

	auto hex = std::make_shared <Hexagon>(hexId, turn, groupTempMerge, 0);
	mergedHex.push_back(hex);
	playerBlackHexCollection.push_back(hex);
	Group myGroup = Group::Group(groupTempMerge, mergedHex);
	myGroupCollectionBlack.push_back(myGroup);
	win = winQuestion(turn);
	groupTemp = -2;
	}

return groupTemp;
}
					
int Board::resetGroupId(int hexId, int turn, std::set<int>& myEdgeSet)
{
	int groupTemp = moveId;
	int swapVal = 0;
	bool hello = false;
	std::vector<int> sameGroup;
	std::vector<std::shared_ptr<Hexagon>> sameHexGroup;

	if (turn == white)
	{
		for (std::set<int>::iterator itForSet = myEdgeSet.begin(); itForSet != myEdgeSet.end(); ++itForSet)
		{
			
			for (auto& hex : playerWhiteHexCollection)
			{
				if (*itForSet == hex->_id)
				{
					sameHexGroup.push_back(hex);
					sameGroup.push_back(hex->_groupNumber);
					
				}
			}
		}

		std::vector<std::vector<std::shared_ptr<Hexagon>>> mergeCollection;
		
		int groupTempMerge = moveId;
		int swapValMerge = 0;

		
		for (auto& hexGroup : sameGroup)
		{
			
			for (auto& GroupCollection : myGroupCollectionWhite)
			{
				if (GroupCollection._groupNumber == hexGroup)
				{
					Group myGroup = GroupCollection;
					mergeCollection.push_back(myGroup._myHexByGroup);
				}
			}
		}
		std::set<std::shared_ptr<Hexagon>> mergedHexSet;

					
		for (auto& mergeOutside : mergeCollection)
					{
						
						for (auto& mergeInside : mergeOutside)
						{
							if (mergeInside->_groupNumber != groupTempMerge)
							{
								mergeInside->_groupNumber = groupTempMerge;
							}
							mergedHexSet.insert(mergeInside);

						}
					}

					std::vector<std::shared_ptr<Hexagon>> mergedHex;

					for (auto& reinsert : mergedHexSet)
					{
						mergedHex.push_back(reinsert);
					}


					auto hex = std::make_shared <Hexagon>(hexId, turn, groupTempMerge, 0);
					mergedHex.push_back(hex);
					playerWhiteHexCollection.push_back(hex);
					Group myGroup = Group::Group(groupTempMerge, mergedHex);
					myGroupCollectionWhite.push_back(myGroup);
					win = winQuestion(turn);
					groupTemp = -1;
				}
				


	else
		{
					for (std::set<int>::iterator itForSet = myEdgeSet.begin(); itForSet != myEdgeSet.end(); ++itForSet)
					{
						
						for (auto& hex : playerBlackHexCollection)
						{
							if (*itForSet == hex->_id)
							{
								

								sameHexGroup.push_back(hex);
								sameGroup.push_back(hex->_groupNumber);
								
							}
						}
					}

					std::vector<std::vector<std::shared_ptr<Hexagon>>> mergeCollection;
					int groupTempMerge = moveId;
					int swapValMerge = 0;

					
					for (auto& hexGroup : sameGroup)
					{
						
						for (auto& GroupCollection : myGroupCollectionBlack)
						{
							if (GroupCollection._groupNumber == hexGroup)
							{
								Group myGroup = GroupCollection;

								
								mergeCollection.push_back(myGroup._myHexByGroup);

								
							}
						}
					}
								std::set<std::shared_ptr<Hexagon>> mergedHexSet;

								
								for (auto& mergeOutside : mergeCollection)
								{
									
									for (auto& mergeInside : mergeOutside)
									{
										if (mergeInside->_groupNumber != groupTempMerge)
										{
											mergeInside->_groupNumber = groupTempMerge;
										}
										mergedHexSet.insert(mergeInside);

									}
								}

								std::vector<std::shared_ptr<Hexagon>> mergedHex;

								for (auto& reinsert : mergedHexSet)
								{
									mergedHex.push_back(reinsert);
								}

		
								auto hex = std::make_shared <Hexagon>(hexId, turn, groupTempMerge, 0);
								mergedHex.push_back(hex);
								playerBlackHexCollection.push_back(hex);
								Group myGroup = Group::Group(groupTempMerge, mergedHex);			
								myGroupCollectionBlack.push_back(myGroup);
								win = winQuestion(turn);
								groupTemp = -1;
							}
						
							
							return groupTemp;
						}
					
/*
  throws exception if hexId not on board

  returns 1 if top left corner
  returns 2 if top right corner
  returns 3 if bottom left corner
  returns 4 if bottom right corner
  returns 5 if top row but not corners
  returns 6 if left edge but not corners
  returns 7 if right edge but not corners
  returns 8 if bottom row but not corners
  returns 9 if internal to the board but none of the above

*/

int Board::checkPositionNumber(int hexId)
{
	
	int myCheck = isOnBoard(hexId);

	if (myCheck)
	{
		
	}
	else
	{
		throw - 1;
	}

	myCheck = isCorner(hexId);

	if (myCheck)
	{
		return myCheck;
	}
	
	myCheck = isEdge(hexId);

	if (myCheck)
	{
		return myCheck;
	}

	return 9;

}

int Board::isOnBoard(int hexId)
{
	if (hexId > 0 && hexId < (boardSize * boardSize) + 1)
	{
		return 1;
	}

	return 0;
}

int Board::isCorner(int hexId)
{
	// top left corner
	if (hexId == topLeft)
	{
		return 1;
	}

	// top right corner
	if (hexId == topRight)
	{
		return 2;
	}

	//bottom left corner
	if (hexId == bottomLeft )
	{
		return 3;
	}

	// bottom right corner
	if (hexId == bottomRight)
	{
		return 4;
	}
	return 0;
}

int Board::isEdge(int hexId)
{
	// top row but not corners
	if (hexId > topLeft&& hexId < topRight)
	{
		return 5;
	}

	// left edge but not corners
	if ((hexId - 1) % boardSize == 0)
	{
		return 6;
	}

	
	// right edge but not corners
	if ((hexId) % boardSize == 0)
	{
		return 7;
	}

	// bottom row but not corners
	if (hexId > bottomLeft&& hexId < bottomRight)
	{
		return 8;
	}

	return 0;
}
/*
bool Board::winQuestion(int turn)
{
	
	if (turn == white)
	{
		for (auto& whiteWinGroup : myGroupCollectionWhite)
		{
			std::set<int> hiddenWhiteSet1;
			std::set<int> hiddenWhiteSet2;
			for (auto& hidHex : whiteWinGroup.getHiddenHexGroup())
			{


				if (hidHex->_hexId == hiddenWhite1)
				{
					for (auto anInt : hidHex->_groupIds)
					{
						hiddenWhiteSet1.insert(anInt);
					}
				}

				if (hidHex->_hexId == hiddenWhite2)
				{
					for (auto anInt : hidHex->_groupIds)
					{
						hiddenWhiteSet2.insert(anInt);
					}
				}

			}

			if (hiddenWhiteSet1.size() == 0)
			{
				continue;
			}
			if (hiddenWhiteSet2.size() == 0)
			{
				continue;
			}
			//std::sort(hiddenWhiteSet1.begin(), hiddenWhiteSet1.end());
			//std::sort(hiddenWhiteSet2.begin(), hiddenWhiteSet2.end());
			std::set<int> result;
			std::set_intersection(hiddenWhiteSet1.begin(), hiddenWhiteSet1.end(),
				hiddenWhiteSet2.begin(), hiddenWhiteSet2.end(), std::inserter(result, result.begin()));
			if (result.size() > 0)
			{
				winWhite = true;
				return true;
			}
		}

		return false;
	}

	else
	{
		for (auto& blackWinGroup : myGroupCollectionBlack)
		{
			std::set<int> hiddenBlackSet1;
			std::set<int> hiddenBlackSet2;
			for (auto& hidHex : blackWinGroup.getHiddenHexGroup())
			{


				if (hidHex->_hexId == hiddenBlack1)
				{
					for (auto anInt : hidHex->_groupIds)
					{
						hiddenBlackSet1.insert(anInt);
					}
				}

				if (hidHex->_hexId == hiddenBlack2)
				{
					for (auto anInt : hidHex->_groupIds)
					{
						hiddenBlackSet2.insert(anInt);
					}
				}

			}

			if (hiddenBlackSet1.size() == 0)
			{
				continue;
			}
			if (hiddenBlackSet2.size() == 0)
			{
				continue;
			}
			
			std::set<int> result;
			std::set_intersection(hiddenBlackSet1.begin(), hiddenBlackSet1.end(),
				hiddenBlackSet2.begin(), hiddenBlackSet2.end(), std::inserter(result, result.begin()));
			if (result.size() > 0)
			{
				winBlack = true;
				return true;
			}
		}
	}

	return false;

}
*/
/*
bool Board::winQuestion(int turn)
{
	if (turn == white)
	{
		std::set<int> hiddenWhiteSet1;
		std::set<int> hiddenWhiteSet2;
		for (auto hidHex : myHiddenHexCollection)
		{

			if (hidHex->_hexId == hiddenWhite1)
			{
				for (auto anInt : hidHex->_groupIds)
				{
					hiddenWhiteSet1.insert(anInt);
				}
			}

			if (hidHex->_hexId == hiddenWhite2)
			{
				for (auto anInt : hidHex->_groupIds)
				{
					hiddenWhiteSet2.insert(anInt);
				}
			}


		}

			std::set<int> result;
			std::set_intersection(hiddenWhiteSet1.begin(), hiddenWhiteSet1.end(),
				hiddenWhiteSet2.begin(), hiddenWhiteSet2.end(), std::inserter(result, result.begin()));
			if (result.size() > 0)
			{
				winWhite = true;
				return true;
			}

			return false;
		





	}
	else
	{
		std::set<int> hiddenBlackSet1;
		std::set<int> hiddenBlackSet2;
		for (auto hidHex : myHiddenHexCollection)
		{

			if (hidHex->_hexId == hiddenBlack1)
			{
				for (auto anInt : hidHex->_groupIds)
				{
					hiddenBlackSet1.insert(anInt);
				}
			}

			if (hidHex->_hexId == hiddenBlack2)
			{
				for (auto anInt : hidHex->_groupIds)
				{
					hiddenBlackSet2.insert(anInt);
				}
			}


		}

			std::set<int> result;
			std::set_intersection(hiddenBlackSet1.begin(), hiddenBlackSet1.end(),
				hiddenBlackSet2.begin(), hiddenBlackSet2.end(), std::inserter(result, result.begin()));
			if (result.size() > 0)
			{
				winBlack = true;
				return true;
			}

			return false;
		

	}
}
*/
bool Board::winQuestion(int turn)
{
	if (turn == white)
	{
		if (myGroupCollectionWhite.size() < 1)
		{
			return false;
		}

		bool whiteLeft = false;
		bool whiteRight = false;

		Group myGroup = myGroupCollectionWhite.back();

		for (auto searchForWin : myGroup.getHexGroup())
		{
			int positionCode = checkPositionNumber(searchForWin->_id);

			if (positionCode == 9)
			{
				continue;
			}

			if (positionCode == 1 || positionCode == 3 || positionCode == 6)
			{
				whiteLeft = true;
			}

			if (positionCode == 2 || positionCode == 4 || positionCode == 7)
			{
				whiteRight = true;
			}


		}

		if (whiteLeft == true && whiteRight == true)
		{
			winWhite = true;
			return true;
		}

		return false;
	}
	else
	{
		if (myGroupCollectionBlack.size() < 1)
		{
			return false;
		}

		bool blackTop = false;
		bool blackBottom = false;

		Group myGroup = myGroupCollectionBlack.back();

		for (auto searchForWin : myGroup.getHexGroup())
		{
			int positionCode = checkPositionNumber(searchForWin->_id);

			if (positionCode == 9)
			{
				continue;
			}

			if (positionCode == 1 || positionCode == 2 || positionCode == 5)
			{
				blackTop = true;
			}

			if (positionCode == 3 || positionCode == 4 || positionCode == 8)
			{
				blackBottom = true;
			}


		}

		if (blackTop == true && blackBottom == true)
		{
			winBlack = true;
			return true;
		}

		return false;
	}
}
