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

#include <stdafx.h>
#include "GLXMath.h"


//--------------------------
// 2D Vector
//--------------------------

template<class T>
T GLXVec2Length(const glx::vec2<T> *pV) {
	return sqrt(pow(pV->x, 2) + pow(pV->y, 2));
}

template<class T>
glx::vec2<T>* GLXVec2Clamp(glx::vec2<T> *pOut, const glx::vec2<T>* value, const glx::vec2<T>* min, const glx::vec2<T>* max)
{
	if (!value || !min || !max)return pOut;
	//what if pOut null too? -> sooo many decision and mistakes you can do
	//Decision 1: -> check only in debug mode all mistakes that can go wrong
	//Decision 2: -> hope that everyting will be allright

	pOut->x = value->x;
	pOut->y = value->y;

	if (pOut->x < min->x)pOut->x = min->x;
	if (pOut->y < min->y)pOut->y = min->y;

	if (pOut->x > max->x)pOut->x = max->x;
	if (pOut->y > max->y)pOut->y = max->y;
	return pOut;
}

template<class T>
T GLXVec2Dot(const glx::vec2<T> *pV1, const glx::vec2<T> *pV2) {
	return (pV1->x * pV2->x + pV1->y * pV2->y);
}

template<class T>
glx::vec2<T>* GLXVec2Normalize(glx::vec2<T>* pOut, const glx::vec2<T>* v) {
	float a = GLXVec2Length(v);
	pOut->x = v->x / a;
	pOut->y = v->y / a;
	return pOut;
}

template<class T>
glx::vec2<T> GLXVec2ABS(const glx::vec2<T>* value) {
	glx::vec2 pOut(*value);
	if (pOut.x < 0) pOut.x *= -1;
	if (pOut.y < 0) pOut.y *= -1;
	return pOut;
}


//-------------------------
// 3D Vector
//-------------------------

template<class T>
T GLXVec3Length(const glx::vec3<T> *pV) {
	return sqrt(pV->x * pV->x +
		pV->y * pV->y +
		pV->z *	pV->z);
}

template<class T>
glx::vec3<T>* GLXVec3Normalize(glx::vec3<T>* pOut) {
	T a = GLXVec3Length(pOut);
	if (a == 0.0f)return nullptr;

	pOut->x = pOut->x / a;
	pOut->y = pOut->y / a;
	pOut->y = pOut->z / a;
	return pOut;
}

template<class T>
glx::vec3<T>* GLXVec3Cross(glx::vec3<T> *pOut, const glx::vec3<T> *pV1, const glx::vec3<T> *pV2) {

	pOut->x = pV1->y * pV2->z - pV2->y * pV1->z;
	pOut->y = pV1->z * pV2->x - pV2->z * pV1->x;
	pOut->z = pV1->x * pV2->y - pV2->x * pV1->y;
	return pOut;
}


template<class T>
T GLXVec3Dot(const glx::vec3<T> *pV1, const glx::vec3<T> *pV2) {
	return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}

/*
=================================================
Linearly interpolates one vector to another.
=================================================
*/
template<class T>
glx::vec3<T> GLXVec3Lerp(const glx::vec3<T>& pV1, const glx::vec3<T>& pV2, T s)
{
	return glx::vec3<T>(pV1*(1 - s) + pV2*s);
}
template glx::vec3<float> GLXVec3Lerp(const glx::vec3<float>& pV1, const glx::vec3<float>& pV2, float s);


template<class T>
glx::vec3<T>  GLXVec3Transform(const glx::vec3<T>* pVec, const glx::mat4<T>* pMat)
{
	glx::vec3<float> out;
	out.Clear();

	out.x = pVec->x * pMat->_11 + pVec->y * pMat->_21 + pVec->z * pMat->_31 + pMat->_41;
	out.y = pVec->x * pMat->_12 + pVec->y * pMat->_22 + pVec->z * pMat->_32 + pMat->_42;
	out.z = pVec->x * pMat->_13 + pVec->y * pMat->_23 + pVec->z * pMat->_33 + pMat->_43;
	return out;
}
//explicit
template glx::vec3<float> GLXVec3Transform(const glx::vec3<float>* pVec, const glx::mat4<float>* pMat);


