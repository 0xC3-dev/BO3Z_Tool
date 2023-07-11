#pragma once
#include "../../Utils/Utils.h"
#include "../Vectors/Vectors.h"
#include "../../Variables/Varibales.h"

class Entity_t
{
public:
#pragma region Player Vars
	uintptr_t playerBasePtr = 0xA549DE0;
	uintptr_t playerPedPtr = 0xA549DE8;
	uintptr_t playerNoRecoilPtr = 0x11BD903; // \x84\xc0\x74\x00\x32\xc0\xe9\x00\x00\x00\x00\x48\x83\xc4 xxx?xxx????xxx // 84 c0 74 ? 32 c0 e9 ? ? ? ? 48 83 c4
	uintptr_t playerNoRecoilBase = 0;
	uintptr_t playerNoSpreadBase = 0;
	uintptr_t playerBase = 0;
	uintptr_t playerBaseAddr = 0;
	uintptr_t playerPedBase = 0;
	uintptr_t playerPedBaseAddr = 0;
	uintptr_t playerPedBaseAddrCache = 0;
	uintptr_t playerPedHealthAddr = 0;
	uintptr_t playerPedHealthMaxAddr = 0;
	uintptr_t playerCoordAddr = 0;
	uintptr_t playerXCoordAddr = 0;
	uintptr_t playerYCoordAddr = 0;
	uintptr_t playerZCoordAddr = 0;
	uintptr_t playerArraySizeOffset = { 0x171F0 }; // New
	uintptr_t playerWeaponArraySizeOffset = { 0x40 };
	uintptr_t playerArray = { 0x4 };
	uintptr_t playerWeaponArray = { 0x8 };
	std::vector <unsigned int> playerNameOffset = { 0x6060 };
	std::vector <unsigned int> playerGodModeOffset = { 0x2A8 }; // New
	std::vector <unsigned int> playerNormalHealthOffset = { 0x16F28 }; // New
	std::vector <unsigned int> playerClipAmmoOffset = { 0x684 }; // New
	std::vector <unsigned int> playerStockAmmoOffset = { 0x648 }; // New
	std::vector <unsigned int> playerRapidFireOffset = { 0x54 }; // New
	std::vector <unsigned int> playerRapidFireOffset2 = { 0xE80 };
	std::vector <unsigned int> playerNoSpreadOffset = { 0xB78 }; // New
	std::vector <unsigned int> playerNoRecoilOffset = { 0x12F8 }; // 66 41 89 80 ? ? ? ? f3 c3 90 84 0f
	std::vector <unsigned int> playerPointsOffset = { 0x16E84 }; // New
	std::vector <unsigned int> playerRunSpeedOffset = { 0x5C70 };
	std::vector <unsigned int> playerLocationOffset = { 0xDE8 };
	std::vector <unsigned int> playerSetWeaponOffset = { 0x378 };
	std::vector <unsigned int> gameSkipRounds = { 0x333D8 };
	std::vector <unsigned int> playerKillsOffset = { 0x5D28 };
	std::vector <unsigned int> playerCoordOffset = { 0x30 };
	std::vector <unsigned int> playerXCoord = { 0x30 };
	std::vector <unsigned int> playerYCoord = { 0x34 };
	std::vector <unsigned int> playerZCoord = { 0x38 };
	std::vector <unsigned int> playerXView = { 0xD0 };
	std::vector <unsigned int> playerYView = { 0xD4 };
	std::vector <unsigned int> playerZView = { 0xD8 };
	// Player Feature Values
	int iPlayerGodModeValue = 0;
	int iPlayerGodModeOn = 12297;
	int iPlayerGodModeOff = 12296;
	const int iPlayerNoRecoilOn = 0x75; // 3224506229
	const int iPlayerNoRecoilOff = 0x74; // 3224506228
	std::byte noRecoilValue = std::byte(0);
	int iPlayerHealthValue = 0;
	int iPlayerNewAmmoValue = 255;
	int iPlayerNewPointsValue = 100000;
	int iPlayerNewCustomPointsValue = 0;
	int iPlayerNewRecoilValue = 0;
	int iPlayerNewRapidFireValue = 0;
	int iPlayer1NewWeaponValue = 0;
	int iPlayer2NewWeaponValue = 0;
	int iPlayer3NewWeaponValue = 0;
	int iPlayer4NewWeaponValue = 0;
	int iPlayerNoSpreadValue = 0.f;
	float player1NewRunSpeedValue = 1.f;
	float player2NewRunSpeedValue = 1.f;
	float player3NewRunSpeedValue = 1.f;
	float player4NewRunSpeedValue = 1.f;
	float playerDefaultRunSpeedValue = 1.f;
	float currentPlayerCoordsX = 0;
	float currentPlayerCoordsY = 0;
	float currentPlayerCoordsZ = 0;
	Vec3 currentPlayerCoords = { 0, 0, 0 };
	Vec3 currentPlayerCoordsTeleport = { 0, 0, 0 };
	float currentPlayerCoordsTeleportX = 0;
	float currentPlayerCoordsTeleportY = 0;
	float currentPlayerCoordsTeleportZ = 0;
	float currentPlayerViewAngleX = 0;
	float currentPlayerViewAngleY = 0;
	float currentPlayerViewAngleZ = 0;
	float playerDistance = 0;
	int iPlayer1Index = 0;
	int iPlayer2Index = 1;
	int iPlayer3Index = 2;
	int iPlayer4Index = 3;
	//Vec3 currentPlayerViewAngleXYZ;
#pragma endregion

#pragma region Zombie Vars
	uintptr_t zombieBasePtr = 0xA549E48; // New
	uintptr_t zombieBase = 0;
	uintptr_t zombieBaseAddr = 0;
	uintptr_t zombieCountPtr = 0x0A3D3A2C; // New
	uintptr_t zombieCountBase = 0;
	uintptr_t zombieCountBaseAddr = 0;
	uintptr_t zombiesCoordAddr = 0;
	uintptr_t zombiesXCoordAddr = 0;
	uintptr_t zombiesYCoordAddr = 0;
	uintptr_t zombiesZCoordAddr = 0;
	uintptr_t zombiesHeadCoordAddr = 0;
	uintptr_t zombiesHeadXCoordAddr = 0;
	uintptr_t zombiesHeadYCoordAddr = 0;
	uintptr_t zombiesHeadZCoordAddr = 0;
	uintptr_t zombieArraySize = 0x4F8; // New
	uintptr_t zombieNextEntitiyOffset = 0x8;
	std::vector <unsigned int> zombieHealthOffset = { 0x8, 0x2C8 }; // New
	std::vector <unsigned int> zombieHealthMaxOffset = { 0x8, 0x2CC }; // New 
	std::vector <unsigned int> zombieCoord = { 0x8, 0x230 }; // New
	std::vector <unsigned int> zombieXCoord = { 0x8, 0x230 }; // New
	std::vector <unsigned int> zombieYCoord = { 0x8, 0x234 }; // New 
	std::vector <unsigned int> zombieZCoord = { 0x8, 0x238 }; // New
	std::vector <unsigned int> zombieHeadCoord = { 0x8, 0x224 }; // New
	std::vector <unsigned int> zombieHeadXCoord = { 0x8, 0x224 }; // New
	std::vector <unsigned int> zombieHeadYCoord = { 0x8, 0x228 }; // New
	std::vector <unsigned int> zombieHeadZCoord = { 0x8, 0x22C }; // New
	std::vector <unsigned int> zombieHeadXYZCoord = { 0x8, 0x224, 0x228, 0x22C }; // New
	// Zombie Feature Values
	int iZombieCurrentHealthValue = 0;
	int iZombieMaxHealthValue = 0;
	int iZombieNewHealthValue = 1;
	int iZombieNewCriticalValue = -1;
	int iZombieCountValue = 0;
	float currentZombiesCoordsX = 0;
	float currentZombiesCoordsY = 0;
	float currentZombiesCoordsZ = 0;
	float currentZombiesCoordsHeadX = 0;
	float currentZombiesCoordsHeadY = 0;
	float currentZombiesCoordsHeadZ = 0;
	Vec3 currentZombieCoords = { 0, 0, 0 };
	Vec3 currentZombieHeadCoords = { 0, 0, 0 };
	float zombieDistance = 0;
	float closestZombie = 0;
	uintptr_t zombieTarget = 0;
#pragma endregion

#pragma region Global Lobby Vars
	uintptr_t inGamePtr = 0x19C780BC;
	uintptr_t inGameAddr = 0;
	uintptr_t jumpHeightPtr = 0x30789C4;
	uintptr_t jumpHeightBase = 0;
	// Global Game Feature Values
	int iInGameValue = 0;
	float fGlobalNewJumpHeightValue = 39.f;
	float fGlobalDefaultJumpHeightValue = 39.f;
	float fGlobalJetPackValue = 0;
	float fGlobalJetPackAddValue = 8.f;
#pragma endregion
#pragma region Player Functions
	void SetPlayerAddr();

	uintptr_t GetJumpHeightBase();

	void SetGodMode(int index, BOOL state);

	void SetPlayerClipAmmo(int index);

	void SetPlayerStockAmmo(int index);

	void SetCustomPlayerPoints(int index);

	void FreezePlayerPoints(int index);

	void EnableInstaKill();

	void SetPlayerJumpHeight();

	void SetPlayerRunSpeed();

	void EnableRapidFire(int index);

	void SetNoRecoil(BOOL state);

	void EnableNoSpread();

	std::byte ReadNoRecoilValue();

	void EnablePlayerJetPck();

	void SetPlayerWeapon(int index);

	int IsInGame();
#pragma endregion

#pragma region Zombie Functions
	void SetZombieAddr();

	void EnableZombieTP();

	int GetZombieCount();
#pragma endregion
};