#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx11.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_internal.h"

#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN) 
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN)

namespace ImGui
{
    extern ImFont* Header;
    extern ImFont* Header2;
    extern ImFont* Body;
    extern ImFont* Body2;
    extern ImFont* FA;
    extern ImFont* FA2;
}

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
    float DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ...);
}

namespace Menu
{
    void RenderStatic();
    void RenderMenu();
    void RenderFeatures();
}