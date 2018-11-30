#include "csgo.h"

csgo_addr_offhost_s* addr;

int VEngineClient013;
int VGUI_Surface031;
int VClientEntityList003;
int CCInputAddr;
int ClientModeAddr;
int CModelRenderAddr;
int CVRenderViewAddr;
int KeyValuesAddr;

Detour* (*GetDetour)();
void(*XNotify)(wchar_t*);
void*(*user_memcpy)(void*, void*, size_t);
char*(*user_strcpy)(char*, const char*);
void*(*user_memset)(void*, int, size_t);
int(*user_strcmp)(const char*, const char*);
void* (*xbOHookFunction)(Detour* a, void* b, void* c);

VMatrix&(*WorldToScreenMatrix_f)(int pVEngineClient013);
CUserCmd(*GetUserCmd_f)(int pCCInputAddr, int nSlot, int sequence_number);
void(*DrawModelExecute_f)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
void(*GetViewAngles_f)(int pVEngineClient013, QAngle &angles);
void(*SetViewAngles_f)(int VEngineClient013, QAngle &angles);

int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height);
int(*GetLocalClientNumber_f)(int SomeStructure);
int(*GetClientEntity_f)(int SomeStructure, int clientID);
int(*GetHighestEntityIndex_f)(int SomeStructure);
int(*isInGame_f)(int pVEngineClient013);
int(*getPlayerInfo_f)(int pVEngineClient013, int id, player_info_t* info);
void(*DrawShader_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
void(*DrawLine_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
void(*DrawSetColor_f)(int pVGUI_Surface031, int RGBA);
void(*DrawSetTextColor_f)(int pVGUI_Surface031, int r, int g, int b, int a);
void(*DrawSetTextPos_f)(int pVGUI_Surface031, int x, int y);
void(*DrawSetTextFont_f)(int pVGUI_Surface031, int font);
void(*DrawPrintText_f)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType);
void(*DrawOutlinedRect_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
bool(*setupBones_f)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
void(*Cbuf_AddText_f)(int unk, char* cmd, int localClientNum);
void(*ForcedMaterialOverride_f)(int pCModelRenderAddr, IMaterial* mat);
void(*SetColorModulation_f)(int pCVRenderView, int blend);
void(*GetTextSize_f)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall);

void(*DrawLineWithColor)(int x0, int y0, int x1, int y1, int col);
void(*DrawText)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered);
void(*DrawRect)(int x, int y, int w, int h, int col);
int(*createRGBA)(int r, int g, int b, int a);
void(*DrawBox)(float x, float y, float width, float height, int RGBA);
void(*PlayerBox)(float x, float y, float w, float h, int clr);
bool(*GetAsyncKeyState)(int button);
int(*GetScreenSize)(int* width, int* height);
int(*isInGame)();
int(*GetLocalClientNumber)();
int(*GetClientEntity)(int id);
int(*GetHighestEntityIndex)();
void(*drawCheckBox)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked);
void(*DrawRectWithBorder)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor);
void(*DrawTextWithBG)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor);
void(*PopulateVtables)(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr);



void SetViewAngles_f_Real(int pVEngineClient013, QAngle &angles)
{
	void(*SetViewAngles)(int pVEngineClient013, QAngle &angles) = (void(*)(int, QAngle&))addr->_0x8693BB40;
	return SetViewAngles(pVEngineClient013, angles);
}

void GetViewAngles_f_Real(int pVEngineClient013, QAngle &angles)
{
	void(*GetViewAngles)(int pVEngineClient013, QAngle &angles) = (void(*)(int, QAngle&))addr->_0x8693BAF0;
	return GetViewAngles(pVEngineClient013, angles);
}

CUserCmd GetUserCmd_f_Real(int pCCInputAddr, int nSlot, int sequence_number)
{
	CUserCmd(*GetUserCmd)(int pCCInputAddr, int nSlot, int sequence_number) = (CUserCmd(*)(int, int, int))addr->_0x88268EB0;

	return GetUserCmd(pCCInputAddr, nSlot, sequence_number);
}

