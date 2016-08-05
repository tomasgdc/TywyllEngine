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
#ifndef __SYS_PUBLIC__
#define __SYS_PUBLIC__
/*
===============================================================================

Non-portable system services.

===============================================================================
*/

enum class cpuid_t {
	CPUID_NONE = 0x00000,
	CPUID_UNSUPPORTED = 0x00001,	// unsupported (386/486)
	CPUID_GENERIC = 0x00002,	// unrecognized processor
	CPUID_INTEL = 0x00004,	// Intel
	CPUID_AMD = 0x00008,	// AMD
	CPUID_MMX = 0x00010,	// Multi Media Extensions
	CPUID_3DNOW = 0x00020,	// 3DNow!
	CPUID_SSE = 0x00040,	// Streaming SIMD Extensions
	CPUID_SSE2 = 0x00080,	// Streaming SIMD Extensions 2
	CPUID_SSE3 = 0x00100,	// Streaming SIMD Extentions 3 aka Prescott's New Instructions
	CPUID_ALTIVEC = 0x00200,	// AltiVec
	CPUID_HTT = 0x01000,	// Hyper-Threading Technology
	CPUID_CMOV = 0x02000,	// Conditional Move (CMOV) and fast floating point comparison (FCOMI) instructions
	CPUID_FTZ = 0x04000,	// Flush-To-Zero mode (denormal results are flushed to zero)
	CPUID_DAZ = 0x08000,	// Denormals-Are-Zero mode (denormal source operands are set to zero)
	CPUID_XENON = 0x10000,	// Xbox 360
	CPUID_CELL = 0x20000	// PS3
};

enum class fpuExceptions_t {
	FPU_EXCEPTION_INVALID_OPERATION = 1,
	FPU_EXCEPTION_DENORMALIZED_OPERAND = 2,
	FPU_EXCEPTION_DIVIDE_BY_ZERO = 4,
	FPU_EXCEPTION_NUMERIC_OVERFLOW = 8,
	FPU_EXCEPTION_NUMERIC_UNDERFLOW = 16,
	FPU_EXCEPTION_INEXACT_RESULT = 32
};

enum fpuPrecision_t {
	FPU_PRECISION_SINGLE = 0,
	FPU_PRECISION_DOUBLE = 1,
	FPU_PRECISION_DOUBLE_EXTENDED = 2
};

enum class fpuRounding_t {
	FPU_ROUNDING_TO_NEAREST = 0,
	FPU_ROUNDING_DOWN = 1,
	FPU_ROUNDING_UP = 2,
	FPU_ROUNDING_TO_ZERO = 3
};

enum class joystickAxis_t {
	AXIS_LEFT_X,
	AXIS_LEFT_Y,
	AXIS_RIGHT_X,
	AXIS_RIGHT_Y,
	AXIS_LEFT_TRIG,
	AXIS_RIGHT_TRIG,
	MAX_JOYSTICK_AXIS
};

enum class sysEventType_t {
	SE_NONE,				// evTime is still valid
	SE_KEY,					// evValue is a key code, evValue2 is the down flag
	SE_CHAR,				// evValue is an ascii char
	SE_MOUSE,				// evValue and evValue2 are reletive signed x / y moves
	SE_MOUSE_ABSOLUTE,		// evValue and evValue2 are absolute coordinates in the window's client area.
	SE_MOUSE_LEAVE,			// evValue and evValue2 are meaninless, this indicates the mouse has left the client area.
	SE_JOYSTICK,		// evValue is an axis number and evValue2 is the current state (-127 to 127)
	SE_CONSOLE,				// evPtr is a char*, from typing something at a non-game console
	SE_RESIZED			//Windows screen was resized
};

enum class sys_mEvents {
	M_ACTION1,
	M_ACTION2,
	M_ACTION3,
	M_ACTION4,
	M_ACTION5,
	M_ACTION6,
	M_ACTION7,
	M_ACTION8,
	M_DELTAX,
	M_DELTAY,
	M_DELTAZ,
	M_INVALID
};


