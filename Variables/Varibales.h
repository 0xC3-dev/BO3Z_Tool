#pragma once
#include "../imgui/imgui_internal.h"

namespace UI
{
	int iScreenWidth = 0;
	int iScreenHeight = 0;
	int iGuiX = 0;
	int iGuiY = 0;
	int iTab = 0;
	int iExploitPage = 1;
	int iPlayer1ExploitPage = 1;
}

namespace Game
{
	uintptr_t moduleBase = NULL;
	HWND hWnd = NULL;
	DWORD procID = NULL;
	HANDLE hProc = NULL;
}

namespace FeatureSettings
{
	bool bIsInGame = false;
	int iP1PointsValue = 0;
	int iP2PointsValue = 0;
	int iP3PointsValue = 0;
	int iP4PointsValue = 0;
	int iP1WCValue = 0;
	int iP2WCValue = 0;
	int iP3WCValue = 0;
	int iP4WCValue = 0;
	int iJumpHeightValue = 39;
#pragma region Player 1 Bools
	bool bP1InfiniteHealth = false;
	bool bP1InfiniteClipAmmo = false;
	bool bP1InfiniteStockAmmo = false;
	bool bP1RapidFire = false;
	bool bP1InfinitePoints = false;
	bool bP1DynamicPoints = false;
	bool bP1AlwaysInstaKill = false;
	bool bP1JumpHeight = false;
	bool bP1RunSpeed = false;
	bool bP1Speed = false;
	bool bZombieTP = false;
	bool bExtraZombiesTP = false;
	bool bTPAllZombies = false;
	bool bNewZombieLocation = false;
	bool bP1WCycle = false;
	bool bP1WCycleKey = false;
	bool bP1Name = false;
#pragma endregion	
#pragma region Player 2 Bools
	bool bP2InfiniteHealth = false;
	bool bP2InfiniteAmmo = false;
	bool bP2InfiniteClipAmmo = false;
	bool bP2InfiniteStockAmmo = false;
	bool bP2InfinitePoints = false;
	bool bP2DynamicPoints = false;
	bool bP2RapidFire = false;
	bool bP2JumpHeight = false;
	bool bP2RunSpeed = false;
	float p2RunSpeedvalue = 1.f;
	bool bP2WCycle = false;
#pragma endregion
#pragma region Player 3 Bools
	bool bP3InfiniteHealth = false;
	bool bP3InfiniteAmmo = false;
	bool bP3InfiniteClipAmmo = false;
	bool bP3InfiniteStockAmmo = false;
	bool bP3InfinitePoints = false;
	bool bP3DynamicPoints = false;
	bool bP3RapidFire = false;
	bool bP3JumpHeight = false;
	bool bP3RunSpeed = false;
	float p3RunSpeedvalue = 1.f;
	bool bP3WCycle = false;
#pragma endregion
#pragma region Player 4 Bools
	bool bP4InfiniteHealth = false;
	bool bP4InfiniteAmmo = false;
	bool bP4InfiniteClipAmmo = false;
	bool bP4InfiniteStockAmmo = false;
	bool bP4InfinitePoints = false;
	bool bP4DynamicPoints = false;
	bool bP4RapidFire = false;
	bool bP4JumpHeight = false;
	bool bP4RunSpeed = false;
	float p4RunSpeedvalue = 1.f;
	bool bP4WCycle = false;
#pragma endregion
#pragma region Extra Goodies Bools
	bool bJetPack = false;
	bool bAimbot = false;
	bool bZombieCount = false;
	bool bNoRecoilOn = false;
	bool bNoRecoilOff = false;
	bool bNoSpreadOn = false;
	bool bNoGunJitter = false;
#pragma endregion
}

namespace AimSettings
{
	float fFovLimit = 0;
	float fAimSmooth = 1.f;
	int iAimKey = 0x0;
}

namespace MiscSettings
{
	bool bCrosshair = false;
	bool bPlayerFov = false;
	float playerFovSize = 175;
}

namespace VisualSettings
{
	bool bRecoilText = false;
	bool bZombieSnaplines = false;
	bool bZombieSnaplinesTop = false;
	bool bZombieSnaplinesMid = false;
	bool bZombieSnaplinesBottom = false;
	int iZombieSnaplinePos = 1337;
	bool bZombie2DBox = false;
	bool bZombie2DBrackets = false;
	bool bZombieBoxFilled = false;
	bool bZombieHealthBar = false;
	bool bZombieDistance = false;
	bool bZombie2DBracketsRainbow = false;
	bool bZombie2DBoxesRainbow = false;
	bool bZombieSnaplinesRainbow = false;
	bool bZombieDistanceRainbow = false;
	bool bZombieCrosshairRainbow = false;
	bool bZombieFovRainbow = false;
	float boxColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float bracketBoxColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float boxFilledColor[4] = { 0.f, 0.f, 0.f, 0.18f };
	float snaplineColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float distanceColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float crosshairColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fovColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float zombieCounterColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float zombieCounterValueColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	//
	ImVec4 whiteText = ImVec4(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.0f);
	ImVec4 blackText = ImVec4(0.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1.0f);
	ImColor boxImColor = ImColor(boxColor[0], boxColor[1], boxColor[2]);
	ImColor bracketBoxImColor = ImColor(bracketBoxColor[0], bracketBoxColor[1], bracketBoxColor[2]);
	ImColor boxFilledImColor = ImColor(boxFilledColor[0], boxFilledColor[1], boxFilledColor[2], boxFilledColor[3]);
	ImColor snaplineImColor = ImColor(snaplineColor[0], snaplineColor[1], snaplineColor[2]);
	ImColor distanceImColor = ImColor(distanceColor[0], distanceColor[1], distanceColor[2]);
	ImColor healthBarImColor;
	ImColor crosshairImColor = ImColor(crosshairColor[0], crosshairColor[1], crosshairColor[2]);
	ImColor fovImColor = ImColor(fovColor[0], fovColor[1], fovColor[2]);
	ImColor zombieCounterImColor = ImColor(zombieCounterColor[0], zombieCounterColor[1], zombieCounterColor[2]);
	ImColor zombieCounterValueImColor = ImColor(zombieCounterValueColor[0], zombieCounterValueColor[1], zombieCounterValueColor[2]);
}