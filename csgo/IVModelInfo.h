#pragma once

#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define IN_JUMP					(1 << 1)
#define IN_FORWARD				(1 << 3)
#define	FL_ONGROUND				(1 << 0)
#define IN_ATTACK				(1 << 0)

enum Hitboxes
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
class IMaterial;
struct vcollide_t;
struct model_t;
class Vector;
class QAngle;
class CGameTrace;
struct cplane_t;
typedef CGameTrace trace_t;
struct studiohdr_t;
struct virtualmodel_t;
typedef unsigned char byte;
struct virtualterrainparams_t;
class CPhysCollide;
typedef unsigned short MDLHandle_t;
class CUtlBuffer;
class IClientRenderable;
class Quaternion;
struct mstudioanimdesc_t;
struct mstudioseqdesc_t;
struct mstudiobodyparts_t;
struct mstudiotexture_t;

class RadianEuler
{
public:
	inline RadianEuler( void )
	{ }

	inline RadianEuler( float X, float Y, float Z )
	{
		x = X;
		y = Y;
		z = Z;
	}

	inline RadianEuler( Quaternion const& q ); // evil auto type promotion!!!
	inline RadianEuler( QAngle const& angles ); // evil auto type promotion!!!

	// Initialization
	inline void Init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f )
	{
		x = ix;
		y = iy;
		z = iz;
	}

	//	conversion to qangle
	QAngle ToQAngle( void ) const;
	bool IsValid() const;
	void Invalidate();

	inline float* Base()
	{
		return &x;
	}

	inline const float* Base() const
	{
		return &x;
	}

	// array access...
	float operator[]( int i ) const;
	float& operator[]( int i );

	float x, y, z;
};

class Quaternion // same data-layout as engine's vec4_t,
{ //		which is a float[4]
public:
	inline Quaternion( void )
	{}

	inline Quaternion( float ix, float iy, float iz, float iw )
		: x( ix ),
		  y( iy ),
		  z( iz ),
		  w( iw )
	{ }

	inline Quaternion( RadianEuler const& angle ); // evil auto type promotion!!!

	inline void Init( float ix = 0.0f, float iy = 0.0f, float iz = 0.0f, float iw = 0.0f )
	{
		x = ix;
		y = iy;
		z = iz;
		w = iw;
	}

	bool IsValid() const;
	void Invalidate();

	bool operator==( const Quaternion& src ) const;
	bool operator!=( const Quaternion& src ) const;

	float* Base()
	{
		return ( float* )this;
	}

	const float* Base() const
	{
		return ( float* )this;
	}

	// array access...
	float operator[]( int i ) const;
	float& operator[]( int i );

	float x, y, z, w;
};

struct mstudiobbox_t
{
	int bone;
	int group; // intersection group
	Vector bbmin; // bounding box 
	Vector bbmax;
	int hitboxnameindex; // offset to the name of the hitbox.
	int pad[3];
	float radius;
	int pad2[4];

	char* getHitboxName()
	{
		if (hitboxnameindex == 0)
			return "";

		return ((char*)this) + hitboxnameindex;
	}
};

struct mstudiohitboxset_t
{
	int sznameindex;

	inline char* pszName( void ) const
	{
		return ( ( char* )this ) + sznameindex;
	}

	int numhitboxes;
	int hitboxindex;

	inline mstudiobbox_t* pHitbox( int i ) const
	{
		return ( mstudiobbox_t* )( ( ( byte* )this ) + hitboxindex ) + i;
	}
};

struct mstudiobone_t
{
	int sznameindex;

	inline char* pszName( void ) const
	{
		return ( ( char * )this ) + sznameindex;
	}

	int parent; // parent bone
	int bonecontroller[ 6 ]; // bone controller index, -1 == none

	// default values
	Vector pos;
	Quaternion quat;
	RadianEuler rot;
	// compression scale
	Vector posscale;
	Vector rotscale;