enum class sys_jEvents 
{
	J_ACTION1,
	J_ACTION2,
	J_ACTION3,
	J_ACTION4,
	J_ACTION5,
	J_ACTION6,
	J_ACTION7,
	J_ACTION8,
	J_ACTION9,
	J_ACTION10,
	J_ACTION11,
	J_ACTION12,
	J_ACTION13,
	J_ACTION14,
	J_ACTION15,
	J_ACTION16,
	J_ACTION17,
	J_ACTION18,
	J_ACTION19,
	J_ACTION20,
	J_ACTION21,
	J_ACTION22,
	J_ACTION23,
	J_ACTION24,
	J_ACTION25,
	J_ACTION26,
	J_ACTION27,
	J_ACTION28,
	J_ACTION29,
	J_ACTION30,
	J_ACTION31,
	J_ACTION32,
	J_ACTION_MAX = J_ACTION32,

	J_AXIS_MIN,
	//J_AXIS_LEFT_X = J_AXIS_MIN + AXIS_LEFT_X,
	//J_AXIS_LEFT_Y = J_AXIS_MIN + AXIS_LEFT_Y,
	//J_AXIS_RIGHT_X = J_AXIS_MIN + AXIS_RIGHT_X,
	//J_AXIS_RIGHT_Y = J_AXIS_MIN + AXIS_RIGHT_Y,
	//J_AXIS_LEFT_TRIG = J_AXIS_MIN + AXIS_LEFT_TRIG,
	//J_AXIS_RIGHT_TRIG = J_AXIS_MIN + AXIS_RIGHT_TRIG,

	//J_AXIS_MAX = J_AXIS_MIN + MAX_JOYSTICK_AXIS - 1,

	J_DPAD_UP,
	J_DPAD_DOWN,
	J_DPAD_LEFT,
	J_DPAD_RIGHT,

	MAX_JOY_EVENT
};


/*
================================================
The first part of this table maps directly to Direct Input scan codes (DIK_* from dinput.h)
But they are duplicated here for console portability
================================================
*/
enum class keyNum_t {
	K_NONE,

	K_ESCAPE,
	K_1,
	K_2,
	K_3,
	K_4,
	K_5,
	K_6,
	K_7,
	K_8,
	K_9,
	K_0,
	K_MINUS,
	K_EQUALS,
	K_BACKSPACE,
	K_TAB,
	K_Q,
	K_W,
	K_E,
	K_R,
	K_T,
	K_Y,
	K_U,
	K_I,
	K_O,
	K_P,
	K_LBRACKET,
	K_RBRACKET,
	K_ENTER,
	K_LCTRL,
	K_A,
	K_S,
	K_D,
	K_F,
	K_G,
	K_H,
	K_J,
	K_K,
	K_L,
	K_SEMICOLON,
	K_APOSTROPHE,
	K_GRAVE,
	K_LSHIFT,
	K_BACKSLASH,
	K_Z,
	K_X,
	K_C,
	K_V,
	K_B,
	K_N,
	K_M,
	K_COMMA,
	K_PERIOD,
	K_SLASH,
	K_RSHIFT,
	K_KP_STAR,
	K_LALT,
	K_SPACE,
	K_CAPSLOCK,
	K_F1,
	K_F2,
	K_F3,
	K_F4,
	K_F5,
	K_F6,
	K_F7,
	K_F8,
	K_F9,
	K_F10,
	K_NUMLOCK,
	K_SCROLL,
	K_KP_7,
	K_KP_8,
	K_KP_9,
	K_KP_MINUS,
	K_KP_4,
	K_KP_5,
	K_KP_6,
	K_KP_PLUS,
	K_KP_1,
	K_KP_2,
	K_KP_3,
	K_KP_0,
	K_KP_DOT,
	K_F11 = 0x57,
	K_F12 = 0x58,
	K_F13 = 0x64,
	K_F14 = 0x65,
	K_F15 = 0x66,
	K_KANA = 0x70,
	K_CONVERT = 0x79,
	K_NOCONVERT = 0x7B,
	K_YEN = 0x7D,
	K_KP_EQUALS = 0x8D,
	K_CIRCUMFLEX = 0x90,
	K_AT = 0x91,
	K_COLON = 0x92,
	K_UNDERLINE = 0x93,
	K_KANJI = 0x94,
	K_STOP = 0x95,
	K_AX = 0x96,
	K_UNLABELED = 0x97,
	K_KP_ENTER = 0x9C,
	K_RCTRL = 0x9D,
	K_KP_COMMA = 0xB3,
	K_KP_SLASH = 0xB5,
	K_PRINTSCREEN = 0xB7,
	K_RALT = 0xB8,
	K_PAUSE = 0xC5,
	K_HOME = 0xC7,
	K_UPARROW = 0xC8,
	K_PGUP = 0xC9,
	K_LEFTARROW = 0xCB,
	K_RIGHTARROW = 0xCD,
	K_END = 0xCF,
	K_DOWNARROW = 0xD0,
	K_PGDN = 0xD1,
	K_INS = 0xD2,
	K_DEL = 0xD3,
	K_LWIN = 0xDB,
	K_RWIN = 0xDC,
	K_APPS = 0xDD,
	K_POWER = 0xDE,
	K_SLEEP = 0xDF,

