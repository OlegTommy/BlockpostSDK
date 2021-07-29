#pragma once
#define KEYMENY VK_ESCAPE

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "offsetsM.h"
#include "NamePars.h"
#include "Vector.h"
#include "Aim.h"
#include "GetMyPoss.h";
#include "ViewAngle.h"
#include "PlayerData.h"
#include "PlayerDataArray.h"

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;