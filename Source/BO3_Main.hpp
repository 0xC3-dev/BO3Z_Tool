#pragma once
#include "../Overlay/Overlay.hpp"
#include "../Extra_Headers/Display_Messages.hpp"

namespace Startup
{
	// Simple Random String Generator Function.
	std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?" };
	std::random_device rd;
	std::mt19937 generator(rd());
	std::string RandStr(DWORD length)
	{
		const DWORD char_size = (DWORD)chars.size();
		std::uniform_int_distribution<> random_int(0, char_size - 1);
		std::string output;
		for (DWORD i = 0; i < length; ++i)
			output.push_back(chars[random_int(generator)]);
		return output;
	}

	// Set Console App Title and Window Foreground Setting.
	void SetConsoleAppInfo()
	{
		SetConsoleTitle(RandStr(12).c_str());
	}

	// Get Pid and Module Base.
	void GetGameInfo()
	{
		Game::procID = Utils::GetProcId("BlackOps3.exe");
		if (Game::procID < 1)
		{
			Notify::Popup("Load Black Ops 3 first!", "[ ERROR ]", MB_ICONWARNING | MB_DEFBUTTON2);
			exit(0);
		}
		else if (Game::procID > 1)
		{
			Game::hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Game::procID);
			Game::moduleBase = Utils::GetModuleBaseAddress(Game::procID, "BlackOps3.exe");
			Engine::entity.SetPlayerAddr();
			Engine::entity.SetZombieAddr();
		}
	}

	// Create our Separate Threads.
	void CreateThreads()
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::Loop, 0 , 0, nullptr);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Engine::Aimbot::DoAimbot, 0, 0, nullptr);
	}

	// Config System.
	void ConfigSystem()
	{
		// Need to add.
	}
}