	matrix3x4_t poseToBone;
	Quaternion qAlignment;
	int flags;
	int proctype;
	int procindex; // procedural rule
	mutable int physicsbone; // index into physically simulated bone
	inline void* pProcedure() const
	{
		if( procindex == 0 )
			return NULL;
		else
			return ( void * )( ( ( byte * )this ) + procindex );
	};
	int surfacepropidx; // index into string tablefor property name
	inline char* pszSurfaceProp( void ) const
	{
		return ( ( char * )this ) + surfacepropidx;
	}

	inline int GetSurfaceProp( void ) const
	{
		return surfacepropLookup;
	}

	int contents; // See BSPFlags.h for the contents flags
	int surfacepropLookup; // this index must be cached by the loader, not saved in the file
	int unused[ 7 ]; // remove as appropriate
};

struct mstudiobonecontroller_t
{
	int bone; // -1 == 0
	int type; // X, Y, Z, XR, YR, ZR, M
	float start;
	float end;
	int rest; // byte index value at rest
	int inputfield; // 0-3 user set controller, 4 mouth
	int unused[ 8 ];
};

struct studiohdr_t
{
	int id;
	int version;

	long checksum; // this has to be the same in the phy and vtx files to load!

	inline const char* pszName( void ) const
	{
		return name;
	}

	char name[ 64 ];

	int length;

	Vector eyeposition; // ideal eye position

	Vector illumposition; // illumination center

	Vector hull_min; // ideal movement hull size
	Vector hull_max;

	Vector view_bbmin; // clipping bounding box
	Vector view_bbmax;

	int flags;

	int numbones; // bones
	int boneindex;

	inline mstudiobone_t* pBone( int i ) const
	{
		Assert( i >= 0 && i < numbones );
		return ( mstudiobone_t * )( ( ( byte * )this ) + boneindex ) + i;
	};
	int RemapSeqBone( int iSequence, int iLocalBone ) const; // maps local sequence bone to global bone
	int RemapAnimBone( int iAnim, int iLocalBone ) const; // maps local animations bone to global bone

	int numbonecontrollers; // bone controllers
	int bonecontrollerindex;

	inline mstudiobonecontroller_t* pBonecontroller( int i ) const
	{
		Assert( i >= 0 && i < numbonecontrollers );
		return ( mstudiobonecontroller_t * )( ( ( byte * )this ) + bonecontrollerindex ) + i;
	};

	int numhitboxsets;
	int hitboxsetindex;

	// Look up hitbox set by index
	mstudiohitboxset_t* pHitboxSet( int i ) const
	{
		Assert( i >= 0 && i < numhitboxsets );
		return ( mstudiohitboxset_t * )( ( ( byte * )this ) + hitboxsetindex ) + i;
	};

	// Calls through to hitbox to determine size of specified set
	inline mstudiobbox_t* pHitbox( int i, int set ) const
	{
		mstudiohitboxset_t const* s = pHitboxSet( set );
		if( !s )
			return NULL;

		return s->pHitbox( i );
	};

	// Calls through to set to get hitbox count for set
	inline int iHitboxCount( int set ) const
	{
		mstudiohitboxset_t const* s = pHitboxSet( set );
		if( !s )
			return 0;

		return s->numhitboxes;
	};

	// file local animations? and sequences
	//private:
	int numlocalanim; // animations/poses
	int localanimindex; // animation descriptions
	inline mstudioanimdesc_t* pLocalAnimdesc( int i ) const
	{
		return NULL;
	};

	int numlocalseq; // sequences
	int localseqindex;

	inline mstudioseqdesc_t* pLocalSeqdesc( int i ) const
	{
		return NULL;
	};

	//public:
	bool SequencesAvailable() const
	{
		return true;
	}

	int GetNumSeq() const;
	mstudioanimdesc_t& pAnimdesc( int i ) const;
	mstudioseqdesc_t& pSeqdesc( int i ) const;
	int iRelativeAnim( int baseseq, int relanim ) const; // maps seq local anim reference to global anim index
	int iRelativeSeq( int baseseq, int relseq ) const; // maps seq local seq reference to global seq index

