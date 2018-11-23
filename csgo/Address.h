#pragma once

extern int VEngineClient013;
extern int VGUI_Surface031;
extern int VClientEntityList003;
extern int CCInputAddr;
extern int ClientModeAddr;
extern int CModelRenderAddr;
extern int CVRenderViewAddr;
extern int KeyValuesAddr;


struct SYS_FUNCTION_ADDRESS
{
	void* HookFunction;
	void* XNotify;
	void* user_memcpy;
	void* user_memset;
	void* user_strcpy;
	void* memcmp;
	void* user_strcmp;
	void* Sleep;
	void* MmIsAddressValid;
	void* FIsMmIoAddress;
	void* GetDetours;
};


struct csgo_addr_offhost_s
{
	unsigned int _0x86C54178;
	unsigned int _0x85D05BBC;
	unsigned int _0x886FC164;
	unsigned int _0x887302D0;
	unsigned int _0x88729A10;
	unsigned int _0x86E196C8;
	unsigned int _0x86C574BC;
	unsigned int _0x886DA354;
	unsigned int _0x86939560;
	unsigned int _0x869399F0;
	unsigned int _0x8693C8A0;
	unsigned int _0x881DB410;
	unsigned int _0x8847d140;
	unsigned int _0x868C7C28;
	unsigned int _0x8693C200;
	unsigned int _0x85C4A340;
	unsigned int _0x85C49430;
	unsigned int _0x85C44A08;
	unsigned int _0x85C45C40;
	unsigned int _0x85C45D78;
	unsigned int _0x85C45C38;
	unsigned int _0x85c4c430;
	unsigned int _0x85C44C78;
	unsigned int _0x85C45BD8;
	unsigned int _0x8693BB40;
	unsigned int _0x8693BAF0;
	unsigned int _0x88268EB0;
	unsigned int _0x881477C0;
	unsigned int _0x85C45B50;
	unsigned int _0x86A1A330;
	unsigned int _0x8699C368;
	unsigned int _0x869D7170;
	unsigned int _0x86990738;
	unsigned int _0x8853E5A8;
	unsigned int _0x881A18C0;
	unsigned int _0x000000FC;
	unsigned int _0x000000F0;
	unsigned int _0x00000100;
	unsigned int _0x000000E9;
	unsigned int _0x000016B0;
	unsigned int _0x0000025B;
	unsigned int _0x00000110;
	unsigned int _0x00001294;
	unsigned int _0x00001CB4;
	unsigned int _0x00001CBC;
	unsigned int _0x000000AC;
	unsigned int _0x00001AEC;
	unsigned int _0x00000104;
	unsigned int _0x00000310;
	unsigned int _0x000000B8;
	unsigned int _0x000000B7;
	unsigned int _0x85C839C0;
	unsigned int _0x881E6CB8;
	unsigned int _0x82CF501C;

	void SetAddress()
	{
		_0x86C54178 = 0x86C54178;
		_0x85D05BBC = 0x85D05BBC;
		_0x886FC164 = 0x886FC164;
		_0x887302D0 = 0x887302D0;
		_0x88729A10 = 0x88729A10;
		_0x86E196C8 = 0x86E196C8;
		_0x86C574BC = 0x86C574BC;
		_0x886DA354 = 0x886DA354;
		_0x86939560 = 0x86939560;
		_0x869399F0 = 0x869399F0;
		_0x8693C8A0 = 0x8693C8A0;
		_0x881DB410 = 0x881DB410;
		_0x8847d140 = 0x8847d140;
		_0x868C7C28 = 0x868C7C28;
		_0x8693C200 = 0x8693C200;
		_0x85C4A340 = 0x85C4A340;
		_0x85C49430 = 0x85C49430;
		_0x85C44A08 = 0x85C44A08;
		_0x85C45C40 = 0x85C45C40;
		_0x85C45D78 = 0x85C45D78;
		_0x85C45C38 = 0x85C45C38;
		_0x85c4c430 = 0x85c4c430;
		_0x85C44C78 = 0x85C44C78;
		_0x85C45BD8 = 0x85C45BD8;
		_0x8693BB40 = 0x8693BB40;
		_0x8693BAF0 = 0x8693BAF0;
		_0x88268EB0 = 0x88268EB0;
		_0x881477C0 = 0x881477C0;
		_0x85C45B50 = 0x85C45B50;
		_0x86A1A330 = 0x86A1A330;
		_0x8699C368 = 0x8699C368;
		_0x869D7170 = 0x869D7170;
		_0x86990738 = 0x86990738;
		_0x8853E5A8 = 0x8853E5A8;
		_0x881A18C0 = 0x881A18C0;
		_0x000000FC = 0x000000FC;
		_0x000000F0 = 0x000000F0;
		_0x00000100 = 0x00000100;
		_0x000000E9 = 0x000000E9;
		_0x000016B0 = 0x000016B0;
		_0x0000025B = 0x0000025B;
		_0x00000110 = 0x00000110;
		_0x00001294 = 0x00001294;
		_0x000016B0 = 0x000016B0;
		_0x00001CB4 = 0x00001CB4;
		_0x00001CBC = 0x00001CBC;
		_0x000000AC = 0x000000AC;
		_0x00001AEC = 0x00001AEC;
		_0x00000104 = 0x00000104;
		_0x00000310 = 0x00000310;
		_0x000000B8 = 0x000000B8;
		_0x000000B7 = 0x000000B7;
		_0x85C839C0 = 0x85C839C0;
		_0x881E6CB8 = 0x881E6CB8;
		_0x82CF501C = 0x82CF501C;
	}
};



