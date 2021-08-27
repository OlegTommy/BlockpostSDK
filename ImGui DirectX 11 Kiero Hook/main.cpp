
//sack
#include "includes.h"
#include "Settings.h"
#include <iostream>
#include <fstream>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "framework/il2cpp-init.h"
#include "WallHack.h"
#include "Freecam.h";
#include "framework/il2cpp-appdata.h"
#include "Cross.h"
#include "Crash.h"
#include "VisibleCheck.h"
#include "RayCastSack.h"

RayCasstSack sackDaR;
VisibleCheck visibleC;
Crash crash;
CrossH cros;
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
WallHack wall;
FreeCam freeca;
static int tab = 3;

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


const char* config1 = "config1";
const char* config2 = "config2";
const char* config3 = "config3";

bool init = false;
bool DrawWatermark = true;
static const char* Croshairs[8]{ "DEFOLT", "WITH A DOT","DOT","WITHOUT LINE UP","DA","2 LINE","SACK","STRENG DOT" };
static const char* Figure[3]{ "Circle", "Rect","RectFilled"};
static const char* cfg[3]{ config1, config2,config3 };
static int selectiedFigure = 0;
static int selectiedCfg = 0;


float colorTracer[4] = { 0.0f,1.0f,0.0f,1.0f };
float colorWh[4] = { 0.780f, 0.031f, 0.756f,1.0f };
float colorWhS[4] = { 0.007f, 0.152f, 0.788f,1.0f };
static int tabb = 4;

HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	
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
	if (GetAsyncKeyState(KEYMENY ) & 1|| GetAsyncKeyState(VK_F2) & 1)
	{
		show = !show;
	}
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	

	if (show)
	{
		
		ImGui::Begin("BLOCKPOST-US");
		if (ImGui::Button((u8"Aim"), ImVec2(100.f, 0.f)))
			tabb = 0;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button((u8"Vusuals"), ImVec2(100.f, 0.f)))
			tabb = 1;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button((u8"Misc"), ImVec2(100.f, 0.f)))
			tabb = 2;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button((u8"Info"), ImVec2(100.f, 0.f)))
			tabb = 3;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button((u8"CFG"), ImVec2(100.f, 0.f)))
			tabb = 4;
		if (tabb == 0) {
			ImGui::Checkbox("AimBot", &Settings.AimActive);
			ImGui::Checkbox("AimBotKey", &Settings.AimKeyActive);
			ImGui::Checkbox("TeamCheck", &Settings.TeamCheck);
			ImGui::SliderFloat("Distance", &Settings.Dinstace, 1, 250);
			ImGui::SliderFloat("Fov", &Settings.fov, 2.8, 360);
		}
		else if (tabb == 1) {
			ImGui::Checkbox("WallHack", &Settings.Wallhack);
			ImGui::ColorEdit3("WallHackColor", colorWh);
			ImGui::ColorEdit3("WallHackColorInSpawnProtect", colorWhS);
			ImGui::Checkbox("Tracer", &Settings.Tracer);
			ImGui::SliderFloat("LineSize", &Settings.LineSize, 0, 10);
			ImGui::ColorEdit3("ColorTracer", colorTracer);
			ImGui::Combo("figure",&selectiedFigure, Figure,3);
		
		}
		else if (tabb == 2) {
			ImGui::Checkbox("AntiCrash", &Settings.AntiCrash);
			ImGui::Checkbox("Crash  (BUTTON 4)", &Settings.Crash);
			ImGui::Checkbox("Freecam  ", &Settings.FreeCam);
			ImGui::Checkbox("FackeDuck  ", &Settings.Duck);
			ImGui::Checkbox("SpeedBoost  ", &Settings.SpeedBoost);
			ImGui::Checkbox("NoFreez  ", &Settings.NoFreez);
			ImGui::Checkbox("NoReload ", &Settings.NoReload);
			ImGui::ListBox("CrossHair", &cros.selectItemDa, Croshairs, 8, 2);
		}
		else if (tabb == 3)
		{
			ImGui::Checkbox("Discord", &Settings.Discord);
			ImGui::Checkbox("YouTube", &Settings.YouTube);
		}
		else if (tabb == 4)
		{
			ImGui::Combo("CFG", &selectiedCfg, cfg,3);
			if (ImGui::Button("Save", ImVec2(100.f, 0.f)))
				Settings.saveconfig = true;
			ImGui::SameLine(0.f, 2.f);
			if (ImGui::Button("Load", ImVec2(100.f, 0.f)))
				Settings.LoadConfig = true;
			ImGui::SameLine(0.f, 2.f);
			if(ImGui::Button("Delete", ImVec2(100.f, 0.f)))
				Settings.DeleteConfig = true;
		}

		
		
		
		ImGui::GetBackgroundDrawList()->AddCircle({ ScreenCenterX, ScreenCenterY }, Settings.fov * 3, ImColor{ 255, 0, 0, 255 });

		if (Settings.Wallhack)
		{
			
			ImGui::GetBackgroundDrawList()->AddText({ 0,0 }, ImColor{ 10, 63, 255,255 }, "EZHACKBYSCUB");	
			for (int i = 0; i < 40; i++)
			{

				Vector2 Temper = wall.Renders(i);
				if (Temper.d == -1)
					continue;


				std::string text = "HACKER!";
				const char* detectH = text.c_str();
				char aaa[16] = { Temper.str[0], Temper.str[2],Temper.str[4], Temper.str[6], Temper.str[8] ,Temper.str[10], Temper.str[12], Temper.str[14], Temper.str[16], Temper.str[18], Temper.str[20], Temper.str[22], Temper.str[24], Temper.str[26], Temper.str[28], Temper.str[30] };

				if (Temper.d == 3)
				{
					//	ImGui::GetBackgroundDrawList()->AddText({ Temper.x,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, Temper.str);
					ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
					if (selectiedFigure == 0)
						ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] }, 12, 2);
					if (selectiedFigure == 1)
						ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] });
					if (selectiedFigure == 2)
						ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] });

				}
				else if (Temper.d == 44)
				{
					ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
					if (selectiedFigure == 0)
						ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ 255, 255, 222,255 }, 12, 2);
					if (selectiedFigure == 1)
						ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ 255, 255, 222 ,255 });
					if (selectiedFigure == 2)
						ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ 255, 255, 222,255 });

				}
				else
				{
					ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
					if (selectiedFigure == 0)
						ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] }, 12, 2);
					if (selectiedFigure == 1)
						ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] });
					if (selectiedFigure == 2)
						ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] });
				}
				

				if (Settings.Tracer)
				{
					ImGui::GetBackgroundDrawList()->AddLine({ (float)app::Screen_get_width(nullptr) / 2,(float)app::Screen_get_height(nullptr) / 2 + 500 }, { Temper.x,Temper.y }, ImColor{ colorTracer[0],colorTracer[1],colorTracer[2],colorTracer[3] }, Settings.LineSize);
				}
				
				
			}
		}

		ImGui::End();

		ImGui::Render();
		
		
	}
	else
	{
		
		if (Settings.Wallhack)
		{
			ImGui::Begin("dasdas1", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
			ImGui::GetBackgroundDrawList()->AddText({ 0,0 }, ImColor{ 10, 63, 255,255 }, "EZHACKBYSCUB");
			
			for (int i = 0; i < 40; i++)
			{
			
				Vector2 Temper = wall.Renders(i);
				if (Temper.d == -1)
					continue;

			
				char aaa[16] = {Temper.str[0], Temper.str[2],Temper.str[4], Temper.str[6], Temper.str[8] ,Temper.str[10], Temper.str[12], Temper.str[14], Temper.str[16], Temper.str[18], Temper.str[20], Temper.str[22], Temper.str[24], Temper.str[26], Temper.str[28], Temper.str[30] };
				
				std::string text = "HACKER!";
				const char* detectH = text.c_str();
				if (Temper.d == 3)
				{
					
					ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
					if (selectiedFigure == 0)
						ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] }, 12, 2);
					if (selectiedFigure == 1)
						ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] });
					if (selectiedFigure == 2)
						ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] });

				}
				else if (Temper.d == 44)
				{
					ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
					if (selectiedFigure == 0)
						ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ 255, 255, 222,255 }, 12, 2);
					if (selectiedFigure == 1)
						ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ 255, 255, 222 ,255 });
					if (selectiedFigure == 2)
						ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ 255, 255, 222,255 });

				}
				else
				{
					ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
					if (selectiedFigure == 0)
						ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] }, 12, 2);
					if (selectiedFigure == 1)
						ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] });
					if (selectiedFigure == 2)
						ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] });
				}

				if (Settings.Tracer)
				{
					ImGui::GetBackgroundDrawList()->AddLine({ (float)app::Screen_get_width(nullptr) / 2,(float)app::Screen_get_height(nullptr) / 2 + 500 }, { Temper.x,Temper.y }, ImColor{ colorTracer[0],colorTracer[1],colorTracer[2],colorTracer[3] }, Settings.LineSize);
				}
				
				
			}


			ImGui::End();
			ImGui::Render();
			
		}
		else
		{
			ImGui::Begin("dasdas", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);
			ImGui::SetWindowFontScale(1.8);
			
			


			ImGui::End();
			ImGui::Render();
		}
		
	}
	
	ImGui::EndFrame();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI FreeCamThread(HMODULE hMod)
{
	
	int i = 0;
	FreeCam free;
	while (true)
	{
		cros.Render();		
		
		app::Controll__StaticFields* da = (*app::Controll__TypeInfo)->static_fields; // saksak 
		app::Crosshair__StaticFields* cross = (*app::Crosshair__TypeInfo)->static_fields; // saksak
		
	
		
		cross->crosshair_attack = 0;
		
		if (Settings.Duck)
		{
			da->inDuck = true;
			da->boxheight = 1.89;
		}
		if (Settings.NoFreez)
		{
			da->inStuck = false;
			da->inFreeze = false;
		}
		if (Settings.SpeedBoost)
			da->default_speed = 0.55f;	
		if (Settings.NoReload)
			da->inReload = false;
	
		
		
		

		if (Settings.Crash)
		{
			crash.Render();
			crash.active = true;
		}
		else
		{			
			crash.Render();
			crash.active = false;
		}
		if (Settings.FreeCam)
		{
			if(GetAsyncKeyState(0x58) & 1)
			free.Render();
		}
		if (Settings.Visible)
		{
			
				visibleC.Render();
			
		}
		if (Settings.Discord)
		{
			ShellExecute(NULL, "open", "https://discord.gg/QwYW3vMN", NULL, NULL, SW_SHOW);
			Settings.Discord = false;
		}
		if (Settings.YouTube)
		{
			ShellExecute(NULL, "open", "www.youtube.com/channel/UC-jF6GNJZiaNY4SFKfjrNGw?sub_confirmation=1", NULL, NULL, SW_SHOW);
			Settings.YouTube = false;
		}
	}
	
	FreeLibraryAndExitThread(hMod, 0);
}
DWORD WINAPI FunctTread(HMODULE hMod)
{
	
	app::Main__StaticFields* main = (*app::Main__TypeInfo)->static_fields;
	AutomaticW asdddd; 
	asdddd.Render();
	
	
	main->winter = true;
	main->winter = 1;
	while (true)
	{
		
		
		aim.fov = 2+atan(aim.dist) * Settings.fov;
		aim.distanceFov = Settings.Dinstace;
		
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
			wall.teamcheck = true;
			aim.teamcheck = true;
			
		}
		else
		{
			wall.teamcheck = false;
			aim.teamcheck = false;
		}
		if (Settings.AntiCrash)
		{
			DWORD OldProtection;
			uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
			uintptr_t RsolverCrash = baseModule + 0x157100;
			VirtualProtect((LPVOID)RsolverCrash, 4, 0x40, &OldProtection);
			BYTE* antcrash = reinterpret_cast<BYTE*>(RsolverCrash);
			*antcrash = 0xC3;
		}
		else
		{
			DWORD OldProtection;
			uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
			uintptr_t RsolverCrash = baseModule + 0x157100;
			VirtualProtect((LPVOID)RsolverCrash, 4, 0x40, &OldProtection);
			BYTE* antcrash = reinterpret_cast<BYTE*>(RsolverCrash);
			*antcrash = 0x80,0x3D,0x9F,0xAA,0x69,0x7A,0x00;
		}
	
		Sleep(100);
	}

	

	FreeLibraryAndExitThread(hMod, 0);
}