	//------------------------
	// K_JOY codes must be contiguous, too
	//------------------------

	K_JOY1 = 256,
	K_JOY2,
	K_JOY3,
	K_JOY4,
	K_JOY5,
	K_JOY6,
	K_JOY7,
	K_JOY8,
	K_JOY9,
	K_JOY10,
	K_JOY11,
	K_JOY12,
	K_JOY13,
	K_JOY14,
	K_JOY15,
	K_JOY16,

	K_JOY_STICK1_UP,
	K_JOY_STICK1_DOWN,
	K_JOY_STICK1_LEFT,
	K_JOY_STICK1_RIGHT,

	K_JOY_STICK2_UP,
	K_JOY_STICK2_DOWN,
	K_JOY_STICK2_LEFT,
	K_JOY_STICK2_RIGHT,

	K_JOY_TRIGGER1,
	K_JOY_TRIGGER2,

	K_JOY_DPAD_UP,
	K_JOY_DPAD_DOWN,
	K_JOY_DPAD_LEFT,
	K_JOY_DPAD_RIGHT,

	//------------------------
	// K_MOUSE enums must be contiguous (no char codes in the middle)
	//------------------------

	K_MOUSE1,
	K_MOUSE2,
	K_MOUSE3,
	K_MOUSE4,
	K_MOUSE5,
	K_MOUSE6,
	K_MOUSE7,
	K_MOUSE8,

	K_MWHEELDOWN,
	K_MWHEELUP,

	K_LAST_KEY
};

struct sysEvent_t {
	sysEventType_t	evType;
	int				evValue;
	int				evValue2;
	int				evPtrLength;		// bytes of data pointed to by evPtr, for journaling
	void *			evPtr;				// this must be manually freed if not NULL

	int				inputDevice;
	bool			IsKeyEvent() const { return evType == sysEventType_t::SE_KEY; }
	bool			IsMouseEvent() const { return evType == sysEventType_t::SE_MOUSE; }
	bool			IsCharEvent() const { return evType == sysEventType_t::SE_CHAR; }
	bool			IsJoystickEvent() const { return evType == sysEventType_t::SE_JOYSTICK; }
	bool			IsKeyDown() const { return evValue2 != 0; }
	keyNum_t		GetKey() const { return static_cast< keyNum_t >(evValue); }
	int				GetXCoord() const { return evValue; }
	int				GetYCoord() const { return evValue2; }
};

// event generation
void			Sys_GenerateEvents();
sysEvent_t		Sys_GetEvent();
void			Sys_ClearEvents();
#endif /* !__SYS_PUBLIC__ */
