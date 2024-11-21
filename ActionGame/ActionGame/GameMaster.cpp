#include "GameMaster.h"
#include "KeyControlle.h"
#include"GameScene.h"

GameMaster::GameMaster()
{
	GameScene* gameScene = new GameScene{ this,"GameScene"};
	KeyControlle::Create();
	player = new Player{ gameScene };
}

GameMaster::~GameMaster()
{
	KeyControlle::Destroy();
}


void GameMaster::Update()
{
	player->TestUpdate();
}

bool GameMaster::Change(int nextscenenum, std::string nextmapname, std::string oldmapname)
{


	return false;
}


