#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "winmm.lib")
#include <d3d11.h>
#include <D3dx11tex.h>
#pragma comment(lib, "D3DX11.lib")
#include <dinput.h>
#include <tchar.h>
#include <dwmapi.h>
#include <ctime>
#include <string>
#include <sstream>
#include <algorithm>
#include <filesystem>
#include <random>
#include "../Engine/Engine.h"
#include "Overlay_UI.h"
#include "Overlay.h"
#include "../Fonts/Roboto-Bold.h"
#include "../Logo/BO3_Logo.h"
#include "../Fonts/Awesome.h"
#include "../Fonts/Awesome_Light.h"
#include <iostream>

inline bool showMenu = true;
inline HWND hWnd = NULL;
inline MARGINS gMargin = { 0, 0, 600, 600 };
inline MARGINS zero = { -1, -1, -1, -1 };
inline int iLogoWidth = 128;
inline int iLogoHeight = 92;

inline  DWORD lastFrameTime = 0;
inline  int lastTick = 0;
void LimitFPS(int targetfps)
{
    DWORD currentTime = timeGetTime();
    if ((currentTime - lastFrameTime) < (1000 / targetfps))
    {
        Sleep(currentTime - lastFrameTime);
    }
    lastFrameTime = currentTime;
}
void ClickThough(bool click)
{
    if (click)
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
    }
    else
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_LAYERED);
    }
}
void CalcScreenPos()
{
    UI::iGuiX = UI::iScreenWidth - 600;
    UI::iGuiY = UI::iScreenHeight - 500;
}

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
ID3D11ShaderResourceView* renderLogo = nullptr;
void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}
void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}
HRESULT CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return E_FAIL;

    CreateRenderTarget();

    return S_OK;
}
void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}
LRESULT WINAPI WndProc(HWND HookhWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void ImGui::RenderLogo()
{
    ImGui::Image((void*)renderLogo, ImVec2(iLogoWidth, iLogoHeight));
}

void Overlay::Loop(void* blank)
{
    UI::iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    UI::iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    CalcScreenPos();

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "BO3Z_Tool", NULL};
    ::RegisterClassEx(&wc);
    hWnd = ::CreateWindow(wc.lpszClassName, "BO3Z_Tool", WS_EX_TOPMOST | WS_POPUP, 0, 0, UI::iScreenWidth, UI::iScreenHeight, NULL, NULL, wc.hInstance, NULL);
    ClickThough(true);
    SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
    gMargin = { 0, 0, UI::iScreenWidth, UI::iScreenHeight };
    DwmExtendFrameIntoClientArea(hWnd, &gMargin);
    if (CreateDeviceD3D(hWnd) < 0)
    {
        CleanupDeviceD3D();
        return;
    }
    ::ShowWindow(hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hWnd);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;
    //ImGui::SaveIniSettingsToDisk(io.IniFilename);
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 18.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Header = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 26.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Header2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 22.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Body = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 20.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Body2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 16.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::FA = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(awesome_light_compressed_data, awesome_light_compressed_size, 20.0f, &icons_config, icons_ranges);
    ImGui::FA2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Awesome, Awesome_size, 16.f, &icons_config, icons_ranges);
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    D3DX11_IMAGE_LOAD_INFO info;
    ID3DX11ThreadPump* pump{ nullptr };
    D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, _BO3Logo, sizeof(_BO3Logo), &info,
        pump, &renderLogo, 0);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
        ::SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        LimitFPS(144);
        if (GetKeyState(VK_INSERT) & 0x8000)
        {
            if ((GetTickCount64() - lastTick) > 1000)
            {
                showMenu = !showMenu;
                lastTick = GetTickCount64();
            }
        }
        if (showMenu)
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            Render::Start();
            Menu::RenderMenu();
            Menu::RenderStatic();
            Menu::RenderFeatures();
            Render::End();
            ClickThough(false);
        }
        else
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            Render::Start();
            Menu::RenderStatic();
            Menu::RenderFeatures();
            Render::End();
            ClickThough(true);
        }
        ImGui::EndFrame();
        ImGui::Render();
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clearColor);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hWnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Render::Start()
{
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(UI::iScreenWidth, UI::iScreenHeight), ImGuiCond_Always);
    ImGui::Begin(" ", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
}
void Render::End()
{
    ImGui::End();
}

