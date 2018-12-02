#include "csgo.h"



//int(*GetLocalClientNumber_f)(int SomeStructure) = (int(*)(int SomeStructure))0x86939560;
//VMatrix&(*WorldToScreenMatrix_f)(int pVEngineClient013) = (VMatrix&(*)(int pVEngineClient013))0x869399F0;
//int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height) = (int(*)(int pVEngineClient013, int* width, int* height))0x8693C8A0;
//int(*GetClientEntity_f)(int SomeStructure, int clientID) = (int(*)(int SomeStructure, int clientID))0x881DB410;
//int(*GetHighestEntityIndex_f)(int SomeStructure) = (int(*)(int SomeStructure))0x8847d140;
//int(*isInGame_f)(int pVEngineClient013) = (int(*)(int pVEngineClient013))0x868C7C28;
//int(*getPlayerInfo)(int pVEngineClient013, int id, player_info_t* info) = (int(*)(int pVEngineClient013, int id, player_info_t* info))0x8693C200;
//void(*DrawShader)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))0x85C4A340;
//void(*DrawLine)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))0x85C49430;
//void(*DrawSetColor)(int pVGUI_Surface031, int RGBA) = (void(*)(int pVGUI_Surface031, int RGBA))0x85C44A08;
//void(*DrawSetTextColor)(int pVGUI_Surface031, int r, int g, int b, int a) = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))0x85C45C40;
//void(*DrawSetTextPos)(int pVGUI_Surface031, int x, int y) = (void(*)(int pVGUI_Surface031, int x, int y))0x85C45D78;
//void(*DrawSetTextFont)(int pVGUI_Surface031, int font) = (void(*)(int pVGUI_Surface031, int font))0x85C45C38;
//void(*DrawPrintText)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType) = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))0x85c4c430;
//void(*DrawOutlinedRect)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))0x85C44C78;
//int(*GetFontName)(int pVGUI_Surface031, unsigned int font) = (int(*)(int, unsigned int))0x85C45BD8;
//void(*SetViewAngles)(int pVEngineClient013, QAngle &angles) = (void(*)(int, QAngle&))0x8693BB40;
//void(*GetViewAngles)(int pVEngineClient013, QAngle &angles) = (void(*)(int, QAngle&))0x8693BAF0;
//CUserCmd(*GetUserCmd)(int pCCInputAddr, int nSlot, int sequence_number) = (CUserCmd(*)(int, int, int))0x88268EB0;
//bool(*setupBones)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = (bool(*)(int, matrix3x4_t*, int, int, float))0x881477C0;
//void(*GetTextSize)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall) = (void(*)(int, int, const wchar_t*, int*, int*))0x85C45B50;
//void(*Cbuf_AddText)(int unk, char* cmd, int localClientNum) = (void(*)(int, char*, int))0x86A1A330;
//void(*DrawModelExecute)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) = (void(*)(int, void*, void*, ModelRenderInfo_t&, matrix3x4_t*))0x8699C368;
//void(*SetColorModulation)(int pCVRenderView, int blend) = (void(*)(int, int))0x869D7170;
//void(*ForcedMaterialOverride)(int pCModelRenderAddr, IMaterial* mat) = (void(*)(int, IMaterial*))0x86990738;
//void(*LoadFromBuffer)(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc) = (void(*)(KeyValues*, const char*, const char*, void*, const char*, void*))0x8853E5A8;
//void(*InitKeyValues)(KeyValues* pKeyValues, const char* name) = (void(*)(KeyValues*, const char*))0x881A18C0;
bool(*IsInGame)() = (bool(*)())0x8837E408;

CreateInterfaceFn resolveImport(HMODULE module)
{
	return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, (const char*)1));
}

void* get_interface(CreateInterfaceFn f, const char* szInterfaceVersion)
{
	auto result = reinterpret_cast<void*>(f(szInterfaceVersion, nullptr));

	return result;
}

