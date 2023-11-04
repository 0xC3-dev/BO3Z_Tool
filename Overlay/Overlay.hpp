#pragma once
#pragma warning( disable: 4049 )  /* more than 64k source lines */
#include "../Engine/Engine.hpp"
#include "../imgui/imgui.hpp"
#include "../imgui/imgui_impl_dx11.hpp"
#include "../imgui/imgui_impl_win32.hpp"
#include "../imgui/imgui_internal.hpp"
#include "../Logo/BO3_Logo.hpp"
#include "../Fonts/Roboto-Bold.hpp"
#include "../Fonts/Awesome.hpp"
#include "../Fonts/Awesome_Light.hpp"
#include "../Fonts/FontAwesome5/font_awesome_5.hpp"
#include "../Fonts/FontAwesome6/font_awesome_6.hpp"
#define DIRECTINPUT_VERSION 0x0800

#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN)
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN)

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

inline DWORD windowFlags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration; // ImGuiWindowFlags_NoSavedSettings

namespace Overlay
{
    void Loop(void* blank);
}

namespace Render
{
    void Start();

    void End();

    void Text(ImVec2 pos, float fontsize, ImColor color, const char* text_begin, const char* text_end, float wrap_width,
        const ImVec4* cpu_fine_clip_rect);

    void EasyText(ImVec2 pos, ImColor color, const char* text, float fontsize);

    void EasyNumber(ImVec2 pos, ImColor color, int number, float fontsize);

    void RectFilled(int x0, int y0, int x1, int y1, ImColor color, float rounding, int rounding_corners_flags);

    void RectFilled2(int x, int y, int w, int h, ImColor color);

    void Line(ImVec2 a, ImVec2 b, ImColor color, float thickness);

    void DrawBoxBrackets(ImDrawList* list, float x, float y, float width, float height, ImColor color, float thickness);

    void DrawBox(ImColor color, int x, int y, int w, int h);

    void Circle(ImColor color, float fov);

    void HealthBar(int x, int y, int w, int h, int ehealth);

    void CustomHealthColor(float currentHealth, float maxHealth, ImColor* healthColor);

    float DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ...);
}

namespace Menu
{
    void RenderStatic();

    void RenderMenu();

    void RenderFeatures();
}

namespace ImGui
{
#pragma region GUI Setup Functions
	extern ImFont* Header;
	extern ImFont* Header2;
	extern ImFont* Body;
	extern ImFont* Body2;
	extern ImFont* FA;
	extern ImFont* FA2;
	extern ImColor BO3Orange;
	extern ImColor DarkGrey22;
	extern ImColor LightGrey26;
	extern ImColor White;
	extern ImVec4 active;
	extern ImVec4 inactive;

	void RenderLogo();

	void SCP(float x, float y);
	
	void SCPX(float x);
	
	void SCPY(float y);
	
	void Line(int newId);
	
	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine);
	
	void TextNL(const char* text, BOOL newLine);
	
	void TextSL(const char* text, BOOL sameLine, BOOL newLine);
	
	void TextSCP(const char* text, int x, int y);
	
	void TextColor(const char* text, ImVec4 color, int lineId, BOOL seperator, BOOL newLine);
	
	void ButtonNL(const char* featureName, bool* featureBool, ImVec2 size, BOOL newLine);
	
	void ButtonSCP(const char* featureName, bool* featureBool, int x, int y, ImVec2 size, BOOL newLine);
	
	void ButtonIntSCP(const char* featureName, int* featureInt, int value, int x, int y, ImVec2 size, BOOL newLine);
	
	void ButtonPageSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine);
	
	void ButtonWindowSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine);
	
	void InputIntNL(const char* featureName, int* featureInt, bool* featureBool, int size, BOOL sameLine, BOOL newLine);
	
	void ColorEditFeature(const char* featureName, float* colorEditFloat, BOOL newLine);
	
	void WeaponCycleComboBox(const char* featureName, int size, BOOL newLine);
	
	void ZombieTPComboBox(const char* featureName, int size, BOOL newLine);
	
	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine);
	
	float GetX();
	
	float GetY();
	
	void SetGUITheme();
#pragma endregion

#pragma region Main GUI Render Function
	void RenderGUI();
#pragma endregion
}