	//private:
	mutable int activitylistversion; // initialization flag - have the sequences been indexed?
	mutable int eventsindexed;
	//public:
	int GetSequenceActivity( int iSequence );
	void SetSequenceActivity( int iSequence, int iActivity );
	int GetActivityListVersion( void );
	void SetActivityListVersion( int version ) const;
	int GetEventListVersion( void );
	void SetEventListVersion( int version );

	// raw textures
	int numtextures;
	int textureindex;

	inline mstudiotexture_t* pTexture( int i ) const
	{
		return NULL;
	};

	// raw textures search paths
	int numcdtextures;
	int cdtextureindex;

	inline char* pCdtexture( int i ) const
	{
		return ( ( ( char * )this ) + *( ( int * )( ( ( byte * )this ) + cdtextureindex ) + i ) );
	};

	// replaceable textures tables
	int numskinref;
	int numskinfamilies;
	int skinindex;

	inline short* pSkinref( int i ) const
	{
		return ( short * )( ( ( byte * )this ) + skinindex ) + i;
	};

	int numbodyparts;
	int bodypartindex;

	inline mstudiobodyparts_t* pBodypart( int i ) const
	{
		return NULL;
	};
};

//-----------------------------------------------------------------------------
// Indicates the type of translucency of an unmodulated renderable
//-----------------------------------------------------------------------------
enum RenderableTranslucencyType_t
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS, // has both translucent and opaque sub-partsa
};

//-----------------------------------------------------------------------------
// Model info interface
//-----------------------------------------------------------------------------

class IVModelInfo
{
public:
	virtual ~IVModelInfo( void )
	{ }

	virtual const model_t* GetModel( int modelindex ) const = 0;
	// Returns index of model by name
	virtual int GetModelIndex( const char* name ) const = 0;
	// Returns name of model
	virtual const char* GetModelName( const model_t* model ) const = 0;
	virtual vcollide_t* GetVCollide( const model_t* model ) const = 0;
	virtual vcollide_t* GetVCollide( int modelindex ) const = 0;
	virtual void GetModelBounds( const model_t* model, Vector& mins, Vector& maxs ) const = 0;
	virtual void GetModelRenderBounds( const model_t* model, Vector& mins, Vector& maxs ) const = 0;
	virtual int GetModelFrameCount( const model_t* model ) const = 0;
	virtual int GetModelType( const model_t* model ) const = 0;
	virtual void* GetModelExtraData( const model_t* model ) = 0;
	virtual bool ModelHasMaterialProxy( const model_t* model ) const = 0;
	virtual bool IsTranslucent( model_t const* model ) const = 0;
	virtual bool IsTranslucentTwoPass( const model_t* model ) const = 0;

	virtual void Unused0()
	{};
	virtual RenderableTranslucencyType_t ComputeTranslucencyType( const model_t* model, int nSkin, int nBody ) = 0;
	virtual int GetModelMaterialCount( const model_t* model ) const = 0;
	virtual void GetModelMaterials( const model_t* model, int count, IMaterial** ppMaterials ) = 0;
	virtual bool IsModelVertexLit( const model_t* model ) const = 0;
	virtual const char* GetModelKeyValueText( const model_t* model ) = 0;
	virtual bool GetModelKeyValue( const model_t* model, CUtlBuffer& buf ) = 0; // supports keyvalue blocks in submodels
	virtual float GetModelRadius( const model_t* model ) = 0;

	virtual const studiohdr_t* FindModel( const studiohdr_t* pStudioHdr, void** cache, const char* modelname ) const = 0;
	virtual const studiohdr_t* FindModel( void* cache ) const = 0;
	virtual virtualmodel_t* GetVirtualModel( const studiohdr_t* pStudioHdr ) const = 0;
	virtual byte* GetAnimBlock( const studiohdr_t* pStudioHdr, int iBlock ) const = 0;
	virtual bool HasAnimBlockBeenPreloaded( studiohdr_t const*, int ) const = 0;