void DrawModelExecute_f_Real(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	void(*DrawModelExecute)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld) = (void(*)(int, void*, void*, ModelRenderInfo_t&, matrix3x4_t*))addr->_0x8699C368;
	return DrawModelExecute(pCModelRender, ctx, state, pInfo, pCustomBoneToWorld);
}


VMatrix& WorldToScreenMatrix_f_Real(int pVEngineClient013)
{
	VMatrix&(*WorldToScreenMatrix_f)(int pVEngineClient013) = (VMatrix&(*)(int pVEngineClient013))addr->_0x869399F0;
	return WorldToScreenMatrix_f(pVEngineClient013);
}

#if defined(DEVELOPERSDEVELOPERSDEVELOPERS)


int GetLocalClientNumber_f_Real(int SomeStructure)
{
	int(*GetLocalClientNumber_f)(int SomeStructure) = (int(*)(int SomeStructure))addr->_0x86939560;
	return GetLocalClientNumber_f(SomeStructure);
}

int GetScreenSize_f_Real(int pVEngineClient013, int* width, int* height)
{
	int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height) = (int(*)(int pVEngineClient013, int* width, int* height))addr->_0x8693C8A0;
	return GetScreenSize_f(pVEngineClient013, width, height);
}

int GetClientEntity_f_Real(int SomeStructure, int clientID)
{
	int(*GetClientEntity_f)(int SomeStructure, int clientID) = (int(*)(int SomeStructure, int clientID))addr->_0x881DB410;
	return GetClientEntity_f(SomeStructure, clientID);
}

int GetHighestEntityIndex_f_Real(int  SomeStructure)
{
	int(*GetHighestEntityIndex_f)(int SomeStructure) = (int(*)(int SomeStructure))addr->_0x8847d140;
	return GetHighestEntityIndex_f(SomeStructure);
}

int isInGame_f_Real(int pVEngineClient013)
{
	int(*isInGame_f)(int pVEngineClient013) = (int(*)(int pVEngineClient013))addr->_0x868C7C28;
	return isInGame_f(pVEngineClient013);
}

int getPlayerInfo_f_Real(int pVEngineClient013, int id, player_info_t* info)
{
	int(*getPlayerInfo)(int pVEngineClient013, int id, player_info_t* info) = (int(*)(int pVEngineClient013, int id, player_info_t* info))addr->_0x8693C200;

	return getPlayerInfo(pVEngineClient013, id, info);
}

void DrawShader_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2)
{
	void(*DrawShader)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))addr->_0x85C4A340;

	return DrawShader(pVGUI_Surface031, x1, y1, x2, y2);
}

void DrawLine_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2)
{
	void(*DrawLine)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))addr->_0x85C49430;

	return DrawLine(pVGUI_Surface031, x1, y1, x2, y2);
}

void DrawSetColor_f_Real(int pVGUI_Surface031, int RGBA)
{
	void(*DrawSetColor)(int pVGUI_Surface031, int RGBA) = (void(*)(int pVGUI_Surface031, int RGBA))addr->_0x85C44A08;

	return DrawSetColor(pVGUI_Surface031, RGBA);
}

void DrawSetTextColor_f_Real(int pVGUI_Surface031, int r, int g, int b, int a)
{
	void(*DrawSetTextColor)(int pVGUI_Surface031, int r, int g, int b, int a) = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))addr->_0x85C45C40;
	return DrawSetTextColor(pVGUI_Surface031, r, g, b, a);
}

void DrawSetTextPos_f_Real(int pVGUI_Surface031, int x, int y)
{
	void(*DrawSetTextPos)(int pVGUI_Surface031, int x, int y) = (void(*)(int pVGUI_Surface031, int x, int y))addr->_0x85C45D78;
	return DrawSetTextPos(pVGUI_Surface031, x, y);;
}

void DrawSetTextFont_f_Real(int pVGUI_Surface031, int font)
{
	void(*DrawSetTextFont)(int pVGUI_Surface031, int font) = (void(*)(int pVGUI_Surface031, int font))addr->_0x85C45C38;
	return DrawSetTextFont(pVGUI_Surface031, font);
}

