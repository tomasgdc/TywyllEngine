//Copyright 2015-2016 Tomas Mikalauskas. All rights reserved.

#include "stdafx.h"
#include "framework\Engine.h"
#include "System\win32\win_local.h"

/*===========================
Sys_WPrintf - UTF-16
=============================
*/
void Engine::Sys_WPrintf(FILE* stream, const wchar_t* szFormat, ...) {
	if (szFormat == nullptr)
	{
		Sys_DebugPrintf("szFormat is nullptr. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	va_list pArgs;
	va_start(pArgs, szFormat);

	if (m_bIsSysConsoleRunning)
	{
		//caluclate final string length
		//Only for Windows
		int len = _vsnwprintf(nullptr, 0, szFormat, pArgs);

		//Allocate buffer and space for null termination
		wchar_t * msg = TYW_NEW wchar_t[++len];
		if (msg == nullptr) 
		{
			Sys_DebugPrintf("Could not allocate data for msg. Error at: %s line: %d", __FILE__, __LINE__);
			return;
		}

		//Generate the formated string
		_vsnwprintf(msg, len, szFormat, pArgs);

		//Send message to specific OS
#if defined (WIN32) || defined(_WIN32)
		//Sys_WAppendText(msg);
#elif (_linux)

#elif (_APPLE_)

#endif
	
		//Clean up
		SAFE_DELETE_ARRAY(msg);
	}
	else
	{
		std::vfwprintf(stream, szFormat, pArgs);
	}


	//Clean up
	va_end(pArgs);
}

/*=============================
Sys_Printf - UNICODE
===============================
*/
void Engine::Sys_Printf(FILE* stream, const char* szFormat, ...) {
	if (szFormat == nullptr) {
		Sys_DebugPrintf("szFormat is nullptr. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	va_list pArgs;
	va_start(pArgs, szFormat);

	if (m_bIsSysConsoleRunning)
	{
		//Calculate length of final string
		//WINDOWS // NO LINUX OR APPLE SUPPORT
		int len = _vsnprintf(nullptr, 0, szFormat, pArgs);

		//Allocate buffer and space for null termination
		char * msg = TYW_NEW char[++len];
		if (msg == nullptr) {
			Sys_DebugPrintf("Could not allocate data for msg. Error at: %s line: %d", __FILE__, __LINE__);
			return;
		}

		//Generate the formated string
		_vsnprintf(msg, len, szFormat, pArgs);

		//Send message to specific OS
#if defined (WIN32) || defined(_WIN32)
			//Sys_AppendText(msg);
#elif (_linux)

#elif (_APPLE_)

#endif

		//Clean up
		SAFE_DELETE_ARRAY(msg);
	}
	else
	{
		std::vfprintf(stream, szFormat, pArgs);
	}


	//Clean up
	va_end(pArgs);
}

/*==============================
Sys_WDebugPrintf- UTF-16
=================================
*/
void Engine::Sys_WDebugPrintf(const wchar_t* szFormat, ...) {
	if (szFormat == nullptr) {
		Sys_DebugPrintf("szFormat is nullptr. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	va_list pArgs;
	va_start(pArgs, szFormat);

	//Calculate length of final string
	int len = _vsnwprintf(nullptr, 0, szFormat, pArgs);

	//Allocate buffer and space for null termination
	wchar_t * msg = TYW_NEW wchar_t[++len];
	if (msg == nullptr) {
		Sys_DebugPrintf("Could not allocate data for msg. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	//Generate the formated string
	_vsnwprintf(msg, len, szFormat, pArgs);

	OutputDebugString(reinterpret_cast<LPCTSTR> (msg));

	//Clean up
	va_end(pArgs);
	SAFE_DELETE_ARRAY(msg);
}

/*=================================
Sys_DebugPrintf - UNICODE
===================================
*/
void Engine::Sys_DebugPrintf(const char* szFormat, ...) {
	if (szFormat == nullptr) {
		Sys_DebugPrintf("szFormat is nullptr. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	va_list pArgs;
	va_start(pArgs, szFormat);

	//Calculate length of final string
	//WINDOWS // NO LINUX OR APPLE SUPPORT
	int len = _vsnprintf(nullptr, 0, szFormat, pArgs); 

	 //Allocate buffer and space for null termination
	char * msg = TYW_NEW char[++len];
	if (msg == nullptr) {
		Sys_DebugPrintf("Could not allocate data for msg. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	//Generate the formated string
	_vsnprintf(msg, len, szFormat, pArgs);

	OutputDebugString(reinterpret_cast<LPCTSTR> (msg));

	//Clean up
	va_end(pArgs);
	SAFE_DELETE_ARRAY(msg);
}

/*=================================
Sys_WError - UTF-16
===================================
*/
void Engine::Sys_WError(FILE* stream, const wchar_t* szFormat, ...) {
	if (szFormat == nullptr) {
		Sys_DebugPrintf("szFormat is nullptr. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	va_list pArgs;
	va_start(pArgs, szFormat);

	if (m_bIsSysConsoleRunning)
	{
		//Calculate length of final string
		int len = _vsnwprintf(nullptr, 0, szFormat, pArgs);

		//Allocate buffer and space for null termination
		wchar_t * msg = TYW_NEW wchar_t[++len];
		if (msg == nullptr) {
			Sys_DebugPrintf("Could not allocate data for msg. Error at: %s line: %d", __FILE__, __LINE__);
			return;
		}

		//Generate the formated string
		_vsnwprintf(msg, len, szFormat, pArgs);

		//OutputDebugString(msg);

		//Send message to specific OS
#if defined (WIN32) || defined(_WIN32)
		//Sys_WAppendText(msg);
#elif (_linux)

#elif (_APPLE_)

#endif

		//Clean up
		SAFE_DELETE_ARRAY(msg);
	}
	else
	{
		std::vfwprintf(stream, szFormat, pArgs);
	}

	//Clean up
	va_end(pArgs);
	
}

/*=================================
Sys_Error - UNICODE
===================================
*/
void Engine::Sys_Error(FILE * stream, const char* szFormat, ...) 
{
	if (szFormat == nullptr) {
		Sys_DebugPrintf("szFormat is nullptr. Error at: %s line: %d", __FILE__, __LINE__);
		return;
	}

	va_list pArgs;
	va_start(pArgs, szFormat);

	if (m_bIsSysConsoleRunning)
	{
		//Calculate length of final string
		int len = _vsnprintf(nullptr, 0, szFormat, pArgs);

		//Allocate buffer and space for null termination
		char * msg = TYW_NEW char[++len];
		if (msg == nullptr) {
			Sys_DebugPrintf("Could not allocate data for msg. Error at: %s line: %d", __FILE__, __LINE__);
			return;
		}

		//Generate the formated string
		_vsnprintf(msg, len, szFormat, pArgs);

		//OutputDebugString(reinterpret_cast<LPCWSTR> (msg));

		//Send message to specific OS
#if defined (WIN32) || defined(_WIN32)
		//Sys_AppendText(msg);
#elif (_linux)

#elif (_APPLE_)

#endif

		//Clean up
		SAFE_DELETE_ARRAY(msg);
	}
	else
	{
		std::vfprintf(stream, szFormat, pArgs);
	}



	//Clean up
	va_end(pArgs);
}