//--------------------------
// 4D Matrix
//--------------------------

//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixIdentity(glx::mat4<T> *pOut)
{
#ifdef TYW_DEBUG
	if (!pOut)
		return nullptr;
#endif

	pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
		pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
		pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
		pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;

	pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = 1.0f;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixIdentity(glx::mat4<float> *pOut);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
bool GLXMatrixIsIdentity(const glx::mat4<T> *pM)
{
#ifdef TYW_DEBUG
	if (!pM)
		return false;
#endif
	return  pM->m[0][0] == 1.0f && pM->m[0][1] == 0.0f && pM->m[0][2] == 0.0f && pM->m[0][3] == 0.0f &&
		pM->m[1][0] == 0.0f && pM->m[1][1] == 1.0f && pM->m[1][2] == 0.0f && pM->m[1][3] == 0.0f &&
		pM->m[2][0] == 0.0f && pM->m[2][1] == 0.0f && pM->m[2][2] == 1.0f && pM->m[2][3] == 0.0f &&
		pM->m[3][0] == 0.0f && pM->m[3][1] == 0.0f && pM->m[3][2] == 0.0f && pM->m[3][3] == 1.0f;
}
//explicit
template bool GLXMatrixIsIdentity(const glx::mat4<float> *pM);
//=================================================================================================================================






//=================================================================================================================================
template<class T>
glx::mat4<T>*  GLXMatrixInverse(glx::mat4<T> *pOut, T pDeterminant, const glx::mat4<T> *pM)
{
#ifndef TYW_DEBUG
	if (!pOut) return nullptr;
#endif
	if (pDeterminant == 0.0f) {
		//if //((int)pDeterminant == 0) {
		//Big hack, kinda.....
		//Not safe -> never ever use == or != on floating points
		//becuase it's unsafe 
		//Read ->https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
		//Better check whether their difference is within some error bounds or epsilon value
		//bool isEqual = fabs(f1 – f2) <= epsilon;
		return nullptr;
	}

	float rev_det = 1.0f / pDeterminant;  //pow(A, -1)
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			pOut->m[y][x] *= rev_det;
		}
	}
	return pOut;
}
//explicit
template glx::mat4<float>*  GLXMatrixInverse(glx::mat4<float> *pOut, float pDeterminant, const glx::mat4<float> *pM);
//=================================================================================================================================






