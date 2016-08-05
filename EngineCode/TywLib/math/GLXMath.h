/* ============================================================================
* Tywyl Engine
* Platform:      Windows
* WWW:
* ----------------------------------------------------------------------------
* Copyright 2015 Tomas Mikalauskas. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY TOMAS MIKALAUSKAS ''AS IS'' AND ANY EXPRESS OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
* EVENT SHALL TOMAS MIKALAUSKAS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are
* those of the authors and should not be interpreted as representing official
* policies, either expressed or implied, of Tomas Mikalauskas.

DISCLAIMER
The engine design is based on Doom3 BFG engine
https://github.com/id-Software/DOOM-3-BFG.
A lot of tweaks maded to suit my needs.
Tywyll game engine design and functionality will be changed with time.
============================================================================
*/


#ifndef _GLX_MATH_H_
#define _GLX_MATH_H_

//include
#include "GLXConstants.h"
#define RADIANS_TO_DEGREES(x) ((x) * 180.0f / PI)
#define DEGREES_TO_RADIANS(x) ((x) * PI / 180.0f)


#include "GLXVec2.h"
#include "GLXVec3.h"
#include "GLXVec4.h"
#include "GLXMat4x4.h"
#include "GLXQuat.h"


namespace glx
{
	class Math
	{
	public:
		static float InvSqrt(float x);
	};
}
#include "GLXMath.inl"

//--------------------------
// 2D Vector
//--------------------------
template<class T>
extern T GLXVec2Length(const glx::vec2<T> *pV);

template<class T>
T GLXVec2LengthSq(const glx::vec2<T> *pV);

template<class T>
T GLXVec2Dot(const glx::vec2<T> *pV1, const glx::vec2<T> *pV2);

template<class T>
glx::vec2<T>* GLXVec2Normalize(glx::vec2<T>* pOut, const glx::vec2<T>* v);

template<class T>
T GLXVec2CCW(const glx::vec2<T> *pV1, const glx::vec2<T> *pV2);

template<class T>
glx::vec2<T>* GLXVec2Add(glx::vec2<T> *pOut, const glx::vec2<T> *pV1, const glx::vec2<T> *pV2);

template<class T>
glx::vec2<T>* GLXVec2Subtract(glx::vec2<T> *pOut, const glx::vec2<T> *pV1, const glx::vec2<T> *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2)
template<class T>
glx::vec2<T>* GLXVec2Minimize(glx::vec2<T> *pOut, const glx::vec2<T> *pV1, const glx::vec2<T> *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2)
template<class T>
glx::vec2<T>* GLXVec2Maximize(glx::vec2<T> *pOut, const glx::vec2<T> *pV1, const glx::vec2<T> *pV2);

template<class T>
glx::vec2<T>* GLXVec2Scale(glx::vec2<T> *pOut, const glx::vec2<T> *pV, T s);

// Linear interpolation. V1 + s(V2-V1)
template<class T>
glx::vec2<T>* GLXVec2Lerp(glx::vec2<T> *pOut, const glx::vec2<T> *pV1, const glx::vec2<T> *pV2, T s);

//Clamp
template<class T>
glx::vec2<T>* GLXVec2Clamp(glx::vec2<T> *pOut, const glx::vec2<T>* value, const glx::vec2<T>* min, const glx::vec2<T>* max);

template<class T>
glx::vec2<T> GLXVec2ABS(const glx::vec2<T>* value);

//--------------------------
// 3D Vector
//--------------------------

template<class T>
T GLXVec3Length(const glx::vec3<T> *pV);

template<class T>
T GLXVec3LengthSq(const glx::vec3<T> *pV);

template<class T>
T GLXVec3Dot(const glx::vec3<T> *pV1, const glx::vec3<T> *pV2);

template<class T>
glx::vec3<T>* GLXVec3Cross(glx::vec3<T> *pOut, const glx::vec3<T> *pV1, const glx::vec3<T> *pV2);

template<class T>
glx::vec3<T>* GLXVec3Add(glx::vec3<T> *pOut, const glx::vec3<T> *pV1, const glx::vec3<T> *pV2);

template<class T>
glx::vec3<T>* GLXVec3Subtract(glx::vec3<T> *pOut, const glx::vec3<T> *pV1, const glx::vec3<T> *pV2);

// Minimize each component.  x = min(x1, x2), y = min(y1, y2), ...
template<class T>
glx::vec3<T>* GLXVec3Minimize(glx::vec3<T> *pOut, const glx::vec3<T> *pV1, const glx::vec3<T> *pV2);

// Maximize each component.  x = max(x1, x2), y = max(y1, y2), ...
template<class T>
glx::vec3<T>* GLXVec3Maximize(glx::vec3<T> *pOut, const glx::vec3<T> *pV1, const glx::vec3<T> *pV2);

template<class T>
glx::vec3<T>* GLXVec3Scale(glx::vec3<T> *pOut, const glx::vec3<T> *pV, T s);


template<class T>
extern glx::vec3<T> GLXVec3Lerp(const glx::vec3<T>& pV1, const glx::vec3<T>& pV2, T s);

