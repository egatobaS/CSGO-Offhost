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
bool bCompensateRecoil = false;
bool bPrioritized[30] = { 0 };
bool bBhop = false;
bool bNames = false;
bool bSkeleton = false;
bool bEntityESP = false;
bool bShowImpacts = false;
bool bDrawWireframe = false;
bool bDisableFog = false;
bool bCollideWireframe = false;
bool bDrawRenderBoxes = false;

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
	//
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
	getPlayerInfo_f(VEngineClient013, player, &pinfo);
	if (user_strcmp(pinfo.name, "")) {
		MenuVars.currentMenu = (CLIENTS + 1) + player;
	}
}

void AddPlayerMenu(int i)
{
	addMenu("Player", i + (CLIENTS + 1), CLIENTS);
	addOption("Prioritize", &bPrioritized[i], NULL);
}

void updateCvar(int cvar)
{
	if (cvar == FOV)
	{
		if (*(float*)0x88721384 >= (float)174)
			*(float*)0x88721384 = (float)64;
		else
			*(float*)0x88721384 += (float)10;

		char FOVText[0x50] = { 0 };
		_snprintf(FOVText, 0x50, "FOV <%.0f>", *(float*)0x88721384);
		MenuVars.Option_Text[MISC][FOV] = FOVText;
	}
	else if (cvar == IMPACTS)
		*(int*)0x88730794 = bShowImpacts ? 2 : 0;
	else if (cvar == WIREFRAME)
		*(int*)0x886BECA8 = bDrawWireframe ? 2 : 1;
	else if (cvar == FOG)
		*(int*)0x88724724 = bDisableFog ? 0 : 1;
	else if (cvar == RENDERBOXES)
		*(int*)0x886C1D08 = bDrawRenderBoxes ? 2 : 0;
	else if (cvar == COLLIDE)
		*(int*)0x886BEA04 = bCollideWireframe ? 1 : 0;
}

void setupMenu() {
	addMenu("CSGO Menu", MAIN);
	addOption("Aimbot Menu", NULL, openSub, AIMBOT);
	addOption("ESP Menu", NULL, openSub, ESP);
	addOption("Say Menu", NULL, openSub, SAY);
	addOption("Name Menu", NULL, openSub, NAMES);
	addOption("Misc Menu", NULL, openSub, MISC);
	//addOption("Client List", NULL, openSub, CLIENTS);

	addMenu("Aimbot Menu", AIMBOT, 0);
	addOption("Aimbot Status", &bAimbot);
	addOption("Aimkey (LT)", &bAimkey);
	addOption("Auto Aim", &bAutoAim);
	addOption("Compensate Recoil", &bCompensateRecoil);
	addOption("Auto BHop", &bBhop);

	addMenu("ESP Menu", ESP, 0);
	addOption("ESP Status", &ESPStatus);
	addOption("Draw Names", &bNames);
	addOption("Draw 2D Boxes", &b2DBoxes);
	addOption("Draw Snaplines", &bSnaplines);
	addOption("Draw Bones", &bSkeleton);
	addOption("Draw Entities", &bEntityESP);

	addMenu("Say Menu", SAY, 0);
	addOption("Visit xbOnline", NULL, Say, (int)"Visit xbOnline.live for the best cheats!", 0);
	addOption("Rekt", NULL, Say, (int)"You just got rekt", 0);
	addOption("Report Me", NULL, Say, (int)"Report me pls, it gives me pleasure <3", 0);
	addOption("It's only game", NULL, Say, (int)"It's only a game, why you heff to be mad?", 0);
	addOption("I'm not cheating", NULL, Say, (int)"I'm not cheating", 0);
	addOption("Meme", NULL, Say, (int)"Blasts Mods has a small pepe :(", 0);
	addOption("Custom Entry", NULL, Say, 0, 1);

	addMenu("Name Menu", NAMES, 0);
	addOption("xbOnline.live", NULL, changeName, (int)"xbOnline.live", 0);
	addOption("You got rekt", NULL, changeName, (int)"You got rekt", 0);
	addOption("Lord Gaben", NULL, changeName, (int)"Lord Gaben", 0);
	addOption("Subscribe to PewDiePie", NULL, changeName, (int)"Subscribe to PewDiePie", 0);
	addOption("Your Gamertag", NULL, changeName, 0, 1);
	addOption("Custom Entry", NULL, changeName, 0, 2);

	addMenu("Misc Menu", MISC, 0);
	addOption("FOV <64>", NULL, updateCvar, FOV);
	addOption("Show Impacts", &bShowImpacts, updateCvar, IMPACTS);
	addOption("Draw Wireframe", &bDrawWireframe, updateCvar, WIREFRAME);
	addOption("Draw Render Boxes", &bDrawRenderBoxes, updateCvar, RENDERBOXES);
	addOption("Collide Wireframe", &bCollideWireframe, updateCvar, COLLIDE);
	addOption("Disable Fog", &bDisableFog, updateCvar, FOG);

	//addMenu("Clients", CLIENTS, 0);
	//addOption("Not Connected", NULL, &playerSub, 0);
	//addOption("Not Connected", NULL, &playerSub, 1);
	//addOption("Not Connected", NULL, &playerSub, 2);
	//addOption("Not Connected", NULL, &playerSub, 3);
	//addOption("Not Connected", NULL, &playerSub, 4);
	//addOption("Not Connected", NULL, &playerSub, 5);
	//addOption("Not Connected", NULL, &playerSub, 6);
	//addOption("Not Connected", NULL, &playerSub, 7);
	//addOption("Not Connected", NULL, &playerSub, 8);
	//addOption("Not Connected", NULL, &playerSub, 9);
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	AddPlayerMenu(i);
	//}
}