VMatrix& WorldToScreenMatrix()
{
	return WorldToScreenMatrix_f(VEngineClient013);
}



bool ScreenTransform(const Vector &point, Vector &screen)
{
	float w;
	const VMatrix &worldToScreen = WorldToScreenMatrix();

	screen[0] = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen[1] = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen[2] = 0.0f;

	bool behind = false;

	if (w < 0.001f)
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool WorldToScreen(const Vector &origin, Vector &screen)
{
	if (!ScreenTransform(origin, screen))
	{
		int ScreenWidth, ScreenHeight;
		GetScreenSize(&ScreenWidth, &ScreenHeight);
		float x = ScreenWidth / 2.0f;
		float y = ScreenHeight / 2.0f;
		x += 0.5f * screen.x * ScreenWidth + 0.5f;
		y -= 0.5f * screen.y * ScreenHeight + 0.5f;
		screen.x = x;
		screen.y = y;
		return true;
	}

	return false;
}

bool EntityIsInvalid(CBaseEntity* Entity)
{
	if (!Entity)
		return true;
	if (Entity == LocalPlayer)
		return true;
	if (Entity->GetHealth() <= 0)
		return true;
	if (Entity->GetDormant())
		return true;

	return false;
}

void changeNameThread()
{
	XOVERLAPPED XOver;
	WCHAR wcGT[32] = { 0 };
	char tempName[32] = { 0 };

	XShowKeyboardUI(0, VKBD_LATIN_GAMERTAG | VKBD_HIGHLIGHT_TEXT, L"", L"Change Name", L"Type in the name you want to change to", wcGT, 32, &XOver);

	while (!XHasOverlappedIoCompleted(&XOver))
		Sleep(100);

	wcstombs(tempName, wcGT, 32);

	char name[0x150] = { 0 };
	_snprintf(name, 0x150, "name %s;", tempName);
	Cbuf_AddText_f(0, name, 0);
}

void sayThread()
{
	XOVERLAPPED XOver;
	WCHAR wcSay[40] = { 0 };
	char tempsay[40] = { 0 };

	XShowKeyboardUI(0, VKBD_LATIN_GAMERTAG | VKBD_HIGHLIGHT_TEXT, L"", L"Say", L"Type in the text you want to say", wcSay, 40, &XOver);

	while (!XHasOverlappedIoCompleted(&XOver))
		Sleep(100);

	wcstombs(tempsay, wcSay, 40);

	char name[0x150] = { 0 };
	_snprintf(name, 0x150, "say %s;", tempsay);
	Cbuf_AddText_f(0, name, 0);
}

void Say(char* text, int sayFlag)
{
	if (sayFlag == 1)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sayThread, 0, 0, 0);
	}
	else if (sayFlag == 0)
	{
		char sayText[0x150] = { 0 };
		_snprintf(sayText, 0x150, "say %s;", text);
		Cbuf_AddText_f(0, sayText, 0);
	}
}

void changeName(char* text, int nameFlag)
{
	char name[0x150] = { 0 };
	if (nameFlag == 1)
	{
		char pUserName[0x15] = { 0 };
		XamUserGetName(0, pUserName, 0x15);
		_snprintf(name, 0x150, "name %s;", pUserName);
		Cbuf_AddText_f(0, name, 0);
	}
	else if (nameFlag == 2)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changeNameThread, 0, 0, 0);
	}
	else if (nameFlag == 0)
	{
		_snprintf(name, 0x150, "name %s", text);
		Cbuf_AddText_f(0, name, 0);
	}
}

int CBaseEntity::GetHealth()
{
	return *(int*)((DWORD)this + addr->_0x000000FC);
}

int CBaseEntity::GetTeam()
{
	return *(int*)((DWORD)this + addr->_0x000000F0);
}

bool CBaseEntity::IsEnemy()
{
	return (this->GetTeam() == LocalPlayer->GetTeam() || this->GetTeam() == 0) ? false : true;
}

