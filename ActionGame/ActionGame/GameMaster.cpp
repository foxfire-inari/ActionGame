#include "GameMaster.h"
#include "KeyControlle.h"

GameMaster::GameMaster()
{
	BaseScene* baseScene = new BaseScene{ this };
	KeyControlle::Create();
	player = new Player{ baseScene };
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


