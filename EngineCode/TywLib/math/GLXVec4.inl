#ifndef _GLX_VEC4_MATH_INL_H_
#define _GLX_VEC4_MATH_INL_H_


/*
Sets vector to 0, 0, 0, 0
*/
template<class T>
inline void glx::vec4<T>::Clear()
{
	x = y = z = w = T(0);
}


template<class T>
inline glx::vec4<T>::vec4(const T * pf)
{

	if (!pf)return;

	x = pf[0];
	y = pf[1];
	z = pf[2];
	w = pf[3];
}

template<class T>
inline glx::vec4<T>::vec4(const vec3<T>& xyz, T w)
{
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	w = w;
}

template<class T>
inline glx::vec4<T>::vec4(T x, T y, T z, T w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

// casting
template<class T>
inline glx::vec4<T>::operator float*()
{
	return (float *)&x;
}

template<class T>
inline glx::vec4<T>::operator const float* () const
{
	return (const float*)&x;
}


// assignment operators
template<class T>
inline glx::vec4<T>& glx::vec4<T>::operator += (const glx::vec4<T>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

template<class T>
inline glx::vec4<T>& glx::vec4<T>::operator -= (const glx::vec4<T>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

template<class T>
inline glx::vec4<T>& glx::vec4<T>::operator *= (T f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

template<class T>
inline glx::vec4<T>& glx::vec4<T>::operator /= (T f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;
	return *this;
}

template<class T>
inline glx::vec4<T>& glx::vec4<T>::operator  = (const vec4<T>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}


// unary operators
template<class T>
inline glx::vec4<T> glx::vec4<T>::operator + () const
{
	return *this;
}

template<class T>
inline glx::vec4<T> glx::vec4<T>::operator - () const
{
	return glx::vec4<T>(-x, -y, -z, -w);
}

// binary operators
template<class T>
inline glx::vec4<T> glx::vec4<T>::operator + (const glx::vec4<T>& v) const
{
	return glx::vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
}

template<class T>
inline glx::vec4<T> glx::vec4<T>::operator - (const glx::vec4<T>& v) const
{
	return glx::vec4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
}

template<class T>
inline glx::vec4<T> glx::vec4<T>::operator * (T f) const
{
	return glx::vec4<T>(f * x, f *y, f * z, f * w);
}

template<class T>
inline glx::vec4<T> glx::vec4<T>::operator / (T f) const
{
	return glx::vec4<T>(x / f, y / f, z / f, w / f);
}

template<class T>
inline glx::vec4<T> operator * (T s, const struct glx::vec4<T>&)
{

}

template<class T>
inline bool glx::vec4<T>::operator == (const glx::vec4<T>& v) const
{
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

template<class T>
inline bool glx::vec4<T>::operator != (const glx::vec4<T>& v) const
{
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

#endif