void DrawPrintText_f_Real(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType)
{
	void(*DrawPrintText)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType) = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))addr->_0x85c4c430;
	return DrawPrintText(pVGUI_Surface031, text, textLen, drawType);
}

void DrawOutlinedRect_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2)
{
	void(*DrawOutlinedRect)(int pVGUI_Surface031, int x1, int y1, int x2, int y2) = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))addr->_0x85C44C78;
	return DrawOutlinedRect(pVGUI_Surface031, x1, y1, x2, y2);
}

int GetFontName_f_Real(int pVGUI_Surface031, unsigned int font)
{
	int(*GetFontName)(int pVGUI_Surface031, unsigned int font) = (int(*)(int, unsigned int))addr->_0x85C45BD8;
	return GetFontName(pVGUI_Surface031, font);
}


bool setupBones_f_Real(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	bool(*setupBones)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = (bool(*)(int, matrix3x4_t*, int, int, float))addr->_0x881477C0;

	return setupBones(hax, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}

void GetTextSize_f_Real(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall)
{
	void(*GetTextSize)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall) = (void(*)(int, int, const wchar_t*, int*, int*))addr->_0x85C45B50;
	return GetTextSize(pVGUI_Surface031, font, text, wide, tall);
}

void Cbuf_AddText_f_Real(int unk, char* cmd, int localClientNum)
{
	void(*Cbuf_AddText)(int unk, char* cmd, int localClientNum) = (void(*)(int, char*, int))addr->_0x86A1A330;
	return Cbuf_AddText(unk, cmd, localClientNum);

}

void SetColorModulation_f_Real(int pCVRenderView, int blend)
{
	void(*SetColorModulation)(int pCVRenderView, int blend) = (void(*)(int, int))addr->_0x869D7170;
	return SetColorModulation(pCVRenderView, blend);
}

void ForcedMaterialOverride_f_Real(int pCModelRenderAddr, IMaterial* mat)
{
	void(*ForcedMaterialOverride)(int pCModelRenderAddr, IMaterial* mat) = (void(*)(int, IMaterial*))addr->_0x86990738;
	return ForcedMaterialOverride(pCModelRenderAddr, mat);

}

void PopulateVtables_Real(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr)
{
	*VEngineClient013 = addr->_0x86C54178;
	*VGUI_Surface031 = addr->_0x85D05BBC;
	*VClientEntityList003 = addr->_0x886FC164;
	*CCInputAddr = addr->_0x887302D0;
	*ClientModeAddr = addr->_0x88729A10;
	*CModelRenderAddr = addr->_0x86E196C8;
	*CVRenderViewAddr = addr->_0x86C574BC;
	*KeyValuesAddr = addr->_0x886DA354;
}

void DrawLineWithColor_Real(int x0, int y0, int x1, int y1, int col)
{
	DrawSetColor_f(VGUI_Surface031, col);
	DrawLine_f(VGUI_Surface031, x0, y0, x1, y1);
}

void DrawText_Real(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered)
{
	DrawSetTextFont_f(VGUI_Surface031, font);
	int width = 0, height = 0;
	GetTextSize_f(VGUI_Surface031, font, msg, &width, &height);
	DrawSetTextColor_f(VGUI_Surface031, r, g, b, a);
	DrawSetTextPos_f(VGUI_Surface031, centered ? x - width / 2 : x, y);
	DrawPrintText_f(VGUI_Surface031, msg, wcslen(msg), 0);
}

void DrawRect_Real(int x, int y, int w, int h, int col)
{
	DrawSetColor_f(VGUI_Surface031, col);
	DrawShader_f(VGUI_Surface031, x, y, x + w, y + h);
}

int createRGBA_Real(int r, int g, int b, int a)
{
	return ((r & 0xff) << 24) + ((g & 0xff) << 16) + ((b & 0xff) << 8) + ((a & 0xff));
}

void DrawBox_Real(float x, float y, float width, float height, int RGBA)
{
	DrawSetColor_f(VGUI_Surface031, RGBA);

	DrawOutlinedRect_f(VGUI_Surface031, x, y, x + width, y + height);
}

