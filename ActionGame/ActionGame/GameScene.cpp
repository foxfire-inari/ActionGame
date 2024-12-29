#include "GameScene.h"
#include"Player.h"
#include"Camera.h"
#include "BulletManager.h"
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
	common->GetPlayer()->Update();
	common->GetBlockManager()->Update();
	common->GetBulletManager()->Update();

	return false;
}

void GameScene::Draw()
{
	F_Vec2 camDif = common->GetCamera()->GetTarget();
	common->GetPlayer()->Draw(camDif);
	common->GetBlockManager()->Draw(camDif);
	common->GetBulletManager()->Draw(camDif);
}

bool GameScene::GameOverProcessing()
{
	return false;
}

void GameScene::DrawGameOver()
{
}
