#include "csgo.h"

Detour PaintTraverseDetour;
PaintTraverseStub PaintTraverseOriginal;
void PaintTraverseHook(void* _this, void* unk, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	updateStructs();

	renderMenu();

	if (IsInGame())
	{
		int width, height;
		GetScreenSize(&width, &height);

		if (LocalPlayer->m_bIsScoped())
		{
			DrawLineWithColor_Real(width / 2, 0, width / 2, height, createRGBA(15, 15, 15, 255));
			DrawLineWithColor_Real(0, height / 2, width, height / 2, createRGBA(15, 15, 15, 255));
			*(int*)0x887232D4 = 0x00;
			*(int*)0x8870C7A4 = 0x00;
		}
		else
		{
			*(int*)0x887232D4 = 0x01;
			*(int*)0x8870C7A4 = 0x01;
		}

		for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
		{
			__try
			{
				CBaseEntity* Entity = g_EntityList->GetClientEntity(i);
				IClientNetworkable* pNetworkable;
				ClientClass* Client;
				if (Entity)
				{
					pNetworkable = g_EntityList->GetClientNetworkable(i);
					Client = pNetworkable->GetClientClass();
					const char* entityName = GetEntityName(Client->m_ClassID);

					if (!pNetworkable->IsDormant() && Entity != LocalPlayer && strcmp(entityName, ""))
					{
						Vector Origin = Entity->GetOrigin();
						Vector Screen, top, bottom;

						if (Origin.y == 0x00)
							continue;

						Vector max = GetCollideable((int)Entity)->OBBMaxs();
						Vector min = GetCollideable((int)Entity)->OBBMins();
						Vector top3D = Origin + Vector(0, 0, max.z);
						Vector bottom3D = Origin + Vector(0, 0, min.z);

						if (WorldToScreen(Origin, Screen) &&
							WorldToScreen(top3D, top) &&
							WorldToScreen(bottom3D, bottom))
						{
							float eheight = (Screen.y - top.y);
							float ewidth = eheight / 4.f;

							player_info_t pinfo;
							if (!Entity->GetHealth() <= 0 && !Entity->GetAlive())
								getPlayerInfo_f(VEngineClient013, i, &pinfo);

							if (ESPStatus)
							{
								if (i <= 64) //Entity is player
								{
									if (!Entity->GetHealth() <= 0 && !Entity->GetAlive())
									{
										int espColor = !Entity->IsEnemy() ? 0x00FF00FF : 0xFF0000FF;

										if (bSnaplines)
											DrawLineWithColor(Screen.x, Screen.y, width / 2, height - 30, espColor);
										if (bNames)
											DrawText(GetWC(pinfo.name), 0xB7, top.x, top.y - 17, 0xFF, 0xFF, 0xFF, 0xFF, true);
										if (b2DBoxes || b3DBoxes)
										{
											if (b3DBoxes)
												Draw3DBox(i, Entity, espColor);
											if (b2DBoxes)
												DrawEntity(Entity, espColor);

											char armorValue[0x52] = { 0 };
											_snprintf(armorValue, 0x52, "Armor: %d", Entity->GetArmor());
											DrawText(Entity->GetArmor() <= 0 ? L"Armor: 0" : GetWC(armorValue), 0xB7, top.x, Screen.y, 0xFF, 0xFF, 0xFF, 0xFF, true);
										}
										if (bSkeleton)
											DrawSkeleton(Entity, espColor);
									}
								}
								else
								{
									if (bEntityESP)
										DrawText(GetWC(entityName), 0xB7, top.x, top.y - 17, 0xFF, 0xFF, 0xFF, 0xFF, true);
								}
							}
						}
					}
				}
			}
			__except (1)
			{
			}
		}
	}

	PaintTraverseOriginal(_this, unk, vguiPanel, forceRepaint, allowForce);
}

