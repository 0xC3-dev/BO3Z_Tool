#pragma once
#include "../Vectors/Vectors.hpp"
#include "../../Utils/Utils.hpp"

namespace SDK
{
	int IsInGame();

	bool WorldToScreen(vec3_t originPos, vec2_t& screenOut, int windowWidth, int windowHeight);

	float UnitsToMeter(float units);

	class Entity_t
	{
	private:
		// Current addresses.
		uintptr_t playerClipAmmoAddr = 0;
		uintptr_t playerStockAmmoAddr = 0;
		uintptr_t playerPointsAddr = 0;
		uintptr_t playerRunSpeedAddr = 0;
		uintptr_t playerRapidFireAddr = 0;
		uintptr_t playerNoSpreadAddr = 0;
		uintptr_t playerSetWeaponAddr = 0;
		uintptr_t playerGetPosAddr = 0;
		//
		uintptr_t zombieHealthAddr = 0;
		uintptr_t zombieHealthMaxAddr = 0;
		uintptr_t zombieGetPosAddr = 0;
		uintptr_t zombieGetHeadPosAddr = 0;
	public:
#pragma region Player Functions
		__inline void SetPlayerAddr()
		{
			Offsets::playerBase = Game::moduleBase + Offsets::playerBasePtr;
			Offsets::playerPedBase = Game::moduleBase + Offsets::playerPedPtr;
			Offsets::inGameAddr = Game::moduleBase + Offsets::inGamePtr;
			Offsets::jumpHeightBase = Game::moduleBase + Offsets::jumpHeightPtr;
			Offsets::playerNoRecoilBase = Game::moduleBase + Offsets::playerNoRecoilPtr;
			Offsets::inGameAddr = Game::moduleBase + Offsets::inGamePtr;
		}