//=================================================================================================================================
// DUUUDE, THE AMOUNT OF MAAAATTTHHH -> http://www.purplemath.com/modules/minors.htm
template<class T>
T GLXMatrixDeterminant(const glx::mat4<T> *pM)
{
#ifdef TYW_DEBUG
	if (!pM)return -1.69f; //ta ta daaa -> carefull
#endif
	float cofactor[4];
	float minors[3];

	//===========================================================================================================================
	//Row 1, Column1 minors
	minors[0] = pM->m[1][1] * pow(-1, 1 + 1) * ((pM->m[2][2] * pM->m[3][3]) - (pM->m[3][2] * pM->m[2][3]));
	minors[1] = pM->m[1][2] * pow(-1, 1 + 2) * ((pM->m[2][1] * pM->m[3][3]) - (pM->m[3][1] * pM->m[2][3]));
	minors[2] = pM->m[1][3] * pow(-1, 1 + 3) * ((pM->m[2][1] * pM->m[3][2]) - (pM->m[3][1] * pM->m[2][2]));

	//Row 1, Column 2 cofactor
	cofactor[0] = pow(-1, 1 + 1) * (minors[0] + minors[1] + minors[2]);
	//===========================================================================================================================

	//===========================================================================================================================
	//Row 1, Column 2 minors
	minors[0] = pM->m[1][0] * pow(-1, 1 + 1) * ((pM->m[2][2] * pM->m[3][3]) - (pM->m[3][2] * pM->m[2][3]));
	minors[1] = pM->m[1][2] * pow(-1, 1 + 2) * ((pM->m[2][0] * pM->m[3][3]) - (pM->m[3][0] * pM->m[2][3]));
	minors[2] = pM->m[1][3] * pow(-1, 1 + 3) * ((pM->m[2][0] * pM->m[3][2]) - (pM->m[3][0] * pM->m[2][2]));

	//Row 1, Column 2 cofactor
	cofactor[1] = pow(-1, 2 + 1) * (minors[0] + minors[1] + minors[2]);
	//===========================================================================================================================

	//===========================================================================================================================
	//Row 1, Column 3 minors
	minors[0] = pM->m[1][0] * pow(-1, 1 + 1) * ((pM->m[2][1] * pM->m[3][3]) - (pM->m[3][1] * pM->m[2][3]));
	minors[1] = pM->m[1][1] * pow(-1, 1 + 2) * ((pM->m[2][0] * pM->m[3][3]) - (pM->m[3][0] * pM->m[2][3]));
	minors[2] = pM->m[1][3] * pow(-1, 1 + 3) * ((pM->m[2][0] * pM->m[3][1]) - (pM->m[3][0] * pM->m[2][1]));

	//Row 1, Column 3 cofactor
	cofactor[2] = pow(-1, 3 + 1) *(minors[0] + minors[1] + minors[2]);
	//===========================================================================================================================

	//===========================================================================================================================
	//Row 1, Column 4 minors
	minors[0] = pM->m[1][0] * pow(-1, 1 + 1) * ((pM->m[2][1] * pM->m[3][2]) - (pM->m[3][1] * pM->m[2][2]));
	minors[1] = pM->m[1][1] * pow(-1, 1 + 2) * ((pM->m[2][0] * pM->m[3][2]) - (pM->m[3][0] * pM->m[2][2]));
	minors[2] = pM->m[1][2] * pow(-1, 1 + 3) * ((pM->m[2][0] * pM->m[3][1]) - (pM->m[3][0] * pM->m[2][1]));

	//Row 1, Column 4 cofactor
	cofactor[3] = pow(-1, 4 + 1) * (minors[0] + minors[1] + minors[2]);
	//===========================================================================================================================
	return  pM->m[0][0] * cofactor[0] +
		pM->m[0][1] * cofactor[1] +
		pM->m[0][2] * cofactor[2] +
		pM->m[0][3] * cofactor[3];
}
//explicit
template float GLXMatrixDeterminant(const glx::mat4<float> *pM);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>*  GLXMatrixTranspose(glx::mat4<T> *pOut, const	glx::mat4<T> *pM)
{
#ifdef TYW_DEBUG
	if (!pOut || !pM)return nullptr;
#endif

	return pOut;
}
//explcicit
template glx::mat4<float>*  GLXMatrixTranspose(glx::mat4<float> *pOut, const	glx::mat4<float> *pM);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>*  GLXMatrixScaling(glx::mat4<T> *pOut, T sx, T sy, T sz)
{
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	pOut->m[0][0] = sx;
	pOut->m[1][1] = sy;
	pOut->m[2][2] = sz;
	return pOut;
}
//explicit
template glx::mat4<float>*  GLXMatrixScaling(glx::mat4<float> *pOut, float sx, float sy, float sz);
//=================================================================================================================================



