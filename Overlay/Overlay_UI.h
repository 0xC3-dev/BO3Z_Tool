#pragma once
#include <string>
#include <vector>
#include <functional>
#include <Windows.h>
#include "../Fonts/FontAwesome5/font_awesome_5.h"
#include "../Fonts/FontAwesome6/font_awesome_6.h"

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

inline DWORD windowFlags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration; // ImGuiWindowFlags_NoSavedSettings

namespace ImGui
{
#pragma region GUI Setup Functions
	ImFont* Header = NULL;
	ImFont* Header2 = NULL;
	ImFont* Body = NULL;
	ImFont* Body2 = NULL;
	ImFont* FA = NULL;
	ImFont* FA2 = NULL;
	ImColor BO3Orange = ImColor(255, 100, 15, 255);
	ImColor DarkGrey22 = ImColor(22, 22, 22, 255);
	ImColor LightGrey26 = ImColor(26, 26, 26, 255);
	ImColor White = ImColor(255, 255, 255, 255);
	ImVec4 active = ImVec4(ImColor(255, 100, 15, 255));
	ImVec4 inactive = ImVec4(ImColor(255, 100, 15, 75));

	void RenderLogo();

	void SCP(float x, float y)
	{
		ImGui::SetCursorPos(ImVec2(x, y));
	}

	void SCPX(float x)
	{
		ImGui::SetCursorPosX(x);
	}

	void SCPY(float y)
	{
		ImGui::SetCursorPosY(y);
	}

