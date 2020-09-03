#include "pch.h"
#include "Game.h"
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "MainPage.xaml.h"
#include "MainPage.g.h"


using namespace polygon;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

		Game::Game()
		{
		
			turn = 1;
			turnLevel1 = 1;
			boardGridEdgeSize = 11;
			gameOver = false;
			myBoard = Board::Board(boardGridEdgeSize);
			level = 10;
		}

		int Game::makeMove(int hexId)
		{
			int turnValue = getTurn();
			int winQuestion = myBoard.addMoveToBoard(hexId, turnValue);
			if (winQuestion == 0)
			{
				changeTurn();
				return turnValue;
			}
			else
			{
				gameOver = true;
				if (turnValue == 1)
				{
					changeTurn();
					return 3;
				}
				else

				{
					changeTurn();
					return 4;
				}
			}
		}

		int Game::getTurn()
		{
			return turn;
		}

		void Game::changeTurn()
		{
			if (turn == 1)
			{
				turn++;
				return;
			}
			else
			{
				turn--;
				return;
			}
		}

	void Game::setLevel(int myLevel)
		{
			level = myLevel;
		}

	int Game::foo(int hexId)
		{
		std::srand(time(NULL));
		int val = 0;
		while (true)
		{
			 val = rand() % 121;
			if (myBoard.legalMoves.find(val) == myBoard.legalMoves.end())
			{
				continue;
			}
			break;
		}
		return val;
		}

		int Game::secondPlayerMoveLevel0()
		{
			std::srand(time(NULL));
			int val = 0;
			while (true)
			{
				val = rand() % 121 + 1;
				if (myBoard.legalMoves.find(val) == myBoard.legalMoves.end())
				{
					continue;
				}
				break;
			}
			return val;
		}

		void Game::removeMoveFromSet(int hexId)
		{
			
			myBoard.legalMoves.erase(hexId);

		}

		int Game::secondPlayerMoveLevel1(const std::vector<int> moves)
		{
			int val = 0;
			int initialMove = 0;

			struct moveAndSpeed {
				int moveId;
				int speedNumber;
			};

			std::vector<moveAndSpeed> myVal;

			for (int i = 0; i < level; ++i)
			{
				Board setUpBoard = Board::Board(boardGridEdgeSize);

				loadCurrentBoard(moves, setUpBoard);

				initialMove = findLegalMove(setUpBoard);
				val = initialMove;
				int winQuestion = 0;

				while (setUpBoard.winBlack == false && setUpBoard.winWhite == false)
				{
					winQuestion = makeMoveLevel1(val, setUpBoard);
					removeMoveFromSetLevel1(val, setUpBoard);
					val = findLegalMove(setUpBoard);
					if (val == -1 && (setUpBoard.winBlack == false && setUpBoard.winWhite == false))
					{
						break;
					}
				}
				if (setUpBoard.winBlack == true)
				{
					moveAndSpeed valWanted;
					valWanted.moveId = initialMove;
					valWanted.speedNumber = setUpBoard.moveId;
					myVal.push_back(valWanted);
				}

				resetTurnLevel1();
			}
			if (myVal.size() == 0)
			{
				return initialMove;
			}

			int swap = 122;
			int bestMove = 0;

			for (auto low : myVal)
			{
				if (low.speedNumber < swap)
				{
					swap = low.speedNumber;
					bestMove = low.moveId;
				}
			}


			return bestMove;
			
		}

		int Game::makeMoveLevel1(int hexId, Board& setUpBoard)
		{
			int turnValue = getTurnLevel1();
			int winQuestion = setUpBoard.addMoveToBoard(hexId, turnValue);
			if (setUpBoard.winWhite == false && setUpBoard.winBlack == false)
			{
				changeTurnLevel1();
				return turnValue;
			}
			else
			{
				if (turnValue == 1)
				{
					return 3;
				}
				else return 4;
			}
		}

		int Game::getTurnLevel1()
		{
			return turnLevel1;
		}

		void Game::changeTurnLevel1()
		{
			if (turnLevel1 == 1)
			{
				turnLevel1++;
				return;
			}
			else
			{
				turnLevel1--;
				return;
			}
		}

		int Game::findLegalMove(Board& setUpBoard)
		{
			std::srand(time(NULL));
			int val = 0;
			while (true)
			{
				if (setUpBoard.legalMoves.size() == 0)
				{
					return -1;
					break;
				}
				val = rand() % 121 + 1;
				if (setUpBoard.legalMoves.find(val) == setUpBoard.legalMoves.end())
				{
					continue;
				}
				
				break;
			}

			return val;
		}

		void Game::removeMoveFromSetLevel1(int hexId,  Board& setUpBoard)
		{

			setUpBoard.legalMoves.erase(hexId);

		}

		Board& Game::loadCurrentBoard(std::vector<int> moves, Board& setUpBoard)
		{
			for (auto move : moves)
			{
				setUpBoard.addMoveToBoard(move, getTurnLevel1());
				removeMoveFromSetLevel1(move, setUpBoard);
				changeTurnLevel1();

			}

			return setUpBoard;
		}

		void Game::resetTurnLevel1()
		{
			turnLevel1 = 1;
		}