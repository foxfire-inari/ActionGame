#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/// <summary>
/// getline�����������delimiter���Ƃɕ���
/// </summary>
/// <param name="input">gerline����������</param>
/// <param name="delimiter">�������镶��</param>
/// <returns></returns>
vector<string> split(string& input, char delimiter)
{
	//������(input)����̓��͂𓾂邽�߂�istringstream���g�p
	istringstream stream(input);
	//�������ꂽ��������󂯎��ϐ�
	string str;

	//�������ꂽ��������܂Ƃ߂�ϐ�
	vector<string> result;

	//delimiter���Ƃɕ������ĕۑ�
	while (getline(stream, str, delimiter))
	{
		result.emplace_back(str);
	}

	//�������ꂽ���̂��܂Ƃ߂ĕԂ�
	return result;
}


/// <summary>
/// csv�t�@�C���Ń}�b�v���������A�����{�̂̃Q�[���œǂݍ��߂�悤�ɕύX���ĐV�����t�@�C�������
/// warp��camera���̃}�b�v�ɑ��݂��Ȃ����K�v�ȃf�[�^���������݂₷���悤�ɏC������
/// </summary>
int main()
{
	while (true)
	{
		static const int CSV_DIF = 4;	//.csv�͌�납��4�Ԗڂɂ���̂ł��̕����炷�p

		string fileName;	//Csv�t�@�C���̐�΃p�X��ۑ�����

		cout << "csv�t�@�C���̐�΃p�X����͂��Ă�������" << endl;

		cin >> fileName;

		int findCsv = fileName.rfind(".csv");

		//Csv�t�@�C������Ȃ��Ȃ��蒼��
		if (findCsv == string::npos ||
			findCsv != fileName.size() - CSV_DIF)
		{
			cout << "csv�t�@�C���ł͂���܂���\ncsv�t�@�C���ɂ̂ݑΉ����Ă��܂�" << endl;
			continue;
		}

		//�A�h���X����csv�t�@�C�����擾
		ifstream ifs(fileName);
		//�S�Ă̏����ς݂̕�������܂Ƃ߂�ϐ�
		vector<vector<string>> result;

		//�t�@�C�����J���Ȃ���΂�蒼��
		if (!ifs.is_open())
		{
			cout << fileName << "�͊J���܂���\n�p�X���m�F���Ă�������" << endl;
			continue;
		}

		//��񕪂̕�������󂯎��ϐ�
		string line;
		//���̍s��ǉ����邩�̃t���O
		bool isEmplaceBack = true;

		//�e�I�u�W�F�N�g�̍��W��int�^�ŕۑ�����p
		int posX = 0, posY = 0;

		while (getline(ifs, line))
		{
			//�ǂݎ�����s�𕪊�
			vector<string> strvec = split(line, ',');
			//�������ꂽ���̂��m�F��ēx�܂Ƃ߂�p
			vector<string> inputVec;
			isEmplaceBack = true;
			for (int i = 0; i < strvec.size(); i++)
			{
				//���g���Ȃ���΃X�L�b�v
				if (strvec.at(i) == "")continue;
				//0�͉����u���Ȃ��̂ŃX�L�b�v
				if (strvec.at(i) == "0")continue;
				//�R�����g�A�E�g�͍s���ƕۑ�����Ȃ��悤�ɂ���
				if (strvec.at(i) == "//")
				{
					isEmplaceBack = false;
					break;
				}

				//�R�����g�A�E�g����Ă��Ȃ����result�ɕۑ�
				if (isEmplaceBack)
				{
					posX = i;
					//�I�u�W�F�N�g�̎�ނ�o�^
					inputVec.emplace_back(strvec.at(i));
					//�I�u�W�F�N�g�̍��W��o�^
					inputVec.emplace_back(to_string(posX));
					inputVec.emplace_back(to_string(posY));

					//�����܂Ƃ߂����̂�result�ɕۑ�
					result.emplace_back(inputVec);
					//������
					inputVec.clear();
				}
			}
			strvec.clear();

			//�s���ړ�������posY�����₷
			posY++;
		}

		//csv�t�@�C���̖��O�p
		string csvName;

		cout << "�t�@�C���̖��O����͂��ĉ������i�g���q�������j" << endl;

		cin >> csvName;

		//�t�@�C���������o��

		std::ofstream outputCsv("CSV/"+csvName+".csv");
		if (!outputCsv) {
			cerr << "�t�@�C�����J���܂���ł����B" << std::endl;
			return 1;
		}

		//�t�@�C���ɂ܂Ƃ߂�����ۑ�
		for (int y = 0; y < result.size(); y++)
		{
			for (int x = 0; x < result.at(y).size(); x++)
			{
				if (x != 0)
				{
					outputCsv << ",";
				}
				outputCsv << result.at(y).at(x);
			}
			if (y != result.size() - 1)outputCsv << "\n";
		}

		outputCsv.close();

		//�����̐؂�ڂ𕪂���₷�����邽�߂ɉ��s��ǉ����Ă���
		cout << csvName << ".csv��ۑ����܂���\nsln�t�@�C��������t�H���_����CSVtoMAP/CSV�Ɛ�������Ƀt�@�C��������܂�\n" << endl;

	}
}