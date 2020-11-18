#include <iostream>
#include "Game.h"

using namespace std;


int main()
{
	
	Game myGame;

	if (myGame.Load())
	{
		while (!myGame.GameOver())
		{
			myGame.Run();
		}

		cout << "You won!" << endl;
		
		// PlayWinSound();
	}
	else
	{
		cout << "Oops! Something went wrong.." << endl;
	}
}

//
//void PlayDoorClosedSound()
//{
//	Beep(500, 75);
//	Beep(500, 75);
//}
//
//void PlayDoorOpenedSound()
//{
//	Beep(1397, 200);
//}
//
//void PlayPickupKeySound()
//{
//	Beep(1568, 200);
//}
//
//void PlayWinSound()
//{
//	Beep(1568, 200);
//	Beep(1568, 200);
//	Beep(1568, 200);
//	Beep(1245, 1000);
//	Beep(1397, 200);
//	Beep(1397, 200);
//	Beep(1397, 200);
//	Beep(1175, 1000);
//}