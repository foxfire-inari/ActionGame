#pragma once
#include "Singleton.h"

/// <summary>
/// csvファイルを読み込むシングルトンクラス
/// </summary>
class CsvFile : public Singleton<CsvFile>
{
public:
	CsvFile();
	~CsvFile();
	
	/// <summary>
	/// csvファイルの読み込み
	/// </summary>
	/// <param name="fileName">読み込むファイルの名前</param>
	/// <returns>読み込んだデータ</returns>
	std::vector<std::vector<std::string>> Input(const char* fileName);
	
	
private:

	/// <summary>
	/// getlineした文字列をdelimiterごとに分割
	/// </summary>
	/// <param name="input">gerlineした文字列</param>
	/// <param name="delimiter">分割する文字</param>
	/// <returns></returns>
	std::vector<std::string>
		split(std::string& input, char delimiter);
	
};

//取得する文字列の要素(左から)
// 種類(ブロックか敵か等)
// 詳細な種類(敵やブロックの種類)
// 初期座標(Csvの行と列で管理)
// 
//