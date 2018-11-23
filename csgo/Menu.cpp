#include "csgo.h"

Vars MenuVars;
int MenuIndex = 0;

bool bAimbot = false;
bool bAimkey = false;
bool bAutoAim = false;
bool ESPStatus = false;
bool b2DBoxes = false;
bool bSnaplines = false;
bool bSpinbot = false;
bool bDisableEffects = false;
bool bPrioritized[30] = { 0 };
bool bBhop = false;
bool bNames = false;
bool bSkeleton = false;

void addMenu(const char* Name, int Index, int Previous = -1)
{
	MenuVars.Menu_Title[Index] = Name;
	MenuVars.currentOption[Index] = Index;
	MenuVars.previousMenu[Index] = Previous;
	MenuVars.currentOption[Index] = 0;
	MenuIndex = Index;
}

void addArray(const char* Name, char **Array = NULL, int ArraySize = NULL, int *ArrayCur = 0, void(*Function)(int) = NULL)
{
	int Index = MenuVars.optionCount[MenuIndex];
	MenuVars.Option_Text[MenuIndex][Index] = Name;

	MenuVars.Option_Function[MenuIndex][Index] = (void(*)(int, int)) Function;
	MenuVars.Option_Toggle[MenuIndex][Index] = NULL;
	MenuVars.Option_Param1[MenuIndex][Index] = NULL;
	MenuVars.Option_ToggleArr[MenuIndex][Index] = Array;
	MenuVars.Option_ToggleArr_Size[MenuIndex][Index] = ArraySize;
	MenuVars.Option_ToggleArr_Cur[MenuIndex][Index] = ArrayCur;
	MenuVars.optionCount[MenuIndex]++;
}

void addOption(const char* Name, bool* Toggle = NULL, void* Function = NULL, int Param = -1, int Param2 = -1)
{
	int Index = MenuVars.optionCount[MenuIndex];
	MenuVars.Option_Text[MenuIndex][Index] = Name;
	MenuVars.Option_Function[MenuIndex][Index] = (void(*)(int, int)) Function;
	MenuVars.Option_Toggle[MenuIndex][Index] = Toggle;
	MenuVars.Option_Param1[MenuIndex][Index] = Param;
	MenuVars.Option_Param2[MenuIndex][Index] = Param2;
	MenuVars.optionCount[MenuIndex]++;
}

void openSub(int Menu, int client = NULL)
{
	MenuVars.currentMenu = Menu;
}

void playerSub(int player)
{
	player_info_t pinfo;
	getPlayerInfo(VEngineClient013, player, &pinfo);
	if (strcmp(pinfo.name, "")) {
		MenuVars.currentMenu = (CLIENTS + 1) + player;
	}
}

void AddPlayerMenu(int i)
{
	addMenu("Player", i + (CLIENTS + 1), CLIENTS);
	addOption("Prioritize", &bPrioritized[i], NULL);
}

void setupMenu() {
	addMenu("CSGO Menu", MAIN);
	addOption("Aimbot Menu", NULL, openSub, AIMBOT);
	addOption("ESP Menu", NULL, openSub, ESP);
	addOption("Client List", NULL, openSub, CLIENTS);

	addMenu("Aimbot Menu", AIMBOT, 0);
	addOption("Aimbot Status", &bAimbot);
	//addOption("Aimkey (RT)", &bAimkey);
	addOption("Auto Aim", &bAutoAim);
	addOption("No Recoil", &bDisableEffects);
	addOption("Auto BHop", &bBhop);

	addMenu("ESP Menu", ESP, 0);
	addOption("ESP Status", &ESPStatus);
	addOption("Draw Names", &bNames);
	addOption("Draw 2D Boxes", &b2DBoxes);
	addOption("Draw Snaplines", &bSnaplines);
	addOption("Draw Bones", &bSkeleton);

	addMenu("Clients", CLIENTS, 0);
	addOption("Not Connected", NULL, &playerSub, 0);
	addOption("Not Connected", NULL, &playerSub, 1);
	addOption("Not Connected", NULL, &playerSub, 2);
	addOption("Not Connected", NULL, &playerSub, 3);
	addOption("Not Connected", NULL, &playerSub, 4);
	addOption("Not Connected", NULL, &playerSub, 5);
	addOption("Not Connected", NULL, &playerSub, 6);
	addOption("Not Connected", NULL, &playerSub, 7);
	addOption("Not Connected", NULL, &playerSub, 8);
	addOption("Not Connected", NULL, &playerSub, 9);

	for (int i = 0; i < 10; i++)
	{
		AddPlayerMenu(i);
	}
}