struct GAME_ADDRESS_TRANSFER_CSGO
{
	csgo_addr_offhost_s* addr;

	void* GetLocalClientNumber_f;
	void* WorldToScreenMatrix_f;
	void* GetScreenSize_f;
	void* GetClientEntity_f;
	void* GetHighestEntityIndex_f;
	void* isInGame_f;
	void* getPlayerInfo;
	void* DrawShader;
	void* DrawLine;
	void* DrawSetColor;
	void* DrawSetTextColor;
	void* DrawSetTextPos;
	void* DrawSetTextFont;
	void* DrawPrintText;
	void* DrawOutlinedRect;
	void* GetFontName;
	void* SetViewAngles;
	void* GetViewAngles;
	void* GetUserCmd;
	void* setupBones;
	void* GetTextSiz;
	void* Cbuf_AddText;
	void* DrawModelExecute;
	void* SetColorModulation;
	void* ForcedMaterialOverride;

};


extern Detour* (*GetDetour)();
extern void(*XNotify)(wchar_t*);
extern void*(*user_memcpy)(void*, void*, size_t);
extern char*(*user_strcpy)(char*, const char*);
extern void*(*user_memset)(void*, int, size_t);
extern int(*user_strcmp)(const char*, const char*);
extern void* (*xbOHookFunction)(Detour* a, void* b, void* c);



