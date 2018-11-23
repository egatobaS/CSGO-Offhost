#pragma once

extern bool bAimbot;
extern bool bAutoAim;
extern bool bAimkey;
extern bool ESPStatus;
extern bool bSpinbot;
extern bool bDisableEffects;
extern bool bPrioritized[30];
extern bool bBhop;
extern bool bNames;
extern bool b2DBoxes;
extern bool bSnaplines;
extern bool bSkeleton;

struct Vars
{
	static const int Max_Sub = 40, Max_Opt = 100;

	bool isOpen;

	int currentMenu;

	int selectedClient;

	const char* Menu_Title[Max_Sub];
	int previousMenu[Max_Sub], currentOption[Max_Opt], optionCount[Max_Opt];

	const char* Option_Text[Max_Sub][Max_Opt];
	void(*Option_Function[Max_Sub][Max_Opt])(int, int);
	bool* Option_Toggle[Max_Sub][Max_Opt];

	char **Option_ToggleArr[Max_Sub][Max_Opt];
	int Option_ToggleArr_Size[Max_Sub][Max_Opt];
	int *Option_ToggleArr_Cur[Max_Sub][Max_Opt];

	int Option_Param1[Max_Sub][Max_Opt];
	int Option_Param2[Max_Sub][Max_Opt];
};

extern Vars MenuVars;

enum Submenus
{
	MAIN,
	AIMBOT,
	ESP,
	CLIENTS
};

extern void setupMenu();