#pragma once

struct player_info_t
{
	char __pad0[0x8];
	char name[128];
	char __pad1[0x250];
};

class IClientNetworkable;

class CBaseEntity
{
public:
	char __pad[0x64];
	int index;
	int GetHealth();
	int GetTeam();
	int GetFlags();
	int GetTickBase();
	int GetShotsFired();
	int GetMoveType();
	int GetModelIndex();
	int GetHitboxSet();
	int GetUserID();
	int GetArmor();
	int GetCollisionGroup();
	int PhysicsSolidMaskForEntity();
	int GetOwner();
	int GetGlowIndex();
	int get_tick_base();
	bool GetAlive();
	bool GetDormant();
	bool GetImmune();
	bool IsEnemy();
	bool IsVisible(int bone);
	bool m_visible;
	float GetCurTime();
	bool IsBroken();
	bool HasHelmet();
	bool IsFlashed();
	bool IsTargetingLocal();
	float GetFlashDuration();
	float GetBombTimer();
	bool SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
	Vector GetOrigin();
	Vector GetEyePosition();
	QAngle GetPunch();
	Vector GetVelocity();
	Vector GetPredicted(Vector p0);
	player_info_t GetPlayerInfo();
	int& GetXUIDLow();
	int& GetXUIDHigh();
	char* GetName();
};

class IClientEntityList
{
public:
	virtual IClientNetworkable*   GetClientNetworkable(int entnum) = 0;
	virtual void*                 vtablepad0x1(void) = 0;
	virtual void*                 vtablepad0x2(void) = 0;
	virtual CBaseEntity*        GetClientEntity(int entNum) = 0;
	virtual CBaseEntity*        GetClientEntityFromHandle(int hEnt) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
	virtual void                  SetMaxEntities(int maxEnts) = 0;
	virtual int                   GetMaxEntities() = 0;
};

class ICollideable
{
public:
	virtual void pad0();
	virtual const Vector& OBBMins() const;
	virtual const Vector& OBBMaxs() const;
};

/*class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* mat);
	void DrawModelExecute(void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld = NULL);
};*/

struct model_t
{
	char name[255];
};

typedef unsigned short ModelInstanceHandle_t;

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	char pad0[0x04];
	void* pRenderable;
	model_t* pModel;
	matrix3x4_t* pModelToWorld;
	matrix3x4_t* pLightingOffset;
	Vector* pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};