#include "CsvFile.h"
#include <iostream>
#include<fstream>
#include<sstream>

CsvFile* CsvFile::Singleton::instance = nullptr;

CsvFile::CsvFile()
{
}

CsvFile::~CsvFile()
{
}

std::vector<std::vector<std::string>> CsvFile::Input(const char* fileName)
{
	//�t�@�C������̓��͂𓾂邽�߂�ifstream���g�p
	std::ifstream ifs(fileName);
	//�S�Ă̏����ς݂̕�������܂Ƃ߂�ϐ�
	std::vector<std::vector<std::string>> result;

	//�t�@�C�����J���Ȃ���Ή������ꂸ���^�[��
	if (!ifs.is_open())return result;

	//��񕪂̕�������󂯎��ϐ�
	std::string line;
	//���̍s��ǉ����邩�̃t���O
	bool isEmplaceBack = true;

	while (std::getline(ifs, line))
	{
		//�ǂݎ�����s�𕪊�
		std::vector<std::string> strvec = split(line, ',');
		//�������ꂽ���̂��m�F��ēx�܂Ƃ߂�
		std::vector<std::string> inputVec;
		isEmplaceBack = true;

		for (int i = 0; i < strvec.size(); i++)
		{
			//���g���Ȃ���΃X�L�b�v
			if (strvec.at(i) == "")continue;
			//�R�����g�A�E�g�͍s���ƕۑ�����Ȃ��悤�ɂ���
			if (strvec.at(i) == "//")
			{
				isEmplaceBack = false;
				break;
			}
			inputVec.emplace_back(strvec.at(i));
		}
		//�R�����g�A�E�g����Ă��Ȃ����result�ɕۑ�
		if (isEmplaceBack)result.emplace_back(inputVec);

		//������
		inputVec.clear();
		strvec.clear();
	}

	return result;
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
