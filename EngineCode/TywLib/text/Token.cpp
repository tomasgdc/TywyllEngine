#include <stdafx.h>
#include "Token.h"


Token::Token(enumToken type, std::string& s) :m_type(type), m_stringvalue(s)
{

}

Token::~Token()
{

}

enumToken Token::GetTokenType(char c)
{
	if (ispunct(c))
		return enumToken::TT_PUNCTUATION;

	else if (c == ' ')
		return enumToken::TT_SPACE;

	else if (isdigit(c))
		return enumToken::TT_NUMBER;

	return enumToken::TT_STRING;
}

inline const std::string& Token::GetStringValue() const
{
	return m_stringvalue;
}

inline enumToken Token::GetTokenType() const
{
	return m_type;
}