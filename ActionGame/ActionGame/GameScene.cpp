#include "GameScene.h"
#include"Player.h"
#include"BlockManager.h"

GameScene::GameScene(SceneChange* sceneChange, std::string _nowMapName)
	:BaseScene{sceneChange}
	,nowMapName{_nowMapName}
{
	common = new CommonObjectAndManager{ this };
}

GameScene::~GameScene()
{
}

bool GameScene::Update()
{
	common->GetPlayer()->TestUpdate();
	common->GetBlockManager()->Update();

	return false;
}

void GameScene::Draw()
{
	common->GetBlockManager()->Draw();
}

bool GameScene::GameOverProcessing()
{
	return false;
}

void GameScene::DrawGameOver()
{
}