		__inline void GetPlayerAddr()
		{
			Offsets::playerPedBaseAddr = Utils::PointerChain(Game::hProc, Offsets::playerPedBase, Offsets::playerGodModeOffset);
			playerClipAmmoAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerClipAmmoOffset);
			playerStockAmmoAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerStockAmmoOffset);
			playerRunSpeedAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerRunSpeedOffset);
			playerPointsAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerPointsOffset);
			playerRapidFireAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerRapidFireOffset);
			playerNoSpreadAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerNoSpreadOffset);
			playerSetWeaponAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerSetWeaponOffset);
			playerGetPosAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerCoordOffset);
			zombieHealthAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieHealthOffset);
			zombieHealthMaxAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieHealthMaxOffset);
			zombieGetPosAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieCoord);
			zombieGetHeadPosAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieHeadCoord);
		}

		__inline void GetPlayerValues()
		{
			Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 0), (BYTE*)&GameValues::iPlayer1CurrentPointsValue, sizeof(GameValues::iPlayer1CurrentPointsValue), Game::hProc);
			Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 1), (BYTE*)&GameValues::iPlayer2CurrentPointsValue, sizeof(GameValues::iPlayer2CurrentPointsValue), Game::hProc);
			Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 2), (BYTE*)&GameValues::iPlayer3CurrentPointsValue, sizeof(GameValues::iPlayer3CurrentPointsValue), Game::hProc);
			Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 3), (BYTE*)&GameValues::iPlayer4CurrentPointsValue, sizeof(GameValues::iPlayer4CurrentPointsValue), Game::hProc);
			FeatureSettings::iP1PointsValue = GameValues::iPlayer1CurrentPointsValue;
			FeatureSettings::iP2PointsValue = GameValues::iPlayer2CurrentPointsValue;
			FeatureSettings::iP3PointsValue = GameValues::iPlayer3CurrentPointsValue;
			FeatureSettings::iP4PointsValue = GameValues::iPlayer4CurrentPointsValue;
		}

		__inline uintptr_t GetJumpHeightBase()
		{
			return Offsets::jumpHeightBase;
		}

		__inline void SetGodMode(int index, bool* state)
		{
			// Check whether we are back in lobby that way we don't crash the game. I'm sure this can be cleaner but it's a temp fix for now.
			Utils::Read((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeDefaultValue, sizeof(GameValues::iPlayerGodModeDefaultValue), Game::hProc);

			if (*state)
			{
				if (GameValues::iPlayerGodModeDefaultValue == 0)
					return;

				if (GameValues::iPlayerGodModeCurrentValue != GameValues::iPlayerGodModeOn)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOn, sizeof(GameValues::iPlayerGodModeOn), Game::hProc);
					GameValues::iPlayerGodModeCurrentValue = GameValues::iPlayerGodModeOn;
				}
			}
			else if (!*state)
			{
				if (GameValues::iPlayerGodModeCurrentValue == 0)
					return;

				if (GameValues::iPlayerGodModeCurrentValue != GameValues::iPlayerGodModeOff)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOff, sizeof(GameValues::iPlayerGodModeOff), Game::hProc);
					GameValues::iPlayerGodModeCurrentValue = GameValues::iPlayerGodModeOff;
				}
			}
		}

		__inline void SetPlayerClipAmmo(int index)
		{
			for (int i = 0; i < 9; i++)
			{
				Utils::Write((BYTE*)playerClipAmmoAddr + (Offsets::playerArray * i) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayerNewAmmoValue, sizeof(GameValues::iPlayerNewAmmoValue), Game::hProc);
			}
		}

		__inline void SetPlayerStockAmmo(int index)
		{
			for (int i = 0; i < 9; i++)
			{
				Utils::Write((BYTE*)playerStockAmmoAddr + (Offsets::playerArray * i) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayerNewAmmoValue, sizeof(GameValues::iPlayerNewAmmoValue), Game::hProc);
			}
		}

		__inline void SetCustomPlayerPoints(int index)
		{
			switch (index)
			{
			case 0:
				GameValues::iPlayer1NewCustomPointsValue = FeatureSettings::iP1PointsValue;
				Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer1NewCustomPointsValue, sizeof(GameValues::iPlayer1NewCustomPointsValue), Game::hProc);
				break;
			case 1:
				GameValues::iPlayer2NewCustomPointsValue = FeatureSettings::iP2PointsValue;
				Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer2NewCustomPointsValue, sizeof(GameValues::iPlayer2NewCustomPointsValue), Game::hProc);
				break;
			case 2:
				GameValues::iPlayer3NewCustomPointsValue = FeatureSettings::iP3PointsValue;
				Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer3NewCustomPointsValue, sizeof(GameValues::iPlayer3NewCustomPointsValue), Game::hProc);
				break;
			case 3:
				GameValues::iPlayer4NewCustomPointsValue = FeatureSettings::iP4PointsValue;
				Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer4NewCustomPointsValue, sizeof(GameValues::iPlayer4NewCustomPointsValue), Game::hProc);
				break;
			}
		}

		__inline void FreezePlayerPoints(int index)
		{
			SetCustomPlayerPoints(index);
		}

		__inline void EnableInstaKill()
		{
			for (int i = 0; i < 80; i++)
			{
				Utils::Read((BYTE*)zombieHealthAddr + (Offsets::zombieArraySize * i), (BYTE*)&GameValues::iZombieInstaKillCurrentHealthValue, sizeof(GameValues::iZombieInstaKillCurrentHealthValue), Game::hProc);
				if (GameValues::iZombieInstaKillCurrentHealthValue < 1)
					continue;
				Utils::Write((BYTE*)zombieHealthAddr + (Offsets::zombieArraySize * i), (BYTE*)&GameValues::iZombieNewHealthValue, sizeof(GameValues::iZombieNewHealthValue), Game::hProc);
			}
		}

		__inline void SetPlayerJumpHeight(bool* state)
		{
			if (*state)
			{
				if (FeatureSettings::iJumpHeightValue == 39.f)
					return;

				GameValues::fGlobalNewJumpHeightValue = FeatureSettings::iJumpHeightValue;
				Utils::Write((BYTE*)GetJumpHeightBase(), (BYTE*)&GameValues::fGlobalNewJumpHeightValue, sizeof(GameValues::fGlobalNewJumpHeightValue), Game::hProc);
			}
			else if (!*state)
			{
				GameValues::fGlobalNewJumpHeightValue = 39.f;
				Utils::Write((BYTE*)GetJumpHeightBase(), (BYTE*)&GameValues::fGlobalNewJumpHeightValue, sizeof(GameValues::fGlobalNewJumpHeightValue), Game::hProc);
			}
		}

		__inline void SetPlayerRunSpeed(int index)
		{
			switch (index)
			{
			case 0:
				GameValues::fPlayer1NewRunSpeedValue = FeatureSettings::iP1RunValue;
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer1NewRunSpeedValue, sizeof(GameValues::fPlayer1NewRunSpeedValue), Game::hProc);
				break;
			case 1:
				GameValues::fPlayer2NewRunSpeedValue = FeatureSettings::iP2RunValue;
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer2NewRunSpeedValue, sizeof(GameValues::fPlayer2NewRunSpeedValue), Game::hProc);
				break;
			case 2:
				GameValues::fPlayer3NewRunSpeedValue = FeatureSettings::iP3RunValue;
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer3NewRunSpeedValue, sizeof(GameValues::fPlayer3NewRunSpeedValue), Game::hProc);
				break;
			case 3:
				GameValues::fPlayer4NewRunSpeedValue = FeatureSettings::iP4RunValue;
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer4NewRunSpeedValue, sizeof(GameValues::fPlayer4NewRunSpeedValue), Game::hProc);
				break;
			}
		}

		__inline void EnableRapidFire(int index)
		{
			Utils::Write((BYTE*)playerRapidFireAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayerNewRapidFireValue, sizeof(GameValues::iPlayerNewRapidFireValue), Game::hProc);
		}

		__inline void SetNoRecoil(bool* state)
		{
			if (*state)
			{
				if (GameValues::iPlayerGodModeDefaultValue == 0)
					return;

				if (GameValues::noRecoilValue != std::byte(0x75))
				{
					Utils::Write((BYTE*)Offsets::playerNoRecoilBase, (BYTE*)&GameValues::iPlayerNoRecoilOn, sizeof(GameValues::iPlayerNoRecoilOn), Game::hProc);
					GameValues::noRecoilValue = std::byte(0x75);
				}
			}
			else if (!*state)
			{
				if (GameValues::noRecoilValue != std::byte(0x74))
				{
					Utils::Write((BYTE*)Offsets::playerNoRecoilBase, (BYTE*)&GameValues::iPlayerNoRecoilOff, sizeof(GameValues::iPlayerNoRecoilOff), Game::hProc);
					GameValues::noRecoilValue = std::byte(0x74);
				}
			}
		}

		// Needs Fixed.
		__inline void EnableNoSpread()
		{
			Utils::Write((BYTE*)playerNoSpreadAddr, (BYTE*)&GameValues::iPlayerNoSpreadValue, sizeof(GameValues::iPlayerNoSpreadValue), Game::hProc);
		}

		// Needs Fixed.
		__inline void EnablePlayerJetPck()
		{
			if (GetAsyncKeyState(VK_SPACE) && 1)
			{
				Utils::Read((BYTE*)Offsets::playerZCoordAddr, (BYTE*)&GameValues::fCurrentPlayerCoordsZ, sizeof(GameValues::fCurrentPlayerCoordsZ), Game::hProc);
				GameValues::fGlobalJetPackValue = GameValues::fCurrentPlayerCoordsZ + GameValues::fGlobalJetPackAddValue;
				Utils::Write((BYTE*)Offsets::playerZCoordAddr, (BYTE*)&GameValues::fGlobalJetPackValue, sizeof(GameValues::fGlobalJetPackValue), Game::hProc);
			}
		}

		__inline void SetPlayerWeapon(int index)
		{
			switch (index)
			{
			case 0:
				GameValues::iPlayer1NewWeaponValue = FeatureSettings::iP1WCValue;
				Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer1NewWeaponValue, sizeof(GameValues::iPlayer1NewWeaponValue), Game::hProc);
				break;
			case 1:
				GameValues::iPlayer2NewWeaponValue = FeatureSettings::iP2WCValue;
				Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer2NewWeaponValue, sizeof(GameValues::iPlayer2NewWeaponValue), Game::hProc);
				break;
			case 2:
				GameValues::iPlayer3NewWeaponValue = FeatureSettings::iP3WCValue;
				Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer3NewWeaponValue, sizeof(GameValues::iPlayer3NewWeaponValue), Game::hProc);
				break;
			case 3:
				GameValues::iPlayer4NewWeaponValue = FeatureSettings::iP4WCValue;
				Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer4NewWeaponValue, sizeof(GameValues::iPlayer4NewWeaponValue), Game::hProc);
				break;
			}
		}

		__inline vec3_t GetPlayerPos()
		{
			Utils::Read((BYTE*)playerGetPosAddr, (BYTE*)&GameValues::currentPlayerCoords, sizeof(GameValues::currentPlayerCoords), Game::hProc);
			return GameValues::currentPlayerCoords;
		}

		__inline vec3_t GetZombiePos(int index)
		{
			Utils::Read((BYTE*)zombieGetPosAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::currentZombieCoords, sizeof(GameValues::currentZombieCoords), Game::hProc);
			return GameValues::currentZombieCoords;
		}

		__inline vec3_t GetZombieHeadPos(int index)
		{
			Utils::Read((BYTE*)zombieGetHeadPosAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::currentZombieHeadCoords, sizeof(GameValues::currentZombieHeadCoords), Game::hProc);
			return GameValues::currentZombieHeadCoords;
		}

		__inline vec3_t GetHeadPosition(vec3_t origin)
		{
			return origin - vec3_t{ 10, 20, 10 };
		}

		__inline void GetBox(vec2_t screenOrigin, vec2_t screenHead, vec2_t& topLeft, vec2_t& bottomRight)
		{
			auto height = screenOrigin.y - screenHead.y;
			auto width = 0;
			width = height / 4.0f;

			auto size = 1;
			auto left_x = screenOrigin.x - width - size;
			auto right_x = screenOrigin.x + width + size;
			auto top_y = screenHead.y - size;
			auto bottom_y = screenOrigin.y + size;

			topLeft = { left_x, top_y };
			bottomRight = { right_x, bottom_y };
		}