//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixTranslationRM(glx::mat4<T> *pOut, T x, T y, T z)
{
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	pOut->m[3][0] = -x;
	pOut->m[3][1] = -y;
	pOut->m[3][2] = -z;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixTranslationRM(glx::mat4<float> *pOut, float x, float y, float z);
template glx::mat4<int>* GLXMatrixTranslationRM(glx::mat4<int> *pOut, int x, int y, int z);
template glx::mat4<double>* GLXMatrixTranslationRM(glx::mat4<double> *pOut, double x, double y, double z);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixTranslationCM(glx::mat4<T> *pOut, T x, T y, T z)
{
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	pOut->m[0][3] = x;
	pOut->m[1][3] = y;
	pOut->m[2][3] = z;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixTranslationCM(glx::mat4<float> *pOut, float x, float y, float z);
template glx::mat4<int>* GLXMatrixTranslationCM(glx::mat4<int> *pOut, int x, int y, int z);
template glx::mat4<double>* GLXMatrixTranslationCM(glx::mat4<double> *pOut, double x, double y, double z);
//=================================================================================================================================






//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixOrthoCM(glx::mat4<T> *pOut, float left, float right, float top, float bottom, float zn, float zf)
{
#ifdef TYW_DEBUG
	if (pOut) return nullptr;
#endif

	//translate
	pOut->m[0][3] = -(right + left) / (right - left);
	pOut->m[1][3] = -(top + bottom) / (top - bottom);
	pOut->m[2][3] = -(zn + zf) / (zf - zn);

	//scale
	pOut->m[0][0] = 2.0f / (right - left);
	pOut->m[1][1] = 2.0f / (top - bottom);
	pOut->m[2][2] = -2.0f / (zn - zf);
	pOut->m[3][3] = 1.0f;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixOrthoCM(glx::mat4<float> *pOut, float left, float right, float top, float bottom, float zn, float zf);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixOrthoRM(glx::mat4<T> *pOut, float left, float right, float top, float bottom, float zn, float zf)
{
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif	
	//translate
	pOut->m[3][0] = -(right + left) / (right - left);
	pOut->m[3][1] = -(top + bottom) / (top - bottom);
	pOut->m[3][2] = -(zn + zf) / (zf - zn);

	//scale
	pOut->m[0][0] = 2.0f / (right - left);
	pOut->m[1][1] = 2.0f / (top - bottom);
	pOut->m[2][2] = -2.0f / (zn - zf);
	pOut->m[3][3] = 1.0f;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixOrthoRM(glx::mat4<float> *pOut, float left, float right, float top, float bottom, float zn, float zf);
//=================================================================================================================================






//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixPerspectiveRM(glx::mat4<T> *pOut, float fov, float aspect, float zn, float zf) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	const float q = 1.0f / tan(0.5f*fov * (PI / 180.0f));
	const float A = q / aspect;
	const float B = (zn + zf) / (zn - zf);
	const float C = (2.0f * zn * zf) / (zn - zf);

	pOut->m[0][0] = A;
	pOut->m[1][1] = q;
	pOut->m[2][2] = B;
	pOut->m[2][3] = -1;
	pOut->m[3][2] = C;
	pOut->m[3][3] = 0;
	return pOut;
}
//Explicit
template glx::mat4<float>* GLXMatrixPerspectiveRM(glx::mat4<float> *pOut, float fov, float aspect, float zn, float zf);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixPerspectiveCM(glx::mat4<T> *pOut, float fov, float aspect, float zn, float zf) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	float q = tan(0.5f*fov * (PI / 180.0f));
	float A = 1.0f / (q*aspect);
	float B = (-zn + zf) / (zn - zf);
	float C = (2.0f * zn * zf) / (zn - zf);

	pOut->m[0][0] = A;
	pOut->m[1][1] = 1.0f / q;
	pOut->m[2][2] = B;
	pOut->m[2][3] = C;
	pOut->m[3][2] = -1;
	pOut->m[3][3] = 0;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixPerspectiveCM(glx::mat4<float> *pOut, float fov, float aspect, float zn, float zf);
//=================================================================================================================================




//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixRotationX(glx::mat4<T> *pOut, T Angle) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif

	float radians = Angle * (PI / 180.0f);
	pOut->m[1][1] = cosf(radians);
	pOut->m[1][2] = sinf(radians);
	pOut->m[2][1] = -sinf(radians);
	pOut->m[2][2] = cosf(radians);
	return pOut;

}
//explicit
template glx::mat4<float>* GLXMatrixRotationX(glx::mat4<float> *pOut, float Angle);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixRotationY(glx::mat4<T> *pOut, float Angle) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	float radians = Angle * (PI / 180.0f);
	pOut->m[0][0] = cosf(radians);
	pOut->m[0][2] = -sinf(radians);
	pOut->m[2][0] = sinf(radians);
	pOut->m[2][2] = cosf(radians);
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixRotationY(glx::mat4<float> *pOut, float Angle);
//=================================================================================================================================




//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixRotationZ(glx::mat4<T> *pOut, float Angle) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	float radians = Angle * (PI / 180.0f);
	pOut->m[0][0] = cosf(radians);
	pOut->m[0][1] = -sinf(radians);
	pOut->m[1][0] = sinf(radians);
	pOut->m[1][1] = cosf(radians);
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixRotationZ(glx::mat4<float> *pOut, float Angle);
//=================================================================================================================================





//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixRotate(glx::mat4<T>* pOut, float angle, float x, float y, float z) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	const float x2 = x*x;
	const float y2 = y*y;
	const float z2 = z*z;
	float rads = angle  * (PI / 180.0f);
	const float c = cosf(rads);
	const float s = sinf(rads);
	const float omc = 1.0f - c;

	pOut->m[0][0] = x2 * omc + c;
	pOut->m[0][1] = y * x * omc + z * s;
	pOut->m[0][2] = x * z * omc - y * s;

	pOut->m[1][0] = x * y * omc - z * s;
	pOut->m[1][1] = y2 * omc + c;
	pOut->m[1][2] = y * z * omc + x * s;

	pOut->m[2][0] = x * z * omc + y * s;
	pOut->m[2][1] = y * z * omc - x * s;
	pOut->m[2][2] = z2 * omc + c;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixRotate(glx::mat4<float>* pOut, float angle, float x, float y, float z);
//=================================================================================================================================






//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXLookAt(glx::mat4<T>* pOut, const glx::vec3<T>& eye, const glx::vec3<T>& center, const glx::vec3<T>& up) {
#ifdef TYW_DEBUG
	if (!pOut)return nullptr;
#endif
	glx::vec3<T> zaxis = center - eye;
	glx::vec3<T> xaxis;
	glx::vec3<T> yaxis;
	GLXVec3Normalize(&zaxis);
	GLXVec3Normalize(GLXVec3Cross(&xaxis, &up, &zaxis));
	GLXVec3Cross(&yaxis, &zaxis, &xaxis);

	glx::mat4<T> m(
		xaxis.x, yaxis.x, zaxis.x, 0.0f,
		xaxis.y, yaxis.y, zaxis.y, 0.0f,
		xaxis.z, yaxis.z, zaxis.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	glx::mat4<T> mt(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-eye.x, -eye.y, -eye.z, 1.0f);
	//  *pOut = m * mt;
	*pOut = mt;
	return pOut;
}
//explicit
template glx::mat4<float>* GLXLookAt(glx::mat4<float>* pOut, const glx::vec3<float>& eye, const glx::vec3<float>& center, const glx::vec3<float>& up);
//=================================================================================================================================






//=================================================================================================================================
template<class T>
glx::mat4<T>* GLXMatrixMultiply(glx::mat4<T>* pOut, const glx::mat4<T> *pM1, const glx::mat4<T> *pM2) {
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			pOut->m[row][col] = 0.0f;
			for (int inner = 0; inner < 4; inner++) {
				pOut->m[row][col] += pM1->m[row][inner] * pM2->m[inner][col];
			}
		}
	}
	return pOut;
}
//explicit
template glx::mat4<float>* GLXMatrixMultiply(glx::mat4<float>* pOut, const glx::mat4<float> *pM1, const glx::mat4<float> *pM2);
template glx::mat4<int>* GLXMatrixMultiply(glx::mat4<int>* pOut, const glx::mat4<int> *pM1, const glx::mat4<int> *pM2);
template glx::mat4<double>* GLXMatrixMultiply(glx::mat4<double>* pOut, const glx::mat4<double> *pM1, const glx::mat4<double> *pM2);
//=================================================================================================================================