void PlayerBox_Real(float x, float y, float w, float h, int clr)
{
	DrawSetColor_f(VGUI_Surface031, clr);
	DrawOutlinedRect_f(VGUI_Surface031, x, y, x + w, y + h);

	DrawSetColor_f(VGUI_Surface031, 0x000000FF);
	DrawOutlinedRect_f(VGUI_Surface031, x - 1, y - 1, x + w + 1, y + h + 1);
	DrawOutlinedRect_f(VGUI_Surface031, x + 1, y + 1, x + w - 1, y + h - 1);
}

XINPUT_STATE InputState;

bool GetAsyncKeyState_Real(int button)
{
	XInputGetState(0, &InputState);

	if (button == 0) return true;

	else if (button == 0x1337) return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	else if (button == 0x1338) return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return (InputState.Gamepad.wButtons & button);
}

void DrawRectWithBorder_Real(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor)
{
	DrawRect(x, y, width, height, rectColor);

	DrawRect(x, y, lineWidth, height, borderColor);
	DrawRect(x + lineWidth, y, width - lineWidth, lineWidth, borderColor);
	DrawRect(x + lineWidth, y + height - lineWidth, width - lineWidth, lineWidth, borderColor);
	DrawRect(x + (width - lineWidth), y + lineWidth, lineWidth, height - (lineWidth * 2), borderColor);
}

void drawCheckBox_Real(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked) {
	DrawRect(centerX, centerY, 12, 1, outlineBoxColor);
	DrawRect(centerX, centerY + 12, 12, 1, outlineBoxColor);
	DrawRect(centerX, centerY, 1, 12, outlineBoxColor);
	DrawRect(centerX + 12, centerY, 1, 13, outlineBoxColor);

	DrawRect(centerX + 1, centerY + 1, 11, 11, ticked ? 0x00FF007D : 0xFF00007D);
}

void DrawTextWithBG_Real(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor)
{
	int TextWidth = 0, TextHeight = 0, lineWidth = 3;
	GetTextSize_f(VGUI_Surface031, fontName, GetWC(text), &TextWidth, &TextHeight);

	DrawRectWithBorder(x - 5, y - 3, TextWidth + 10, TextHeight + 2, lineWidth, 0x00000091, menuColor);

	DrawText(GetWC(text), fontName, x, y, r, g, b, a, centered);
}

extern "C"
{
	PVOID MmGetPhysicalAddress(PVOID Address);
	UCHAR KeGetCurrentProcessType(VOID);
	DWORD XamUserGetName(DWORD dwUserIndex, LPSTR pUserName, DWORD cchUserName);
}

FARPROC ResolveFunction(PCHAR ModuleName, DWORD Ordinal)
{
	HMODULE mHandle = GetModuleHandle(ModuleName);
	return (mHandle == NULL) ? NULL : GetProcAddress(mHandle, (LPCSTR)Ordinal);
}

VOID(*XNotifyQueueUI)(DWORD dwType, DWORD dwUserIndex, DWORD dwPriority, LPCWSTR pwszStringParam, ULONGLONG qwParam) = (VOID(*)(DWORD, DWORD, DWORD, LPCWSTR, ULONGLONG))ResolveFunction("xam.xex", 0x290);

VOID XNotifyThread(PWCHAR NotifyText)
{
	XNotifyQueueUI(14, 0, 2, NotifyText, NULL);
}

VOID XNotify_Real(PWCHAR NotifyText)
{
	if (KeGetCurrentProcessType() != 1)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)XNotifyThread, (LPVOID)NotifyText, 0, NULL);
	}
	else { XNotifyThread(NotifyText); }
}

int GetScreenSize_Real(int* width, int* height)
{
	return GetScreenSize_f(VEngineClient013, width, height);
}

int isInGame_Real()
{
	return isInGame_f(VEngineClient013);
}

int GetLocalClientNumber_Real()
{
	return GetLocalClientNumber_f(VEngineClient013);
}

int GetClientEntity_Real(int id)
{
	return GetClientEntity_f(VClientEntityList003, id);
}

int GetHighestEntityIndex_Real()
{
	return GetHighestEntityIndex_f(VClientEntityList003);
}

