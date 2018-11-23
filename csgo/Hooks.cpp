#include "csgo.h"

Detour PaintTraverseDetour;
PaintTraverseStub PaintTraverseOriginal;
void PaintTraverseHook(int r3, int r4, int r5, int r6, int r7)
{
	updateStructs();

	renderMenu();

	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		__try {
			CBaseEntity* Entity = g_EntityList->GetClientEntity(i);

			if (EntityIsInvalid(Entity))
				continue;

			Vector Origin = Entity->GetOrigin();
			Vector Screen, top;
			int width, height;

			Vector max = GetCollideable((int)Entity)->OBBMaxs();
			Vector top3D = Origin + Vector(0, 0, max.z);

			if (WorldToScreen(Origin, Screen) &&
				WorldToScreen(top3D, top))
			{
				int espColor = !Entity->IsEnemy() ? 0x00FF00FF : 0xFF0000FF;

				float eheight = (Screen.y - top.y);
				float ewidth = eheight / 4.f;

				player_info_t pinfo;
				getPlayerInfo_f(VEngineClient013, i, &pinfo);
				GetScreenSize(&width, &height);

				if (ESPStatus)
				{
					if (bSnaplines)
						DrawLineWithColor(Screen.x, Screen.y, width / 2, height - 30, espColor);
					if (bNames)
						DrawText(GetWC(pinfo.name), 0xB7, top.x, top.y - 17, 0xFF, 0xFF, 0xFF, 0xFF, true);
					if (b2DBoxes)
					{
						PlayerBox(top.x, top.y, ewidth, eheight, espColor);
						HealthBar(Screen, top, Entity->GetHealth());

						char armorValue[0x52] = { 0 };
						_snprintf(armorValue, 0x52, "Armor: %d", Entity->GetArmor());
						DrawText(GetWC(armorValue), 0xB7, Screen.x, Screen.y, 0xFF, 0xFF, 0xFF, 0xFF, true);
					}
					if (bSkeleton)
						DrawSkeleton(Entity, espColor);
				}
			}
		}
		__except (1) {
		}
	}

	PaintTraverseOriginal(r3, r4, r5, r6, r7);
}

Detour CreateMoveDetour;
CreateMoveStub CreateMoveOriginal;
bool CreateMoveHook(int pClientModeAddr, float flInputSampleTime, CUserCmd* cmd)
{
	for (int i = 0; i < g_EntityList->GetHighestEntityIndex(); i++)
	{
		__try {

			CBaseEntity* Entity = g_EntityList->GetClientEntity(i);

			if (EntityIsInvalid(Entity))
				continue;

			if (bAimbot)
			{
				if (!Entity->GetDormant() && !Entity->GetAlive() && Entity->IsEnemy())
				{
					Vector aimPos = GetBonePosition((int)Entity, 5);
					Vector FinalAngles = vectoangles(aimPos - LocalPlayer->GetEyePosition());
					QAngle aim_angle = QAngle(FinalAngles.x, FinalAngles.y, FinalAngles.z);

					if (Entity->IsVisible(5))
					{
						if (!bAimkey || GetAsyncKeyState(0x1338))
						{
							cmd->viewangles = aim_angle -= LocalPlayer->GetPunch() * 2.f;
							if (bAutoAim)
								cmd->buttons |= 4;
						}
					}
				}
			}

			//as of right now, there is a bug with this vv auto bunny hop
			static bool bLastJumped = false;
			static bool bShouldFake = false;

			if (!bLastJumped && bShouldFake)
			{
				bShouldFake = false;
				cmd->buttons |= IN_JUMP;
			}
			else if (cmd->buttons & IN_JUMP)
			{
				if (LocalPlayer->GetFlags() & FL_ONGROUND)
				{
					bLastJumped = true;
					bShouldFake = true;
				}
				else
				{
					cmd->buttons &= ~IN_JUMP;
					bLastJumped = false;
				}
			}
			else
			{
				bLastJumped = false;
				bShouldFake = false;
			}
		}
		__except (1) {
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