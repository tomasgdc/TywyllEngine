#ifndef _GLX_MATH_VEC4_H_
#define _GLX_MATH_VEC4_H_

namespace glx
{
	template<class T>
	class vec4
	{
	public:
		T x, y, z, w;

	public:
		vec4() {};
		vec4(const T*);
		vec4(const vec3<T>& xyz, T w);
		vec4(T x, T y, T z, T w);

		// casting
		operator float* ();
		operator const float* () const;

		// assignment operators
		vec4<T>& operator += (const vec4<T>&);
		vec4<T>& operator -= (const vec4<T>&);
		vec4<T>& operator *= (T);
		vec4<T>& operator /= (T);
		vec4<T>& operator  = (const vec4<T>&);

		// unary operators
		vec4<T> operator + () const;
		vec4<T> operator - () const;

		// binary operators
		vec4<T> operator + (const vec4<T>&) const;
		vec4<T> operator - (const vec4<T>&) const;
		vec4<T> operator * (T) const;
		vec4<T> operator / (T) const;

		friend vec4<T> operator * (T, const vec4<T>&);

		bool operator == (const vec4<T>&) const;
		bool operator != (const vec4<T>&) const;

		//Resets to 0,0,0,0
		void Clear();
	};
}

#include "GLXVec4.inl"
#endif
