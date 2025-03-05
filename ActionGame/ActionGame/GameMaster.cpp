#include "GameMaster.h"

//シングルトンクラス
#include "KeyControlle.h"
#include "Image.h"
#include "BackGroundMusic.h"

//全てのシーンをインクルード
#include "TitleScene.h"
#include "GameScene.h"

GameMaster::GameMaster()
{
	//シングルトンクラスを作成
	KeyControlle::Create();
	Image::Create();
	BackGroundMusic::Create();

	//最初のシーンを追加
	TitleScene* title = new TitleScene{ this};
	scene.emplace_back(title);
}

GameMaster::~GameMaster()
{
	if (scene.empty())return;
	//シーンを全てデリート
	for (auto it = scene.begin(); it != scene.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = scene.erase(it);
		}
		else it++;
	}

	//シングルトンクラスをデリート
	KeyControlle::Destroy();
	Image::Destroy();
	BackGroundMusic::Destroy();
}


void GameMaster::Update()
{
	//キー入力を更新
	KeyControlle::GetInstance()->Update();

	//シーンに中身があれば更新＆描画
	if (scene.empty())return;
	if ((*scene.begin())->Update())return;
	(*scene.begin())->Draw();
}

bool GameMaster::Change(int nextSceneNum, std::string nextMapName, std::string oldMapName)
{
	//今までのシーン全てをリストから消す
	for (auto it = scene.begin(); it != scene.end();)
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = scene.erase(it);
		}
		else it++;
	}

	//次のシーンを登録する
	switch (nextSceneNum)
	{
	case E_SCENE::TITLE:
	{
		TitleScene* title = new TitleScene{ this };
		scene.emplace_front(title);
		(*scene.begin())->Start();
	}
	return true;

	case E_SCENE::GAME:
	{
		GameScene* game = new GameScene{ this,nextMapName ,oldMapName };
		scene.emplace_front(game);
		(*scene.begin())->Start();
	}
	return true;

	default:
		assert(false);
		break;
	}

	return false;
}


