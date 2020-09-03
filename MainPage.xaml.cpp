//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Game.h"
#include <string>
#include <chrono>
#include <ppltasks.h>


using namespace polygon;
using namespace concurrency;
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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
Game *myGame;
bool gameOver;
bool twoPlayerMode;
int timeStep;



MainPage::MainPage()
{
	InitializeComponent();
	myGame = new Game();
	Turn->IsEnabled = false;
	gameOver = false;
	twoPlayerMode = false;
	autoGameSelected = false;
	singleMode = false;
	timeStep = 0;
	
	
}

void polygon::MainPage::clickHelper(Platform::Object^ sender, int buttonId)
{
	if (gameOver == true)
	{
		return;
	}

	if (autoGameSelected == true)
	{
		return;
	}
	// here test for myGame->getTurn() == 2 checks if it is blacks move
	if (singleMode == true && myGame->getTurn() == 2)
	{
		return;
	}

	movesSoFar.push_back(buttonId);
	int myRet = myGame->makeMove(buttonId);
	myGame->removeMoveFromSet(buttonId);
	Button^ b = safe_cast<Windows::UI::Xaml::Controls::Button^>(sender);

	

	if (myRet == 1)
	{
		b->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer2"));
	}
	if (myRet == 2)
	{
		b->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer2"));
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
	}

	if (myRet == 3)
	{
		gameOver = true;
		Turn->Content = "fini";
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonFini"));
		b->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
	}

	if (myRet == 4)
	{
		gameOver = true;
		Turn->Content = "fini";
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonFini"));
		b->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer2"));
	}
	b->IsEnabled = false;
	
	

	if (timeStep == 0)
	{
		TwoPlayerMode->IsEnabled = false;
		TwoPlayerMode->Content = "Single Mode";
		timeStep = 1;
		// initialize second player here
	}
	
	if (twoPlayerMode == false && myRet == 1)
	{
		
		blackToMove();
		//PlayerTwoAddMove(retByGame);
		/*
		auto myDispatcher = Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher;
	
		create_task(foo(2, movesSoFar).task::then([](int hexId)
			{
				//PlayerTwoAddMove(hexId);
				return hexId;
				
			}, task_continuation_context::use_arbitrary()).then([=](int hexId)
				{

					myDispatcher->RunAsync(
						Windows::UI::Core::CoreDispatcherPriority::Normal,
						ref new Windows::UI::Core::DispatchedHandler([this, hexId]()mutable
							{
								
								PlayerTwoAddMove(hexId);

							}));
					
				}
		));
		*/
	}
}


/*
the following two functions were written with the help of the following references
 Microsoft (2018) Creating Asynchronous Operations in Cpp for UWP Apps [online]
 Available at: https://docs.microsoft.com/en-us/cpp/parallel/concrt/creating-asynchronous-operations-in-cpp-for-windows-store-apps?view=vs-2019 [Accessed 9th January 2020]
 
 StackOverflow (2018) Updating UWP UI from PPL task continuation – warning C4451 [online] Available at: 
 https://stackoverflow.com/questions/49676840/updating-uwp-ui-from-ppl-task-continuation-warning-c4451   [Accessed 9th January 2020]
*/
void polygon::MainPage::blackToMove()
{
	auto myDispatcher = Windows::UI::Core::CoreWindow::GetForCurrentThread()->Dispatcher;

	create_task(foo(2, movesSoFar).task::then([](int hexId)
		{
			//PlayerTwoAddMove(hexId);
			return hexId;

		}, task_continuation_context::use_arbitrary()).then([=](int hexId)
			{

				myDispatcher->RunAsync(
					Windows::UI::Core::CoreDispatcherPriority::Normal,
					ref new Windows::UI::Core::DispatchedHandler([this, hexId]()mutable
						{

							PlayerTwoAddMove(hexId);

						}));

			}
		));
}


task<int> polygon::MainPage::foo(int hexId, const std::vector<int> moves)
{
	return create_task([hexId, moves]()
		{

			//int hex = myGame->secondPlayerMoveLevel0();
			int hex = myGame->secondPlayerMoveLevel1(moves);

			return hex;
		});

}



void polygon::MainPage::autoGameInit()
{
	
	autoGame();
}

void polygon::MainPage::disableLevelButtons()
{
	Level1->IsEnabled = false;
	Level2->IsEnabled = false;
	Level3->IsEnabled = false;
	Level4->IsEnabled = false;
	Level5->IsEnabled = false;
	Level6->IsEnabled = false;
	Level7->IsEnabled = false;
	Level8->IsEnabled = false;
	Level9->IsEnabled = false;
	Level10->IsEnabled = false;
}

void polygon::MainPage::autoGame()
{
	int hex = myGame->secondPlayerMoveLevel0();

	PlayerTwoAddMove(hex);
}
void polygon::MainPage::ButtonUIChange(Windows::UI::Xaml::Controls::Button^ b)
{
	if (myGame->getTurn() == 1)
	{
		b->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer2"));
	}
	else
	{
		b->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
	}
	b->IsEnabled = false;
}

