#include "GameMaster.h"
#include "KeyControlle.h"
#include"GameScene.h"

GameMaster::GameMaster()
{
	GameScene* gameScene = new GameScene{ this,"Map_1"};
	scene.emplace_back(gameScene);

	KeyControlle::Create();
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
}


void GameMaster::Update()
{
	if (scene.empty())return;
	if ((*scene.begin())->Update())return;
	(*scene.begin())->Draw();
}

bool GameMaster::Change(int nextscenenum, std::string nextmapname, std::string oldmapname)
{


	return false;
}


