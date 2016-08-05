#ifndef _GLX_MATH_QUAT_H_
#define _GLX_MATH_QUAT_H_


namespace glx
{
	class quat
	{
	public:
		float x, y, z, w;

	public:
		quat() {}
		quat(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		quat(float _x, float _y, float _z, float _w) :x(_x), y(_y), z(_z), w(_w) {}
		void CalcW();

		quat& Slerp(const quat &from, const quat &to, float t);
		mat4<float> ToMat4() const;

		// assignment operators
		quat& operator += (const quat&);
		quat& operator -= (const quat&);
		quat& operator *= (const quat&);
		quat& operator =  (const quat&);

		// unary operators
		quat operator + () const;
		quat operator - () const;

		// binary operators
		quat operator + (const quat&) const;
		quat operator - (const quat&) const;

		quat operator * ( const quat&) const;
		quat operator * (float) const;

		quat operator / (float) const;
		

		bool operator == (const quat&) const;
		bool operator != (const quat&) const;


		friend quat operator * (const float rhs, const quat& lhs){ return quat(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }
	};
}

#include "GLXQuat.inl"
#endif
