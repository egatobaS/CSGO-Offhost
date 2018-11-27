#pragma once


typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

extern VMatrix& WorldToScreenMatrix();
extern void updateStructs();
extern Vector vectoangles(Vector Angles);
extern bool WorldToScreen(const Vector &origin, Vector &screen);
extern CreateInterfaceFn resolveImport(HMODULE module);
extern void* get_interface(CreateInterfaceFn f, const char* szInterfaceVersion);
extern bool EntityIsInvalid(CBaseEntity* Entity);
extern const wchar_t *GetWC(const char *c);
extern ICollideable* GetCollideable(int Entety);
extern Vector GetBonePosition(DWORD EntityPtr, int BoneIndex);
extern void renderMenu();
extern void updatePlayerList();
extern void HealthBar(Vector bot, Vector top, float health);
extern void DrawSkeleton(CBaseEntity* entity, int color);
extern float menuColor;
extern void Say(char* text, int);
extern void changeName(char* text, int originalGT);
extern const char* GetEntityName(int WeaponID);
extern bool(*IsInGame)();