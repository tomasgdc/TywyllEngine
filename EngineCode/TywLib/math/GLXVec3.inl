#ifndef _GLX_VEC3_MATH_INLINE_H_
#define _GLX_VEC3_MATH_INLINE_H_




/*
Sets vector to 0, 0, 0
*/
template<class T>
inline void glx::vec3<T>::Clear()
{
	x = y = z = T(0);
}


template<class T>
inline glx::vec3<T>::vec3()
{

}

template<class T>
inline glx::vec3<T>::vec3(const T * pf)
{

	if (!pf)return;

	x = pf[0];
	y = pf[1];
	z = pf[2];
}



template<class T>
inline glx::vec3<T>::vec3(const glx::vec3<T>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

template<class T>
inline glx::vec3<T>::vec3(T fx, T fy, T fz)
{
	x = fx;
	y = fy;
	z = fz;
}

// casting
template<class T>
inline glx::vec3<T>::operator float*()
{
	return (float *)&x;
}

template<class T>
inline glx::vec3<T>::operator const float* () const
{
	return (const float*)&x;
}


// assignment operators
template<class T>
inline glx::vec3<T>& glx::vec3<T>::operator += (const glx::vec3<T>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

template<class T>
inline glx::vec3<T>& glx::vec3<T>::operator -= (const glx::vec3<T>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

template<class T>
inline glx::vec3<T>& glx::vec3<T>::operator *= (T f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

template<class T>
inline glx::vec3<T>& glx::vec3<T>::operator /= (T f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

template<class T>
inline glx::vec3<T>& glx::vec3<T>::operator =  (const vec3<T>& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

// unary operators
template<class T>
inline glx::vec3<T> glx::vec3<T>::operator + () const
{
	return *this;
}

template<class T>
inline glx::vec3<T> glx::vec3<T>::operator - () const
{
	return glx::vec3<T>(-x, -y, -z);
}

// binary operators
template<class T>
inline glx::vec3<T> glx::vec3<T>::operator + (const glx::vec3<T>& v) const
{
	return glx::vec3<T>(x + v.x, y + v.y, z + v.z);
}



template<class T>
inline glx::vec3<T> glx::vec3<T>::operator - (const glx::vec3<T>& v) const
{
	return glx::vec3<T>(x - v.x, y - v.y, z - v.z);
}

template<class T>
inline glx::vec3<T> glx::vec3<T>::operator * (T f) const
{
	return glx::vec3<T>(f * x, f *y, f * z);
}


template<class T>
inline glx::vec3<T> glx::vec3<T>::operator / (T f) const
{
	return glx::vec3<T>(x / f, y / f, z / f);
}


template<class T>
inline bool glx::vec3<T>::operator == (const glx::vec3<T>& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

template<class T>
inline bool glx::vec3<T>::operator != (const glx::vec3<T>& v) const
{
	return x != v.x || y != v.y || z != v.z;
}


#endif
