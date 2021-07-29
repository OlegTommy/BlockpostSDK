
//sack
#include "includes.h"
#include "Settings.h"
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "framework/il2cpp-init.h"
#include "WallHack.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
USettings Settings;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
bool show = true;
bool initOnce = false;
AimBot aim;
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
	return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}



bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	WallHack wall;
	uintptr_t gameoverlayrenderer = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("gameoverlayrenderer.dll")));
	int height = *reinterpret_cast<int*>(gameoverlayrenderer + 0x1418DC);
	int width = *reinterpret_cast<int*>(gameoverlayrenderer + 0x1418D8);
	float ScreenCenterY = height * 0.5f;
	float ScreenCenterX = width * 0.5f;
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	if (GetAsyncKeyState(KEYMENY) & 1)
	{
		show = !show;
	}
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (show)
	{
		
		
		ImGui::Begin("BLOCKPOST-US");
		ImGui::Checkbox("AllName", &Settings.NameActive);
		ImGui::Checkbox("AimBot", &Settings.AimActive);
		ImGui::Checkbox("AimBotKey", &Settings.AimKeyActive);
		ImGui::Checkbox("TeamCheck", &Settings.TeamCheck);
		ImGui::SliderFloat("Distance", &Settings.Dinstace,1,250);
		ImGui::Checkbox("WallHack", &Settings.Wallhack);
		ImGui::SliderFloat("Fov", &Settings.fov, 2.8, 360);
		ImGui::GetBackgroundDrawList()->AddCircle({ ScreenCenterX, ScreenCenterY }, Settings.fov * 3, ImColor{ 255, 0, 0, 255 });
		
		ImGui::End();

		ImGui::Render();
		
		
	}
	else
	{
		if (Settings.Wallhack)
		{
			ImGui::Begin("dasdas1", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

			//ImGui::GetBackgroundDrawList()->AddCircle({ ScreenCenterX + aim.mysackx * aim.dist / 30, ScreenCenterY + aim.mysacky * aim.dist / 30 },  40, ImColor{ 235, 52, 232, 255 });
			wall.Render();
			ImGui::GetBackgroundDrawList()->AddCircle({ wall.pos.x,wall.pos.y }, 10, ImColor{ 235, 52, 232, 255 });

			ImGui::End();
			ImGui::Render();
			
		}
		else
		{
			ImGui::Begin("dasdas", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

			//ImGui::GetBackgroundDrawList()->AddCircle({ ScreenCenterX + aim.mysackx * aim.dist / 30, ScreenCenterY + aim.mysacky * aim.dist / 30 },  40, ImColor{ 235, 52, 232, 255 });


			ImGui::End();
			ImGui::Render();
		}
		
	}
	
	ImGui::EndFrame();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI FunctTread(HMODULE hMod)
{
	
	Name name;
	
	
	
	while (true)
	{
		
		aim.fov = 2+atan(aim.dist) * Settings.fov;
		aim.distanceFov = Settings.Dinstace;
		
		if (Settings.NameActive)
		{
			Name name;
			name.togle = true;
			Settings.NameActive = false;
			name.Render();

		}
		if (Settings.AimActive)
		{
			
			aim.Render();
		}
		if (Settings.AimKeyActive)
		{
			
			aim.toggle = true;
		}
		else
		{
			
			aim.toggle = false;
		}
		if (Settings.TeamCheck)
		{
			aim.teamcheck = true;
		}
		else
		{
			aim.teamcheck = false;
		}
	
		Sleep(100);
	}

	

	FreeLibraryAndExitThread(hMod, 0);
}



DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		init_il2cpp();
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)FunctTread);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}