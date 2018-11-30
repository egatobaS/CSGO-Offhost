#pragma once

struct player_info_t
{
	char __pad0[0x8];
	char name[128];
	char __pad1[0x250];
};

extern struct RecvProp;

struct RecvTable
{
	RecvProp* m_pProps;
	int m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

struct RecvProp
{
	char* m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char* m_pParentArrayPropName;
};

struct ClientClass
{
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class IClientUnknown;

class IClientNetworkable
{
public:
	virtual IClientUnknown*  GetIClientUnknown() = 0;
	virtual void             Release() = 0;
	virtual ClientClass*     GetClientClass() = 0;
	virtual void             NotifyShouldTransmit(int state) = 0;
	virtual void             OnPreDataChanged(int updateType) = 0;
	virtual void             OnDataChanged(int updateType) = 0;
	virtual void             PreDataUpdate(int updateType) = 0;
	virtual void             PostDataUpdate(int updateType) = 0;
	virtual void             __unkn(void) = 0;
	virtual bool             IsDormant(void) = 0;
	virtual int              EntIndex(void) const = 0;
	virtual void             ReceiveMessage(int classID, const char* msg) = 0;
	virtual void*            GetDataTableBasePtr() = 0;
	virtual void             SetDestroyedOnRecreateEntities(void) = 0;
};

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
	ClientClass* GetClientClass();
	QAngle GetViewAngles();
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

enum eClientClassId
{
	NextBotCombatCharacter = 0,
	CAK47 = 1,
	CBaseAnimating = 2,
	CBaseAnimatingOverlay = 3,
	CBaseAttributableItem = 4,
	CBaseButton = 5,
	CBaseCombatCharacter = 6,
	CBaseCombatWeapon = 7,
	CBaseCSGrenade = 8,
	CBaseCSGrenadeProjectile = 9,
	CBaseDoor = 10,
	CBaseFlex = 12,
	CBaseGrenade = 13,
	CBaseParticleEntity = 14,
	CBasePlayer = 15,
	CBasePropDoor = 16,
	CBaseTeamObjectiveResource = 17,
	CBaseTempEntity = 18,
	CBaseToggle = 19,
	CBaseTrigger = 20,
	CBaseViewModel = 21,
	CBaseVPhysicsTrigger = 22,
	CBaseWeaponWorldModel = 23,
	CBeam = 24,
	CBeamSpotlight = 25,
	CBoneFollower = 26,
	CBreakableProp = 27,
	CBreakableSurface = 28,
	CC4 = 27,
	CCascadeLight = 30,
	CChicken = 40,
	CColorCorrection = 32,
	CColorCorrectionVolume = 33,
	CCSGameRulesProxy = 34,
	CCSPlayer = 35,
	CCSPlayerResource = 36,
	CCSRagdoll = 37,
	CCSTeam = 38,
	CDEagle = 36,
	CDecoyGrenade = 40,
	CDecoyProjectile = 41,
	CDynamicLight = 42,
	CDynamicProp = 43,
	CEconEntity = 44,
	CEmbers = 45,
	CEntityDissolve = 46,
	CEntityFlame = 47,
	CEntityFreezing = 48,
	CEntityParticleTrail = 49,
	CEnvAmbientLight = 50,
	CEnvDetailController = 51,
	CEnvDOFController = 52,
	CEnvParticleScript = 53,
	CEnvProjectedTexture = 54,
	CEnvQuadraticBeam = 55,
	CEnvScreenEffect = 56,
	CEnvScreenOverlay = 57,
	CEnvTonemapController = 58,
	CEnvWind = 59,
	CFireCrackerBlast = 60,
	CFireSmoke = 61,
	CFireTrail = 62,
	CFish = 63,
	CFlashbang = 60,
	CFogController = 65,
	CFootstepControl = 66,
	CFunc_Dust = 67,
	CFunc_LOD = 68,
	CFuncAreaPortalWindow = 69,
	CFuncBrush = 70,
	CFuncConveyor = 71,
	CFuncLadder = 72,
	CFuncMonitor = 73,
	CFuncMoveLinear = 74,
	CFuncOccluder = 75,
	CFuncReflectiveGlass = 76,
	CFuncRotating = 77,
	CFuncSmokeVolume = 78,
	CFuncTrackTrain = 79,
	CGameRulesProxy = 80,
	CHandleTest = 81,
	CHEGrenade = 82,
	CHostage = 83,
	CHostageCarriableProp = 84,
	CIncendiaryGrenade = 85,
	CInferno = 86,
	CInfoLadderDismount = 87,
	CInfoOverlayAccessor = 88,
	CKnife = 89,
	CKnifeGG = 90,
	CLightGlow = 91,
	CMaterialModifyControl = 92,
	CMolotovGrenade = 93,
	CMolotovProjectile = 94,
	CMovieDisplay = 95,
	CParticleFire = 96,
	CParticlePerformanceMonitor = 97,
	CParticleSystem = 98,
	CPhysBox = 99,
	CPhysBoxMultiplayer = 100,
	CPhysicsProp = 101,
	CPhysicsPropMultiplayer = 102,
	CPhysMagnet = 103,
	CPlantedC4 = 99,
	CPlasma = 105,
	CPlayerResource = 106,
	CPointCamera = 107,
	CPointCommentaryNode = 108,
	CPoseController = 109,
	CPostProcessController = 110,
	CPrecipitation = 111,
	CPrecipitationBlocker = 112,
	CPredictedViewModel = 113,
	CProp_Hallucination = 114,
	CPropDoorRotating = 115,
	CPropJeep = 116,
	CPropVehicleDriveable = 117,
	CRagdollManager = 118,
	CRagdollProp = 119,
	CRagdollPropAttached = 120,
	CRopeKeyframe = 121,
	CSCAR17 = 122,
	CSceneEntity = 123,
	CShadowControl = 124,
	CSlideshowDisplay = 125,
	CSmokeGrenade = 126,
	CSmokeGrenadeProjectile = 127,
	CSmokeStack = 128,
	CSpatialEntity = 129,
	CSpotlightEnd = 130,
	CSprite = 131,
	CSpriteOriented = 132,
	CSpriteTrail = 133,
	CStatueProp = 134,
	CSteamJet = 135,
	CSun = 136,
	CSunlightShadowControl = 137,
	CTeam = 138,
	CTeamplayRoundBasedRulesProxy = 139,
	CTEArmorRicochet = 140,
	CTEBaseBeam = 141,
	CTEBeamEntPoint = 142,
	CTEBeamEnts = 143,
	CTEBeamFollow = 144,
	CTEBeamLaser = 145,
	CTEBeamPoints = 146,
	CTEBeamRing = 147,
	CTEBeamRingPoint = 148,
	CTEBeamSpline = 149,
	CTEBloodSprite = 150,
	CTEBloodStream = 151,
	CTEBreakModel = 152,
	CTEBSPDecal = 153,
	CTEBubbles = 154,
	CTEBubbleTrail = 155,
	CTEClientProjectile = 156,
	CTEDecal = 157,
	CTEDust = 158,
	CTEDynamicLight = 159,
	CTEEffectDispatch = 160,
	CTEEnergySplash = 161,
	CTEExplosion = 162,
	CTEFireBullets = 163,
	CTEFizz = 164,
	CTEFootprintDecal = 165,
	CTEFoundryHelpers = 166,
	CTEGaussExplosion = 167,
	CTEGlowSprite = 168,
	CTEImpact = 169,
	CTEKillPlayerAttachments = 170,
	CTELargeFunnel = 171,
	CTEMetalSparks = 172,
	CTEMuzzleFlash = 173,
	CTEParticleSystem = 174,
	CTEPhysicsProp = 175,
	CTEPlantBomb = 176,
	CTEPlayerAnimEvent = 177,
	CTEPlayerDecal = 178,
	CTEProjectedDecal = 179,
	CTERadioIcon = 180,
	CTEShatterSurface = 181,
	CTEShowLine = 182,
	CTesla = 183,
	CTESmoke = 184,
	CTESparks = 185,
	CTESprite = 186,
	CTESpriteSpray = 187,
	CTest_ProxyToggle_Networkable = 188,
	CTestTraceline = 189,
	CTEWorldDecal = 190,
	CTriggerPlayerMovement = 191,
	CTriggerSoundOperator = 192,
	CVGuiScreen = 193,
	CVoteController = 194,
	CWaterBullet = 195,
	CWaterLODControl = 196,
	CWeaponAug = 190,
	CWeaponAWP = 191,
	CWeaponBizon = 192,
	CWeaponCSBase = 200,
	CWeaponCSBaseGun = 201,
	CWeaponCycler = 202,
	CWeaponElite = 196,
	CWeaponFamas = 197,
	CWeaponFiveSeven = 198,
	CWeaponG3SG1 = 206,
	CWeaponGalil = 207,
	CWeaponGalilAR = 201,
	CWeaponGlock = 202,
	CWeaponHKP2000 = 203,
	CWeaponM249 = 204,
	CWeaponM3 = 212,
	CWeaponM4A1 = 206,
	CWeaponMAC10 = 207,
	CWeaponMag7 = 208,
	CWeaponMP5Navy = 216,
	CWeaponMP7 = 210,
	CWeaponMP9 = 211,
	CWeaponNegev = 212,
	CWeaponNOVA = 213,
	CWeaponP228 = 221,
	CWeaponP250 = 215,
	CWeaponP90 = 216,
	CWeaponSawedoff = 217,
	CWeaponSCAR20 = 218,
	CWeaponScout = 226,
	CWeaponSG550 = 227,
	CWeaponSG552 = 228,
	CWeaponSG553 = 222,
	CWeaponSG556 = 229,
	CWeaponSSG08 = 223,
	CWeaponTaser = 224,
	CWeaponTec9 = 225,
	CWeaponTMP = 233,
	CWeaponUMP45 = 227,
	CWeaponUSP = 235,
	CWeaponXM1014 = 229,
	CWorld = 237,
	DustTrail = 238,
	MovieExplosion = 239,
	ParticleSmokeGrenade = 240,
	RocketTrail = 241,
	SmokeTrail = 242,
	SporeExplosion = 243,
	SporeTrail = 244,
};