#pragma once
#include "../Includes/Includes.h"
#include "../Engine/Engine.h"
#include "../Overlay/Overlay.h"
#include "../Extra_Headers/Display_Messages.h"

namespace Startup
{
	// Simple Random String Generator Function.
	std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?" };
	std::random_device rd;
	std::mt19937 generator(rd());
	std::string RandStr(size_t length)
	{
		const size_t char_size = chars.size();
		std::uniform_int_distribution<> random_int(0, char_size - 1);
		std::string output;
		for (size_t i = 0; i < length; ++i)
			output.push_back(chars[random_int(generator)]);
		return output;
	}

	// Set Console App Title and Window Foreground Setting.
	void SetConsoleAppInfo()
	{
		SetConsoleTitle(RandStr(12).c_str());
		ShowWindow(GetConsoleWindow(), FALSE);
	}

	// Get Pid and Module Base.
	void GetGameInfo()
	{
		Game::procID = Utils::GetProcId("BlackOps3.exe");
		Game::hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Game::procID);
		if (Game::procID < 1)
		{
			Notify::Popup("Load Black Ops 3 first!", "[ ERROR ]", MB_ICONWARNING | MB_DEFBUTTON2);
			exit(0);
		}
		else if (Game::procID > 1)
		{
			Game::moduleBase = Utils::GetModuleBaseAddress(Game::procID, "BlackOps3.exe");
		}
	}

	// Create our Separate Threads so ESP is as smooth as possible.
	void CreateThreads()
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::Loop, nullptr, 0, nullptr);
	}

	// Config System.
	void ConfigSystem()
	{
		
	}
}