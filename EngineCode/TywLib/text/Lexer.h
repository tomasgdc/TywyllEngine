#ifndef _LEXER_H_
#define _LEXER_H_

/*
===========================================================================
Simple minimalistic lexer
It takes only one line and splits it into tokens
When reading new line, the old data is dumped and new data is parsed
============================================================================
*/

class Lexer 
{
public:
	Lexer();
	~Lexer();

	//loads whole text file into buffer
	void					LoadTextFile(std::string filename, std::string path);

	//frees allocated buffer data
	void					FreeSource();

	//reads token
	void					ReadToken(Token& token);

	//expects certin toekn, read the token while available
	void					ExpectTokenString(const std::string* str);

	//skip the rest of the current line
	void					SkipRestOfLine();

	//skips white space
	void					SkipWhiteSpace();

	//read a signed integer
	int						ParseInt();

	//read a boolean
	bool					ParseBool();

	//read a  floating point number
	float					ParseFloat();

	void					Parse1DVector(int x);
	void					Parse2DVector(int x, int y);
	void					Parse3DVector(int x, int y, int z);
private:
	bool								allocated;
	bool								loaded;
	std::string							filename;
	std::string							buffer;
	int									line;			//current line
	int									lastline;		//line before reading token
	Token								token;			//available token

private:
	void								ReadString(Token& token);
	void								ReadNumber(Token& token);
};
#endif
