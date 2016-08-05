#ifndef _GLX_MATH_QUAT_INL_H_
#define _GLX_MATH_QUAT_INL_H_



inline glx::quat& glx::quat::operator += (const quat& q)
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;

	return *this;
}

inline glx::quat& glx::quat::operator -= (const quat& q)
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;

	return *this;
}

inline glx::quat&  glx::quat::operator *= (const quat& q)
{
	return *this = *this * q;
}

inline glx::quat& glx::quat::operator =  (const quat& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
	return *this;
}

inline glx::quat  glx::quat::operator + () const
{
	return *this;
}

inline glx::quat  glx::quat::operator - () const
{
	return glx::quat(-x, -y, -z, -w);
}

inline bool  glx::quat::operator == (const glx::quat& q) const
{
	return x == q.x && y == q.y && z == q.z && w == q.w;
}

inline bool glx::quat::operator != (const glx::quat& q) const
{
	return x != q.x || y != q.y || z != q.z || w != q.w;
}

inline glx::quat glx::quat::operator + (const glx::quat& q) const
{
	return glx::quat(x + q.x, y + q.y, z + q.z, w + q.w);
}


inline glx::quat glx::quat::operator - (const glx::quat& q) const
{
	return glx::quat(x - q.x, y - q.y, z - q.z, w - q.w);
}


inline glx::quat glx::quat::operator * (float f) const
{
	return glx::quat(x * f, y * f, z * f, w * f);
}

inline glx::quat glx::quat::operator * ( const glx::quat& q) const
{
	return glx::quat(w*q.x + x*q.w + y*q.z - z*q.y,
					w*q.y + y*q.w + z*q.x - x*q.z,
					w*q.z + z*q.w + x*q.y - y*q.x,
					w*q.w - x*q.x - y*q.y - z*q.z);
}

inline glx::quat glx::quat::operator / (float f) const
{
	return glx::quat(x / f, y / f, z / f, w / f);
}
#endif