//=================================================================================================================================
template<class T>
glx::vec3<T> GLXGetYawPitchRoll(const glx::mat4<T> & m)
{
	float yaw, pitch, roll;

	//pitch = asin(-_32);
	pitch = asin(-m.m[2][2]);

	double threshold = 0.001; // Hardcoded constant - burn him, he's a witch
	double test = cos(pitch);

	if (test > threshold)
	{
		//roll = atan2(_12, _22);
		//yaw = atan2(_31, _33);

		roll = atan2(m.m[0][1], m.m[1][1]);
		yaw = atan2(m.m[2][0], m.m[2][2]);
	}
	else
	{
		//roll = atan2(-_21, _11);
		roll = atan2(-m.m[1][0], m.m[0][0]);
		yaw = 0.0;
	}

	return (glx::vec3<T>(yaw, pitch, roll));
}
template glx::vec3<float> GLXGetYawPitchRoll(const glx::mat4<float> & m);
template glx::vec3<int> GLXGetYawPitchRoll(const glx::mat4<int> & m);
template glx::vec3<double> GLXGetYawPitchRoll(const glx::mat4<double> & m);
//=================================================================================================================================



//=================================================================================================================================
template<class T>
void GLXBuildYawPitchRoll(glx::mat4<T>& mat, const float yawRadians, const float pitchRadians, const float rollRadians)
{
	glx::quat rot(pitchRadians, yawRadians, rollRadians);
	rot.CalcW();

	rot.x = GLXQuatGetPitch(rot);
	rot.y = GLXQuatGetYaw(rot);
	rot.z = GLXQuatGetRoll(rot);
	rot.CalcW();


	mat.SetRotation(rot.ToMat4());
}
template void GLXBuildYawPitchRoll(glx::mat4<float>& mat, const float yawRadians, const float pitchRadians, const float rollRadians);
//=================================================================================================================================