Detour CreateMoveDetour;
CreateMoveStub CreateMoveOriginal;
bool CreateMoveHook(int pClientModeAddr, float flInputSampleTime, CUserCmd* cmd)
{
	if (IsInGame())
	{
		for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
		{
			__try {

				CBaseEntity* Entity = g_EntityList->GetClientEntity(i);
				IClientNetworkable* pNetworkable;
				ClientClass* Client;
				if (Entity)
				{
					pNetworkable = g_EntityList->GetClientNetworkable(i);
					Client = pNetworkable->GetClientClass();
				}

				if (bAimbot)
				{
					if (!pNetworkable->IsDormant() && !EntityIsInvalid(Entity) && Entity->IsEnemy())
					{
						Vector aimPos = Entity->GetPredicted(GetBonePosition((int)Entity, 5));
						Vector FinalAngles = vectoangles(aimPos - LocalPlayer->GetEyePosition());
						QAngle aim_angle = QAngle(FinalAngles.x, FinalAngles.y, FinalAngles.z);
						QAngle AimPunch = *(QAngle*)(&LocalPlayer->GetPunch()) * 2.f;

						if (Entity->IsVisible(5))
						{
							if (!bAimkey || GetAsyncKeyState(0x1337) || LocalPlayer->m_bIsScoped())
							{
								cmd->viewangles = aim_angle - AimPunch;

								if (bAutoAim)
									cmd->buttons |= 4;
							}
						}
					}
				}

				//BunnyHop
				if (bBhop)
				{
					if ((cmd->buttons & IN_JUMP) && !(LocalPlayer->GetFlags() & FL_ONGROUND))
						cmd->buttons &= ~IN_JUMP;
				}
			}
			__except (1) {
			}
		}
	}

	return CreateMoveOriginal(pClientModeAddr, flInputSampleTime, cmd);
}

bool shootLocal = false;

Detour XamInputGetStateDetour;
XamInputGetStateStub XamInputGetStateOriginal;
DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState)
{
	DWORD dwResult = XamInputGetStateOriginal(dwUserIndex, r4, pState);

	if (dwUserIndex != 0 || dwResult != 0)
		return dwResult;

	if (MenuVars.isOpen) {
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_UP;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_DOWN;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_LEFT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_DPAD_RIGHT;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_A;
		pState->Gamepad.wButtons &= ~XINPUT_GAMEPAD_B;
	}

	return dwResult;
}

void ForceMaterial(IMaterial* material, int color)
{
	if (material != NULL)
	{
		SetColorModulation_f(CVRenderViewAddr, color);
		ForcedMaterialOverride_f(CModelRenderAddr, material);
	}
}

#include <string>
#define strenc( s ) ( s )

IMaterial* visible_flat;

Detour DrawModelExecuteDetour;
DrawModelExecuteStub DrawModelExecuteOriginal;
void DrawModelExecuteHook(int pCModelRenderAddr, void* context, void* state, ModelRenderInfo_t& info, matrix3x4_t* pCustomBoneToWorld)
{
	//was going to do chams and stuff but never got around to fully doing it
	__try {
		if (isInGame_f(VEngineClient013) && LocalPlayer)
		{
			if (info.pModel)
			{
				CBaseEntity* pModelEntity = (CBaseEntity*)g_EntityList->GetClientEntity(info.entity_index);
				if (pModelEntity && pModelEntity->GetAlive() && !pModelEntity->GetDormant())
				{
					int render_color_hidden = pModelEntity->GetTeam() == LocalPlayer->GetTeam() ? createRGBA(72, 219, 75, 255) : createRGBA(232, 209, 32, 255);
					int render_color_visible = pModelEntity->GetTeam() == LocalPlayer->GetTeam() ? createRGBA(84, 167, 255, 255) : createRGBA(200, 60, 60, 255);

					ForceMaterial(visible_flat, render_color_visible);


				}
			}
		}
		DrawModelExecuteOriginal(pCModelRenderAddr, context, state, info, pCustomBoneToWorld);
	}
	__except (1) {
	}
}