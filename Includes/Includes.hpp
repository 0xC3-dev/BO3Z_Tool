#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <cstdint>
#include <vector>
#include <thread>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <tchar.h>
#include <limits>
#include <cmath>
#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <random>
#pragma comment (lib, "winmm.lib")
#include "../D3D11_SDK/d3d11.hpp"
#pragma comment (lib, "d3d11.lib")
#include "../D3D11_SDK/d3dx11tex.hpp"
#pragma comment(lib, "D3DX11.lib")
#include "../imgui/imgui.hpp"
#include "../imgui/imgui_impl_dx11.hpp"
#include "../imgui/imgui_impl_win32.hpp"
#include "../imgui/imgui_internal.hpp"
#include "../Fonts/Roboto-Bold.hpp"
#include "../Logo/BO3_Logo.hpp"
#include "../Fonts/Awesome.hpp"
#include "../Fonts/Awesome_Light.hpp"
#include "../Fonts/FontAwesome5/font_awesome_5.hpp"
//#include "../Fonts/FontAwesome6/font_awesome_6.hpp"
#include "../Engine/Vectors/Vectors.hpp"