#endif

__int64 __declspec(naked) HvxGetVersion(unsigned int key, __int64 type, __int64 SourceAddress, __int64 DestAddress, __int64 lenInBytes)
{
	__asm
	{
		li r0, 0x0
		sc
		blr
	}
}

unsigned int HVGetVersionsPeekDWORD(unsigned long long Address)
{
	unsigned int *data = (unsigned int *)XPhysicalAlloc(4, MAXULONG_PTR, 0, PAGE_READWRITE); ;

	__int64 dest = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress((unsigned int*)data);

	HvxGetVersion(0x72627472, 5, Address, dest, 4);

	unsigned int retData = *(unsigned int*)data;

	XPhysicalFree(data);

	return retData;
}

int * GetDetours_Real()
{
	return (int*)new Detour();
}

void* HookFunction_Real(Detour* a, void* b, void* c)
{
	return (void*)a->HookFunction((unsigned int)b, (unsigned int)c);

}

unsigned int ReverseInt(unsigned int val)
{
	int RetVal = ((val << 24)) | (((val << 8) & 0x00ff0000)) | (((val >> 8) & 0x0000ff00)) | (((val >> 24) & 0x000000ff));

	return (RetVal + 0x90E00000);
}

void LoadAddresses()
{
	WorldToScreenMatrix_f = (VMatrix&(*)(int pVEngineClient013))WorldToScreenMatrix_f_Real;
	GetUserCmd_f = (CUserCmd(*)(int pCCInputAddr, int nSlot, int sequence_number))GetUserCmd_f_Real;
	DrawModelExecute_f = (void(*)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld))DrawModelExecute_f_Real;
	GetViewAngles_f = (void(*)(int pVEngineClient013, QAngle &angles))GetViewAngles_f_Real;
	SetViewAngles_f = (void(*)(int VEngineClient013, QAngle &angles))SetViewAngles_f_Real;


