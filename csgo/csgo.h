#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <setjmp.h>
#include <cmath>

#include "Detour.h"
#include "Vector.h"
#include "IVModelInfo.h"
#include "Structs.h"
#include "Functions.h"
#include "Menu.h"
#include "Hooks.h"
#include "Trace.h"
#include "IEngineTrace.h"
#include "IMaterial.h"

#define VEngineClient013 0x86C54178
#define VGUI_Surface031 0x85D05BBC
#define VClientEntityList003  0x886FC164
#define CCInputAddr 0x887302D0
#define ClientModeAddr 0x88729A10
#define CModelRenderAddr 0x86E196C8
#define CVRenderViewAddr 0x86C574BC
#define KeyValuesAddr 0x886DA354

extern bool unloadModule;
extern bool Initialized;

extern IClientEntityList* g_EntityList;
extern CBaseEntity* LocalPlayer;
extern IEngineTrace* EngineTrace;
extern IVModelInfo* ModelInfo;
//extern IVRenderView* I::RenderView;
//extern IVModelRender* I::ModelRender;