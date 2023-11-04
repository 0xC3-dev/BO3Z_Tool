/*
*	UPDATE Change Log:
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
*	Update : 07/13/23 | Added button toggle for weapon cycle. Also added combo box (aka dropdown menu) for selecting weapon cycle hotkey. Also added Zombie Counter toggle to Player 1 Exploits.
* 
*	Update : 11/03/23 | A lot has been updated. Mostly codebase updates with a sprinkle of ESP features added in.
* 
* 
*	TODO:
* 
*	Aimbot: Refine Aimbot and add Skeleton/Bone Selection.
*	ESP: Add Skeleton ESP.
*	Exploits: Fix JetPack feature. Fix No Spread.
*	Config System: Add Config System to Load/Save feature states.
*/

#include "BO3_Main.hpp"

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
		Sleep(2);
	}
}
