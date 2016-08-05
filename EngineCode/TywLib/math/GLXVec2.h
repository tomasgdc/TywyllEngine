#ifndef _GLX_MATH_VEC2_H_
#define _GLX_MATH_VEC2_H_

namespace glx
{
	template<class T>
	class vec2
	{
	public:
		T x, y;

	public:
		vec2() {};
		vec2(const T* p);
		vec2(T _x, T _y);
		//GLXVECTOR2(const GLXFLOAT16 *);

		// casting
		operator float* ();
		operator const float* () const;

		// assignment operators
		vec2<T>& operator += (const vec2<T>&);
		vec2<T>& operator -= (const vec2<T>&);
		vec2<T>& operator *= (T);
		vec2<T>& operator /= (T);
		vec2<T>& operator  = (const vec2<T>&);

		// unary operators
		vec2<T> operator + () const;
		vec2<T> operator - () const;

		// binary operators
		vec2<T> operator + (const vec2<T>&) const;
		vec2<T> operator - (const vec2<T>&) const;
		vec2<T> operator * (T) const;
		vec2<T> operator / (T) const;

		friend vec2<T> operator * (T, const vec2<T>&);

		bool operator == (const vec2<T>&) const;
		bool operator != (const vec2<T>&) const;

		//Resets to 0,0,0
		void Clear();
	};
}

#include "GLXVec2.inl"
#endif