template<class T>
glx::vec3<T>* GLXVec3Normalize(glx::vec3<T>* pOut);

template<class T>
glx::vec3<T>  GLXVec3Transform(const glx::vec3<T>* pVec, const glx::mat4<T>* pMat);

//--------------------------
// 4D Matrix
//--------------------------
// inline

template<class T>
extern glx::mat4<T>* GLXMatrixIdentity(glx::mat4<T> *pOut);

template<class T>
extern bool GLXMatrixIsIdentity(const glx::mat4<T> *pM);

template<class T>
extern T GLXMatrixDeterminant(const glx::mat4<T> *pM); //_stdcall

template<class T>
extern glx::mat4<T>*  GLXMatrixTranspose(glx::mat4<T> *pOut, const glx::mat4<T> *pM); //_stdcall

																					  // Matrix multiplication.  The result represents the transformation M2
																					  // followed by the transformation M1.  (Out = M1 * M2)
template<class T>
extern glx::mat4<T>* GLXMatrixMultiply(glx::mat4<T>* pOut, const glx::mat4<T> *pM1, const glx::mat4<T> *pM2);


// Calculate inverse of matrix.  Inversion my fail, in which case NULL will
// be returned.  The determinant of pM is also returned it pfDeterminant
// is non-NULL.

template<class T>
extern glx::mat4<T>*  GLXMatrixInverse(glx::mat4<T> *pOut, T pDeterminant, const glx::mat4<T> *pM);

// Build a matrix which scales by (sx, sy, sz)
template<class T>
extern glx::mat4<T>*  GLXMatrixScaling(glx::mat4<T> *pOut, T sx, T sy, T sz);

// Build a matrix which translates by (x, y, z) // row major
template<class T>
extern glx::mat4<T>* GLXMatrixTranslationRM(glx::mat4<T> *pOut, T x, T y, T z);

// Build a matrix which translates by (x, y, z) // collumn major
template<class T>
extern glx::mat4<T>* GLXMatrixTranslationCM(glx::mat4<T> *pOut, T x, T y, T z); //_stdcall


																				// Build a matrix which rotates around the X axis
template<class T>
extern glx::mat4<T>* GLXMatrixRotationX(glx::mat4<T> *pOut, T Angle); //_stdcall

																	  // Build a matrix which rotates around the Y axis
template<class T>
extern glx::mat4<T>* GLXMatrixRotationY(glx::mat4<T> *pOut, float Angle); //_stdcall

																		  // Build a matrix which rotates around the Z axis
template<class T>
extern glx::mat4<T>* GLXMatrixRotationZ(glx::mat4<T> *pOut, float Angle); //_stdcall

																		  //Build a matrix which rotates around arbitray X,Y Z axes
template<class T>
extern glx::mat4<T>* GLXMatrixRotate(glx::mat4<T>* pOut, float angle, float x, float y, float z);

// Build a matrix which rotates around an arbitrary axis
template<class T>
extern glx::mat4<T>* GLXMatrixRotationAxis(glx::mat4<T> *pOut, const glx::vec3<T> *pV, float Angle); //_stdcall

																									  // Build a perspective projection matrix. //column major
template<class T>
extern glx::mat4<T>* GLXMatrixPerspectiveCM(glx::mat4<T> *pOut, float fov, float aspect, float zn, float zf);

// Build a perspective projection matrix. //row major
template<class T>
extern glx::mat4<T>* GLXMatrixPerspectiveRM(glx::mat4<T> *pOut, float fov, float aspect, float zn, float zf);

// Build an ortho projection matrix. //column major
template<class T>
extern glx::mat4<T>* GLXMatrixOrthoCM(glx::mat4<T> *pOut, float left, float right, float top, float bottom, float zn, float zf); //_stdcall

																																 // Build an ortho projection matrix. //row major
template<class T>
extern glx::mat4<T>* GLXMatrixOrthoRM(glx::mat4<T> *pOut, float left, float right, float top, float bottom, float zn, float zf); //_stdcall;

template<class T>
extern glx::mat4<T>* GLXLookAt(glx::mat4<T>* pOut, const glx::vec3<T>& eye, const glx::vec3<T>& center, const glx::vec3<T>& up);

template<class T>
extern glx::vec3<T> GLXGetYawPitchRoll(const glx::mat4<T> & m);

template<class T>
extern void GLXBuildYawPitchRoll(glx::mat4<T>& mat, const float yawRadians, const float pitchRadians, const float rollRadians);

//--------------------------
// Quaternon
//--------------------------
extern glx::quat GLXQuatNormalize(glx::quat& in);

extern glx::quat GLXQuatLerp(const glx::quat& q1, const glx::quat& q2, float t);

extern glx::quat GLXQuatSlerp(const glx::quat& q1, const glx::quat& q2, float t);

extern float GLXQuatDot(const glx::quat& q1, const glx::quat& q2);

extern float GLXQuatGetYaw(const glx::quat& q);

extern float GLXQuatGetPitch(const glx::quat& q);

extern float GLXQuatGetRoll(const glx::quat& q);
#endif  // end _GLXMATH_