	// Available on client only!!!
	virtual void GetModelMaterialColorAndLighting( const model_t* model, Vector const& origin,
	                                               QAngle const& angles, trace_t* pTrace,
	                                               Vector& lighting, Vector& matColor ) = 0;
	virtual void GetIlluminationPoint( const model_t* model, IClientRenderable* pRenderable, Vector const& origin,
	                                   QAngle const& angles, Vector* pLightingCenter ) = 0;

	virtual int GetModelContents( int modelIndex ) const = 0;
	virtual studiohdr_t* GetStudioModel( const model_t* mod ) = 0;
	virtual int GetModelSpriteWidth( const model_t* model ) const = 0;
	virtual int GetModelSpriteHeight( const model_t* model ) const = 0;

	// Sets/gets a map-specified fade range (client only)
	virtual void SetLevelScreenFadeRange( float flMinSize, float flMaxSize ) = 0;
	virtual void GetLevelScreenFadeRange( float* pMinArea, float* pMaxArea ) const = 0;

	// Sets/gets a map-specified per-view fade range (client only)
	virtual void SetViewScreenFadeRange( float flMinSize, float flMaxSize ) = 0;

	// Computes fade alpha based on distance fade + screen fade (client only)
	virtual unsigned char ComputeLevelScreenFade( const Vector& vecAbsOrigin, float flRadius, float flFadeScale ) const = 0;
	virtual unsigned char ComputeViewScreenFade( const Vector& vecAbsOrigin, float flRadius, float flFadeScale ) const = 0;

	// both client and server
	virtual int GetAutoplayList( const studiohdr_t* pStudioHdr, unsigned short** pAutoplayList ) const = 0;

	// Gets a virtual terrain collision model (creates if necessary)
	// NOTE: This may return NULL if the terrain model cannot be virtualized
	virtual CPhysCollide* GetCollideForVirtualTerrain( int index ) = 0;
	virtual bool IsUsingFBTexture( const model_t* model, int nSkin, int nBody, void /*IClientRenderable*/ * pClientRenderable ) const = 0;
	virtual const model_t* FindOrLoadModel( const char* name ) const = 0;
	virtual MDLHandle_t GetCacheHandle( const model_t* model ) const = 0;
	// Returns planes of non-nodraw brush model surfaces
	virtual int GetBrushModelPlaneCount( const model_t* model ) const = 0;
	virtual void GetBrushModelPlane( const model_t* model, int nIndex, cplane_t& plane, Vector* pOrigin ) const = 0;
	virtual int GetSurfacepropsForVirtualTerrain( int index ) = 0;
	virtual bool UsesEnvCubemap( const model_t* model ) const = 0;
	virtual bool UsesStaticLighting( const model_t* model ) const = 0;
};

class IVModelInfoClient : public IVModelInfo
{
public:
};

struct virtualterrainparams_t
{
	// UNDONE: Add grouping here, specified in BSP file? (test grouping to see if this is necessary)
	int index;
};

#define FCVAR_MATERIAL_THREAD_MASK ( FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD )

struct FileHandle_t;

class KeyValues
{
public:
	//	By default, the KeyValues class uses a string table for the key names that is
	//	limited to 4MB. The game will exit in error if this space is exhausted. In
	//	general this is preferable for game code for performance and memory fragmentation
	//	reasons.
	//
	//	If this is not acceptable, you can use this call to switch to a table that can grow
	//	arbitrarily. This call must be made before any KeyValues objects are allocated or it
	//	will result in undefined behavior. If you use the growable string table, you cannot
	//	share KeyValues pointers directly with any other module. You can serialize them across
	//	module boundaries. These limitations are acceptable in the Steam backend code 
	//	this option was written for, but may not be in other situations. Make sure to
	//	understand the implications before using this.
	static void SetUseGrowableStringTable(bool bUseGrowableTable);

	KeyValues(const char* setName)
	{}

