#pragma once
#include <vector>
#include <set>
#include <memory>
#include "Hexagon.h"
#include "HiddenHex.h"
#include "Group.h"
class Board
{

public:
	Board();
	Board(int boardGridEdgeSize);
	void setUp();
	int boardSize;
	int topLeft;
	int topRight;
	int bottomLeft;
	int bottomRight;
	int addMoveToBoard(const int hexId,const int turn);
	int checkPositionNumber(int hexId);
	int isCorner(int hexId);
	int isEdge(int hexId);
	int isOnBoard(int hexId);
	//std::vector<Hexagon> myHexCollection;
	//std::vector<int> myEdgeCollection;
	std::vector<Group> myGroupCollectionWhite;
	std::vector<Group> myGroupCollectionBlack;
	int checkEdge(int hexId, int turn, int edge);
	void checkGroupIds(int returnedEdgeGroupId, std::vector<int>& myEdgeCollection);
	int checkEdgeCollection(int hexId, int turn, std::vector<int>& myEdgeCollection);
	int resetGroupId(int hexId, int turn, std::set<int>& myEdgeSet);
	//int resetGroupIdLinking(int hexId, int turn, std::set<int>& myEdgeSet, std::vector<std::shared_ptr<Hexagon>>& playerHexCollection, std::vector<Group> &myGroupCollection);
	int resetGroupIdLinking(int hexId, int turn, std::set<int>& myEdgeSet);
	//int addHiddenEdge(int turn, int returnedEdgeGroup);
	int hiddenWhite1;
	int hiddenWhite2;
	int hiddenBlack1;
	int hiddenBlack2;
	int white;
	int black;

	bool createdHiddenWhite1;
	bool createdHiddenWhite2;
	bool createdHiddenBlack1;
	bool createdHiddenBlack2;

	//bool createHiddenHex(int hexId);

	//std::vector<std::shared_ptr<HiddenHex>> myHiddenHexCollection;

	std::vector<std::shared_ptr<Hexagon>>playerWhiteHexCollection;
	std::vector<std::shared_ptr<Hexagon>> playerBlackHexCollection;

	bool win;
	bool winQuestion(int turn);

	std::set<int> legalMoves;
	int moveId;
	bool winBlack;
	bool winWhite;

};

