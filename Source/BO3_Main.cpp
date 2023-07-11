/*
*	UPDATE Channel Log:
*	
*	Update : 01/23/23 | Updated Codebase. Fixed several bugs. Fixed crashing issues due to No Recoil and God Mode.
*	
*	Update : 02/18/23 | Updated Codebase. Cleaned up file names.
* 
*	Update : 03/23/23 | Overhauled Codebase. Overhauled UI.
* 
*	Update : 05/09/23 | Updated offsets.
* 
*	Update : 07/11/23 | Updated Codebase. Cleaned up Player and Zombie Coordinate Reads/Writes.
* 
* 
*	TODO:
* 
*	Finish refining aimbot. Add true bone aim to make aimbot much better than roughly aiming at z head.
* 
*	Implement button toggle for key cycling weapons (currently hard coded to true).
* 
*	Add Zombie Counter Button Toggle in GUI. 
*/

#include "BO3_Main.h"

int main()
{
	Startup::SetConsoleAppInfo();
	Startup::GetGameInfo();
	Startup::CreateThreads();
	while (true)
	{
		Engine::IsInGame();
		Engine::Player1Features();
		Engine::Player2Features();
		Engine::Player3Features();
		Engine::Player4Features();
		Engine::ExtraGoodieFeatures();
		Engine::DisableAllFeatures();
		Sleep(5);
	}
}