	//
	// AutoDelete class to automatically free the keyvalues.
	// Simply construct it with the keyvalues you allocated and it will free them when falls out of scope.
	// When you decide that keyvalues shouldn't be deleted call Assign(NULL) on it.
	// If you constructed AutoDelete(NULL) you can later assign the keyvalues to be deleted with Assign(pKeyValues).
	// You can also pass temporary KeyValues object as an argument to a function by wrapping it into KeyValues::AutoDelete
	// instance:   call_my_function( KeyValues::AutoDelete( new KeyValues( "test" ) ) )
	//
	class AutoDelete
	{
	public:
		explicit inline AutoDelete(KeyValues* pKeyValues)
			: m_pKeyValues(pKeyValues)
		{}

		explicit inline AutoDelete(const char* pchKVName)
			: m_pKeyValues(new KeyValues(pchKVName))
		{}

		inline ~AutoDelete(void)
		{
			if (m_pKeyValues)
				m_pKeyValues->deleteThis();
		}

		inline void Assign(KeyValues* pKeyValues)
		{
			m_pKeyValues = pKeyValues;
		}

		KeyValues* operator->()
		{
			return m_pKeyValues;
		}

		operator KeyValues *()
		{
			return m_pKeyValues;
		}

	private:
		AutoDelete(AutoDelete const& x); // forbid
		AutoDelete& operator=(AutoDelete const& x); // forbid
		KeyValues* m_pKeyValues;
	};

	// Quick setup constructors
	KeyValues(const char* setName, const char* firstKey, const char* firstValue);
	KeyValues(const char* setName, const char* firstKey, const wchar_t* firstValue);
	KeyValues(const char* setName, const char* firstKey, int firstValue);
	KeyValues(const char* setName, const char* firstKey, const char* firstValue, const char* secondKey, const char* secondValue);
	KeyValues(const char* setName, const char* firstKey, int firstValue, const char* secondKey, int secondValue);

	// Section name
	const char* GetName() const;
	void SetName(const char* setName);

	// gets the name as a unique int
	int GetNameSymbol() const
	{
		return m_iKeyName;
	}

	// File access. Set UsesEscapeSequences true, if resource file/buffer uses Escape Sequences (eg \n, \t)
	void UsesEscapeSequences(bool state); // default false
	void UsesConditionals(bool state); // default true
	bool LoadFromFile(void* filesystem, const char* resourceName, const char* pathID = NULL);
	bool SaveToFile(void* filesystem, const char* resourceName, const char* pathID = NULL, bool sortKeys = false, bool bAllowEmptyString = false);

	// Read from a buffer...  Note that the buffer must be null terminated
	bool LoadFromBuffer(char const* resourceName, const char* pBuffer, void* pFileSystem = NULL, const char* pPathID = NULL);

	// Read from a utlbuffer...
	bool LoadFromBuffer(char const* resourceName, void* buf, void* pFileSystem = NULL, const char* pPathID = NULL);

	// Find a keyValue, create it if it is not found.
	// Set bCreate to true to create the key if it doesn't already exist (which ensures a valid pointer will be returned)
	KeyValues* FindKey(const char* keyName, bool bCreate = false);
	KeyValues* FindKey(int keySymbol) const;
	KeyValues* CreateNewKey(); // creates a new key, with an autogenerated name.  name is guaranteed to be an integer, of value 1 higher than the highest other integer key name
	void AddSubKey(KeyValues* pSubkey); // Adds a subkey. Make sure the subkey isn't a child of some other keyvalues
	void RemoveSubKey(KeyValues* subKey); // removes a subkey from the list, DOES NOT DELETE IT

										  // Key iteration.
										  //
										  // NOTE: GetFirstSubKey/GetNextKey will iterate keys AND values. Use the functions 
										  // below if you want to iterate over just the keys or just the values.
										  //
	KeyValues* GetFirstSubKey()
	{
		return m_pSub;
	} // returns the first subkey in the list
	KeyValues* GetNextKey()
	{
		return m_pPeer;
	} // returns the next subkey
	void SetNextKey(KeyValues* pDat);
	KeyValues* FindLastSubKey(); // returns the LAST subkey in the list.  This requires a linked list iteration to find the key.  Returns NULL if we don't have any children

