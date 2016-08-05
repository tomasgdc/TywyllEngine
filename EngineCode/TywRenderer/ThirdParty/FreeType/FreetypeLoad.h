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
#ifndef _FREETYPE_H
#define _FREETPYE_H_

#include "../../External/FreeType/include/ft2build.h"
#include FT_FREETYPE_H //Include main FREETYPE2 API



	typedef struct TYWRENDERER_API Data_
	{
		unsigned char *bitmap_buffer;   // texture data
		FT_Vector advance;  // this variable contains the information of how much we need to move to the right from the last character
		int bitmap_left;    // width of the glyph in pixels
		int bitmap_top;     // height of the glyph in pixels
		unsigned int bitmap_width;   // texture width
		unsigned int bitmap_rows;    // texture height
		unsigned int size;   // font size
		char c;     // the character of this glyph
	}Data;

class TYWRENDERER_API GlyphData {
public:
	GlyphData();
	bool LoadGlyph(const char* strTypeface, int point_size, int dpi);
	std::string getLog() const { return log; };
	Data getChar(char c);
	bool InitiliazeChars(const char* source);
	bool Release();
	void ReleaseBuffer();
	~GlyphData();

private:
	inline int NextP2(int a); //This Function Gets The First Power Of 2
	bool IntiliazeFont(const char* strTypeface, int point_size, int dpi);
	FT_Library  library;	/* handle to library     */
	FT_Face     face;      /* handle to face object */
	FT_GlyphSlot glyph;         /*Access glyph information*/
	std::unordered_map<char, Data> glyphs; //Create hash map
	std::string log; //Get any log information
	//char* log -> bitch, breaking bitch
};
#endif