bool CBaseEntity::m_bIsScoped()
{
	return *(bool*)((DWORD)this + 0x1ABC);
}

int CBaseEntity::GetFlags()
{
	return *(int*)((DWORD)this + addr->_0x00000100);
}

QAngle CBaseEntity::GetPunch()
{
	return ((QAngle(*)(...))0x88176B80)(this);
}

bool CBaseEntity::GetDormant()
{
	return *(bool*)((DWORD)this + addr->_0x000000E9);
}

float CBaseEntity::GetCurTime()
{
	return *(float*)((DWORD)this + addr->_0x000016B0);
}

bool CBaseEntity::GetAlive()
{
	return (bool)(*(int*)((DWORD)this + addr->_0x0000025B) == 0);
}

#define VectorSubtract(a,b,c) ((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])

Vector CBaseEntity::GetVelocity()
{
	Vector newOrigin = *(Vector*)((DWORD)this + 0x134);
	Vector oldOrigin = *(Vector*)((DWORD)this + 0x39C);
	Vector ret = Vector(0, 0, 0);
	VectorSubtract(newOrigin, oldOrigin, ret);

	return ret;
}

int CBaseEntity::GetTickBase()
{
	return *(DWORD *)(this + (addr->_0x00001294 + addr->_0x000016B0));
}

inline Vector ExtrapolateTick(Vector p0, Vector v0)
{
	return p0 + (v0 * 1.2);
}

Vector CBaseEntity::GetPredicted(Vector p0)
{
	return ExtrapolateTick(p0, this->GetVelocity());
}

bool CBaseEntity::HasHelmet()
{
	return *(bool*)((DWORD)this + addr->_0x00001CB4);
}

int CBaseEntity::GetArmor()
{
	return *(int*)((DWORD)this + addr->_0x00001CBC);
}

Vector CBaseEntity::GetOrigin()
{
	return *(Vector*)((DWORD)this + addr->_0x000000AC);
}

model_t* GetModel(CBaseEntity* Entity)
{
	return *(model_t**)((DWORD)Entity + addr->_0x00001AEC);
}

QAngle CBaseEntity::GetViewAngles()
{
	return *(QAngle*)((DWORD)this + 0xC4);
}

Vector CBaseEntity::GetEyePosition()
{
	Vector origin = this->GetOrigin();
	Vector offset = *(Vector*)((DWORD)this + addr->_0x00000104);

	return (origin + offset);
}

player_info_t CBaseEntity::GetPlayerInfo()
{
	player_info_t pinfo;
	getPlayerInfo_f(VEngineClient013, (int)this, &pinfo);
	return pinfo;
}

void HealthBar(Vector bot, Vector top, float health)
{
	float h = (bot.y - top.y);
	float offset = (h / 4.f) + 5;
	float w = h / 64.f;

	UINT hp = h - (UINT)((h * health) / 100);

	int Red = 255 - (health * 2.55);
	int Green = health * 2.55;

	DrawRect((top.x - offset) - 1, top.y - 1, 3, h + 2, 0x000000FF);

	DrawLineWithColor((top.x - offset), top.y + hp, (top.x - offset), top.y + h, createRGBA(Red, Green, 0, 255));
}

