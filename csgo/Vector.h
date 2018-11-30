#pragma once

#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )

class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	__forceinline Vector& operator+=(const Vector& v);
	__forceinline Vector& operator-=(const Vector& v);
	__forceinline Vector& operator*=(const Vector& v);
	__forceinline Vector& operator*=(float s);
	__forceinline Vector& operator/=(const Vector& v);
	__forceinline Vector& operator/=(float s);
	__forceinline Vector& operator+=(float fl);
	__forceinline Vector& operator-=(float fl);
	inline float Length() const;

	__forceinline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (this->x * this->x + this->y * this->y + this->z * this->z);
	}

	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	float NormalizeInPlace();
	Vector Normalize();
	__forceinline float DistToSqr(const Vector& vOther) const;
	__forceinline float Dist(const Vector& vOther) const;
	float Dot(const Vector& vOther) const;
	float Dot(const float* fOther) const;
	float Length2D(void) const;
	float Length2DSqr(void) const;
	Vector& operator=(const Vector& vOther);
	Vector operator-(const Vector& v) const;
	Vector operator+(const Vector& v) const;
	Vector operator*(const Vector& v) const;
	void Vector::Rotate2D(const float &f);
	Vector operator/(const Vector& v) const;
	Vector operator*(float fl) const;
	Vector operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
	CHECK_VALID(*this);
}

struct Vector2D
{
public:
	float x, y;

	Vector2D()
	{}

	Vector2D(float x_, float y_)
	{
		x = x_;
		y = y_;
	}
};

void inline SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

inline void Vector::Rotate2D(const float &f)
{
	float _x, _y;

	float s, c;

	SinCos(DEG2RAD(f), &s, &c);

	_x = x;
	_y = y;

	x = (_x * c) - (_y * s);
	y = (_x * s) + (_y * c);
}

//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	CHECK_VALID(*this);
}

inline float Vector::Length2D(void) const { return (float)sqrtf(x*x + y * y); }

//===============================================
inline Vector::Vector(void)
{ }

//===============================================
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}

//===============================================
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}

//===============================================
inline Vector& Vector::operator=(const Vector& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x;
	y = vOther.y;
	z = vOther.z;
	return *this;
}

//===============================================
inline float& Vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//===============================================
inline float Vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//===============================================
inline bool Vector::operator==(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//===============================================
__forceinline void VectorCopy(const Vector& src, Vector& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

//===============================================
__forceinline Vector& Vector::operator+=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator-=(const Vector& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator*=(const Vector& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

//===============================================
__forceinline Vector& Vector::operator/=(const Vector& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}

//===============================================
inline float Vector::Length(void) const
{
	return (x * x + y * y);
}

//===============================================
inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

//===============================================
float Vector::DistToSqr(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}

float Vector::Dist(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}

inline Vector Vector::Normalize()
{
	Vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
		vector.x = vector.y = 0.0f;
	vector.z = 1.0f;

	return vector;
}

//===============================================
inline float Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
}

//===============================================
inline float VectorNormalize(Vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
		v.z = 1.0f;
	}
	return l;
}

//===============================================
FORCEINLINE float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast< Vector * >(v)));
}

//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

