#pragma once
#include <string>
#include <future>
#include <vector>
#include "Board.h"
#include "MainPage.xaml.h"
#include "MainPage.g.h"

class Game
{
public:
	Game();
	int makeMove(int buttonId);
	int secondPlayerMoveLevel0();
	int secondPlayerMoveLevel1(const std::vector<int> moves);
	int foo(int hexId);
	int getTurn();
	void changeTurn();
	int turn;
	int turnLevel1;
	int boardGridEdgeSize;
	Board myBoard;
	void removeMoveFromSet(int hexId);
	int makeMoveLevel1(int hexId, Board& setUpBoard);
	int getTurnLevel1();
	void changeTurnLevel1();
	int findLegalMove(Board& setUpBoard);
	void removeMoveFromSetLevel1(int hexId, Board& setUpBoard);
	Board& loadCurrentBoard(std::vector<int> moves, Board& setUpBoard);
	void resetTurnLevel1();
	bool gameOver;
	int level;
	void setLevel(int myLevel);
};