Windows::UI::Xaml::Controls::Button^ polygon::MainPage::HexButtonSwitch(int hexId)
{
	switch (hexId)
	{
	case 1:
		return A1;
		break;
	case 2:
		return A2;
		break;
	case 3:
		return A3;
		break;
	case 4:
		return A4;
		break;
	case 5:
		return A5;
		break;
	case 6:
		return A6;
		break;
	case 7:
		return A7;
		break;
	case 8:
		return A8;
		break;
	case 9:
		return A9;
		break;
	case 10:
		return A10;
		break;
	case 11:
		return A11;
		break;

		// 12 - 22 B buttons
	case 12:
		return B1;
		break;
	case 13:
		return B2;
		break;
	case 14:
		return B3;
		break;
	case 15:
		return B4;
		break;
	case 16:
		return B5;
		break;
	case 17:
		return B6;
		break;
	case 18:
		return B7;
		break;
	case 19:
		return B8;
		break;
	case 20:
		return B9;
		break;
	case 21:
		return B10;
		break;
	case 22:
		return B11;
		break;

		// 23 - 33 C buttons
	case 23:
		return C1;
		break;
	case 24:
		return C2;
		break;
	case 25:
		return C3;
		break;
	case 26:
		return C4;
		break;
	case 27:
		return C5;
		break;
	case 28:
		return C6;
		break;
	case 29:
		return C7;
		break;
	case 30:
		return C8;
		break;
	case 31:
		return C9;
		break;
	case 32:
		return C10;
		break;
	case 33:
		return C11;
		break;


		// 34 - 44 D buttons
	case 34:
		return D1;
		break;
	case 35:
		return D2;
		break;
	case 36:
		return D3;
		break;
	case 37:
		return D4;
		break;
	case 38:
		return D5;
		break;
	case 39:
		return D6;
		break;
	case 40:
		return D7;
		break;
	case 41:
		return D8;
		break;
	case 42:
		return D9;
		break;
	case 43:
		return D10;
		break;
	case 44:
		return D11;
		break;

		// 45 - 55 E buttons
	case 45:
		return E1;
		break;
	case 46:
		return E2;
		break;
	case 47:
		return E3;
		break;
	case 48:
		return E4;
		break;
	case 49:
		return E5;
		break;
	case 50:
		return E6;
		break;
	case 51:
		return E7;
		break;
	case 52:
		return E8;
		break;
	case 53:
		return E9;
		break;
	case 54:
		return E10;
		break;
	case 55:
		return E11;
		break;

		// 56 - 66 F buttons
	case 56:
		return F1;
		break;
	case 57:
		return F2;
		break;
	case 58:
		return F3;
		break;
	case 59:
		return F4;
		break;
	case 60:
		return F5;
		break;
	case 61:
		return F6;
		break;
	case 62:
		return F7;
		break;
	case 63:
		return F8;
		break;
	case 64:
		return F9;
		break;
	case 65:
		return F10;
		break;
	case 66:
		return F11;
		break;

		// 67 - 77 G buttons
	case 67:
		return G1;
		break;
	case 68:
		return G2;
		break;
	case 69:
		return G3;
		break;
	case 70:
		return G4;
		break;
	case 71:
		return G5;
		break;
	case 72:
		return G6;
		break;
	case 73:
		return G7;
		break;
	case 74:
		return G8;
		break;
	case 75:
		return G9;
		break;
	case 76:
		return G10;
		break;
	case 77:
		return G11;
		break;

		// 78 - 88 H buttons
	case 78:
		return H1;
		break;
	case 79:
		return H2;
		break;
	case 80:
		return H3;
		break;
	case 81:
		return H4;
		break;
	case 82:
		return H5;
		break;
	case 83:
		return H6;
		break;
	case 84:
		return H7;
		break;
	case 85:
		return H8;
		break;
	case 86:
		return H9;
		break;
	case 87:
		return H10;
		break;
	case 88:
		return H11;
		break;

		// 89 - 99 I buttons
	case 89:
		return I1;
		break;
	case 90:
		return I2;
		break;
	case 91:
		return I3;
		break;
	case 92:
		return I4;
		break;
	case 93:
		return I5;
		break;
	case 94:
		return I6;
		break;
	case 95:
		return I7;
		break;
	case 96:
		return I8;
		break;
	case 97:
		return I9;
		break;
	case 98:
		return I10;
		break;
	case 99:
		return I11;
		break;

		// 100 - 110 J buttons
	case 100:
		return J1;
		break;
	case 101:
		return J2;
		break;
	case 102:
		return J3;
		break;
	case 103:
		return J4;
		break;
	case 104:
		return J5;
		break;
	case 105:
		return J6;
		break;
	case 106:
		return J7;
		break;
	case 107:
		return J8;
		break;
	case 108:
		return J9;
		break;
	case 109:
		return J10;
		break;
	case 110:
		return J11;
		break;

		// 111 - 121 K buttons
	case 111:
		return K1;
		break;
	case 112:
		return K2;
		break;
	case 113:
		return K3;
		break;
	case 114:
		return K4;
		break;
	case 115:
		return K5;
		break;
	case 116:
		return K6;
		break;
	case 117:
		return K7;
		break;
	case 118:
		return K8;
		break;
	case 119:
		return K9;
		break;
	case 120:
		return K10;
		break;
	case 121:
		return K11;
		break;
	}
}


