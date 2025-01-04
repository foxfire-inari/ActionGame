#pragma once
#include "Singleton.h"

/// <summary>
/// csv�t�@�C����ǂݍ��ރV���O���g���N���X
/// </summary>
class CsvFile : public Singleton<CsvFile>
{
public:
	CsvFile();
	~CsvFile();
	
	/// <summary>
	/// csv�t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="fileName">�ǂݍ��ރt�@�C���̖��O</param>
	/// <returns>�ǂݍ��񂾃f�[�^</returns>
	std::vector<std::vector<std::string>> Input(const char* fileName);
	
	
private:

	/// <summary>
	/// getline�����������delimiter���Ƃɕ���
	/// </summary>
	/// <param name="input">gerline����������</param>
	/// <param name="delimiter">�������镶��</param>
	/// <returns></returns>
	std::vector<std::string>
		split(std::string& input, char delimiter);
	
};

//�擾���镶����̗v�f(������)
// ���(�u���b�N���G����)
// �ڍׂȎ��(�G��u���b�N�̎��)
// �������W(Csv�̍s�Ɨ�ŊǗ�)
// 
//