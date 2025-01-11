#include "GameMaster.h"
#include "KeyControlle.h"
#include "Image.h"

#include"GameScene.h"

GameMaster::GameMaster()
{
	KeyControlle::Create();
	Image::Create();

	GameScene* gameScene = new GameScene{ this,"Map_01"};
	scene.emplace_back(gameScene);
}

GameMaster::~GameMaster()
{
	if (scene.empty())return;
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

	KeyControlle::Destroy();
	Image::Destroy();
}


void GameMaster::Update()
{

	KeyControlle::GetInstance()->Update();

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

	switch (nextSceneNum)
	{

	case E_SCENE::GAME:
	{
		GameScene* game = new GameScene{ this,nextMapName };
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


