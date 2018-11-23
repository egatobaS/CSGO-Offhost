#include "csgo.h"

int(*GetLocalClientNumber_f)(int SomeStructure) = (int(*)(int SomeStructure))0x86939560;
VMatrix&(*WorldToScreenMatrix_f)(int pVEngineClient013) = (VMatrix&(*)(int pVEngineClient013))0x869399F0;
int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height) = (int(*)(int pVEngineClient013, int* width, int* height))0x8693C8A0;
int(*GetClientEntity_f)(int SomeStructure, int clientID) = (int(*)(int SomeStructure, int clientID))0x881DB410;
int(*GetHighestEntityIndex_f)(int SomeStructure) = (int(*)(int SomeStructure))0x8847d140;
int(*isInGame_f)(int pVEngineClient013) = (int(*)(int pVEngineClient013))0x868C7C28;
int(*getPlayerInfo)(int pVEngineClient013, int id, player_info_t* info) = (int(*)(int pVEngineClient013, int id, player_info_t* info))0x8693C200;
void(*DrawShader)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))0x85C4A340;
void(*DrawLine)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))0x85C49430;
void(*DrawSetColor)(int pVGUI_Surface031, int RGBA) = (void(*)(int pVGUI_Surface031, int RGBA))0x85C44A08;
void(*DrawSetTextColor)(int pVGUI_Surface031, int r, int g, int b, int a) = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))0x85C45C40;
void(*DrawSetTextPos)(int pVGUI_Surface031, int x, int y) = (void(*)(int pVGUI_Surface031, int x, int y))0x85C45D78;
void(*DrawSetTextFont)(int pVGUI_Surface031, int font) = (void(*)(int pVGUI_Surface031, int font))0x85C45C38;
void(*DrawPrintText)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType) = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))0x85c4c430;
void(*DrawOutlinedRect)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))0x85C44C78;
int(*GetFontName)(int pVGUI_Surface031, unsigned int font) = (int(*)(int, unsigned int))0x85C45BD8;
void(*SetViewAngles)(int pVEngineClient013, QAngle &angles) = (void(*)(int, QAngle&))0x8693BB40;
void(*GetViewAngles)(int pVEngineClient013, QAngle &angles) = (void(*)(int, QAngle&))0x8693BAF0;
CUserCmd(*GetUserCmd)(int pCCInputAddr, int nSlot, int sequence_number) = (CUserCmd(*)(int, int, int))0x88268EB0;
bool(*setupBones)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = (bool(*)(int, matrix3x4_t*, int, int, float))0x881477C0;
void(*GetTextSize)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall) = (void(*)(int, int, const wchar_t*, int*, int*))0x85C45B50;
void(*Cbuf_AddText)(int unk, char* cmd, int localClientNum) = (void(*)(int, char*, int))0x86A1A330;
void(*DrawModelExecute)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) = (void(*)(int, void*, void*, ModelRenderInfo_t&, matrix3x4_t*))0x8699C368;
void(*SetColorModulation)(int pCVRenderView, int blend) = (void(*)(int, int))0x869D7170;
void(*ForcedMaterialOverride)(int pCModelRenderAddr, IMaterial* mat) = (void(*)(int, IMaterial*))0x86990738;
void(*LoadFromBuffer)(KeyValues* pKeyValues, const char* resourceName, const char* pBuffer, void* pFileSystem, const char* pPathID, void* pfnEvaluateSymbolProc) = (void(*)(KeyValues*, const char*, const char*, void*, const char*, void*))0x8853E5A8;
void(*InitKeyValues)(KeyValues* pKeyValues, const char* name) = (void(*)(KeyValues*, const char*))0x881A18C0;

CreateInterfaceFn resolveImport(HMODULE module)
{
	return reinterpret_cast<CreateInterfaceFn>(GetProcAddress(module, (const char*)1));
}

void* get_interface(CreateInterfaceFn f, const char* szInterfaceVersion)
{
	auto result = reinterpret_cast<void*>(f(szInterfaceVersion, nullptr));

	return result;
}

void DrawLineWithColor(int x0, int y0, int x1, int y1, int col)
{
	DrawSetColor(VGUI_Surface031, col);
	DrawLine(VGUI_Surface031, x0, y0, x1, y1);
}

VMatrix& WorldToScreenMatrix()
{
	return WorldToScreenMatrix_f(VEngineClient013);
}

int GetScreenSize(int* width, int* height)
{
	return GetScreenSize_f(VEngineClient013, width, height);
}

