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
#ifndef _GLX_MATH_CONSTANTS_H_
#define _GLX_MATH_CONSTANTS_H_




//Natural logarithm of 2
const float LOG_NAT_2 = 0.69314718055994530941723212145818f;

//Reciprocal natural logarithm of 2
const float INV_LOG_NAT_2 = 1.4426950408889634073599246810019f;

//Epsilon
const float EPSILON = 1e-6f;

//Square root of 2
const float SQRT_2 = 1.4142135623730950488016887242097f;

//PI / 2
const float PI_05 = 1.5707963267948966192313216916398f;

//PI
const float PI = 3.1415926535897932384626433832795f;

// 1 / PI
const float INV_PI = 0.31830988618379067153776752674503f;

//(PI * 2)
const float PI_2 = 6.283185307179586476925286766559f;

// 1 / (PI * 2)
const float INV_PI_2 = 0.159154943091895335768883763f;

//PI times 4
const float PI_4 = 12.566370614359172953850573533118f;

//One over PI times 4
const float INV_PI_4 = 0.07957747154594766788444188168626f;

//PI * PI * 2
const float PI_2_2 = 19.739208802178717237668981999752f;

//PI * 4 / 3 --> Sphere volume constant
const float SPHERE_VOLUME = 4.188790204786390984616857844373f;

// 180/PI
const float _180OVERPI = 57.295779513082320876798154814105f;

// PI/180
const float PI_OVER180 = 0.017453292519943295769236907685f;



/*
================================================================================================

floating point bit layouts according to the IEEE 754-1985 and 754-2008 standard

================================================================================================
*/

#define IEEE_FLT16_MANTISSA_BITS	10
#define IEEE_FLT16_EXPONENT_BITS	5
#define IEEE_FLT16_EXPONENT_BIAS	15
#define IEEE_FLT16_SIGN_BIT			15
#define IEEE_FLT16_SIGN_MASK		( 1U << IEEE_FLT16_SIGN_BIT )

#define IEEE_FLT_MANTISSA_BITS		23
#define IEEE_FLT_EXPONENT_BITS		8
#define IEEE_FLT_EXPONENT_BIAS		127
#define IEEE_FLT_SIGN_BIT			31
#define IEEE_FLT_SIGN_MASK			( 1UL << IEEE_FLT_SIGN_BIT )

#define IEEE_DBL_MANTISSA_BITS		52
#define IEEE_DBL_EXPONENT_BITS		11
#define IEEE_DBL_EXPONENT_BIAS		1023
#define IEEE_DBL_SIGN_BIT			63
#define IEEE_DBL_SIGN_MASK			( 1ULL << IEEE_DBL_SIGN_BIT )

#define IEEE_DBLE_MANTISSA_BITS		63
#define IEEE_DBLE_EXPONENT_BITS		15
#define IEEE_DBLE_EXPONENT_BIAS		0
#define IEEE_DBLE_SIGN_BIT			79


const int SMALLEST_NON_DENORMAL = 1 << IEEE_FLT_MANTISSA_BITS;
const int NAN_VALUE = 0x7f800000;
const float FLT_SMALLEST_NON_DENORMAL = *reinterpret_cast< const float * >(&SMALLEST_NON_DENORMAL);

#endif