								 //
								 // These functions can be used to treat it like a true key/values tree instead of 
								 // confusing values with keys.
								 //
								 // So if you wanted to iterate all subkeys, then all values, it would look like this:
								 //     for ( KeyValues *pKey = pRoot->GetFirstTrueSubKey(); pKey; pKey = pKey->GetNextTrueSubKey() )
								 //     {
								 //		   Msg( "Key name: %s\n", pKey->GetName() );
								 //     }
								 //     for ( KeyValues *pValue = pRoot->GetFirstValue(); pKey; pKey = pKey->GetNextValue() )
								 //     {
								 //         Msg( "Int value: %d\n", pValue->GetInt() );  // Assuming pValue->GetDataType() == TYPE_INT...
								 //     }
	KeyValues* GetFirstTrueSubKey();
	KeyValues* GetNextTrueSubKey();

	KeyValues* GetFirstValue(); // When you get a value back, you can use GetX and pass in NULL to get the value.
	KeyValues* GetNextValue();

	// Data access
	int GetInt(const char* keyName = NULL, int defaultValue = 0);
	UINT64 GetUint64(const char* keyName = NULL, UINT64 defaultValue = 0);
	float GetFloat(const char* keyName = NULL, float defaultValue = 0.0f);
	const char* GetString(const char* keyName = NULL, const char* defaultValue = "");
	const wchar_t* GetWString(const char* keyName = NULL, const wchar_t* defaultValue = L"");
	void* GetPtr(const char* keyName = NULL, void* defaultValue = (void*)0);
	bool GetBool(const char* keyName = NULL, bool defaultValue = false);
	int GetColor(const char* keyName = NULL /* default value is all black */);
	bool IsEmpty(const char* keyName = NULL);

	// Data access
	int GetInt(int keySymbol, int defaultValue = 0);
	float GetFloat(int keySymbol, float defaultValue = 0.0f);
	const char* GetString(int keySymbol, const char* defaultValue = "");
	const wchar_t* GetWString(int keySymbol, const wchar_t* defaultValue = L"");
	void* GetPtr(int keySymbol, void* defaultValue = (void*)0);
	int GetColor(int keySymbol /* default value is all black */);
	bool IsEmpty(int keySymbol);

	// Key writing
	void SetWString(const char* keyName, const wchar_t* value);
	void SetString(const char* keyName, const char* value);
	void SetInt(const char* keyName, int value);
	void SetUint64(const char* keyName, UINT64 value);
	void SetFloat(const char* keyName, float value);
	void SetPtr(const char* keyName, void* value);
	void SetColor(const char* keyName, int value);

	void SetBool(const char* keyName, bool value)
	{
		SetInt(keyName, value ? 1 : 0);
	}

	// Adds a chain... if we don't find stuff in this keyvalue, we'll look
	// in the one we're chained to.
	void ChainKeyValue(KeyValues* pChain);

	void RecursiveSaveToFile(void* buf, int indentLevel, bool sortKeys = false, bool bAllowEmptyString = false);

	bool WriteAsBinary(void* buffer);
	bool ReadAsBinary(void* buffer, int nStackDepth = 0);

	// Allocate & create a new copy of the keys
	KeyValues* MakeCopy(void) const;

	// Make a new copy of all subkeys, add them all to the passed-in keyvalues
	void CopySubkeys(KeyValues* pParent) const;

	// Clear out all subkeys, and the current value
	void Clear(void);

	// Data type
	enum types_t
	{
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_NUMTYPES,
	};

	types_t GetDataType(const char* keyName = NULL);

	// Virtual deletion function - ensures that KeyValues object is deleted from correct heap
	void deleteThis();

	void SetStringValue(char const* strValue);

	// unpack a key values list into a structure
	void UnpackIntoStructure(struct KeyValuesUnpackStructure const* pUnpackTable, void* pDest, size_t DestSizeInBytes);

	// Process conditional keys for widescreen support.
	bool ProcessResolutionKeys(const char* pResString);

	// Dump keyvalues recursively into a dump context
	bool Dump(class IKeyValuesDumpContext* pDump, int nIndentLevel = 0);

	// Merge in another KeyValues, keeping "our" settings
	void RecursiveMergeKeyValues(KeyValues* baseKV);

private:
	KeyValues(KeyValues&); // prevent copy constructor being used

