#include "Engine.h"
#include "../Overlay/Overlay.h"

namespace Engine
{
	Entity_t entity;

	// Check if Player is in Game.
	void IsInGame()
	{
		if (entity.IsInGame() < 1)
		{
			if (entity.playerBase == NULL)
			{
				entity.SetPlayerAddr();
				entity.SetZombieAddr();
			}
			if (FeatureSettings::bIsInGame)
			{
				FeatureSettings::bIsInGame = false;
			}
		}
		else if (entity.IsInGame() > 0)
		{
			if (entity.playerBase == NULL)
			{
				entity.SetPlayerAddr();
				entity.SetZombieAddr();
			}
			if (!FeatureSettings::bIsInGame)
			{
				FeatureSettings::bIsInGame = true;
			}
		}
	}
	// Features for Player 1.
	void Player1Features()
	{
		if (FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP1InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer1Index, TRUE);
			}
			if (!FeatureSettings::bP1InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer1Index, FALSE);
			}
			if (FeatureSettings::bP1InfiniteClipAmmo)
			{
				entity.SetPlayerClipAmmo(entity.iPlayer1Index);
			}
			if (FeatureSettings::bP1InfiniteStockAmmo)
			{
				entity.SetPlayerStockAmmo(entity.iPlayer1Index);
			}
			if (FeatureSettings::bP1DynamicPoints)
			{
				entity.SetCustomPlayerPoints(entity.iPlayer1Index);
				FeatureSettings::bP1DynamicPoints = false;
			}
			if (FeatureSettings::bP1InfinitePoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer1Index);
			}
			if (FeatureSettings::bP1AlwaysInstaKill)
			{
				entity.EnableInstaKill();
			}
			if (FeatureSettings::bP1JumpHeight)
			{
				entity.SetPlayerJumpHeight();
			}
			if (FeatureSettings::bNoRecoilOn)
			{
				entity.SetNoRecoil(TRUE);
			}
			if (!FeatureSettings::bNoRecoilOn)
			{
				entity.SetNoRecoil(FALSE);
			}
			/*if (FeatureSettings::bNoSpreadOn)
			{
				entity.EnableNoSpread();
			}*/
			if (FeatureSettings::bP1RapidFire)
			{
				entity.EnableRapidFire(entity.iPlayer1Index);
			}
			/*
			if (FeatureSettings::bJetPack)
			{
				entity.EnablePlayerJetPck();
			}*/
			if (FeatureSettings::bP1WCycle)
			{
				entity.SetPlayerWeapon(entity.iPlayer1Index);
				FeatureSettings::bP1WCycle = false;
			}
			if (FeatureSettings::bP1WCycleKey) // Need to add button toggle to menu instead of having it harded coded to true.
			{
				if (GetAsyncKeyState(0x56) & 1) // V Key.
				{
					FeatureSettings::iP1WCValue = FeatureSettings::iP1WCValue + 1;
					entity.SetPlayerWeapon(entity.iPlayer1Index);
				}
			}
		}
		if (!FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP1InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer1Index, FALSE);
				FeatureSettings::bP1InfiniteHealth = false;
			}
			if (FeatureSettings::bNoRecoilOn)
			{
				entity.SetNoRecoil(FALSE);
				FeatureSettings::bNoRecoilOn = false;
			}
			/*if (FeatureSettings::bJetPack)
			{
				FeatureSettings::bJetPack = false;
				entity.fGlobalJetPackValue = 0.f;
				entity.fGlobalJetPackAddValue = 8.f;
			}*/
		}
	}
	// Features for Player 2.
	void Player2Features()
	{
		if (FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP2InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer2Index, TRUE);
			}
			if (!FeatureSettings::bP2InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer2Index, FALSE);
			}
			if (FeatureSettings::bP2InfiniteClipAmmo)
			{
				entity.SetPlayerClipAmmo(entity.iPlayer2Index);
			}
			if (FeatureSettings::bP2InfiniteStockAmmo)
			{
				entity.SetPlayerStockAmmo(entity.iPlayer2Index);
			}
			if (FeatureSettings::bP2DynamicPoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer2Index);
				FeatureSettings::bP2DynamicPoints = false;
			}
			if (FeatureSettings::bP2InfinitePoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer2Index);
			}
			if (FeatureSettings::bP2RunSpeed)
			{
				// Needs Added.
			}
			if (FeatureSettings::bP2RapidFire)
			{
				entity.EnableRapidFire(entity.iPlayer2Index);
			}
			if (FeatureSettings::bP2WCycle)
			{
				entity.SetPlayerWeapon(entity.iPlayer2Index);
			}
		}
		if (!FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP2InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer2Index, FALSE);
				FeatureSettings::bP2InfiniteHealth = false;
			}
		}
	}
	// Features for Player 3.
	void Player3Features()
	{
		if (FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP3InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer3Index, TRUE);
			}
			if (!FeatureSettings::bP3InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer3Index, FALSE);
			}
			if (FeatureSettings::bP3InfiniteClipAmmo)
			{
				entity.SetPlayerClipAmmo(entity.iPlayer3Index);
			}
			if (FeatureSettings::bP3InfiniteStockAmmo)
			{
				entity.SetPlayerStockAmmo(entity.iPlayer3Index);
			}
			if (FeatureSettings::bP3DynamicPoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer3Index);
				FeatureSettings::bP3DynamicPoints = false;
			}
			if (FeatureSettings::bP3InfinitePoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer3Index);
			}
			if (FeatureSettings::bP3RunSpeed)
			{
				// Needs Added.
			}
			if (FeatureSettings::bP3RapidFire)
			{
				entity.EnableRapidFire(entity.iPlayer3Index);
			}
			if (FeatureSettings::bP3WCycle)
			{
				entity.SetPlayerWeapon(entity.iPlayer3Index);
			}
		}
		if (!FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP3InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer3Index, FALSE);
				FeatureSettings::bP3InfiniteHealth = false;
			}
		}
	}
	// Features for Player 4.
	void Player4Features()
	{
		if (FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP4InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer4Index, TRUE);
			}
			if (!FeatureSettings::bP4InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer4Index, FALSE);
			}
			if (FeatureSettings::bP4InfiniteClipAmmo)
			{
				entity.SetPlayerClipAmmo(entity.iPlayer4Index);
			}
			if (FeatureSettings::bP4InfiniteStockAmmo)
			{
				entity.SetPlayerStockAmmo(entity.iPlayer4Index);
			}
			if (FeatureSettings::bP4DynamicPoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer4Index);
				FeatureSettings::bP4DynamicPoints = false;
			}
			if (FeatureSettings::bP4InfinitePoints)
			{
				entity.FreezePlayerPoints(entity.iPlayer4Index);
			}
			if (FeatureSettings::bP4RunSpeed)
			{
				// Needs Added.
			}
			if (FeatureSettings::bP4RapidFire)
			{
				entity.EnableRapidFire(entity.iPlayer4Index);
			}
			if (FeatureSettings::bP4WCycle)
			{
				entity.SetPlayerWeapon(entity.iPlayer4Index);
			}
		}
		if (!FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bP4InfiniteHealth)
			{
				entity.SetGodMode(entity.iPlayer4Index, FALSE);
				FeatureSettings::bP4InfiniteHealth = false;
			}
		}
	}
	// Features for Zombies.
	void ExtraGoodieFeatures()
	{
		if (FeatureSettings::bIsInGame)
		{
			if (FeatureSettings::bZombieTP)
			{
				entity.EnableZombieTP();
			}
			if (FeatureSettings::bZombieCount)
			{
				entity.GetZombieCount();
			}
		}
	}
	// Disbale All Features.
	void DisableAllFeatures()
	{
		if (Utils::GetProcId("BlackOps3.exe") < 1)
		{
			exit(0);
		}
		if (GetAsyncKeyState(VK_DELETE))
		{
			/*
			*	Player 1 booleans
			*/
			FeatureSettings::bP1InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer1Index, FALSE);
			FeatureSettings::bP1InfiniteClipAmmo = false;
			FeatureSettings::bP1InfiniteStockAmmo = false;
			FeatureSettings::bP1InfinitePoints = false;
			FeatureSettings::bP1AlwaysInstaKill = false;
			FeatureSettings::bNoRecoilOn = false;
			entity.SetNoRecoil(FALSE);
			FeatureSettings::bP1RapidFire = false;
			FeatureSettings::bP1JumpHeight = false;
			FeatureSettings::bZombieTP = false;
			FeatureSettings::bExtraZombiesTP = false;
			FeatureSettings::bTPAllZombies = false;
			FeatureSettings::bP1WCycle = false;
			/*
			*	Player 2 booleans
			*/
			FeatureSettings::bP2InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer2Index, FALSE);
			FeatureSettings::bP2InfiniteClipAmmo = false;
			FeatureSettings::bP2InfiniteStockAmmo = false;
			FeatureSettings::bP2InfinitePoints = false;
			FeatureSettings::bP2RapidFire = false;
			FeatureSettings::bP2WCycle = false;
			/*
			*	Player 3 booleans
			*/
			FeatureSettings::bP3InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer3Index, FALSE);
			FeatureSettings::bP3InfiniteClipAmmo = false;
			FeatureSettings::bP3InfiniteStockAmmo = false;
			FeatureSettings::bP3InfinitePoints = false;
			FeatureSettings::bP3RapidFire = false;
			FeatureSettings::bP3WCycle = false;
			/*
			*	Player 4 booleans
			*/
			FeatureSettings::bP4InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer4Index, FALSE);
			FeatureSettings::bP4InfiniteClipAmmo = false;
			FeatureSettings::bP4InfiniteStockAmmo = false;
			FeatureSettings::bP4InfinitePoints = false;
			FeatureSettings::bP4RapidFire = false;
			FeatureSettings::bP4WCycle = false;
			/*
			*	Extra Goodies booleans
			*/
			VisualSettings::bZombie2DBox = false;
			VisualSettings::bZombie2DBrackets = false;
			VisualSettings::bZombieSnaplines = false;
			MiscSettings::bCrosshair = false;
			MiscSettings::bPlayerFov = false;
			FeatureSettings::bZombieCount = false;
		}
		if (GetAsyncKeyState(VK_HOME))
		{
			/*
			*	Player 1 booleans
			*/
			FeatureSettings::bP1InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer1Index, FALSE);
			FeatureSettings::bP1InfiniteClipAmmo = false;
			FeatureSettings::bP1InfiniteStockAmmo = false;
			FeatureSettings::bP1InfinitePoints = false;
			FeatureSettings::bP1AlwaysInstaKill = false;
			FeatureSettings::bNoRecoilOn = false;
			entity.SetNoRecoil(FALSE);
			FeatureSettings::bP1RapidFire = false;
			FeatureSettings::bP1JumpHeight = false;
			FeatureSettings::bZombieTP = false;
			FeatureSettings::bExtraZombiesTP = false;
			FeatureSettings::bTPAllZombies = false;
			FeatureSettings::bP1WCycle = false;
			/*
			*	Player 2 booleans
			*/
			FeatureSettings::bP2InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer2Index, FALSE);
			FeatureSettings::bP2InfiniteClipAmmo = false;
			FeatureSettings::bP2InfiniteStockAmmo = false;
			FeatureSettings::bP2InfinitePoints = false;
			FeatureSettings::bP2RapidFire = false;
			FeatureSettings::bP2WCycle = false;
			/*
			*	Player 3 booleans
			*/
			FeatureSettings::bP3InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer3Index, FALSE);
			FeatureSettings::bP3InfiniteClipAmmo = false;
			FeatureSettings::bP3InfiniteStockAmmo = false;
			FeatureSettings::bP3InfinitePoints = false;
			FeatureSettings::bP3RapidFire = false;
			FeatureSettings::bP3WCycle = false;
			/*
			*	Player 4 booleans
			*/
			FeatureSettings::bP4InfiniteHealth = false;
			entity.SetGodMode(entity.iPlayer4Index, FALSE);
			FeatureSettings::bP4InfiniteClipAmmo = false;
			FeatureSettings::bP4InfiniteStockAmmo = false;
			FeatureSettings::bP4InfinitePoints = false;
			FeatureSettings::bP4RapidFire = false;
			FeatureSettings::bP4WCycle = false;
			/*
			*	Extra Goodies booleans
			*/
			VisualSettings::bZombie2DBox = false;
			VisualSettings::bZombie2DBrackets = false;
			VisualSettings::bZombieSnaplines = false;
			MiscSettings::bCrosshair = false;
			MiscSettings::bPlayerFov = false;
			FeatureSettings::bZombieCount = false;
			exit(0);
		}
	}

	namespace AimVarsLocal
	{
		float fCurrentDist = NULL;
		float fClosestDist = FLT_MAX;
		float fCacheDist[24] = { };
		float fFov = NULL;
		int iBestTarget = -1;
		int iCheckTarget = NULL;
		Vec2 vScreen = { 0, 0 };
		Vec2 vHead = { 0, 0 };
	};

	namespace ESP
	{
		float UnitsToMeter(float units)
		{
			return units * 0.0254;
		}

		bool WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int windowWidth, int windowHeight)
		{
			Vec4 clipCoords;
			clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
			clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
			clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
			clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

			if (clipCoords.w < 0.1f)
				return false;


			Vec3 NDC;
			NDC.x = clipCoords.x / clipCoords.w;
			NDC.y = clipCoords.y / clipCoords.w;
			NDC.z = clipCoords.z / clipCoords.w;

			screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
			screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
			return true;
		}

		void DoESP()
		{
			if (FeatureSettings::bIsInGame)
			{
				entity.playerCoordAddr = Utils::PointerChain(Game::hProc, entity.playerBase, entity.playerCoordOffset);
				entity.zombiesCoordAddr = Utils::PointerChain(Game::hProc, entity.zombieBase, entity.zombieCoord);
				entity.zombiesHeadCoordAddr = Utils::PointerChain(Game::hProc, entity.zombieBase, entity.zombieHeadCoord);
				entity.playerPedHealthAddr = Utils::PointerChain(Game::hProc, entity.zombieBase, entity.zombieHealthOffset);
				entity.playerPedHealthMaxAddr = Utils::PointerChain(Game::hProc, entity.zombieBase, entity.zombieHealthMaxOffset);
				for (uintptr_t i = 0; i < 80; i++)
				{
					Utils::Read((BYTE*)entity.playerPedHealthAddr + (entity.zombieArraySize * i), (BYTE*)&entity.iZombieCurrentHealthValue, sizeof(entity.iZombieCurrentHealthValue), Game::hProc);
					Utils::Read((BYTE*)entity.playerPedHealthMaxAddr + (entity.zombieArraySize * i), (BYTE*)&entity.iZombieMaxHealthValue, sizeof(entity.iZombieMaxHealthValue), Game::hProc);
					if (entity.iZombieCurrentHealthValue < 1 || entity.iZombieCurrentHealthValue == 0)
						continue;
					Utils::Read((BYTE*)entity.playerCoordAddr, (BYTE*)&entity.currentPlayerCoords, sizeof(entity.currentPlayerCoords), Game::hProc);
					Utils::Read((BYTE*)entity.zombiesCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombieCoords, sizeof(entity.currentZombieCoords), Game::hProc);
					Utils::Read((BYTE*)entity.zombiesHeadCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombieHeadCoords, sizeof(entity.currentZombieHeadCoords), Game::hProc);
					float Matrix[16];
					Vec2 vScreen;
					Vec2 vHead;
					DWORD viewMatrix = 0x36752A0; // 0x36752A0 // 0x36772A0
					Utils::Read((BYTE*)Game::moduleBase + viewMatrix, (BYTE*)&Matrix, sizeof(Matrix), Game::hProc);
					Vec3 zombiePos = entity.currentZombieCoords;
					Vec3 zombieHeadPos = { entity.currentZombieHeadCoords.x - 10.f, entity.currentZombieHeadCoords.y - 20.f, entity.currentZombieHeadCoords.z - 10.f };
					Vec3 playerPos = entity.currentPlayerCoords;
					if (WorldToScreen(zombiePos, vScreen, Matrix, UI::iScreenWidth, UI::iScreenHeight))
					{
						if (WorldToScreen(zombieHeadPos, vHead, Matrix, UI::iScreenWidth, UI::iScreenHeight))
						{
							float headHeight = vHead.y - vScreen.y;
							float width = headHeight / 2;
							float center = width / -2;
							if (VisualSettings::bZombieSnaplines)
							{
								if (VisualSettings::iZombieSnaplinePos == 1)
								{
									Render::Line(ImVec2(UI::iScreenWidth / 2, UI::iScreenHeight - UI::iScreenHeight), ImVec2(vScreen.x, vHead.y), VisualSettings::snaplineImColor, 1.f);
								}
								else if (VisualSettings::iZombieSnaplinePos == 2)
								{
									Render::Line(ImVec2(UI::iScreenWidth / 2, UI::iScreenHeight / 2), ImVec2(vScreen.x, vHead.y), VisualSettings::snaplineImColor, 1.f);
								}
								else if (VisualSettings::iZombieSnaplinePos == 3)
								{
									Render::Line(ImVec2(UI::iScreenWidth / 2, UI::iScreenHeight), ImVec2(vScreen.x, vHead.y), VisualSettings::snaplineImColor, 1.f);
								}
							}
							if (VisualSettings::bZombieHealthBar)
							{
								float iCurrentZHealth = entity.iZombieCurrentHealthValue;
								float iCurrentZMaxHealth = entity.iZombieMaxHealthValue;
								if (iCurrentZHealth > iCurrentZMaxHealth / 1.25)
								{
									VisualSettings::healthBarImColor = ImColor(0, 255, 0);
								}
								else if (iCurrentZHealth <= iCurrentZMaxHealth / 2 && iCurrentZHealth >= iCurrentZMaxHealth / 4)
								{
									VisualSettings::healthBarImColor = ImColor(255, 255, 0);
								}
								else if (iCurrentZHealth <= iCurrentZMaxHealth / 4)
								{
									VisualSettings::healthBarImColor = ImColor(255, 0, 0);
								}
							}
							if (VisualSettings::bZombie2DBrackets)
							{
								if (VisualSettings::bZombieHealthBar)
								{
									Render::DrawBoxBrackets(ImGui::GetWindowDrawList(), vScreen.x + center, vScreen.y, width, headHeight, VisualSettings::healthBarImColor, 1.f);
								}
								else
								{
									Render::DrawBoxBrackets(ImGui::GetWindowDrawList(), vScreen.x + center, vScreen.y, width, headHeight, VisualSettings::bracketBoxImColor, 1.f);
								}
							}
							if (VisualSettings::bZombieBoxFilled)
							{
								Render::RectFilled2(vScreen.x + center, vScreen.y, width, headHeight, VisualSettings::boxFilledImColor);
							}
							if (VisualSettings::bZombie2DBox)
							{
								Render::DrawBox(VisualSettings::boxImColor, vScreen.x + center, vScreen.y, width, headHeight);
							}
							if (VisualSettings::bZombieDistance)
							{
								auto dist = ESP::UnitsToMeter(playerPos.GetDistance(zombiePos));
								char buf[64];
								sprintf_s(buf, "[%.1f]m", dist);
								Render::DrawOutlinedText(ImGui::Body, ImVec2(vScreen.x, vScreen.y + 10), 13.0f, VisualSettings::distanceImColor, true, buf);
							}
						}
					}
				}
			}
		}

		void MiscFeatures()
		{
			if (MiscSettings::bCrosshair)
			{
				// Small Crosshair in the Center of the Screen.
				constexpr long crosshairSize = 10.0f;
				ImVec2 center = ImVec2(WND_SIZEX / 2, WND_SIZEY / 2);
				Render::Line(ImVec2((center.x), (center.y) - crosshairSize), ImVec2((center.x), (center.y) + crosshairSize), VisualSettings::crosshairImColor, 1.5f);
				Render::Line(ImVec2((center.x) - crosshairSize, (center.y)), ImVec2((center.x) + crosshairSize, (center.y)), VisualSettings::crosshairImColor, 1.5f);
			}
			if (MiscSettings::bPlayerFov)
			{
				// Center Screen.
				Render::Circle(VisualSettings::fovImColor, MiscSettings::playerFovSize);
			}
			if (FeatureSettings::bZombieCount)
			{
				// Draw Zombie Counter in Bottom Left Screen.
				Render::EasyText(ImVec2(10, UI::iScreenHeight - 30), VisualSettings::zombieCounterImColor, "Zombie Count: ", 15.f);
				Render::EasyNumber(ImVec2(100, UI::iScreenHeight - 30), VisualSettings::zombieCounterValueImColor, entity.iZombieCountValue, 15.f);
			}
		}

		void FeatureLoop()
		{
			//Aimbot::DoAimbot();
			ESP::DoESP();
			ESP::MiscFeatures();
		}
	}

	namespace Aimbot
	{
		inline float DistanceCursor(Vec2 vec)
		{
			POINT p;
			if (GetCursorPos(&p))
			{
				float ydist = (vec.y - p.y);
				float xdist = (vec.x - p.x);
				float ret = sqrt(pow(ydist, 2) + pow(xdist, 2));
				return ret;
			}
		}

		Vec2 Smooth(Vec2 pos)
		{
			Vec2 center{ (float)(UI::iScreenWidth / 2), (float)(UI::iScreenHeight / 2) };
			Vec2 target{ 0, 0 };
			if (pos.x != 0) {
				if (pos.x > center.x) {
					target.x = -(center.x - pos.x);
					target.x /= 1;
					if (target.x + center.x > center.x * 2)
						target.x = 0;
				}

				if (pos.x < center.x) {
					target.x = pos.x - center.x;
					target.x /= 1;
					if (target.x + center.x < 0)
						target.x = 0;
				}
			}

			if (pos.y != 0) {
				if (pos.y > center.y) {
					target.y = -(center.y - pos.y);
					target.y /= 1;
					if (target.y + center.y > center.y * 2)
						target.y = 0;
				}

				if (pos.y < center.y) {
					target.y = pos.y - center.y;
					target.y /= 1;
					if (target.y + center.y < 0)
						target.y = 0;
				}
			}

			target.x /= AimSettings::fAimSmooth;
			target.y /= AimSettings::fAimSmooth;

			if (abs(target.x) < 1) {
				if (target.x > 0) {
					target.x = 1;
				}
				if (target.x < 0) {
					target.x = -1;
				}
			}
			if (abs(target.y) < 1) {
				if (target.y > 0) {
					target.y = 1;
				}
				if (target.y < 0) {
					target.y = -1;
				}
			}

			return target;
		}

		void MouseAim(Vec2 target)
		{
			INPUT input;
			input.type = INPUT_MOUSE;
			input.mi.mouseData = 0;
			input.mi.time = 0;
			input.mi.dx = target.x;
			input.mi.dy = target.y;
			input.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &input, sizeof(input));
		}

		int GetClosestTarget()
		{
			for (uintptr_t i = 0; i < 80; i++)
			{
				Utils::Read((BYTE*)entity.playerPedHealthAddr + (entity.zombieArraySize * i), (BYTE*)&entity.iZombieCurrentHealthValue, sizeof(entity.iZombieCurrentHealthValue), Game::hProc);

				if (entity.iZombieCurrentHealthValue < 1)
					continue;

				Utils::Read((BYTE*)entity.playerXCoordAddr, (BYTE*)&entity.currentPlayerCoordsX, sizeof(entity.currentPlayerCoordsX), Game::hProc);
				Utils::Read((BYTE*)entity.playerYCoordAddr, (BYTE*)&entity.currentPlayerCoordsY, sizeof(entity.currentPlayerCoordsY), Game::hProc);
				Utils::Read((BYTE*)entity.playerZCoordAddr, (BYTE*)&entity.currentPlayerCoordsZ, sizeof(entity.currentPlayerCoordsZ), Game::hProc);
				Utils::Read((BYTE*)entity.zombiesXCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombiesCoordsX, sizeof(entity.currentZombiesCoordsX), Game::hProc);
				Utils::Read((BYTE*)entity.zombiesYCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombiesCoordsY, sizeof(entity.currentZombiesCoordsY), Game::hProc);
				Utils::Read((BYTE*)entity.zombiesZCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombiesCoordsZ, sizeof(entity.currentZombiesCoordsZ), Game::hProc);
				Utils::Read((BYTE*)entity.zombiesHeadXCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombiesCoordsHeadX, sizeof(entity.currentZombiesCoordsHeadX), Game::hProc);
				Utils::Read((BYTE*)entity.zombiesHeadYCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombiesCoordsHeadY, sizeof(entity.currentZombiesCoordsHeadY), Game::hProc);
				Utils::Read((BYTE*)entity.zombiesHeadZCoordAddr + (entity.zombieArraySize * i), (BYTE*)&entity.currentZombiesCoordsHeadZ, sizeof(entity.currentZombiesCoordsHeadZ), Game::hProc);

				float Matrix[16];
				DWORD viewMatrix = 0x36772A0;
				Utils::Read((BYTE*)Game::moduleBase + viewMatrix, (BYTE*)&Matrix, sizeof(Matrix), Game::hProc);

				Vec3 zombiePos = { entity.currentZombiesCoordsX, entity.currentZombiesCoordsY, entity.currentZombiesCoordsZ };
				Vec3 zombieHeadPos = { entity.currentZombiesCoordsHeadX - 10.f, entity.currentZombiesCoordsHeadY - 20.f, entity.currentZombiesCoordsHeadZ - 10.f };
				Vec3 playerPos = { entity.currentPlayerCoordsX, entity.currentPlayerCoordsY, entity.currentPlayerCoordsZ };

				if (ESP::WorldToScreen(zombiePos, AimVarsLocal::vScreen, Matrix, UI::iScreenWidth, UI::iScreenHeight))
				{
					if (ESP::WorldToScreen(zombieHeadPos, AimVarsLocal::vHead, Matrix, UI::iScreenWidth, UI::iScreenHeight))
					{
						AimVarsLocal::fCurrentDist = ESP::UnitsToMeter(playerPos.GetDistance(zombiePos));

						if (AimVarsLocal::fCurrentDist < 200.f)
						{
							AimVarsLocal::fFov = DistanceCursor(AimVarsLocal::vHead);

							if (AimVarsLocal::fFov < MiscSettings::playerFovSize)
							{
								if (AimVarsLocal::fCurrentDist < AimVarsLocal::fClosestDist)
								{
									AimVarsLocal::fCurrentDist = AimVarsLocal::fCurrentDist;
									AimVarsLocal::iBestTarget = i;
								}
								if (AimVarsLocal::fCurrentDist > AimVarsLocal::fCurrentDist)
								{
									continue;
								}
							}
						}
					}
				}
			}
			AimVarsLocal::fClosestDist = FLT_MAX;
			return AimVarsLocal::iBestTarget;
		}

		void DoAimbot()
		{
			if (FeatureSettings::bAimbot)
			{
				if (FeatureSettings::bIsInGame)
				{
					int iClosestTarget = GetClosestTarget();
					if (iClosestTarget >= 0)
					{
						Utils::Read((BYTE*)entity.playerPedHealthAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.iZombieCurrentHealthValue, sizeof(entity.iZombieCurrentHealthValue), Game::hProc);

						if (entity.iZombieCurrentHealthValue < 1)
							return;

						Utils::Read((BYTE*)entity.playerXCoordAddr, (BYTE*)&entity.currentPlayerCoordsX, sizeof(entity.currentPlayerCoordsX), Game::hProc);
						Utils::Read((BYTE*)entity.playerYCoordAddr, (BYTE*)&entity.currentPlayerCoordsY, sizeof(entity.currentPlayerCoordsY), Game::hProc);
						Utils::Read((BYTE*)entity.playerZCoordAddr, (BYTE*)&entity.currentPlayerCoordsZ, sizeof(entity.currentPlayerCoordsZ), Game::hProc);
						Utils::Read((BYTE*)entity.zombiesXCoordAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.currentZombiesCoordsX, sizeof(entity.currentZombiesCoordsX), Game::hProc);
						Utils::Read((BYTE*)entity.zombiesYCoordAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.currentZombiesCoordsY, sizeof(entity.currentZombiesCoordsY), Game::hProc);
						Utils::Read((BYTE*)entity.zombiesZCoordAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.currentZombiesCoordsZ, sizeof(entity.currentZombiesCoordsZ), Game::hProc);
						Utils::Read((BYTE*)entity.zombiesHeadXCoordAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.currentZombiesCoordsHeadX, sizeof(entity.currentZombiesCoordsHeadX), Game::hProc);
						Utils::Read((BYTE*)entity.zombiesHeadYCoordAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.currentZombiesCoordsHeadY, sizeof(entity.currentZombiesCoordsHeadY), Game::hProc);
						Utils::Read((BYTE*)entity.zombiesHeadZCoordAddr + (entity.zombieArraySize * iClosestTarget), (BYTE*)&entity.currentZombiesCoordsHeadZ, sizeof(entity.currentZombiesCoordsHeadZ), Game::hProc);

						float Matrix[16];
						DWORD viewMatrix = 0x36772A0;
						Utils::Read((BYTE*)Game::moduleBase + viewMatrix, (BYTE*)&Matrix, sizeof(Matrix), Game::hProc);

						Vec3 zombiePos = { entity.currentZombiesCoordsX, entity.currentZombiesCoordsY, entity.currentZombiesCoordsZ };
						Vec3 zombieHeadPos = { entity.currentZombiesCoordsHeadX - 10.f, entity.currentZombiesCoordsHeadY - 20.f, entity.currentZombiesCoordsHeadZ - 10.f };
						Vec3 playerPos = { entity.currentPlayerCoordsX, entity.currentPlayerCoordsY, entity.currentPlayerCoordsZ };

						if (ESP::WorldToScreen(zombiePos, AimVarsLocal::vScreen, Matrix, UI::iScreenWidth, UI::iScreenHeight))
						{
							if (ESP::WorldToScreen(zombieHeadPos, AimVarsLocal::vHead, Matrix, UI::iScreenWidth, UI::iScreenHeight))
							{
								AimVarsLocal::fCurrentDist = ESP::UnitsToMeter(playerPos.GetDistance(zombiePos));

								if (AimVarsLocal::fCurrentDist < 200.f)
								{
									AimVarsLocal::fFov = DistanceCursor(AimVarsLocal::vHead);

									if (AimVarsLocal::fFov < MiscSettings::playerFovSize)
									{
										if (GetAsyncKeyState(VK_LMENU))
										{
											AimVarsLocal::vHead.y = AimVarsLocal::vHead.y + 20.f;
											AimVarsLocal::vHead = { AimVarsLocal::vHead.x, AimVarsLocal::vHead.y };
											MouseAim(Smooth(AimVarsLocal::vHead));
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}