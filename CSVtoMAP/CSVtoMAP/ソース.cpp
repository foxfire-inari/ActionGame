#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/// <summary>
/// getlineした文字列をdelimiterごとに分割
/// </summary>
/// <param name="input">gerlineした文字列</param>
/// <param name="delimiter">分割する文字</param>
/// <returns></returns>
vector<string> split(string& input, char delimiter)
{
	//文字列(input)からの入力を得るためにistringstreamを使用
	istringstream stream(input);
	//分割された文字列を受け取る変数
	string str;

	//分割された文字列をまとめる変数
	vector<string> result;

	//delimiterごとに分割して保存
	while (getline(stream, str, delimiter))
	{
		result.emplace_back(str);
	}

	//分割されたものをまとめて返す
	return result;
}


/// <summary>
/// csvファイルでマップを作った後、それを本体のゲームで読み込めるように変更して新しいファイルを作る
/// warpやcamera等のマップに存在しないが必要なデータを書き込みやすいように修正する
/// </summary>
int main()
{
	while (true)
	{
		static const int CSV_DIF = 4;	//.csvは後ろから4番目にあるのでその分減らす用

		string fileName;	//Csvファイルの絶対パスを保存する

		cout << "csvファイルの絶対パスを入力してください" << endl;

		cin >> fileName;

		int findCsv = fileName.rfind(".csv");

		//Csvファイルじゃないならやり直し
		if (findCsv == string::npos ||
			findCsv != fileName.size() - CSV_DIF)
		{
			cout << "csvファイルではありません\ncsvファイルにのみ対応しています" << endl;
			continue;
		}

		//アドレスからcsvファイルを取得
		ifstream ifs(fileName);
		//全ての処理済みの文字列をまとめる変数
		vector<vector<string>> result;

		//ファイルが開かなければやり直し
		if (!ifs.is_open())
		{
			cout << fileName << "は開けません\nパスを確認してください" << endl;
			continue;
		}

		//一列分の文字列を受け取る変数
		string line;
		//この行を追加するかのフラグ
		bool isEmplaceBack = true;

		//各オブジェクトの座標をint型で保存する用
		int posX = 0, posY = 0;

		while (getline(ifs, line))
		{
			//読み取った行を分割
			vector<string> strvec = split(line, ',');
			//分割されたものを確認後再度まとめる用
			vector<string> inputVec;
			isEmplaceBack = true;
			for (int i = 0; i < strvec.size(); i++)
			{
				//中身がなければスキップ
				if (strvec.at(i) == "")continue;
				//0は何も置かないのでスキップ
				if (strvec.at(i) == "0")continue;
				//コメントアウトは行ごと保存されないようにする
				if (strvec.at(i) == "//")
				{
					isEmplaceBack = false;
					break;
				}

				//コメントアウトされていなければresultに保存
				if (isEmplaceBack)
				{
					posX = i;
					//オブジェクトの種類を登録
					inputVec.emplace_back(strvec.at(i));
					//オブジェクトの座標を登録
					inputVec.emplace_back(to_string(posX));
					inputVec.emplace_back(to_string(posY));

					//情報をまとめたものをresultに保存
					result.emplace_back(inputVec);
					//初期化
					inputVec.clear();
				}
			}
			strvec.clear();

			//行が移動したらposYも増やす
			posY++;
		}

		//csvファイルの名前用
		string csvName;

		cout << "ファイルの名前を入力して下さい（拡張子を除く）" << endl;

		cin >> csvName;

		//ファイルを書き出す

		std::ofstream outputCsv("CSV/"+csvName+".csv");
		if (!outputCsv) {
			cerr << "ファイルを開けませんでした。" << std::endl;
			return 1;
		}

		//ファイルにまとめた情報を保存
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

		//処理の切れ目を分かりやすくするために改行を追加している
		cout << csvName << ".csvを保存しました\nslnファイルがあるフォルダからCSVtoMAP/CSVと潜った先にファイルがあります\n" << endl;

	}
}