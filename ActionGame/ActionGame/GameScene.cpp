#include "GameScene.h"

GameScene::GameScene(SceneChange* sceneChange, std::string _nowMapName)
	:BaseScene{sceneChange}
	,nowMapName{_nowMapName}
{
}

GameScene::~GameScene()
{
}

bool GameScene::Update()
{


	return false;
}

void GameScene::Draw()
{
}

bool GameScene::GameOverProcessing()
{
	return false;
}

void GameScene::DrawGameOver()
{
}