int isInGame()
{
	return isInGame_f(VEngineClient013);
}

int GetLocalClientNumber()
{
	return GetLocalClientNumber_f(VEngineClient013);
}

int GetClientEntity(int id)
{
	return GetClientEntity_f(VClientEntityList003, id);
}

int GetHighestEntityIndex()
{
	return GetHighestEntityIndex_f(VClientEntityList003);
}

void DrawText(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered)
{
	DrawSetTextFont(VGUI_Surface031, font);
	int width = 0, height = 0;
	GetTextSize(VGUI_Surface031, font, msg, &width, &height);
	DrawSetTextColor(VGUI_Surface031, r, g, b, a);
	DrawSetTextPos(VGUI_Surface031, centered ? x - width / 2 : x, y);
	DrawPrintText(VGUI_Surface031, msg, wcslen(msg), 0);
}

void DrawRect(int x, int y, int w, int h, int col)
{
	DrawSetColor(VGUI_Surface031, col);
	DrawShader(VGUI_Surface031, x, y, x + w, y + h);
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
	if (Entity->GetAlive())
		return true;
	if (Entity->GetDormant())
		return true;

	return false;
}

int CBaseEntity::GetHealth()
{
	return *(int*)((DWORD)this + 0xFC);
}

int CBaseEntity::GetTeam()
{
	return *(int*)((DWORD)this + 0xF0);
}

bool CBaseEntity::IsEnemy()
{
	return (this->GetTeam() == LocalPlayer->GetTeam() || this->GetTeam() == 0) ? false : true;
}

int CBaseEntity::GetFlags()
{
	return *(int*)((DWORD)this + 0x100);
}

QAngle CBaseEntity::GetPunch()
{
	return ((QAngle(*)(...))0x88176B80)(this);
}

bool CBaseEntity::GetDormant()
{
	return *(bool*)((DWORD)this + 0xE9);
}

float CBaseEntity::GetCurTime()
{
	return *(float*)((DWORD)this + 0x16B0);
}

bool CBaseEntity::GetAlive()
{
	return (bool)(*(int*)((DWORD)this + 0x25B) == 0);
}

Vector CBaseEntity::GetVelocity()
{
	return *(Vector*)((DWORD)this + 0x110);
}

int CBaseEntity::GetTickBase()
{
	return *(DWORD *)(this + (0x1294 + 0x16B0));
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
	return *(bool*)((DWORD)this + 0x1CB4);
}

int CBaseEntity::GetArmor()
{
	return *(int*)((DWORD)this + 0x1CBC);
}

Vector CBaseEntity::GetOrigin()
{
	return *(Vector*)((DWORD)this + 0xAC);
}

model_t* GetModel(CBaseEntity* Entity)
{
	return *(model_t**)((DWORD)Entity + 0x1AEC);
}

Vector CBaseEntity::GetEyePosition()
{
	Vector origin = this->GetOrigin();
	Vector offset = *(Vector*)((DWORD)this + 0x104);

	return (origin + offset);
}

player_info_t CBaseEntity::GetPlayerInfo()
{
	player_info_t pinfo;
	getPlayerInfo(VEngineClient013, (int)this, &pinfo);
	return pinfo;
}