extern VMatrix&(*WorldToScreenMatrix_f)(int pVEngineClient013);
extern CUserCmd(*GetUserCmd_f)(int pCCInputAddr, int nSlot, int sequence_number);
extern void(*DrawModelExecute_f)(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
extern void(*GetViewAngles_f)(int pVEngineClient013, QAngle &angles);
extern void(*SetViewAngles_f)(int VEngineClient013, QAngle &angles);

extern int(*GetScreenSize_f)(int pVEngineClient013, int* width, int* height);
extern int(*GetLocalClientNumber_f)(int SomeStructure);
extern int(*GetClientEntity_f)(int SomeStructure, int clientID);
extern int(*GetHighestEntityIndex_f)(int SomeStructure);
extern int(*isInGame_f)(int pVEngineClient013);
extern int(*getPlayerInfo_f)(int pVEngineClient013, int id, player_info_t* info);
extern void(*DrawShader_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
extern void(*DrawLine_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
extern void(*DrawSetColor_f)(int pVGUI_Surface031, int RGBA);
extern void(*DrawSetTextColor_f)(int pVGUI_Surface031, int r, int g, int b, int a);
extern void(*DrawSetTextPos_f)(int pVGUI_Surface031, int x, int y);
extern void(*DrawSetTextFont_f)(int pVGUI_Surface031, int font);
extern void(*DrawPrintText_f)(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType);
extern void(*DrawOutlinedRect_f)(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
extern bool(*setupBones_f)(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
extern void(*Cbuf_AddText_f)(int unk, char* cmd, int localClientNum);
extern void(*ForcedMaterialOverride_f)(int pCModelRenderAddr, IMaterial* mat);
extern void(*SetColorModulation_f)(int pCVRenderView, int blend);
extern void(*GetTextSize_f)(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall);
extern void(*DrawLineWithColor)(int x0, int y0, int x1, int y1, int col);
extern void(*DrawText)(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered);
extern void(*DrawRect)(int x, int y, int w, int h, int col);
extern int(*createRGBA)(int r, int g, int b, int a);
extern void(*DrawBox)(float x, float y, float width, float height, int RGBA);
extern void(*PlayerBox)(float x, float y, float w, float h, int clr);
extern bool(*GetAsyncKeyState)(int button);
extern int(*GetScreenSize)(int* width, int* height);
extern int(*isInGame)();
extern int(*GetLocalClientNumber)();
extern int(*GetClientEntity)(int id);
extern int(*GetHighestEntityIndex)();
extern void(*drawCheckBox)(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked);
extern void(*DrawRectWithBorder)(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor);
extern void(*DrawTextWithBG)(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered);
extern void(*PopulateVtables)(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr);

//LocalFunctions
VMatrix& WorldToScreenMatrix_f_Real(int pVEngineClient013);
CUserCmd GetUserCmd_f_Real(int pCCInputAddr, int nSlot, int sequence_number);
void SetViewAngles_f_Real(int pVEngineClient013, QAngle &angles);
void GetViewAngles_f_Real(int pVEngineClient013, QAngle &angles);
void DrawModelExecute_f_Real(int pCModelRender, void* ctx, void* state, ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
int GetLocalClientNumber_f_Real(int SomeStructure);
int GetScreenSize_f_Real(int pVEngineClient013, int* width, int* height);
int GetClientEntity_f_Real(int SomeStructure, int clientID);
int GetHighestEntityIndex_f_Real(int  SomeStructure);
int isInGame_f_Real(int pVEngineClient013);
int getPlayerInfo_f_Real(int pVEngineClient013, int id, player_info_t* info);
void DrawShader_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
void DrawLine_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
void DrawSetColor_f_Real(int pVGUI_Surface031, int RGBA);
void DrawSetTextColor_f_Real(int pVGUI_Surface031, int r, int g, int b, int a);
void DrawSetTextPos_f_Real(int pVGUI_Surface031, int x, int y);
void DrawSetTextFont_f_Real(int pVGUI_Surface031, int font);
void DrawPrintText_f_Real(int pVGUI_Surface031, const wchar_t *text, int textLen, int drawType);
void DrawOutlinedRect_f_Real(int pVGUI_Surface031, int x1, int y1, int x2, int y2);
int GetFontName_f_Real(int pVGUI_Surface031, unsigned int font);
void GetTextSize_f_Real(int pVGUI_Surface031, int font, const wchar_t *text, int* wide, int* tall);
void Cbuf_AddText_f_Real(int unk, char* cmd, int localClientNum);
void SetColorModulation_f_Real(int pCVRenderView, int blend);
void ForcedMaterialOverride_f_Real(int pCModelRenderAddr, IMaterial* mat);
bool setupBones_f_Real(int hax, matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);

void DrawLineWithColor_Real(int x0, int y0, int x1, int y1, int col);
void DrawText_Real(const wchar_t* msg, int font, int x, int y, int r, int g, int b, int a, bool centered = false);
void DrawRect_Real(int x, int y, int w, int h, int col);
int createRGBA_Real(int r, int g, int b, int a);
void DrawBox_Real(float x, float y, float width, float height, int RGBA);
void PlayerBox_Real(float x, float y, float w, float h, int clr);
bool GetAsyncKeyState_Real(int button);
int GetScreenSize_Real(int* width, int* height);
int isInGame_Real();
int GetLocalClientNumber_Real();
int GetClientEntity_Real(int id);
int GetHighestEntityIndex_Real();
void drawCheckBox_Real(float centerX, float centerY, int checkColor, int outlineBoxColor, bool ticked);
void DrawRectWithBorder_Real(float x, float y, float width, float height, int lineWidth, int rectColor, int borderColor);
void DrawTextWithBG_Real(const char *text, int fontName, float x, float y, int r, int g, int b, int a, bool centered = false);
void PopulateVtables_Real(int* VEngineClient013, int* VGUI_Surface031, int* VClientEntityList003, int* CCInputAddr, int* ClientModeAddr, int* CModelRenderAddr, int* CVRenderViewAddr, int*  KeyValuesAddr);

void LoadAddresses();

extern csgo_addr_offhost_s* addr;