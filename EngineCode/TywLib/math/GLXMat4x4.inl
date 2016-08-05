#ifndef _GLX_MAT4X4_MATH_INLINE_H_
#define _GLX_MAT4X4_MATH_INLINE_H_

#include "GLXVec3.h"
#include "GLXMat4x4.h"


/*
Supports only floats
resets do identity matrix
*/
template<class T>
inline void glx::mat4<T>::Clear()
{
	m[0][0] = m[1][1] = m[3][3] = T(1);

	m[0][1] = m[0][2] = m[0][3] =
	m[1][0] = m[1][2] = m[1][3] =
	m[2][0] = m[2][1] = m[2][3] =
	m[3][0] = m[3][1] = m[3][2] = T(0);
}

template<class T>
inline glx::mat4<T>::mat4(T m11, T m21, T m31, T m41,
	T m12, T m22, T m32, T m42,
	T m13, T m23, T m33, T m43,
	T m14, T m24, T m34, T m44)
{

	_11 = m11; _21 = m21; _31 = m31; _41 = m41;
	_12 = m12; _22 = m22; _32 = m32; _42 = m42;
	_13 = m13; _23 = m23; _33 = m33; _43 = m43;
	_14 = m14; _24 = m24; _34 = m34; _44 = m44;
}


template<class T>
inline glx::mat4<T>::mat4(glx::mat4<T>& mat)
{
	std::memcpy(&_11, &mat, sizeof(glx::mat4<T>));
}

template<class T>
inline glx::mat4<T>::mat4(const T* pF)
{
	if (!pF)return;
	std::memcpy(&_11, pF, sizeof(glx::mat4<T>));
}

//acces grants
template<class T>
inline T& glx::mat4<T>::operator () (unsigned int row, unsigned int col)
{
	return m[row][col];
}

template<class T>
inline T glx::mat4<T>::operator () (unsigned int row, unsigned int col)const
{
	return m[row][col];
}

//casting operators

template<class T>
inline glx::mat4<T>::operator float* ()
{
	return (float*)&_11;
}

template<class T>
inline glx::mat4<T>::operator const float* () const
{
	return (const float*)&_11;
}


//assignement operators
template<class T>
inline glx::mat4<T>& glx::mat4<T>::operator *= (const glx::mat4<T>& mat)
{
	//wrooooooong. Do you eve math microsoft?
	//GLXMatrixMultiply(this, this, &mat);
	return *this;
}

template<class T>
inline glx::mat4<T>& glx::mat4<T>::operator += (const glx::mat4<T>& mat)
{
	_11 += mat._11; _12 += mat._12; _13 += mat._13; _14 += mat._14;
	_21 += mat._21; _22 += mat._22; _23 += mat._23; _24 += mat._24;
	_31 += mat._31; _32 += mat._32; _33 += mat._33; _34 += mat._34;
	_41 += mat._41; _42 += mat._42; _43 += mat._43; _44 += mat._44;
	return *this;
}

template<class T>
inline glx::mat4<T>& glx::mat4<T>::operator -= (const glx::mat4<T>& mat)
{
	_11 -= mat._11; _12 -= mat._12; _13 -= mat._13; _14 -= mat._14;
	_21 -= mat._21; _22 -= mat._22; _23 -= mat._23; _24 -= mat._24;
	_31 -= mat._31; _32 -= mat._32; _33 -= mat._33; _34 -= mat._34;
	_41 -= mat._41; _42 -= mat._42; _43 -= mat._43; _44 -= mat._44;
	return *this;
}

template<class T>
inline glx::mat4<T>& glx::mat4<T>::operator *= (T f)
{
	_11 *= f; _12 *= f; _13 *= f; _14 *= f;
	_21 *= f; _22 *= f; _23 *= f; _24 *= f;
	_31 *= f; _32 *= f; _33 *= f; _34 *= f;
	_41 *= f; _42 *= f; _43 *= f; _44 *= f;
	return *this;
}

template<class T>
inline glx::mat4<T>& glx::mat4<T>::operator /= (T f)
{
	_11 /= f; _12 /= f; _13 /= f; _14 /= f;
	_21 /= f; _22 /= f; _23 /= f; _24 /= f;
	_31 /= f; _32 /= f; _33 /= f; _34 /= f;
	_41 /= f; _42 /= f; _43 /= f; _44 /= f;
	return *this;
}

template<class T>
inline glx::mat4<T>& glx::mat4<T>::operator  = (const mat4<T>& mat)
{
	_11 = mat._11; _12 = mat._12; _13 = mat._13; _14 = mat._14;
	_21 = mat._21; _22 = mat._22; _23 = mat._23; _24 = mat._24;
	_31 = mat._31; _32 = mat._32; _33 = mat._33; _34 = mat._34;
	_41 = mat._41; _42 = mat._42; _43 = mat._43; _44 = mat._44;
	return *this;
}


//unary operators
template<class T>
inline glx::mat4<T> glx::mat4<T>::operator + () const
{
	return *this;
}

