#ifndef _GLX_MATH_VEC3_H_
#define _GLX_MATH_VEC3_H_

//forward declared
class JointMat;

namespace glx
{
	template<class T>
	class vec3
	{
	public:
		T x, y, z;

	public:
		vec3();
		vec3(const T *);
		vec3(const vec3<T>&);
		vec3(T x, T y, T z);
		//GLXVECTOR3(const GLXFLOAT16 *);

		// casting
		operator float*();
		operator const float* () const;

		// assignment operators
		vec3<T>& operator += (const vec3<T>&);
		vec3<T>& operator -= (const vec3<T>&);
		vec3<T>& operator *= (T);
		vec3<T>& operator /= (T);
		vec3<T>& operator =  (const vec3<T>&);

		// unary operators
		vec3<T> operator + () const;
		vec3<T> operator - () const;

		// binary operators
		vec3<T> operator + (const vec3<T>&) const;
		vec3<T> operator - (const vec3<T>&) const;
		vec3<T> operator * (T) const;
		vec3<T> operator / (T) const;

		friend vec3<T> operator * (T rhs, const  vec3<T>& lhs)
		{
			return glx::vec3<T>(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
		}

		bool operator == (const vec3<T>&) const;
		bool operator != (const vec3<T>&) const;


		//Resets to 0,0,0
		void Clear();
	};
}
#include "GLXVec3.inl"
#endif