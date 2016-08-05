#ifndef _GLX_MATH_INL_H_
#define _GLX_MATH_INL_H_


inline float glx::Math::InvSqrt(float x)
{
	return (x > FLT_SMALLEST_NON_DENORMAL) ? sqrtf(1.0f / x) : INFINITY;
}
#endif
