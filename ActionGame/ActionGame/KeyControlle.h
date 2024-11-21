#pragma once
#include"Common.h"
#include"Vector"

class KeyControlle
{
public:

	/// <summary>
	/// KeyLogに対象のキーがあるかの確認
	/// </summary>
	/// <param name="KEY_INPUT">対象とするキー</param>
	/// <returns>あるならTrue</returns>
	bool FindKeyLog(int KEY_INPUT);

	/// <summary>
	/// KeyLogにある対象のキーログがあれば削除
	/// </summary>
	/// <param name="KEY_INPUT">対象とするキー</param>
	void DeletKeyLog(int KEY_INPUT);

	/// <summary>
	/// 対象のキーが押された瞬間
	/// </summary>
	/// <param name="KEY_INPUT">対象とするキー</param>
	/// <returns>押された瞬間ならTrue</returns>
	bool GetKeyDown(int KEY_INPUT);

	/// <summary>
	/// 対象のキーが押され続けているか
	/// </summary>
	/// <param name="KEY_INPUT">対象とするキー</param>
	/// <returns>押され続けているならTrue</returns>
	bool GetKeyPressed(int KEY_INPUT);

	//全てのファイルで同じものを取得させる
	static  KeyControlle* GetInstance()
	{
		return instance;
	}

	/// <summary>
	/// 生成（instanceに中身を入れて動くようにする）
	/// </summary>
	static void Create();

	/// <summary>
	/// 削除（instanceの中身をnullptrにして動かないようにする）
	/// </summary>
	static void Destroy();
private:
	//KeyCOntrolleのインスタンス
	static KeyControlle* instance;

	//キーの動的配列
	std::vector<int> KeyLog;
};