void polygon::MainPage::PlayerTwoAddMove(int hexId)
{
	movesSoFar.push_back(hexId);
	int myRet = myGame->makeMove(hexId);
	
	myGame->removeMoveFromSet(hexId);

	Windows::UI::Xaml::Controls::Button^ b = HexButtonSwitch(hexId);

	ButtonUIChange(b);
	if (myGame->gameOver == true)
	{
		gameOver = true;
		if (myGame->getTurn() == 1)
		{

			
			AutoGameButton->IsEnabled = true;
			AutoGameButton->Content = "Black wins";
		}
		else
		{
			
			AutoGameButton->IsEnabled = true;
			AutoGameButton->Content = "White wins";
		}
		Turn->Content = "fini";
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonFini"));
		return;
	}
	
	if (twoPlayerMode == true || autoGameSelected == false)
	{
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
		return;
	}
	

	
		//Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
	if (myGame->getTurn() == 1)
	{
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer1"));
		autoGame();
	}
	else
	{
		Turn->Style = safe_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("ButtonPlayer2"));
		blackToMove();
	}
	
}


void polygon::MainPage::A1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	int buttonId = 1;
	clickHelper(sender, buttonId);
}




void polygon::MainPage::A2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 2;
	clickHelper(sender, buttonId);
}



void polygon::MainPage::A3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 3;
	clickHelper(sender, buttonId);
}



void polygon::MainPage::A4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 4;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::A5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 5;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::A6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 6;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::A7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 7;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::A8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 8;
	clickHelper(sender, buttonId);
}



void polygon::MainPage::A9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 9;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::A10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 10;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::A11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 11;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 12;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 13;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 14;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 15;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 16;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 17;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 18;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 19;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 20;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 21;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::B11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 22;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 23;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 24;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 25;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 26;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 27;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 28;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 29;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 30;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 31;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 32;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::C11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 33;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 34;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 35;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 36;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 37;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 38;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 39;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 40;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 41;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 42;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 43;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::D11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 44;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 45;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 46;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 47;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 48;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 49;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 50;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 51;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 52;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 53;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 54;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::E11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 55;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 56;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 57;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 58;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 59;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 60;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 61;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 62;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 63;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 64;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 65;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::F11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 66;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 67;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 68;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 69;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 70;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 71;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 72;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 73;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 74;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 75;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 76;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::G11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 77;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 78;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 79;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 80;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 81;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 82;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 83;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 84;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 85;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 86;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 87;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::H11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 88;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 89;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 90;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 91;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 92;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 93;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 94;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 95;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 96;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 97;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 98;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::I11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 99;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 100;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 101;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 102;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 103;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 104;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 105;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 106;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 107;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 108;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 109;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::J11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 110;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 111;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 112;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 113;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 114;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 115;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 116;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 117;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 118;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 119;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 120;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::K11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	int buttonId = 121;
	clickHelper(sender, buttonId);
}


void polygon::MainPage::TwoPlayerMode_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	twoPlayerMode = true;
	disableLevelButtons();
	TwoPlayerMode->IsEnabled = false;
	AutoGameButton->IsEnabled = false;
	PlayComputer->IsEnabled = false;
	TwoPlayerMode->Content = "Engaged";
	timeStep = 1;
}


void polygon::MainPage::Click_Level1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(10);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(20);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(30);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(40);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level5(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(50);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level6(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(60);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level7(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(70);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level8(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(80);
	disableLevelButtons();
}


void polygon::MainPage::Click_Level9(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(90);
	disableLevelButtons();
}




void polygon::MainPage::Click_Level10(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	myGame->setLevel(100);
	disableLevelButtons();
}


void polygon::MainPage::Click_AutoSelector(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	disableLevelButtons();
	TwoPlayerMode->IsEnabled = false;
	AutoGameButton->IsEnabled = false;
	PlayComputer->IsEnabled = false;
	autoGameSelected = true;
	autoGameInit();
}


void polygon::MainPage::Click_Singleton(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	disableLevelButtons();
	TwoPlayerMode->IsEnabled = false;
	AutoGameButton->IsEnabled = false;
	PlayComputer->IsEnabled = false;
	twoPlayerMode = false;
	autoGameSelected = false;
	singleMode = true;
	
}
