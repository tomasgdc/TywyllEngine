#include <stdafx.h>
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"


Parser::Parser()
{

}

Parser::~Parser()
{

}

int	 Parser::ExpectInt()
{
	std::string output;
	ExpectToken(output);

	return std::stoi(output);
}

float Parser::ExpectFloat()
{
	std::string output;
	ExpectToken(output);

	return std::stof(output);
}

std::string Parser::ExpectString(std::string name)
{
	std::string output;
	ExpectToken(name, output);

	return output;

}

enumError Parser::ExpectToken(std::string& output)
{
	int         ret;
	std::string line;
	enumError   error;
	size_t		position;

	while (std::getline(m_file, line))
	{
		if ((error = CheckErrorBits()) != enumError::PARSE_GOOD)
		{
			return error;
		}

		if (ret != -1)
		{
			return enumError::PARSE_GOOD;
		}
	}
	return enumError::PARSE_EOF;
}

enumError Parser::ExpectToken(std::string& name, std::string& output)
{
	int         ret;
	std::string line;
	enumError   error;
	size_t		position;

	while (std::getline(m_file, line))
	{
		if ( (error = CheckErrorBits()) != enumError::PARSE_GOOD)
		{
			return error;
		}


		if (ret != -1)
		{
			return enumError::PARSE_GOOD;
		}
	}
	return enumError::PARSE_EOF;
}


void Parser::ReadFileIntoMemory()
{
	auto const start_pos = m_file.tellg();
	if (std::streamsize(-1) == start_pos)
	{
		//fucked up
	}

	/*
	if (!m_file.ignore(std::numeric_limits<std::streamsize>::max()))
	{
		//fucked up
	}
	*/

	auto const char_count = m_file.gcount();
	if (!m_file.seekg(start_pos))
	{
		//fucked up
	}
}

enumError Parser::ReadTextFile(std::string name, std::string path)
{
	m_file.open((path + name).c_str(), std::ios::in);
	if (!m_file.is_open())
	{
		return enumError::PARSE_OPEN_FAIL;
	}
	return enumError::PARSE_GOOD;
}


enumError Parser::CheckErrorBits()
{
	if (m_file.eof())
	{
		return enumError::PARSE_EOF;
	}

	else if (m_file.fail())
	{
		return enumError::PARSE_FAIL;
	}

	else if (m_file.bad())
	{
		return enumError::PARSE_BAD;
	}

	return enumError::PARSE_GOOD;
}


inline void Parser::CloseFile()
{
	m_file.close();
}