#include "BackGroundMusic.h"

BackGroundMusic::BackGroundMusic()
{
	LoadSound("Data/BGM/.mp3",E_BGM_KND::TITLE);
	LoadSound("Data/BGM/.mp3",E_BGM_KND::MAP_01);
	LoadSound("Data/BGM/.mp3",E_BGM_KND::BOSS);
}

BackGroundMusic::~BackGroundMusic()
{
	for (auto& i : bgmVec)
	{
		//二つ目の要素（サウンドメモリ）を削除
		DeleteSoundMem(i.second);
	}
}

void BackGroundMusic::PlayBGM(E_BGM_KND _bgmKnd)
{
	for (int i = 0; i < bgmVec.size(); i++)
	{
		//一つ目の要素（BGMの種類）で検索
		if (bgmVec.at(i).first != _bgmKnd)continue;
		//ヒットしたらループで流す
		PlaySoundMem(bgmVec.at(i).second, DX_PLAYTYPE_LOOP);
		break;
	}
}

void BackGroundMusic::StopBGM(E_BGM_KND _bgmKnd)
{
	for (int i = 0; i < bgmVec.size(); i++)
	{
		//一つ目の要素（BGMの種類）で検索
		if (bgmVec.at(i).first != _bgmKnd)continue;

		//ここで止まったなら流れていないBGMを止めようとしている
		//のでコードを見直すべき
		assert(!CheckSoundMem(_bgmKnd));
		
		//ヒットしたら停止する
		StopSoundMem(bgmVec.at(i).second);
		break;
	}
}

void BackGroundMusic::LoadSound(const char* fileName, E_BGM_KND _knd)
{
	//サウンドメモリに登録＆一時的に変数に保存
	int handle = LoadSoundMem(fileName);
	assert(handle > 0);
	//全ての情報をpair型で保存
	std::pair<E_BGM_KND, int> pair = { _knd,handle };
	//bgmVecに登録
	bgmVec.emplace_back(pair);
}
