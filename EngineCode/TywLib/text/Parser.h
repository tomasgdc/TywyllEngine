#ifndef _PARSER_H_
#define _PARSER_H_


enum class enumError
{
	PARSE_GOOD,			//Indicates that there is no error
	PARSE_EOF,			//End of file reached
	PARSE_FAIL,			//Check whether either failbit or badbit is set
	PARSE_BAD,			//Check whether badbit is set 
	PARSE_OPEN_FAIL		//could not open file
};

class Parser
{
public:
	Parser();
	~Parser();

	int				ExpectInt();
	float			ExpectFloat();
	std::string		ExpectString(std::string name);
	
	enumError		ReadTextFile(std::string name, std::string path);
	void			CloseFile();

private:
	void			ReadFileIntoMemory();
	enumError		ExpectToken(std::string& output);
	enumError		ExpectToken(std::string& name, std::string& output);
	enumError		CheckErrorBits();

private:
	std::ifstream m_file;
	Lexer		  m_lexer;
	std::vector<std::string> m_buffer;
};
#endif
