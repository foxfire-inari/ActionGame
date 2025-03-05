#pragma once
#include "Singleton.h"

/// <summary>
/// BGMを処理するシングルトンクラス
/// </summary>
class BackGroundMusic : public Singleton<BackGroundMusic>
{
public:
	BackGroundMusic();
	~BackGroundMusic();

	//他のシングルトンクラスと違い
	//BGMクラス内で処理が完結しているため
	//クラス内にenumを作る

	//BGMの種類
	enum E_BGM_KND
	{
		TITLE,
		MAP_01,
		BOSS,
	};

	/// <summary>
	/// BGMを流す
	/// </summary>
	/// <param name="_bgmKnd">流すBGMの種類</param>
	void PlayBGM(E_BGM_KND _bgmKnd);

	/// <summary>
	/// BGMを止める
	/// </summary>
	void StopBGM(E_BGM_KND _bgmKnd);

private:
	//上のE_BGM_KNDと同じ理由で他と保存方法が違う

	/// <summary>
	/// 各BGMをpairのvector型で保存
	/// </summary>
	std::vector<std::pair<E_BGM_KND, int>> bgmVec;

	void LoadSound(const char* fileName, E_BGM_KND _knd);


};