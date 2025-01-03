#include "CsvFile.h"
#include <iostream>
#include<fstream>
#include<sstream>

CsvFile::CsvFile()
{
}

CsvFile::~CsvFile()
{
}

std::vector<std::vector<std::string>> CsvFile::Input(const char* fileName)
{
	std::ifstream ifs(fileName);


	return std::vector<std::vector<std::string>>();
}

std::vector<std::string> CsvFile::split(std::string& input, char delimiter)
{
	//•¶š—ñ(input)‚©‚ç‚Ì“ü—Í‚ğ“¾‚é‚½‚ß‚Éistringstream‚ğg—p
	std::istringstream stream(input);
	//•ªŠ„‚³‚ê‚½•¶š—ñ‚ğó‚¯æ‚é•Ï”
	std::string str;

	//•ªŠ„‚³‚ê‚½•¶š—ñ‚ğ‚Ü‚Æ‚ß‚é•Ï”
	std::vector<std::string> result;

	//delimiter‚²‚Æ‚É•ªŠ„‚µ‚Ä•Û‘¶
	while (std::getline(stream, str, delimiter))
	{
		result.emplace_back(str);
	}

	//•ªŠ„‚³‚ê‚½‚à‚Ì‚ğ‚Ü‚Æ‚ß‚Ä•Ô‚·
	return result;
}