void Render::Text(ImVec2 pos, float fontsize, ImColor color, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
{
    ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), fontsize, pos, color, text_begin, text_end,
        wrap_width, cpu_fine_clip_rect);
}
void Render::RectFilled(int x0, int y0, int x1, int y1, ImColor color, float rounding, int rounding_corners_flags)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
}
void Render::RectFilled2(int x, int y, int w, int h, ImColor color)
{
    ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
}
void Render::Line(ImVec2 a, ImVec2 b, ImColor color, float thickness)
{
    ImGui::GetWindowDrawList()->AddLine(a, b, color, thickness);
}
void Render::DrawBoxBrackets(ImDrawList* list, float x, float y, float width, float height, ImColor color, float thickness)
{
    ImVec2 dLine[2];
    dLine[0] = { x, y };
    dLine[1] = { x + 1 * (width / 4), y };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x + 3 * (width / 4), y };
    dLine[1] = { x + width, y };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x + width, y };
    dLine[1] = { x + width, y + 1 * (height / 4) };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x + width, y + 3 * (height / 4) };
    dLine[1] = { x + width, y + height };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x, y + height };
    dLine[1] = { x + 1 * (width / 4), y + height };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x + 3 * (width / 4), y + height };
    dLine[1] = { x + width, y + height };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x, y };
    dLine[1] = { x, y + 1 * (height / 4) };
    list->AddLine(dLine[0], dLine[1], color, thickness);

    dLine[0] = { x, y + 3 * (height / 4) };
    dLine[1] = { x, y + height };
    list->AddLine(dLine[0], dLine[1], color, thickness);
    //delete[] dLine;
}
void Render::EasyText(ImVec2 pos, ImColor color, const char* text, float fontsize)
{
    Render::Text(ImVec2(pos.x + 1.f, pos.y + 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x - 1.f, pos.y - 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y - 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y + 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y), 15.f, color, text, text + strlen(text), 800, 0);
}
void Render::EasyNumber(ImVec2 pos, ImColor color, int number, float fontsize)
{
    auto text = std::to_string(number);
    Render::Text(ImVec2(pos.x + 1.f, pos.y + 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
    Render::Text(ImVec2(pos.x - 1.f, pos.y - 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y - 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y + 1.f), 15.f, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
    Render::Text(ImVec2(pos.x, pos.y), 15.f, color, text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
}
void Render::DrawBox(ImColor color, int x, int y, int w, int h)
{
    float thicc = 1.0f;
    Line(ImVec2(x, y), ImVec2(x + w, y), color, thicc);
    Line(ImVec2(x, y), ImVec2(x, y + h), color, thicc);
    Line(ImVec2(x + w, y), ImVec2(x + w, y + h), color, thicc);
    Line(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thicc);
}
void Render::Circle(ImColor color, float fov)
{
    ImVec2 center = ImVec2(UI::iScreenWidth / 2, UI::iScreenHeight / 2);
    ImGui::GetWindowDrawList()->AddCircle(center, fov, color, 100, 1.f);
}
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
void Render::HealthBar(int x, int y, int w, int h, int ehealth)
{
    int healthValue = max(0, min(ehealth, 100));
    float HealthPerc = healthValue / 100.f;

    ImColor barColor = ImColor
    (
        min(510 * (100 - healthValue) / 100, 255),
        min(510 * healthValue / 100, 255),
        25,
        255
    );

    Render::RectFilled(x, y, x + w, y + (int)(((float)h / 100.0f) * (float)ehealth), barColor, 0.0f, 0);
}
float Render::DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ...)
{
    va_list(args);
    va_start(args, text);

    CHAR wbuffer[256] = { };
    vsprintf_s(wbuffer, text, args);

    va_end(args);

    auto DrawList = ImGui::GetForegroundDrawList();

    std::stringstream stream(text);
    std::string line;

    float y = 0.0f;
    int i = 0;

    while (std::getline(stream, line))
    {
        ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, wbuffer);

        if (center)
        {
            DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
            DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
            DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
            DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);

            DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), wbuffer);
        }
        else
        {
            DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
            DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
            DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
            DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);

            DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), wbuffer);
        }

        y = pos.y + textSize.y * (i + 1);
        i++;
    }
    return y;
}

void Menu::RenderStatic()
{
    ImGuiStyle* style2 = &ImGui::GetStyle();
    std::string toptext;
    toptext = "Open Source BO3 ZM Tool";
    const char* text = toptext.c_str();
    Render::EasyText(ImVec2(10, 10), ImColor(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)), text, 15.f);
}

void Menu::RenderMenu()
{
    ImGui::SetNextWindowPos(ImVec2(UI::iGuiX / 2, UI::iGuiY / 2), ImGuiCond_Once);
    ImGui::SetGUITheme();
    if (ImGui::Begin("BO3Z_Tool", 0, windowFlags))
    {
        ImGui::RenderGUI();
    } ImGui::End();
}

void Menu::RenderFeatures()
{
    Engine::ESP::FeatureLoop();
}