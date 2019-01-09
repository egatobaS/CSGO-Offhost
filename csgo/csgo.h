#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <setjmp.h>
#include <cmath>

#define DEVELOPERSDEVELOPERSDEVELOPERS 0

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
#include "Address.h"

extern bool unloadModule;
extern bool Initialized;

extern IClientEntityList* g_EntityList;
extern CBaseEntity* LocalPlayer;
extern IEngineTrace* EngineTrace;
extern IVModelInfo* ModelInfo;
extern IBaseClientDll* Client;
//extern IVRenderView* I::RenderView;
//extern IVModelRender* I::ModelRender;