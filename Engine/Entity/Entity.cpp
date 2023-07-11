#include "Entity_t.h"
#include <iostream>

#pragma region Player Functions
void Entity_t::SetPlayerAddr()
{
	playerBase = Game::moduleBase + playerBasePtr;
	playerPedBase = Game::moduleBase + playerPedPtr;
	inGameAddr = Game::moduleBase + inGamePtr;
	jumpHeightBase = Game::moduleBase + jumpHeightPtr;
	playerNoRecoilBase = Game::moduleBase + playerNoRecoilPtr;
}

uintptr_t Entity_t::GetJumpHeightBase()
{
	return jumpHeightBase;
}

void Entity_t::SetGodMode(int index, BOOL state)
{
	if (!playerPedBaseAddr)
	{
		playerPedBaseAddr = Utils::PointerChain(Game::hProc, playerPedBase, playerGodModeOffset);
	}
	if (state)
	{
		if (iPlayerGodModeValue != iPlayerGodModeOn)
		{
			iPlayerGodModeValue = iPlayerGodModeOn;
			Utils::Write((BYTE*)playerPedBaseAddr + (zombieArraySize * index), (BYTE*)&iPlayerGodModeOn, sizeof(iPlayerGodModeOn), Game::hProc);
		}
	}
	else if (!state)
	{
		if (iPlayerGodModeValue != iPlayerGodModeOff)
		{
			iPlayerGodModeValue = iPlayerGodModeOff;
			Utils::Write((BYTE*)playerPedBaseAddr + (zombieArraySize * index), (BYTE*)&iPlayerGodModeOff, sizeof(iPlayerGodModeOff), Game::hProc);
		}
	}
}

void Entity_t::SetPlayerClipAmmo(int index)
{
	playerBaseAddr = Utils::PointerChain(Game::hProc, playerBase, playerClipAmmoOffset);
	for (uintptr_t a = 0; a < 9; a++)
	{
		Utils::Write((BYTE*)playerBaseAddr + (a * playerArray) + (playerArraySizeOffset * index), (BYTE*)&iPlayerNewAmmoValue, sizeof(iPlayerNewAmmoValue), Game::hProc);
	}
}

void Entity_t::SetPlayerStockAmmo(int index)
{
	playerBaseAddr = Utils::PointerChain(Game::hProc, playerBase, playerStockAmmoOffset);
	for (uintptr_t a = 0; a < 9; a++)
	{
		Utils::Write((BYTE*)playerBaseAddr + (a * playerArray) + (playerArraySizeOffset * index), (BYTE*)&iPlayerNewAmmoValue, sizeof(iPlayerNewAmmoValue), Game::hProc);
	}
}

void Entity_t::SetCustomPlayerPoints(int index)
{
	playerBaseAddr = Utils::PointerChain(Game::hProc, playerBase, playerPointsOffset);
	switch (index)
	{
		case 0:
			iPlayerNewCustomPointsValue = FeatureSettings::iP1PointsValue;
			break;
		case 1:
			iPlayerNewCustomPointsValue = FeatureSettings::iP2PointsValue;
			break;
		case 2:
			iPlayerNewCustomPointsValue = FeatureSettings::iP3PointsValue;
			break;
		case 3:
			iPlayerNewCustomPointsValue = FeatureSettings::iP4PointsValue;
			break;
	}
	Utils::Write((BYTE*)playerBaseAddr + (playerArraySizeOffset * index), (BYTE*)&iPlayerNewCustomPointsValue, sizeof(iPlayerNewCustomPointsValue), Game::hProc);
}

void Entity_t::FreezePlayerPoints(int index)
{
	playerBaseAddr = Utils::PointerChain(Game::hProc, playerBase, playerPointsOffset);
	switch (index)
	{
	case 0:
		iPlayerNewCustomPointsValue = FeatureSettings::iP1PointsValue;
		break;
	case 1:
		iPlayerNewCustomPointsValue = FeatureSettings::iP2PointsValue;
		break;
	case 2:
		iPlayerNewCustomPointsValue = FeatureSettings::iP3PointsValue;
		break;
	case 3:
		iPlayerNewCustomPointsValue = FeatureSettings::iP4PointsValue;
		break;
	}
	Utils::Write((BYTE*)playerBaseAddr + (playerArraySizeOffset * index), (BYTE*)&iPlayerNewCustomPointsValue, sizeof(iPlayerNewCustomPointsValue), Game::hProc);
}

void Entity_t::EnableInstaKill()
{
	for (uintptr_t i = 0; i < 80; i++)
	{
		Utils::Read((BYTE*)playerPedHealthAddr + (zombieArraySize * i), (BYTE*)&iZombieCurrentHealthValue, sizeof(iZombieCurrentHealthValue), Game::hProc);

		if (iZombieCurrentHealthValue < 1)
			continue;

		Utils::Write((BYTE*)playerPedHealthAddr + (zombieArraySize * i), (BYTE*)&iZombieNewHealthValue, sizeof(iZombieNewHealthValue), Game::hProc);
	}
}

void Entity_t::SetPlayerJumpHeight()
{
	fGlobalNewJumpHeightValue = FeatureSettings::iJumpHeightValue;
	Utils::Write((BYTE*)GetJumpHeightBase(), (BYTE*)&fGlobalNewJumpHeightValue, sizeof(fGlobalNewJumpHeightValue), Game::hProc);
}