//===============================================
inline Vector Vector::operator*(float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

//===============================================
inline Vector Vector::operator/(float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return (a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

inline float Vector::Dot(const float* fOther) const
{
	const Vector& a = *this;

	return (a.x * fOther[0] + a.y * fOther[1] + a.z * fOther[2]);
}

inline float* Vector::Base()
{
	return (float*)this;
}

inline float const* Vector::Base() const
{
	return (float const*)this;
}

class QAngleByValue;

class QAngle
{
public:
	float x, y, z;

	QAngle(void);
	QAngle(float X, float Y, float Z);

	operator QAngleByValue &()
	{
		return *((QAngleByValue *)(this));
	}

	operator const QAngleByValue &() const
	{
		return *((const QAngleByValue *)(this));
	}

	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void Random(float minVal, float maxVal);

	bool IsValid() const;
	void Invalidate();

	bool IsZero()
	{
		CHECK_VALID(*this);
		if (this->x == 0.f && this->y == 0.f && this->z == 0.f)
			return true;

		return false;
	}

	float operator[](int i) const;
	float& operator[](int i);

	float* Base();
	float const* Base() const;

	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	QAngle& operator+=(const QAngle& v);
	QAngle& operator-=(const QAngle& v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	float Length() const;
	float LengthSqr() const;

	QAngle& operator=(const QAngle& src);

	QAngle operator-(void) const;

	QAngle operator+(const QAngle& v) const;
	QAngle operator-(const QAngle& v) const;
	QAngle operator*(float fl) const;
	QAngle operator/(float fl) const;

	QAngle Clamp();
	QAngle Mod(float N);

	inline QAngle QAngle::Normalize()
	{
		QAngle vector;
		float length = this->Length();

		if (length != 0)
		{
			vector.x = x / length;
			vector.y = y / length;
			vector.z = z / length;
		}
		else
			vector.x = vector.y = 0.0f;
		vector.z = 1.0f;

		return vector;
	}

	QAngle Normalized()
	{
		if (this->x != this->x)
			this->x = 0;
		if (this->y != this->y)
			this->y = 0;
		if (this->z != this->z)
			this->z = 0;

		if (this->x > 89.f)
			this->x = 89.f;
		if (this->x < -89.f)
			this->x = -89.f;

		while (this->y > 180)
			this->y -= 360;
		while (this->y <= -180)
			this->y += 360;

		if (this->y > 180.f)
			this->y = 180.f;
		if (this->y < -180.f)
			this->y = -180.f;

		this->z = 0;

		return *this;
	}
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = float_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
	x = ix;
	y = iy;
	z = iz;
	CHECK_VALID(*this);
}

inline void QAngle::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	CHECK_VALID(*this);
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x;
	y = vOther.y;
	z = vOther.z;
	return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
	CHECK_VALID(*this);
	return (float)sqrt(LengthSqr()); //todo replace with fastsqrt
}

inline float QAngle::LengthSqr() const
{
	CHECK_VALID(*this);
	return x * x + y * y;
}

inline QAngle QAngle::operator-(void) const
{
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator*(float fl) const
{
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle QAngle::Clamp()
{
	CHECK_VALID(*this);

	if (this->x < -89.0f)
		this->x = -89.0f;

	if (this->x > 89.0f)
		this->x = 89.0f;

	while (this->y < -180.0f)
		this->y += 360.0f;

	while (this->y > 180.0f)
		this->y -= 360.0f;

	this->z = 0.0f;

	return *this;
}

inline QAngle QAngle::Mod(float N)
{
	CHECK_VALID(*this);
	this->x = fmod(x, N);
	this->y = fmod(y, N);
	this->z = fmod(z, N);

	return *this;
}

class CUserCmd
{
public:
	virtual ~CUserCmd()
	{ };
	int command_number;
	int tick_count;
	QAngle viewangles;
	Vector aimdirection;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	byte impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	char pad_0x4C[0x18];
};

struct VMatrix
{
	float m[4][4];

	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}
};

struct matrix3x3_t
{
	float m_flMatVal[3][3];
};

struct matrix3x4_t
{
	matrix3x4_t()
	{}

	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;
		m_flMatVal[0][1] = m01;
		m_flMatVal[0][2] = m02;
		m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;
		m_flMatVal[1][1] = m11;
		m_flMatVal[1][2] = m12;
		m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;
		m_flMatVal[2][1] = m21;
		m_flMatVal[2][2] = m22;
		m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x;
		m_flMatVal[0][1] = yAxis.x;
		m_flMatVal[0][2] = zAxis.x;
		m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y;
		m_flMatVal[1][1] = yAxis.y;
		m_flMatVal[1][2] = zAxis.y;
		m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z;
		m_flMatVal[2][1] = yAxis.z;
		m_flMatVal[2][2] = zAxis.z;
		m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void SetOrigin(Vector const& p)
	{
		m_flMatVal[0][3] = p.x;
		m_flMatVal[1][3] = p.y;
		m_flMatVal[2][3] = p.z;
	}

	inline float BitsToFloat(INT32 i)
	{
		union Convertor_t
		{
			float f;
			unsigned long ul;
		} tmp;
		tmp.ul = i;
		return tmp.f;
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = BitsToFloat((INT32)0x7FC00000);
			}
		}
	}

	float* operator[](int i)
	{
		Assert((i >= 0) && (i < 3));
		return m_flMatVal[i];
	}

	const float* operator[](int i) const
	{
		Assert((i >= 0) && (i < 3));
		return m_flMatVal[i];
	}

	float* Base()
	{
		return &m_flMatVal[0][0];
	}

	const float* Base() const
	{
		return &m_flMatVal[0][0];
	}

	float m_flMatVal[3][4];
};