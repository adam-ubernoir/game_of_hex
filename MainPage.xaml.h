//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <string>
#include <vector>

namespace polygon
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
		
		

	private:
		bool singleMode;
		bool autoGameSelected;
		std::vector<int> movesSoFar;
		void PlayerTwoAddMove(int hexId);
		void blackToMove();
		void autoGameInit();
		void autoGame();
		void disableLevelButtons();
		concurrency::task<int> foo(int hexId, const std::vector<int> moves);
		Windows::UI::Xaml::Controls::Button^ HexButtonSwitch(int hexId);
		void polygon::MainPage::ButtonUIChange(Windows::UI::Xaml::Controls::Button^ b);
		void A1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void clickHelper(Platform::Object^ sender, int buttonId);
		void A4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void A11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void B11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void C11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void D11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void E11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void F11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void G11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void H11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void I11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void J11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void K11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void TwoPlayerMode_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level4(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level5(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level6(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level7(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level8(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level9(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Level10(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_AutoSelector(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Click_Singleton(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
};
}
