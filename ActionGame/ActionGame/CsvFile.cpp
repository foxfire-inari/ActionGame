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
	//������(input)����̓��͂𓾂邽�߂�istringstream���g�p
	std::istringstream stream(input);
	//�������ꂽ��������󂯎��ϐ�
	std::string str;

	//�������ꂽ��������܂Ƃ߂�ϐ�
	std::vector<std::string> result;

	//delimiter���Ƃɕ������ĕۑ�
	while (std::getline(stream, str, delimiter))
	{
		result.emplace_back(str);
	}

	//�������ꂽ���̂��܂Ƃ߂ĕԂ�
	return result;
}
