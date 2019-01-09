#include "csgo.h"

void setupHooks() {
	PaintTraverseOriginal = (PaintTraverseStub)PaintTraverseDetour.HookFunction(0x85C839C0, (unsigned int)PaintTraverseHook);
	CreateMoveOriginal = (CreateMoveStub)CreateMoveDetour.HookFunction(0x881E6CB8, (unsigned int)CreateMoveHook);
	XamInputGetStateOriginal = (XamInputGetStateStub)XamInputGetStateDetour.HookFunction(0x82CF501C, (DWORD)XamInputGetStateHook);
	//DrawModelExecuteOriginal = (DrawModelExecuteStub)DrawModelExecuteDetour.HookFunction(0x8699C368, (unsigned int)DrawModelExecuteHook);
}

IClientEntityList* g_EntityList;
IBaseClientDll* Client;
CBaseEntity* LocalPlayer;
IEngineTrace* EngineTrace;
IVModelInfo* ModelInfo;

bool unloadModule = false;
bool Initialized = false;

void mainThread()
{


	//Sleep(10000);
	LoadAddresses();

	XNotify(L"xbOnline CSGO Cheats Loaded!\nDeveloped by Blasts Mods");

	PopulateVtables(&VEngineClient013,
		&VGUI_Surface031,
		&VClientEntityList003,
		&CCInputAddr,
		&ClientModeAddr,
		&CModelRenderAddr,
		&CVRenderViewAddr,
		&KeyValuesAddr);

	setupMenu();
	setupHooks();


	while (!unloadModule)
	{
		//try & except isn't needed, this project doesn't crash :)
		__try {
			if (!Initialized) {
				updateStructs();
	
				//just some fun dvars, show fps etc
				Cbuf_AddText_f(0, "gameinstructor_enable 0;mat_motion_blur_enabled 0;cl_showfps 4;net_graph 1;cl_viewmodel_shift_left_amt 1.5;cl_viewmodel_shift_right_amt 0.75;viewmodel_fov 64.000000;viewmodel_offset_x 0;viewmodel_offset_y 2.0;viewmodel_offset_z -2;viewmodel_presetpos 0;cl_bob_lower_amt 10;cl_bobamt_lat 0.4;cl_bobamt_vert 0.25;cl_bobcycle 0.980000;", 0);
				Cbuf_AddText_f(0, "fps_max 60;rate 786432;cl_cmdrate 128;cl_interp 0;cl_interp_ratio 1;mat_queue_mode 2;r_threaded_renderables 1;r_threaded_particles;", 0);
	
				Initialized = true;
			}
	
			int CurrentMenu = MenuVars.currentMenu,
				CurrentOption = MenuVars.currentOption[CurrentMenu],
				MaxOption = MenuVars.optionCount[CurrentMenu],
				PreviousMenu = MenuVars.previousMenu[CurrentMenu];
			
			if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && GetAsyncKeyState(XINPUT_GAMEPAD_RIGHT_THUMB))
				MenuVars.isOpen = !MenuVars.isOpen;
			
			if (MenuVars.isOpen)
			{
				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && CurrentOption < MaxOption - 1)
					MenuVars.currentOption[CurrentMenu]++;
			
				else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) && CurrentOption == MaxOption - 1)
					MenuVars.currentOption[CurrentMenu] = 0;
			
				if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && CurrentOption > 0)
					MenuVars.currentOption[CurrentMenu]--;
			
				else if (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) && CurrentOption == 0)
					MenuVars.currentOption[CurrentMenu] = MaxOption - 1;
			
				if (GetAsyncKeyState(XINPUT_GAMEPAD_A)) {
					if (MenuVars.Option_Toggle[CurrentMenu][CurrentOption] != NULL)
						*MenuVars.Option_Toggle[CurrentMenu][CurrentOption] = !*MenuVars.Option_Toggle[CurrentMenu][CurrentOption];
					if (MenuVars.Option_Function[CurrentMenu][CurrentOption] != NULL)
						MenuVars.Option_Function[CurrentMenu][CurrentOption](MenuVars.Option_Param1[CurrentMenu][CurrentOption], MenuVars.Option_Param2[CurrentMenu][CurrentOption]);
				}
			
				if (GetAsyncKeyState(XINPUT_GAMEPAD_B)) {
					if (PreviousMenu == -1) MenuVars.isOpen = false;
					else MenuVars.currentMenu = MenuVars.previousMenu[CurrentMenu];
				}
			
				while (GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_UP) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_DOWN) || GetAsyncKeyState(XINPUT_GAMEPAD_A) || GetAsyncKeyState(XINPUT_GAMEPAD_B) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_RIGHT) || GetAsyncKeyState(XINPUT_GAMEPAD_DPAD_LEFT)) {
					Sleep(1);
				}
			}
			
			//if (CurrentMenu == CLIENTS)
			//	updatePlayerList();
			

			Sleep(5);
		}
		__except (1) {
		}
	}
}

BOOL WINAPI DllMain(HANDLE hInstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {


		HANDLE ConstructionThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)mainThread, 0, 0, 0);
		CloseHandle(ConstructionThreadHandle);

		//*(int*)0x8B1CAED4 = 0x60000000;
		//*(int*)0x8B1CAE90 = 0x60000000;
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		unloadModule = true;

#if defined(DEVELOPERSDEVELOPERSDEVELOPERS)

		PaintTraverseDetour.RestoreFunction();
		CreateMoveDetour.RestoreFunction();
		DrawModelExecuteDetour.RestoreFunction();
		XamInputGetStateDetour.RestoreFunction();
#endif
		Sleep(500);
	}
	return true;
}