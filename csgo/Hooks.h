#pragma once

extern Detour PaintTraverseDetour;
typedef void(*PaintTraverseStub)(int r3, int r4, int r5, int r6, int r7);
extern void PaintTraverseHook(int r3, int r4, int r5, int r6, int r7);
extern PaintTraverseStub PaintTraverseOriginal;;

extern Detour CreateMoveDetour;
typedef bool(*CreateMoveStub)(int pClientModeAddr, float flInputSampleTime, CUserCmd* cmd);
extern bool CreateMoveHook(int pClientModeAddr, float flInputSampleTime, CUserCmd* cmd);
extern CreateMoveStub CreateMoveOriginal;

extern Detour DrawModelExecuteDetour;
typedef void(*DrawModelExecuteStub)(int pCModelRenderAddr, void* context, void* state, ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld);
extern void DrawModelExecuteHook(int pCModelRenderAddr, void* context, void* state, ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld);
extern DrawModelExecuteStub DrawModelExecuteOriginal;

extern Detour XamInputGetStateDetour;
typedef int(*XamInputGetStateStub)(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
extern DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
extern XamInputGetStateStub XamInputGetStateOriginal;