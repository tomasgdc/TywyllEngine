#ifndef _TOKEN_H_
#define _TOKEN_H_

/*
==========================================================
				Token class
		It keeps token as a string and tells what type
		of token it is:
			1)STRING
			2)SPACE
			3)NUMBER
			4)PUNCTUATION
==========================================================
*/

// token types
enum class enumToken
{
	TT_STRING,
	TT_SPACE,
	TT_NUMBER,
	TT_PUNCTUATION
};


class Token {
public:
	Token() {}
	Token(enumToken type, std::string& s);
	~Token();

	static enumToken		GetTokenType(char c);

	const std::string&		GetStringValue()	const;

	enumToken				GetTokenType()      const;
private:
	std::string     m_stringvalue;
	enumToken		m_type;
};
#endif
