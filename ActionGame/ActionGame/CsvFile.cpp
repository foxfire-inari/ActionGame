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
	//ファイルからの入力を得るためにifstreamを使用
	std::ifstream ifs(fileName);
	//全ての処理済みの文字列をまとめる変数
	std::vector<std::vector<std::string>> result;

	//ファイルが開かなければ何も入れずリターン
	if (!ifs.is_open())return result;

	//一列分の文字列を受け取る変数
	std::string line;
	//この行を追加するかのフラグ
	bool isEmplaceBack = true;

	while (std::getline(ifs, line))
	{
		//読み取った行を分割
		std::vector<std::string> strvec = split(line, ',');
		//分割されたものを確認後再度まとめる
		std::vector<std::string> inputVec;
		isEmplaceBack = true;

		for (int i = 0; i < strvec.size(); i++)
		{
			//中身がなければスキップ
			if (strvec.at(i) == "")continue;
			//コメントアウトは行ごと保存されないようにする
			if (strvec.at(i) == "//")
			{
				isEmplaceBack = false;
				break;
			}
			inputVec.emplace_back(strvec.at(i));
		}
		//コメントアウトされていなければresultに保存
		if (isEmplaceBack)result.emplace_back(inputVec);

		//初期化
		inputVec.clear();
		strvec.clear();
	}

	return result;
}

std::vector<std::string> CsvFile::split(std::string& input, char delimiter)
{
	//文字列(input)からの入力を得るためにistringstreamを使用
	std::istringstream stream(input);
	//分割された文字列を受け取る変数
	std::string str;

	//分割された文字列をまとめる変数
	std::vector<std::string> result;

	//delimiterごとに分割して保存
	while (std::getline(stream, str, delimiter))
	{
		result.emplace_back(str);
	}

	//分割されたものをまとめて返す
	return result;
}
