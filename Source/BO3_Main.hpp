#pragma once
#include "../Overlay/Overlay.hpp"
#include "../Extra_Headers/Display_Messages.hpp"
#include "../json/json.hpp"
#include "../fmt/format.hpp"

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
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		SetConsoleTitle(RandStr(12).c_str());
	}

	// Get Pid and Module Base.
	void GetGameInfo()
	{
		Game::procID = Utils::GetProcId("Spotify.exe"); // BlackOps3 // Spotify
		if (Game::procID < 1)
		{
			Notify::Popup("Load Black Ops 3 first!", "[ ERROR ]", MB_ICONWARNING | MB_DEFBUTTON2);
			exit(0);
		}
		else if (Game::procID > 1)
		{
			Game::hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Game::procID);
			Game::moduleBase = Utils::GetModuleBaseAddress(Game::procID, "Spotify.exe");
			//Engine::entity.SetPlayerAddr();
			//Engine::entity.SetZombieAddr();
		}
	}

	// Create our Separate Threads.
	void CreateThreads()
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::Loop, 0 , 0, nullptr);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Engine::Aimbot::DoAimbot, 0, 0, nullptr);
	}
}

namespace ConfigSystem
{
	// Convert Color to String for Json.
	std::string ColorToString(ImColor color)
	{
		float colors[4];
		colors[0] = color.Value.x;
		colors[1] = color.Value.y;
		colors[2] = color.Value.z;
		colors[3] = color.Value.w;

		std::string format = fmt::format("X({}) Y({}) Z({}) W({})", colors[0], colors[1], colors[2], colors[3]);
		return format;
	}

	// Convert String to Color for Json.
	ImVec4 StringToColor(std::string color)
	{
		float x, y, z, w;
		sscanf_s(color.c_str(), "X(%f) Y(%f) Z(%f) W(%f)", &x, &y, &z, &w);

		return ImVec4(x, y, z, w);
	}

	// Validate Dir.
	void ValidatePath(std::filesystem::path path)
	{
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
		}
		else if (!std::filesystem::is_directory(path))
		{
			std::filesystem::remove(path);
			std::filesystem::create_directory(path);
		}
	}

	// Get Current File Path Dir.
	std::filesystem::path GetCurrentFilePathDir()
	{
		std::filesystem::path filePath = std::filesystem::current_path();
		filePath /= "BO3Z_Tool_Config";
		ValidatePath(filePath);
		return filePath;
	}

	// Import Settongs from Config.
	void ImportFromJson(const nlohmann::json& j)
	{
		FeatureSettings::bP1InfiniteHealth = j["P1 Godmode"];
	}

	// Write to json format.
	nlohmann::json ToJson()
	{
		return nlohmann::json{
			{ "P1 Godmode", FeatureSettings::bP1InfiniteHealth }
		};
	}

	// Setup Load and Save Config Files.
	void SetupLoadAndSaveConfig(const char* configFile, bool* configLoad, bool* configLoaded, bool* saveConfig, bool* savedConfig)
	{
		if (*configLoad)
		{
			if (std::filesystem::exists(GetCurrentFilePathDir()))
			{
				std::filesystem::path BO3ZMConfig = GetCurrentFilePathDir();

				BO3ZMConfig /= configFile;

				if (!std::filesystem::exists(BO3ZMConfig))
				{
					*configLoad = false;
					*configLoaded = false;
				}
				else
				{
					// Load Config from File.
					nlohmann::json jImportSettings;
					std::ifstream iReadFile;
					iReadFile.open(BO3ZMConfig);
					iReadFile >> jImportSettings;
					iReadFile.close();
					ImportFromJson(jImportSettings);
				}
				*configLoad = false;
			}
		}
		if (*saveConfig)
		{
			if (std::filesystem::exists(GetCurrentFilePathDir()))
			{
				std::filesystem::path BO3ZMConfig = GetCurrentFilePathDir();

				BO3ZMConfig /= configFile;

				if (!std::filesystem::exists(BO3ZMConfig))
				{
					*saveConfig = false;
					*savedConfig = true;
					// Create Save Config File.
					std::ofstream bSaveFile;
					bSaveFile.open(BO3ZMConfig);
					bSaveFile << ToJson().dump(4);
					bSaveFile.close();
				}
				else
				{
					*savedConfig = true;
					std::ofstream bSaveFile;
					bSaveFile.open(BO3ZMConfig);
					bSaveFile << ToJson().dump(4);
					bSaveFile.close();
				}
				*saveConfig = false;
			}
		}
	}

	// Load and Save Config Files.
	void LoadAndSaveConfig()
	{
		SetupLoadAndSaveConfig("Config1.json", &ConfigSettings::bLoadConfig1, &ConfigSettings::bLoadedConfig1, &ConfigSettings::bSaveConfig1, &ConfigSettings::bSavedConfig1);
		SetupLoadAndSaveConfig("Config2.json", &ConfigSettings::bLoadConfig2, &ConfigSettings::bLoadedConfig2, &ConfigSettings::bSaveConfig2, &ConfigSettings::bSavedConfig2);
		SetupLoadAndSaveConfig("Config3.json", &ConfigSettings::bLoadConfig3, &ConfigSettings::bLoadedConfig3, &ConfigSettings::bSaveConfig3, &ConfigSettings::bSavedConfig3);
		SetupLoadAndSaveConfig("Config4.json", &ConfigSettings::bLoadConfig4, &ConfigSettings::bLoadedConfig4, &ConfigSettings::bSaveConfig4, &ConfigSettings::bSavedConfig4);
		SetupLoadAndSaveConfig("Config5.json", &ConfigSettings::bLoadConfig5, &ConfigSettings::bLoadedConfig5, &ConfigSettings::bSaveConfig5, &ConfigSettings::bSavedConfig5);
	}
}