template<class T>
inline glx::mat4<T> glx::mat4<T>::operator - () const
{
	return glx::mat4<T>(-_11, -_12, -_13, -_14,
		-_21, -_22, -_23, -_24,
		-_31, -_32, -_33, -_34,
		-_41, -_42, -_43, -_44);
}

//binary operators
template<class T>
inline glx::mat4<T> glx::mat4<T>::operator * (const glx::mat4<T>& mat) const
{
	glx::mat4<T> buf;
	GLXMatrixMultiply(&buf, this, &mat);
	return buf;
}

template<class T>
inline glx::mat4<T> glx::mat4<T>::operator + (const glx::mat4<T>& mat) const
{
	return glx::mat4<T>(_11 + mat._11, _12 + mat._12, _13 + mat._13, _14 + mat._14,
		_21 + mat._21, _22 + mat._22, _23 + mat._23, _24 + mat._24,
		_31 + mat._31, _32 + mat._32, _33 + mat._33, _34 + mat._34,
		_41 + mat._41, _42 + mat._42, _43 + mat._43, _44 + mat._44);
}

template<class T>
inline glx::mat4<T> glx::mat4<T>::operator - (const glx::mat4<T>& mat) const
{
	return glx::mat4<T>(_11 - mat._11, _12 - mat._12, _13 - mat._13, _14 - mat._14,
		_21 - mat._21, _22 - mat._22, _23 - mat._23, _24 - mat._24,
		_31 - mat._31, _32 - mat._32, _33 - mat._33, _34 - mat._34,
		_41 - mat._41, _42 - mat._42, _43 - mat._43, _44 - mat._44);
}

template<class T>
inline glx::mat4<T> glx::mat4<T>::operator * (T f) const
{
	return glx::mat4<T>(
		_11 * f, _12 * f, _13 * f, _14 * f,
		_21 * f, _22 * f, _23 * f, _24 * f,
		_31 * f, _32 * f, _33 * f, _34 * f,
		_41 * f, _42 * f, _43 * f, _44 * f);
}

template<class T>
inline glx::mat4<T> glx::mat4<T>::operator / (T f) const
{
	return glx::mat4<T>(
		_11 / f, _12 / f, _13 / f, _14 / f,
		_21 / f, _22 / f, _23 / f, _24 / f,
		_31 / f, _32 / f, _33 / f, _34 / f,
		_41 / f, _42 / f, _43 / f, _44 / f);
}

template<class T>
inline glx::mat4<T> operator * (T f, const glx::mat4<T>& mat)
{
	return glx::mat4<T>(f * mat._11, f * mat._12, f * mat._13, f * mat._14,
		f * mat._21, f * mat._22, f * mat._23, f * mat._24,
		f * mat._31, f * mat._32, f * mat._33, f * mat._34,
		f * mat._41, f * mat._42, f * mat._43, f * mat._44);
}

template<class T>
inline bool glx::mat4<T>::operator == (const glx::mat4<T>& mat) const
{
	return (std::memcpy(this, &mat, sizeof(glx::mat4<T>)) == 0);
}

template<class T>
inline bool glx::mat4<T>::operator != (const glx::mat4<T>& mat) const
{
	return (std::memcpy(this, &mat, sizeof(glx::mat4<T>)) != 0);
}


//Setters

template<class T>
inline void glx::mat4<T>::SetPosition(const glx::vec3<T> &vec)
{
	_41 = vec.x;
	_42 = vec.y;
	_43 = vec.z;
}

template<class T>
inline void glx::mat4<T>::SetPosition(const glx::vec4<T> &vec)
{
	_41 = vec.x;
	_42 = vec.y;
	_43 = vec.z;
	_44 = vec.w;
}

template<class T>
inline void glx::mat4<T>::SetScale(const glx::vec3<T> &vec)
{
	_11 = vec.x;
	_22 = vec.y;
	_33 = vec.z;
}


template<class T>
inline void glx::mat4<T>::SetRotation(const glx::mat4<T> & m)
{
	_11 = m.m[0][0];
	_12 = m.m[1][0];
	_13 = m.m[2][0];
	_21 = m.m[0][1];
	_22 = m.m[1][1];
	_23 = m.m[2][1];
	_31 = m.m[0][2];
	_32 = m.m[1][2];
	_33 = m.m[2][2];
}

//Getters

template<class T>
inline glx::vec3<T> glx::mat4<T>::GetPosition() const
{
	return glx::vec3<T>(_41, _42, _43);
}

template<class T>
inline glx::vec3<T> glx::mat4<T>::GetScale() const
{
	return glx::vec3<T>(_11, _22, _33);
}

template<class T>
inline glx::vec3<T> glx::mat4<T>::GetDirection() const
{
	// Note - the following code can be used to double check the vector construction above.
	glx::mat4<T> justRot = *this;
	//justRot.SetPosition(Vec3(0.f, 0.f, 0.f));

	//Vec3 forward = justRot.Xform(g_Forward);
	return justRot;
}

#endif