#pragma endregion

#pragma region Zombie Functions
		__inline void SetZombieAddr()
		{
			Offsets::zombieBase = Game::moduleBase + Offsets::zombieBasePtr;
			Offsets::zombieCountBase = Game::moduleBase + Offsets::zombieCountPtr;
		}

		__inline int GetZombieHealth(int index)
		{
			Utils::Read((BYTE*)zombieHealthAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iZombieCurrentHealthValue, sizeof(GameValues::iZombieCurrentHealthValue), Game::hProc);
			return GameValues::iZombieCurrentHealthValue;
		}

		__inline int GetZombieHealthMax(int index)
		{
			Utils::Read((BYTE*)zombieHealthMaxAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iZombieMaxHealthValue, sizeof(GameValues::iZombieMaxHealthValue), Game::hProc);
			return GameValues::iZombieMaxHealthValue;
		}

		__inline void EnableZombieTP()
		{
			if (GetAsyncKeyState(MiscSettings::iZombieTPKey) & 1)
			{
				// Player Coords.
				Utils::Read((BYTE*)playerGetPosAddr, (BYTE*)&GameValues::currentPlayerCoordsTeleport, sizeof(GameValues::currentPlayerCoordsTeleport), Game::hProc);
			}
			for (int i = 0; i < 80; i++)
			{
				// Zombie Coords.
				Utils::Write((BYTE*)zombieGetPosAddr + (Offsets::zombieArraySize * i), (BYTE*)&GameValues::currentPlayerCoordsTeleport, sizeof(GameValues::currentPlayerCoordsTeleport), Game::hProc);
			}
		}

		__inline int GetZombieCount()
		{
			Utils::Read((BYTE*)Offsets::zombieCountBase, (BYTE*)&GameValues::iZombieCountValue, sizeof(GameValues::iZombieCountValue), Game::hProc);
			return GameValues::iZombieCountValue;
		}
#pragma endregion
	};
}