DWORD WINAPI ConfigThread(HMODULE hMod)
{
	while (true)
	{
		if (Settings.saveconfig)
		{
			std::ofstream out1("cfg1.txt");
			out1 << Settings.AimActive << std::endl << Settings.AimKeyActive << std::endl << Settings.Crash << std::endl << Settings.Dinstace << std::endl << Settings.espTeamCheck << std::endl << Settings.fov << std::endl << Settings.FreeCam << std::endl << Settings.LineSize << std::endl << Settings.TeamCheck << std::endl << Settings.Tracer << std::endl << Settings.Wallhack << std::endl << colorTracer[0] << std::endl << colorTracer[1] << std::endl  << colorTracer[2] << std::endl  << colorTracer[3] << std::endl << colorWh[0] << std::endl << colorWh[1] << std::endl << colorWh[2] << std::endl << colorWh[3] << std::endl << colorWhS[0] << std::endl << colorWhS[1] << std::endl << colorWhS[2] << std::endl << colorWhS[3]   << std::endl << cros.selectItemDa << std::endl << Settings.Duck << std::endl << Settings.NoFreez << std::endl << Settings.NoReload << std::endl << Settings.SpeedBoost;
			out1.close();
			Settings.saveconfig = false;
		}
		if (Settings.LoadConfig)
		{
			std::string index[29];
			std::size_t count = 0;
			for (std::ifstream input("cfg1.txt"); (count < 29) && std::getline(input, index[count]); ++count)
			{
				// this space intentionally blank
			}
			for (std::size_t i = 0; i < count; ++i)
			{
				
				
			}
		
			Settings.AimActive = std::stoi(index[0]);
			Settings.AimKeyActive = std::stoi(index[1]);
			Settings.Crash = std::stoi(index[2]);
			Settings.Dinstace = std::stoi(index[3]);
			Settings.espTeamCheck = std::stoi(index[4]);
			Settings.fov = std::stoi(index[5]);
			Settings.FreeCam = std::stoi(index[6]);
			Settings.LineSize = std::stoi(index[7]);
			Settings.TeamCheck = std::stoi(index[8]);
			Settings.Tracer = std::stoi(index[9]);
			Settings.Wallhack = std::stoi(index[10]);
			colorTracer[0] = std::stof(index[11]);
			colorTracer[1] = std::stof(index[12]);
			colorTracer[2] = std::stof(index[13]);
			colorTracer[3] = std::stof(index[14]);
			colorWh[0] = std::stof(index[15]);
			colorWh[1] = std::stof(index[16]);
			colorWh[2] = std::stof(index[17]);
			colorWh[3] = std::stof(index[18]);
			colorWhS[0] = std::stof(index[19]);
			colorWhS[1] = std::stof(index[20]);
			colorWhS[2] = std::stof(index[21]);
			colorWhS[3] = std::stof(index[22]);
			cros.selectItemDa = std::stof(index[23]);
			Settings.Duck = std::stof(index[24]);
			Settings.NoFreez = std::stof(index[25]);
			Settings.NoReload = std::stof(index[26]);
			Settings.SpeedBoost = std::stof(index[27]);
			Settings.LoadConfig = false;
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}
DWORD WINAPI RayCastThread(HMODULE hMod)
{
	/*while (true)
	{
		for (int i = 0; i < 40; i++)
		{
			sackDaR.Render(i);		
		
		}
	}*/
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
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)FreeCamThread);
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)ConfigThread);
		//StartThread(nullptr, (LPTHREAD_START_ROUTINE)RayCastThread);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}