#if defined(DEVELOPERSDEVELOPERSDEVELOPERS)

	GetDetour = (Detour*(*)())GetDetours_Real;

	user_memcpy = (void*(*)(void*, void*, size_t))memcpy;
	user_strcpy = (char*(*)(char*, const char*))strcpy;
	user_memset = (void*(*)(void*, int, size_t))memset;
	user_strcmp = (int(*)(const char*, const char*))strcmp;

	xbOHookFunction = (void*(*)(Detour* a, void* b, void* c))HookFunction_Real;

	WorldToScreenMatrix_f = (VMatrix&(*)(int pVEngineClient013))WorldToScreenMatrix_f_Real;
	GetUserCmd_f = (CUserCmd(*)(int pCCInputAddr, int nSlot, int sequence_number))GetUserCmd_f_Real;
	DrawModelExecute_f = (void(*)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld))DrawModelExecute_f_Real;
	GetViewAngles_f = (void(*)(int pVEngineClient013, QAngle &angles))GetViewAngles_f_Real;
	SetViewAngles_f = (void(*)(int VEngineClient013, QAngle &angles))SetViewAngles_f_Real;

	GetScreenSize_f = (int(*)(int pVEngineClient013, int* width, int* height))GetScreenSize_f_Real;
	GetLocalClientNumber_f = (int(*)(int SomeStructure))GetLocalClientNumber_f_Real;
	GetClientEntity_f = (int(*)(int SomeStructure, int clientID))GetClientEntity_f_Real;
	GetHighestEntityIndex_f = (int(*)(int SomeStructure))GetHighestEntityIndex_f_Real;
	isInGame_f = (int(*)(int pVEngineClient013))isInGame_f_Real;
	getPlayerInfo_f = (int(*)(int pVEngineClient013, int id, player_info_t* info))getPlayerInfo_f_Real;
	DrawShader_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))DrawShader_f_Real;
	DrawLine_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))DrawLine_f_Real;
	DrawSetColor_f = (void(*)(int pVGUI_Surface031, int RGBA))DrawSetColor_f_Real;
	DrawSetTextColor_f = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))DrawSetTextColor_f_Real;
	DrawSetTextPos_f = (void(*)(int pVGUI_Surface031, int x, int y))DrawSetTextPos_f_Real;
	DrawSetTextFont_f = (void(*)(int pVGUI_Surface031, int font))DrawSetTextFont_f_Real;
	DrawPrintText_f = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))DrawPrintText_f_Real;
	DrawOutlinedRect_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))DrawOutlinedRect_f_Real;
	setupBones_f = (bool(*)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime))setupBones_f_Real;
	Cbuf_AddText_f = (void(*)(int unk, char* cmd, int localClientNum))Cbuf_AddText_f_Real;
	ForcedMaterialOverride_f = (void(*)(int pCModelRenderAddr, IMaterial* mat))ForcedMaterialOverride_f_Real;
	SetColorModulation_f = (void(*)(int pCVRenderView, int blend))SetColorModulation_f_Real;
	GetTextSize_f = (void(*)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall))GetTextSize_f_Real;
	DrawLineWithColor = (void(*)(int x0, int y0, int x1, int y1, int col))DrawLineWithColor_Real;
	DrawText = (void(*)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered))DrawText_Real;
	DrawRect = (void(*)(int x, int y, int w, int h, int col))DrawRect_Real;
	createRGBA = (int(*)(int r, int g, int b, int a))createRGBA_Real;
	DrawBox = (void(*)(float x, float y, float width, float height, int RGBA))DrawBox_Real;
	PlayerBox = (void(*)(float x, float y, float w, float h, int clr))PlayerBox_Real;
	GetAsyncKeyState = (bool(*)(int button))GetAsyncKeyState_Real;
	GetScreenSize = (int(*)(int* width, int* height))GetScreenSize_Real;
	isInGame = (int(*)())isInGame_Real;
	GetLocalClientNumber = (int(*)())GetLocalClientNumber_Real;
	GetClientEntity = (int(*)(int id))GetClientEntity_Real;
	GetHighestEntityIndex = (int(*)())GetHighestEntityIndex_Real;
	drawCheckBox = (void(*)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked))drawCheckBox_Real;
	DrawRectWithBorder = (void(*)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor))DrawRectWithBorder_Real;
	DrawTextWithBG = (void(*)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor))DrawTextWithBG_Real;
	PopulateVtables = (void(*)(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr))PopulateVtables_Real;
	XNotify = (void(*)(wchar_t*))XNotify_Real;

	addr = new csgo_addr_offhost_s;

	addr->SetAddress();