	void Line(int newId)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine)
	{
		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();
		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextNL(const char* text, BOOL newLine)
	{
		ImGui::Text(text);
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSL(const char* text, BOOL sameLine, BOOL newLine)
	{
		ImGui::Text(text);
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSCP(const char* text, int x, int y)
	{
		ImGui::SCP(x, y);
		ImGui::Text(text);
	}

	void TextColor(const char* text, ImVec4 color, int lineId, BOOL seperator, BOOL newLine)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color));
		ImGui::Text(text);
		ImGui::PopStyleColor();
		if (seperator)
		{
			ImGui::NewLine();
			Line(lineId);
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonNL(const char* featureName, bool* featureBool, ImVec2 size, BOOL newLine)
	{
		if (ImGui::Button(featureName, size))
		{
			*featureBool = !*featureBool;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSCP(const char* featureName, bool* featureBool, int x, int y, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(x, y);
		if (ImGui::Button(featureName, size))
		{
			*featureBool = !*featureBool;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonIntSCP(const char* featureName, int* featureInt, int value, int x, int y, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(x, y);
		if (ImGui::Button(featureName, size))
		{
			*featureInt = value;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonPageSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::PushStyleColor(ImGuiCol_Button, UI::iTab == pageNumber ? active : inactive);
		if (ImGui::Button(label, size))
		{
			*page = pageNumber;
		}
		ImGui::PopStyleColor();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonWindowSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		if (ImGui::Button(label, size))
		{
			*page = pageNumber;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void InputIntNL(const char* featureName, int* featureInt, bool* featureBool, int size, BOOL sameLine, BOOL newLine)
	{
		ImGui::PushItemWidth(size);
		if (ImGui::InputInt(featureName, featureInt))
		{
			*featureBool = true;
		}
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ColorEditFeature(const char* featureName, float* colorEditFloat, BOOL newLine)
	{
		ImGui::PushItemWidth(105);
		ImGui::ColorEdit3(featureName, colorEditFloat, ImGuiColorEditFlags_NoInputs);
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(toggleName, ImVec2(width, height));
		if (ImGui::IsItemClicked())
			*featureBool = !*featureBool;

		float t = *featureBool ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.08f;
		if (g.LastActiveId == g.CurrentWindow->GetID(toggleName))// && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
			t = *featureBool ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 0.40f), ImVec4(ImColor(255, 100, 15, 200)), t));
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 0.60f), ImVec4(ImColor(255, 100, 15, 255)), t));

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		ImGui::SameLine();
		ImGui::Text(toggleName);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	float GetX()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float GetY()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	void SetGUITheme()
	{
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowBorderSize = 0;
		Style->FrameBorderSize = 0;
		Style->WindowRounding = 4;
		Style->ChildRounding = 4;
		Style->ChildBorderSize = 2;
		Style->FrameRounding = 4;
		Style->ScrollbarSize = 0;
		Style->WindowPadding = ImVec2(0, 0);
		Style->FramePadding = ImVec2(0, 0);
		Style->ItemSpacing = ImVec2(0, 0);
		Style->ItemInnerSpacing = ImVec2(0, 0);
		Style->IndentSpacing = 0;
		Style->DisplayWindowPadding = ImVec2(0, 0);
		Style->Colors[ImGuiCol_WindowBg] = BO3Orange;
		Style->Colors[ImGuiCol_ChildBg] = BO3Orange;
		Style->Colors[ImGuiCol_Border] = BO3Orange;
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 255, 255);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 0, 255, 255);
		Style->Colors[ImGuiCol_Button] = ImColor(255, 100, 15, 255);
		Style->Colors[ImGuiCol_ButtonHovered] = ImColor(255, 100, 15, 200);
		Style->Colors[ImGuiCol_ButtonActive] = ImColor(255, 100, 15, 155);
		Style->Colors[ImGuiCol_Separator] = BO3Orange;
		Style->Colors[ImGuiCol_SeparatorActive] = BO3Orange;
		Style->Colors[ImGuiCol_CheckMark] = BO3Orange;
		Style->Colors[ImGuiCol_HeaderHovered] = BO3Orange;
		Style->Colors[ImGuiCol_HeaderActive] = BO3Orange;
		Style->Colors[ImGuiCol_Header] = BO3Orange;
		Style->Colors[ImGuiCol_TextSelectedBg] = BO3Orange;
	}
#pragma endregion

#pragma region Main GUI Render Function
	void RenderGUI()
	{
		// Main Child Window.
		if (ImGui::BeginChild("MainChildWindow", ImVec2(600, 500), true, windowFlags))
		{
			// Top Logo Window.
			ImGui::SCP(1, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("TopLogoWindow", ImVec2(144, 120), true, windowFlags))
			{
				ImGui::SCP(ImGui::GetX() / 2 - 64, ImGui::GetY() / 2 - 46);
				ImGui::RenderLogo();
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Top Header Window.
			ImGui::SCP(145, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("TopHeaderWindow", ImVec2(454, 50), true, windowFlags))
			{
				ImGui::SCPY(12);
				ImGui::PushFont(Header2);
				if (UI::iTab == 0)
				{
					ImGui::CenterText("BO3 Zombie Visuals", 0, FALSE, FALSE);
				}
				if (UI::iTab == 1)
				{
					ImGui::CenterText("BO3 Zombie Aimbot", 0, FALSE, FALSE);
				}
				if (UI::iTab == 2)
				{
					ImGui::CenterText("BO3 Zombie Exploits", 0, FALSE, FALSE);
				}
				if (UI::iTab == 3)
				{
					ImGui::CenterText(("SAVE | LOAD | CONFIG SYSTEM"), 0, FALSE, FALSE);
				}
				ImGui::PopFont();
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Left Side Task Bar.
			ImGui::SCP(1, 120);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("LeftSideTaskBarWindow", ImVec2(145, 379), true, windowFlags))
			{
				// Window Buttons.
				ImGui::PushFont(Body2);
				ImGui::ButtonPageSCP("ESP", &UI::iTab, 0, ImVec2(10, 43), ImVec2(125, 40), FALSE);
				ImGui::ButtonPageSCP("Beta", &UI::iTab, 1, ImVec2(10, 138), ImVec2(125, 40), FALSE);
				ImGui::ButtonPageSCP("Player", &UI::iTab, 2, ImVec2(10, 233), ImVec2(125, 40), FALSE);
				ImGui::ButtonPageSCP("Settings", &UI::iTab, 3, ImVec2(10, 328), ImVec2(125, 40), FALSE);
				ImGui::PopFont();
				ImGui::PushFont(Body);
				ImGui::TextSCP("Visuals", 10, 13);
				ImGui::TextSCP("Aimbot", 10, 108);
				ImGui::TextSCP("Exploits", 10, 203);
				ImGui::TextSCP("Config", 10, 298);
				ImGui::PopFont();
				ImGui::PushFont(Body2);
				ImGui::TextSCP(ICON_FA_VECTOR_SQUARE, 15, 57);
				ImGui::TextSCP(ICON_FA_BULLSEYE, 15, 152);
				ImGui::TextSCP(ICON_FA_CODE, 15, 247);
				ImGui::TextSCP(ICON_FA_COGS, 15, 342);
				ImGui::PopFont();
			} ImGui::PopStyleColor(); ImGui::EndChild();
			
			// Main Content.
			ImGui::SCP(145, 60);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("MainContentWindow", ImVec2(454, 439), true, windowFlags))
			{
				// Visuals Window.
				if (UI::iTab == 0)
				{
					// Visuals Features Window.
					ImGui::SCP(10, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("VisualsFeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Visuals", 10, TRUE, TRUE);
						ImGui::Indent(12);
						ImGui::ToggleNL("  2D Box", &VisualSettings::bZombie2DBox, TRUE);
						ImGui::ToggleNL("  2D Bracket", &VisualSettings::bZombie2DBrackets, TRUE);
						ImGui::ToggleNL("  Box Filled", &VisualSettings::bZombieBoxFilled, TRUE);
						ImGui::ToggleNL("  Snapline", &VisualSettings::bZombieSnaplines, TRUE);
						ImGui::ToggleNL("  Health Bar", &VisualSettings::bZombieHealthBar, TRUE);
						ImGui::ToggleNL("  Distance", &VisualSettings::bZombieDistance, TRUE);
						ImGui::ToggleNL("  Crosshair +", &MiscSettings::bCrosshair, TRUE);
						ImGui::ToggleNL("  FOV Circle", &MiscSettings::bPlayerFov, TRUE);
						ImGui::ButtonIntSCP("Snapline Top", &VisualSettings::iZombieSnaplinePos, 1, 12, 343, ImVec2(188, 20), FALSE);
						ImGui::ButtonIntSCP("Snapline Mid", &VisualSettings::iZombieSnaplinePos, 2, 12, 368, ImVec2(188, 20), FALSE);
						ImGui::ButtonIntSCP("Snapline Bottom", &VisualSettings::iZombieSnaplinePos, 3, 12, 393, ImVec2(188, 20), FALSE);
						ImGui::Unindent(12);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

					// Visuals Color Settings Window.
					ImGui::SCP(232, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("ColorSettingsWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Color Settings", 10, TRUE, TRUE);
						ImGui::Indent(12);
						ImGui::ColorEditFeature("  2D Box", (float*)&VisualSettings::boxImColor, TRUE);
						ImGui::ColorEditFeature("  2D Bracket", (float*)&VisualSettings::bracketBoxImColor, TRUE);
						ImGui::ColorEditFeature("  Box Filled", (float*)&VisualSettings::boxFilledImColor, TRUE);
						ImGui::ColorEditFeature("  Snapline", (float*)&VisualSettings::snaplineImColor, TRUE);
						ImGui::ColorEditFeature("  Distance", (float*)&VisualSettings::distanceImColor, TRUE);
						ImGui::ColorEditFeature("  Crosshair +", (float*)&VisualSettings::crosshairImColor, TRUE);
						ImGui::ColorEditFeature("  FOV", (float*)&VisualSettings::fovImColor, TRUE);
						ImGui::Unindent(12);
						//std::string text = std::to_string(ImGui::GetX());
						//ImGui::Text(text.c_str());
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
				}
				// Aimbot Window.
				if (UI::iTab == 1)
				{
					// Aimbot Features Window.
					ImGui::SCP(10, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("AimbotFeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Aimbot", 10, TRUE, TRUE);
						ImGui::SCPY(ImGui::GetY() / 2 - 50);
						ImGui::CenterText("COMING SOON!", 0, FALSE, FALSE);
						ImGui::SCPY(ImGui::GetY() / 2 + 50);
						ImGui::CenterText("PLEASE BE PATIENT", 0, FALSE, FALSE);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

					// Aimbot Bone Select Window.
					ImGui::SCP(232, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("AimbotBoneSettingsWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Bone Select", 10, TRUE, TRUE);
						ImGui::SCPY(ImGui::GetY() / 2 - 50);
						ImGui::CenterText("COMING SOON!", 0, FALSE, FALSE);
						ImGui::SCPY(ImGui::GetY() / 2 + 50);
						ImGui::CenterText("PLEASE BE PATIENT", 0, FALSE, FALSE);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
				}
				// Exploits Window.
				if (UI::iTab == 2)
				{
					if (UI::iExploitPage == 1)
					{
						// Player 1 Feature Window.
						ImGui::SCP(10, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player1FeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 1 ( HOST )", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP1InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP1InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP1InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP1RapidFire, TRUE);
							ImGui::ToggleNL("  No Recoil", &FeatureSettings::bNoRecoilOn, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP1PointsValue, &FeatureSettings::bP1DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP1InfinitePoints, TRUE);
							ImGui::InputIntNL("  Weapon Cycle", &FeatureSettings::iP1WCValue, &FeatureSettings::bP1WCycle, 80, FALSE, TRUE);
							ImGui::Unindent(12);
							ImGui::Separator();
							ImGui::NewLine();
							ImGui::Indent(12);
							ImGui::InputIntNL("  Jumpheight", &FeatureSettings::iJumpHeightValue, &FeatureSettings::bP1JumpHeight, 100, FALSE, TRUE);
							ImGui::ToggleNL("  Teleport Zombie", &FeatureSettings::bZombieTP, FALSE);
							ImGui::Unindent(12);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

						// Player 2 Feature Window.
						ImGui::SCP(232, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player2FeatureWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 2", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP2InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP2InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP2InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP2RapidFire, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP2PointsValue, &FeatureSettings::bP2DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP2InfinitePoints, TRUE);
							ImGui::Unindent(12);
							ImGui::ButtonWindowSCP(">", &UI::iExploitPage, 2, ImVec2(152, 390), ImVec2(50, 20), FALSE);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
					}
					
					if (UI::iExploitPage == 2)
					{
						// Player 3 Feature Window.
						ImGui::SCP(10, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player3FeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 3", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP3InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP3InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP3InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP3RapidFire, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP3PointsValue, &FeatureSettings::bP3DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP3InfinitePoints, TRUE);
							ImGui::Unindent(12);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

						// Player 4 Feature Window.
						ImGui::SCP(232, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player4FeatureWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 4", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP4InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP4InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP4InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP4RapidFire, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP4PointsValue, &FeatureSettings::bP4DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP4InfinitePoints, TRUE);
							ImGui::Unindent(12);
							ImGui::ButtonWindowSCP("<", &UI::iExploitPage, 1, ImVec2(152, 390), ImVec2(50, 20), FALSE);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
					}
				}
				// Config System Window.
				if (UI::iTab == 3)
				{
					// Config Feature Window.
					ImGui::SCP(10, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("ConfigSystemWindow", ImVec2(434, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Config System", 10, TRUE, TRUE);
						ImGui::SCPY(225);
						ImGui::CenterText("COMING SOON!", 10, TRUE, TRUE);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
				}
			} ImGui::PopStyleColor(); ImGui::EndChild();
		} ImGui::EndChild();
	}
#pragma endregion
}