//--------------------------
// Quaternon
//--------------------------


//=================================================================================================================================
glx::quat GLXQuatNormalize(glx::quat& in)
{
	double length = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z + in.w * in.w);
	return glx::quat(in.x / length, in.y / length, in.z / length, in.w / length);
}
//=================================================================================================================================


//=================================================================================================================================
glx::quat GLXQuatLerp(const glx::quat& q1, const glx::quat& q2, float t)
{
	glx::quat temp(q1*(1 - t) + q2*t);
	return GLXQuatNormalize(temp);
}
//=================================================================================================================================


//=================================================================================================================================
extern glx::quat GLXQuatSlerp(const glx::quat& q1, const glx::quat& q2, float t)
{
	glx::quat q3;
	float dot = GLXQuatDot(q1, q2);

	/*	dot = cos(theta)
	if (dot < 0), q1 and q2 are more than 90 degrees apart,
	so we can invert one to reduce spinning	*/
	if (dot < 0)
	{
		dot = -dot;
		q3 = -q2;
	}
	else q3 = q2;

	if (dot < 0.95f)
	{
		float angle = acosf(dot);
		return (q1*sinf(angle*(1 - t)) + q3*sinf(angle*t)) / sinf(angle);
	}
	else
	{
		// if the angle is small, 
		return GLXQuatLerp(q1, q3, t);
	}
}
//=================================================================================================================================


//=================================================================================================================================
float GLXQuatDot(const glx::quat& q1, const glx::quat& q2)
{
	return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}