#else

	GAME_ADDRESS_TRANSFER_CSGO* Game_Functions = (GAME_ADDRESS_TRANSFER_CSGO*)ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BEE0));
	SYS_FUNCTION_ADDRESS* Sys_Functions = (SYS_FUNCTION_ADDRESS*)ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED8));

	if (Sys_Functions)
	{
		GetDetour = (Detour*(*)())Sys_Functions->GetDetours;
		XNotify = (void(*)(wchar_t*))Sys_Functions->XNotify;

		user_memcpy = (void*(*)(void*, void*, size_t))Sys_Functions->memcpy;
		user_strcpy = (char*(*)(char*, const char*))Sys_Functions->strcpy;
		user_memset = (void*(*)(void*, int, size_t))Sys_Functions->memset;
		user_strcmp = (int(*)(const char*, const char*))Sys_Functions->strcmp;

		xbOHookFunction = (void*(*)(Detour* a, void* b, void* c))Sys_Functions->HookFunction;
	}

	if (Game_Functions)
	{
		addr = Game_Functions->addr;

		GetScreenSize_f = (int(*)(int pVEngineClient013, int* width, int* height))ReverseInt((int)Game_Functions->GetScreenSize_f);
		GetLocalClientNumber_f = (int(*)(int SomeStructure))ReverseInt((int)Game_Functions->GetLocalClientNumber_f);
		GetClientEntity_f = (int(*)(int SomeStructure, int clientID))ReverseInt((int)Game_Functions->GetClientEntity_f);
		GetHighestEntityIndex_f = (int(*)(int SomeStructure))ReverseInt((int)Game_Functions->GetHighestEntityIndex_f);
		isInGame_f = (int(*)(int pVEngineClient013))ReverseInt((int)Game_Functions->isInGame_f);
		getPlayerInfo_f = (int(*)(int pVEngineClient013, int id, player_info_t* info))ReverseInt((int)Game_Functions->getPlayerInfo_f);
		DrawShader_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))ReverseInt((int)Game_Functions->DrawShader_f);
		DrawLine_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))ReverseInt((int)Game_Functions->DrawLine_f);
		DrawSetColor_f = (void(*)(int pVGUI_Surface031, int RGBA))ReverseInt((int)Game_Functions->DrawSetColor_f);
		DrawSetTextColor_f = (void(*)(int pVGUI_Surface031, int r, int g, int b, int a))ReverseInt((int)Game_Functions->DrawSetTextColor_f);
		DrawSetTextPos_f = (void(*)(int pVGUI_Surface031, int x, int y))ReverseInt((int)Game_Functions->DrawSetTextPos_f);
		DrawSetTextFont_f = (void(*)(int pVGUI_Surface031, int font))ReverseInt((int)Game_Functions->DrawSetTextFont_f);
		DrawPrintText_f = (void(*)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType))ReverseInt((int)Game_Functions->DrawPrintText_f);
		DrawOutlinedRect_f = (void(*)(int pVGUI_Surface031, int x1, int y1, int x2, int y2))ReverseInt((int)Game_Functions->DrawOutlinedRect_f);
		setupBones_f = (bool(*)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime))ReverseInt((int)Game_Functions->setupBones_f);
		Cbuf_AddText_f = (void(*)(int unk, char* cmd, int localClientNum))ReverseInt((int)Game_Functions->Cbuf_AddText_f);
		ForcedMaterialOverride_f = (void(*)(int pCModelRenderAddr, IMaterial* mat))ReverseInt((int)Game_Functions->ForcedMaterialOverride_f);
		SetColorModulation_f = (void(*)(int pCVRenderView, int blend))ReverseInt((int)Game_Functions->SetColorModulation_f);
		GetTextSize_f = (void(*)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall))ReverseInt((int)Game_Functions->GetTextSize_f);
		DrawLineWithColor = (void(*)(int x0, int y0, int x1, int y1, int col))ReverseInt((int)Game_Functions->DrawLineWithColor);
		DrawText = (void(*)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered))ReverseInt((int)Game_Functions->DrawText);
		DrawRect = (void(*)(int x, int y, int w, int h, int col))ReverseInt((int)Game_Functions->DrawRect);
		createRGBA = (int(*)(int r, int g, int b, int a))ReverseInt((int)Game_Functions->createRGBA);
		DrawBox = (void(*)(float x, float y, float width, float height, int RGBA))ReverseInt((int)Game_Functions->DrawBox);
		PlayerBox = (void(*)(float x, float y, float w, float h, int clr))ReverseInt((int)Game_Functions->PlayerBox);
		GetAsyncKeyState = (bool(*)(int button))ReverseInt((int)Game_Functions->GetAsyncKeyState);
		GetScreenSize = (int(*)(int* width, int* height))ReverseInt((int)Game_Functions->GetScreenSize);
		isInGame = (int(*)())ReverseInt((int)Game_Functions->isInGame);
		GetLocalClientNumber = (int(*)())ReverseInt((int)Game_Functions->GetLocalClientNumber);
		GetClientEntity = (int(*)(int id))ReverseInt((int)Game_Functions->GetClientEntity);
		GetHighestEntityIndex = (int(*)())ReverseInt((int)Game_Functions->GetHighestEntityIndex);
		drawCheckBox = (void(*)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked))ReverseInt((int)Game_Functions->drawCheckBox);
		DrawRectWithBorder = (void(*)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor))ReverseInt((int)Game_Functions->DrawRectWithBorder);
		DrawTextWithBG = (void(*)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered, float menuColor))ReverseInt((int)Game_Functions->DrawTextWithBG);
		PopulateVtables = (void(*)(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr))ReverseInt((int)Game_Functions->PopulateVtables);
	}
#endif	
}