						   // prevent delete being called except through deleteThis()
	~KeyValues();

	KeyValues* CreateKey(const char* keyName);

	/// Create a child key, given that we know which child is currently the last child.
	/// This avoids the O(N^2) behaviour when adding children in sequence to KV,
	/// when CreateKey() wil have to re-locate the end of the list each time.  This happens,
	/// for example, every time we load any KV file whatsoever.
	KeyValues* CreateKeyUsingKnownLastChild(const char* keyName, KeyValues* pLastChild);
	void AddSubkeyUsingKnownLastChild(KeyValues* pSubKey, KeyValues* pLastChild);

	void RecursiveCopyKeyValues(KeyValues& src);
	void RemoveEverything();
	//	void RecursiveSaveToFile( IBaseFileSystem *filesystem, void*buffer, int indentLevel );
	//	void WriteConvertedString( void*buffer, const char *pszString );

	// NOTE: If both filesystem and pBuf are non-null, it'll save to both of them.
	// If filesystem is null, it'll ignore f.
	void RecursiveSaveToFile(void* filesystem, FileHandle_t f, void* pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void SaveKeyToFile(KeyValues* dat, void* filesystem, FileHandle_t f, void* pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void WriteConvertedString(void* filesystem, FileHandle_t f, void* pBuf, const char* pszString);

	void RecursiveLoadFromBuffer(char const* resourceName, void* buf);

	// For handling #include "filename"
	void AppendIncludedKeys(void* includedKeys);
	void ParseIncludedKeys(char const* resourceName, const char* filetoinclude,
		void* pFileSystem, const char* pPathID, void* includedKeys);

	// For handling #base "filename"
	void MergeBaseKeys(void* baseKeys);

	// NOTE: If both filesystem and pBuf are non-null, it'll save to both of them.
	// If filesystem is null, it'll ignore f.
	void InternalWrite(void* filesystem, FileHandle_t f, void* pBuf, const void* pData, int len);

	void Init();
	const char* ReadToken(void* buf, bool& wasQuoted, bool& wasConditional);
	void WriteIndents(void* filesystem, FileHandle_t f, void* pBuf, int indentLevel);

	void FreeAllocatedValue();
	void AllocateValueBlock(int size);

	int m_iKeyName; // keyname is a symbol defined in KeyValuesSystem

					// These are needed out of the union because the API returns string pointers
	char* m_sValue;
	wchar_t* m_wsValue;

	// we don't delete these
	union
	{
		int m_iValue;
		float m_flValue;
		void* m_pValue;
		unsigned char m_Color[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences; // true, if while parsing this KeyValue, Escape Sequences are used (default false)
	char m_bEvaluateConditionals; // true, if while parsing this KeyValue, conditionals blocks are evaluated (default true)
	char unused[1];

	KeyValues* m_pPeer; // pointer to next key in list
	KeyValues* m_pSub; // pointer to Start of a new sub key list
	KeyValues* m_pChain;// Search here if it's not in our list

private:
	// Statics to implement the optional growable string table
	// Function pointers that will determine which mode we are in
	static int(*s_pfGetSymbolForString)(const char* name, bool bCreate);
	static const char*(*s_pfGetStringForSymbol)(int symbol);
	static void* s_pGrowableStringTable;

public:
	// Functions that invoke the default behavior
	static int GetSymbolForStringClassic(const char* name, bool bCreate = true);
	static const char* GetStringForSymbolClassic(int symbol);

	// Functions that use the growable string table
	static int GetSymbolForStringGrowable(const char* name, bool bCreate = true);
	static const char* GetStringForSymbolGrowable(int symbol);

	// Functions to get external access to whichever of the above functions we're going to call.
	static int CallGetSymbolForString(const char* name, bool bCreate = true)
	{
		return s_pfGetSymbolForString(name, bCreate);
	}

	static const char* CallGetStringForSymbol(int symbol)
	{
		return s_pfGetStringForSymbol(symbol);
	}
};