//=================================================================================================================================


//=================================================================================================================================
glx::mat4<float> glx::quat::ToMat4() const
{
	glx::mat4<float> mat;

	float	wx, wy, wz;
	float	xx, yy, yz;
	float	xy, xz, zz;
	float	x2, y2, z2;

	x2 = x + x;
	y2 = y + y;
	z2 = z + z;

	xx = x * x2;
	xy = x * y2;
	xz = x * z2;

	yy = y * y2;
	yz = y * z2;
	zz = z * z2;

	wx = w * x2;
	wy = w * y2;
	wz = w * z2;

	mat.m[0][0] = 1.0f - (yy + zz);
	mat.m[0][1] = xy - wz;
	mat.m[0][2] = xz + wy;
	mat.m[0][3] = 0.0f;

	mat.m[1][0] = xy + wz;
	mat.m[1][1] = 1.0f - (xx + zz);
	mat.m[1][2] = yz - wx;
	mat.m[1][3] = 0.0f;

	mat.m[2][0] = xz - wy;
	mat.m[2][1] = yz + wx;
	mat.m[2][2] = 1.0f - (xx + yy);
	mat.m[2][3] = 0.0f;

	mat.m[3][0] = 0.0f;
	mat.m[3][1] = 0.0f;
	mat.m[3][2] = 0.0f;
	mat.m[3][3] = 1.0f;

	return mat;
}
//===========================================================================================================================================================================================================================================================


//===========================================================================================================================================================================================================================================================
void glx::quat::CalcW()
{
	float t = 1.0f - (x * x) - (y * y) - (z * z);
	if (t < 0.0f)
	{
		w = 0.0f;
	}
	else
	{
		w = -sqrtf(t);
	}
}
//===========================================================================================================================================================================================================================================================





//==========================================================================
//Spherical linear interpolation between two quaternions
//==========================================================================
glx::quat& glx::quat::Slerp(const quat &from, const quat &to, float t)

{
	glx::quat temp;
	float	omega, cosom, sinom, scale0, scale1;


	if (t <= 0.0f) {
		*this = from;
		return *this;
	}

	if (t >= 1.0f) {
		*this = to;
		return *this;
	}

	if (from == to) {
		*this = to;
		return *this;
	}

	cosom = from.x * to.x + from.y * to.y + from.z * to.z + from.w * to.w;
	if (cosom < 0.0f) {
		temp = -to;
		cosom = -cosom;
	}
	else {
		temp = to;
	}

	if ((1.0f - cosom) > 1e-6f) {
#if 0
		omega = acos(cosom);
		sinom = 1.0f / sin(omega);
		scale0 = sin((1.0f - t) * omega) * sinom;
		scale1 = sin(t * omega) * sinom;
#else
		scale0 = 1.0f - cosom * cosom;
		sinom = glx::Math::InvSqrt(scale0);
		omega =  atan2f(scale0 * sinom, cosom);
		scale0 = sinf((1.0f - t) * omega) * sinom;
		scale1 = sinf(t * omega) * sinom;
#endif
	}
	else {
		scale0 = 1.0f - t;
		scale1 = t;
	}

	*this = (scale0 * from) + (scale1 * temp);
	return *this;
}

//==========================================================
inline float GLXQuatGetYaw(const glx::quat& q)
{
	return asin(2 * (q.x*q.z - q.w*q.y));
}
//==========================================================


//==========================================================
inline float GLXQuatGetPitch(const glx::quat& q)
{
	return atan2(2 * (q.x*q.y + q.z*q.w), 1 - 2 * (q.y*q.y + q.z*q.z));
}
//==========================================================


//==========================================================
inline float GLXQuatGetRoll(const glx::quat& q)
{
	return atan2(2 * (q.x*q.w + q.y*q.z), 1 - 2 * (q.z*q.z + q.w*q.w));
}
//==========================================================