Vector vectoangles(Vector Angles)
{
	float forward;
	float yaw, pitch;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrt((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	Vector AnglesVector(-pitch, yaw, 0);
	return AnglesVector;
}

void updateStructs()
{
	auto client = resolveImport(GetModuleHandleA("client_360.dll"));
	auto engine = resolveImport(GetModuleHandleA("engine_360.dll"));

	g_EntityList = (IClientEntityList*)get_interface(client, "VClientEntityList003");
	EngineTrace = (IEngineTrace*)get_interface(engine, "EngineTraceClient004");

	LocalPlayer = g_EntityList->GetClientEntity(GetLocalClientNumber());
}

wchar_t wc[0x2000];

const wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;

	mbstowcs(wc, c, cSize);

	return wc;
}

// Current bone matrix offset
#define BONE_MATRIX_OFFSET DWORD(0xA04)

struct mat3x4
{
	float c[3][4];
};

mat3x4 GetBoneMatrix(DWORD EntityPtr)
{
	DWORD BoneMatrixPtr = *(int*)(EntityPtr + BONE_MATRIX_OFFSET);
	return *(mat3x4*)(BoneMatrixPtr);
}

Vector GetBonePosition(DWORD EntityPtr, int BoneIndex)
{
	DWORD BoneMatrixPtr = *(int*)(EntityPtr + BONE_MATRIX_OFFSET);
	mat3x4 BoneMatrix = *(mat3x4*)(BoneMatrixPtr + (0x30 * BoneIndex));
	return Vector(BoneMatrix.c[0][3], BoneMatrix.c[1][3], BoneMatrix.c[2][3]);
}

bool CBaseEntity::IsVisible(int bone)
{
	Ray_t ray;
	trace_t tr;
	m_visible = false;
	ray.Init(LocalPlayer->GetEyePosition(), GetBonePosition((int)this, bone));

	CTraceFilter filter;
	filter.pSkip = LocalPlayer;

	EngineTrace->TraceRay(ray, MASK_NPCWORLDSTATIC | CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX, &filter, &tr);

	if (tr.m_pEnt == this || tr.fraction > 0.99f)
	{
		m_visible = true;
		return true;
	}

	return false;
}


ICollideable* GetCollideable(int Entety)
{
	return (ICollideable*)((DWORD)(Entety + 0x00000310));
}

bool GetBox(CBaseEntity* pEntity, float &x, float &y, float &w, float &h)
{
	// Variables
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	// Get the locations
	vOrigin = pEntity->GetOrigin();
	min = GetCollideable((int)pEntity)->OBBMins() + vOrigin;
	max = GetCollideable((int)pEntity)->OBBMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	// Get screen positions
	if (!WorldToScreen(points[3], flb) || !WorldToScreen(points[5], brt)
		|| !WorldToScreen(points[0], blb) || !WorldToScreen(points[4], frt)
		|| !WorldToScreen(points[2], frb) || !WorldToScreen(points[1], brb)
		|| !WorldToScreen(points[6], blt) || !WorldToScreen(points[7], flt))
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	// Width / height
	x = left;
	y = top;
	w = right - left;
	h = bottom - top;

	return true;
}

void Draw3DBox(int client, CBaseEntity* Entity, int col)
{
	IClientNetworkable* pNetworkable = g_EntityList->GetClientNetworkable(client);
	IClientUnknown* pUnknown = pNetworkable->GetIClientUnknown();

	ICollideable* coll = GetCollideable((int)Entity);

	int iScreenWidth, iScreenHeight;
	GetScreenSize(&iScreenWidth, &iScreenHeight);

	Vector min = coll->OBBMins();
	Vector max = coll->OBBMaxs();

	Vector corners[8] =
	{
	Vector(min.x,min.y,min.z),
	Vector(min.x,max.y,min.z),
	Vector(max.x,max.y,min.z),
	Vector(max.x,min.y,min.z),
	Vector(min.x,min.y,max.z),
	Vector(min.x,max.y,max.z),
	Vector(max.x,max.y,max.z),
	Vector(max.x,min.y,max.z)
	};

	float ang = Entity->GetViewAngles().y;

	for (int i = 0; i <= 7; i++) corners[i].Rotate2D(ang); Vector _corners[8]; for (int i = 0; i <= 7; i++) WorldToScreen(Entity->GetOrigin() + corners[i], _corners[i]);

	int x1 = iScreenWidth * 2, y1 = iScreenHeight * 2, x2 = -iScreenWidth, y2 = -iScreenHeight;

	for (int i = 1; i <= 4; i++) {
		DrawLineWithColor((int)(_corners[i - 1].x), (int)(_corners[i - 1].y), (int)(_corners[i % 4].x), (int)(_corners[i % 4].y), col); DrawLineWithColor((int)(_corners[i - 1].x), (int)(_corners[i - 1].y), (int)(_corners[i + 3].x), (int)(_corners[i + 3].y), col); DrawLineWithColor((int)(_corners[i + 3].x), (int)(_corners[i + 3].y), (int)(_corners[i % 4 + 4].x), (int)(_corners[i % 4 + 4].y), col);
	}
}

void DrawEntity(CBaseEntity* entity, int color)
{
	float x, y, w, h;
	if (GetBox(entity, x, y, w, h))
	{
		PlayerBox(x, y, w, h, color);
		float health = entity->GetHealth();
		float maxHealth = 100;
		float offset = (h / 4.f) + 5;

		UINT hp = h - (UINT)((h * health) / (maxHealth));

		int Red = 255 - (health * 2.55);
		int Green = health * 2.55;

		DrawRect((x - 5) - 1, y - 1, 3, h + 2, 0x000000FF);

		DrawLineWithColor(x - 5, y + hp, (x - 5), y + h, createRGBA(Red, Green, 0, 255));
	}
}

void DrawBone(CBaseEntity* entity, int tagname1, int tagname2, int col)
{
	Vector Origin1 = GetBonePosition((int)entity, tagname1), Origin2 = GetBonePosition((int)entity, tagname2);

	Vector Loc1, Loc2;
	if (WorldToScreen(Origin1, Loc1) && WorldToScreen(Origin2, Loc2)) {
		DrawLineWithColor(Loc1.x, Loc1.y, Loc2.x, Loc2.y, col);
	}
}

void DrawSkeleton(CBaseEntity* entity, int color)
{
	static BYTE iBoneLegL[] = { 24, 23, 22, 1 };
	static BYTE iBoneLegR[] = { 27, 26, 25, 1 };
	static BYTE iBoneBody[] = { 5, 4, 3, 2, 1 };
	static BYTE iBoneArmL[] = { 9, 8, 7, 5 };
	static BYTE iBoneArmR[] = { 15, 14, 13, 5 };

	for (int i = 0; i < 4; i++)
	{
		DrawBone(entity, iBoneBody[i], iBoneBody[i + 1], 0xFFFFFFFF);
	}

	for (int i = 0; i < 3; i++)
	{
		DrawBone(entity, iBoneLegL[i], iBoneLegL[i + 1], 0xFFFFFFFF);
		DrawBone(entity, iBoneLegR[i], iBoneLegR[i + 1], 0xFFFFFFFF);
		DrawBone(entity, iBoneArmL[i], iBoneArmL[i + 1], 0xFFFFFFFF);
		DrawBone(entity, iBoneArmR[i], iBoneArmR[i + 1], 0xFFFFFFFF);
	}
}

void updatePlayerList()
{
	for (int i = 0; i < 10; i++)
	{
		player_info_t pinfo;
		getPlayerInfo_f(VEngineClient013, i, &pinfo);
		if (user_strcmp(pinfo.name, "")) {
			MenuVars.Option_Text[CLIENTS][i] = pinfo.name;
		}
	}
}


//Menu Dimensions
float MENU_X = 920;
float MENU_Y = 100;
float MENU_WIDTH = 200;
float MENU_HEIGHT = 260;
float TEXT_ADDITIVE = 17;
float menuColor = 0;


void renderMenu() {
	menuColor = createRGBA(44, 143, 237, 0x91);

	if (MenuVars.isOpen) {
		int CurrentMenu = MenuVars.currentMenu,
			CurrentOption = MenuVars.currentOption[CurrentMenu],
			MaxOption = MenuVars.optionCount[CurrentMenu],
			PreviousMenu = MenuVars.previousMenu[CurrentMenu];

		MENU_HEIGHT = 46 + (TEXT_ADDITIVE * MaxOption);

		//Draw Menu Background With Border
		DrawRectWithBorder(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT, 3, 0x00000091, menuColor);

		//Draw Menu Title
		DrawText(GetWC(MenuVars.Menu_Title[CurrentMenu]), addr->_0x000000B8, MENU_X + 10, MENU_Y + 10, 0x2C, 0x8F, 0xED, 0xFF, false);

		//Draw Menu Text
		for (int i = 0; i < MaxOption; i++)
		{
			float menuText_y = MENU_Y + 40 + (TEXT_ADDITIVE * i);

			if (MenuVars.Option_Text[CurrentMenu][i] != NULL)
			{
				if (i == CurrentOption)
				{
					DrawRect(MENU_X + 3, menuText_y, MENU_WIDTH - 6, TEXT_ADDITIVE, menuColor);
				}
				if (!MenuVars.Option_Toggle[CurrentMenu][i] != NULL)
					DrawText(GetWC(MenuVars.Option_Text[CurrentMenu][i]), addr->_0x000000B7, MENU_X + 10, menuText_y, 0xFF, 0xFF, 0xFF, 0xFF, false);
				else
				{
					DrawText(GetWC(MenuVars.Option_Text[CurrentMenu][i]), addr->_0x000000B7, MENU_X + 10, menuText_y, 0xFF, 0xFF, 0xFF, 0xFF, false);
					*MenuVars.Option_Toggle[CurrentMenu][i] ? drawCheckBox(MENU_X + 180, menuText_y + 2.2, 0x00FF00FF, 0x000000FF, true) : drawCheckBox(MENU_X + 180, menuText_y + 2.2, 0x00FF00FF, 0x000000FF, false);
				}
			}
		}
	}
	DrawTextWithBG("xbOnline Cheats Beta v1.1", 0xB7, 1100, 10, 0x2C, 0x8F, 0xED, 0xFF, false, menuColor);
	DrawTextWithBG(MenuVars.isOpen ? "Press B to close" : "Press DPAD UP & RS to open", 0xB7, 15, 695, 0x2C, 0x8F, 0xED, 0xFF, false, menuColor);
}

const char* GetEntityName(int WeaponID) {
	switch (WeaponID) {
		/*pistols*/
	case 202:
		return "Glock-18";
	case 196:
		return "Dual Berettas";
	case 215:
		return "P250";
	case 225:
		return "Tec-9";
	case 36:
		return "Desert Eagle";
	case 203:
		return "P2000";
	case 198:
		return "Five-SeveN";
		/*heavy*/
	case 213:
		return "Nova";
	case 229:
		return "XM1014";
	case 217:
		return "Sawed-Off";
	case 204:
		return "M249";
	case 212:
		return "Negev";
	case 208:
		return "Mag-7";
		/*smgs*/
	case 207:
		return "MAC-10";
	case 210:
		return "MP7";
	case 227:
		return "UMP45";
	case 216:
		return "P90";
	case 192:
		return "PP-Bizon";
	case 211:
		return "MP9";
		/*rifles*/
	case 197:
		return "Famas";
	case 206:
		return "M4A4";
	case 223:
		return "SSG 08";
	case 190:
		return "AUG";
	case 191:
		return "AWP";
	case 218:
		return "SCAR-20";
	case 201:
		return "Galil AR";
	case 1:
		return "AK-47";
	case 222:
		return "SG 553";
	case 199:
		return "G3SG1";
		/*grenades*/
	case 88:
		return "Molotov";
	case 80:
		return "Incendiary Grenade";
	case 78:
		return "HE Grenade";
	case 60:
		return "Flashbang";
	case 121:
		return "Smoke Grenade";
	case 37:
		return "Decoy";
		/*other*/
	case 224:
		return "Zeus";
	case 27:
		return "C4 Explosive";
	case 99:
		return "Bomb";
	case 40:
		return "Chicken";
	case 79:
		return "Hostage";
	case 32:
		return "Player";

	default:
		return "";
	}
}