void Entity_t::SetPlayerRunSpeed()
{
	// Need to Add.
}

void Entity_t::EnableRapidFire(int index)
{
	playerBaseAddr = Utils::PointerChain(Game::hProc, playerBase, playerRapidFireOffset);
	Utils::Write((BYTE*)playerBaseAddr + (playerArraySizeOffset * index), (BYTE*)&iPlayerNewRapidFireValue, sizeof(iPlayerNewRapidFireValue), Game::hProc);
}

void Entity_t::SetNoRecoil(BOOL state)
{
	if (state)
	{
		if (noRecoilValue != std::byte(0x75))
		{
			noRecoilValue = std::byte(0x75);
			Utils::Write((BYTE*)playerNoRecoilBase, (BYTE*)&noRecoilValue, sizeof(noRecoilValue), Game::hProc);
		}
	}
	else if (!state)
	{
		if (noRecoilValue != std::byte(0x74))
		{
			noRecoilValue = std::byte(0x74);
			Utils::Write((BYTE*)playerNoRecoilBase, (BYTE*)&noRecoilValue, sizeof(noRecoilValue), Game::hProc);
		}
	}
}

void Entity_t::EnableNoSpread()
{
	playerNoSpreadBase = Utils::PointerChain(Game::hProc, playerBase, playerNoSpreadOffset);
	Utils::Write((BYTE*)playerNoSpreadBase, (BYTE*)&iPlayerNoSpreadValue, sizeof(iPlayerNoSpreadValue), Game::hProc);
}

std::byte Entity_t::ReadNoRecoilValue()
{
	Utils::Read((BYTE*)playerNoRecoilBase, (BYTE*)&noRecoilValue, sizeof(noRecoilValue), Game::hProc);
	return noRecoilValue;
}

void Entity_t::EnablePlayerJetPck()
{
	if (GetAsyncKeyState(VK_SPACE) && 1)
	{
		Utils::Read((BYTE*)playerZCoordAddr, (BYTE*)&currentPlayerCoordsZ, sizeof(currentPlayerCoordsZ), Game::hProc);
		fGlobalJetPackValue = currentPlayerCoordsZ + fGlobalJetPackAddValue;
		Utils::Write((BYTE*)playerZCoordAddr, (BYTE*)&fGlobalJetPackValue, sizeof(fGlobalJetPackValue), Game::hProc);
	}
}

void Entity_t::SetPlayerWeapon(int index)
{
	playerBaseAddr = Utils::PointerChain(Game::hProc, playerBase, playerSetWeaponOffset);
	switch (index)
	{
	case 0:
		iPlayer1NewWeaponValue = FeatureSettings::iP1WCValue;
		Utils::Write((BYTE*)playerBaseAddr + (playerWeaponArray * 6) + (playerArraySizeOffset * index), (BYTE*)&iPlayer1NewWeaponValue, sizeof(iPlayer1NewWeaponValue), Game::hProc);
		break;
	case 1:
		iPlayer2NewWeaponValue = FeatureSettings::iP2WCValue;
		Utils::Write((BYTE*)playerBaseAddr + (playerWeaponArray * 6) + (playerArraySizeOffset * index), (BYTE*)&iPlayer2NewWeaponValue, sizeof(iPlayer2NewWeaponValue), Game::hProc);
		break;
	case 2:
		iPlayer3NewWeaponValue = FeatureSettings::iP3WCValue;
		Utils::Write((BYTE*)playerBaseAddr + (playerWeaponArray * 6) + (playerArraySizeOffset * index), (BYTE*)&iPlayer3NewWeaponValue, sizeof(iPlayer3NewWeaponValue), Game::hProc);
		break;
	case 3:
		iPlayer4NewWeaponValue = FeatureSettings::iP4WCValue;
		Utils::Write((BYTE*)playerBaseAddr + (playerWeaponArray * 6) + (playerArraySizeOffset * index), (BYTE*)&iPlayer4NewWeaponValue, sizeof(iPlayer4NewWeaponValue), Game::hProc);
		break;
	}
}

int Entity_t::IsInGame()
{
	inGameAddr = Game::moduleBase + inGamePtr;
	Utils::Read((BYTE*)inGameAddr, (BYTE*)&iInGameValue, sizeof(iInGameValue), Game::hProc);
	return iInGameValue;
}
#pragma endregion

#pragma region Zombie Functions
void Entity_t::SetZombieAddr()
{
	zombieBase = Game::moduleBase + zombieBasePtr;
	zombieCountBase = Game::moduleBase + zombieCountPtr;
}

void Entity_t::EnableZombieTP()
{
	if (GetAsyncKeyState(0x5A)) // Z Key.
	{
		// Player Coords
		Utils::Read((BYTE*)playerCoordAddr, (BYTE*)&currentPlayerCoordsTeleport, sizeof(currentPlayerCoordsTeleport), Game::hProc);
	}
	for (uintptr_t i = 0; i < 80; i++)
	{
		// Zombie Coords
		Utils::Write((BYTE*)zombiesCoordAddr + (zombieArraySize * i), (BYTE*)&currentPlayerCoordsTeleport, sizeof(currentPlayerCoordsTeleport), Game::hProc);
	}
}

int Entity_t::GetZombieCount()
{
	Utils::Read((BYTE*)zombieCountBase, (BYTE*)&iZombieCountValue, sizeof(iZombieCountValue), Game::hProc);
	return iZombieCountValue;
}
#pragma endregion