int createRGBA(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + ((a & 0xff));
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
	float PI = 3.1415926535897931;
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

XINPUT_STATE InputState;

bool GetAsyncKeyState(int button)
{
	XInputGetState(0, &InputState);

	if (button == 0) return true;

	else if (button == 0x1337) return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	else if (button == 0x1338) return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return (InputState.Gamepad.wButtons & button);
}

void updateStructs()
{
	auto client = resolveImport(GetModuleHandleA("client_360.dll"));
	auto engine = resolveImport(GetModuleHandleA("engine_360.dll"));

	g_EntityList = (IClientEntityList*)get_interface(client, "VClientEntityList003");

	EngineTrace = (IEngineTrace*)get_interface(engine, "EngineTraceClient004");

	LocalPlayer = g_EntityList->GetClientEntity(GetLocalClientNumber());
}

const wchar_t *GetWC(const char *c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
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

void DrawBox(float x, float y, float width, float height, int RGBA)
{
	DrawSetColor(VGUI_Surface031, RGBA);

	DrawOutlinedRect(VGUI_Surface031, x, y, x + width, y + height);
}

void PlayerBox(float x, float y, float w, float h, int clr)
{
	DrawSetColor(VGUI_Surface031, clr);
	DrawOutlinedRect(VGUI_Surface031, x - w, y, x + w, y + h);

	DrawSetColor(VGUI_Surface031, 0x000000FF);
	DrawOutlinedRect(VGUI_Surface031, x - w - 1, y - 1, x + w + 1, y + h + 1);
	DrawOutlinedRect(VGUI_Surface031, x - w + 1, y + 1, x + w - 1, y + h - 1);
}

ICollideable* GetCollideable(int Entety)
{
	return (ICollideable*)((DWORD)(Entety + 0x00000310));
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
		getPlayerInfo(VEngineClient013, i, &pinfo);
		if (strcmp(pinfo.name, "")) {
			MenuVars.Option_Text[CLIENTS][i] = pinfo.name;
		}
	}
}

void DrawRectWithBorder(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor)
{
	DrawRect(x, y, width, height, rectColor);

	DrawRect(x, y, lineWidth, height, borderColor);
	DrawRect(x + lineWidth, y, width - lineWidth, lineWidth, borderColor);
	DrawRect(x + lineWidth, y + height - lineWidth, width - lineWidth, lineWidth, borderColor);
	DrawRect(x + (width - lineWidth), y + lineWidth, lineWidth, height - (lineWidth * 2), borderColor);
}

void drawCheckBox(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked) {
	DrawRect(centerX, centerY, 12, 1, outlineBoxColor);
	DrawRect(centerX, centerY + 12, 12, 1, outlineBoxColor);
	DrawRect(centerX, centerY, 1, 12, outlineBoxColor);
	DrawRect(centerX + 12, centerY, 1, 13, outlineBoxColor);

	DrawRect(centerX + 1, centerY + 1, 11, 11, ticked ? 0x00FF007D : 0xFF00007D);
}

void DrawTextWithBG(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered = false)
{
	int TextWidth = 0, TextHeight = 0, lineWidth = 3;
	GetTextSize(VGUI_Surface031, fontName, GetWC(text), &TextWidth, &TextHeight);

	DrawRectWithBorder(x - 5, y - 3, TextWidth + 10, TextHeight + 2, lineWidth, 0x00000091, menuColor);

	DrawText(GetWC(text), fontName, x, y, r, g, b, a, centered);
}

//Menu Dimensions
float MENU_X = 920;
float MENU_Y = 100;
float MENU_WIDTH = 200;
float MENU_HEIGHT = 260;
float TEXT_ADDITIVE = 17;
float menuColor = createRGBA(44, 143, 237, 0x91);

void renderMenu() {
	if (MenuVars.isOpen) {
		int CurrentMenu = MenuVars.currentMenu,
			CurrentOption = MenuVars.currentOption[CurrentMenu],
			MaxOption = MenuVars.optionCount[CurrentMenu],
			PreviousMenu = MenuVars.previousMenu[CurrentMenu];

		MENU_HEIGHT = 46 + (TEXT_ADDITIVE * MaxOption);

		//Draw Menu Background With Border
		DrawRectWithBorder(MENU_X, MENU_Y, MENU_WIDTH, MENU_HEIGHT, 3, 0x00000091, menuColor);

		//Draw Menu Title
		DrawText(GetWC(MenuVars.Menu_Title[CurrentMenu]), 0xB8, MENU_X + 10, MENU_Y + 10, 0x2C, 0x8F, 0xED, 0xFF);

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
					DrawText(GetWC(MenuVars.Option_Text[CurrentMenu][i]), 0xB7, MENU_X + 10, menuText_y, 0xFF, 0xFF, 0xFF, 0xFF);
				else
				{
					DrawText(GetWC(MenuVars.Option_Text[CurrentMenu][i]), 0xB7, MENU_X + 10, menuText_y, 0xFF, 0xFF, 0xFF, 0xFF);
					*MenuVars.Option_Toggle[CurrentMenu][i] ? drawCheckBox(MENU_X + 180, menuText_y + 2.2, 0x00FF00FF, 0x000000FF, true) : drawCheckBox(MENU_X + 180, menuText_y + 2.2, 0x00FF00FF, 0x000000FF, false);
				}
			}
		}
	}
	DrawTextWithBG("xbOnline Cheats Beta v1", 0xB7, 1110, 10, 0x2C, 0x8F, 0xED, 0xFF);
	DrawTextWithBG(MenuVars.isOpen ? "Press B to close" : "Press DPAD UP & RS to open", 0xB7, 15, 695, 0x2C, 0x8F, 0xED, 0xFF);
}