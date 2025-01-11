#include "GameScene.h"
#include"CsvFile.h"
#include"Player.h"
#include"Camera.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include"BlockManager.h"
#include"WarpManager.h"

GameScene::GameScene(SceneChange* sceneChange, std::string _nowMapName)
	:BaseScene{sceneChange}
	,nowMapName{_nowMapName}
{
	//マップの生成情報
	std::vector<std::vector<std::string>> information =
		CsvFile::GetInstance()->Input("Data/Csv/Map01.csv");

	common = new CommonObjectAndManager{ this ,information };
}

GameScene::~GameScene()
{
}

bool GameScene::Update()
{
	common->GetPlayer()->Update();
	common->GetBlockManager()->Update();
	common->GetBulletManager()->Update();
	common->GetEnemyManager()->Update();
	common->GetWarpManager()->Update();

	//次のマップに行くならtrue
	if (GoToNextMap())return true;

	return false;
}

void GameScene::Draw()
{
	F_Vec2 camDif = common->GetCamera()->GetTarget();
	common->GetPlayer()->Draw(camDif);
	common->GetBlockManager()->Draw(camDif);
	common->GetBulletManager()->Draw(camDif);
	common->GetEnemyManager()->Draw(camDif);
	common->GetWarpManager()->Draw(camDif);
}

bool GameScene::GoToNextMap()
{
	if (NextMapPlayer(nextMapName))
	{
		GetSceneChange()->Change(E_SCENE::GAME, nextMapName, nowMapName);
		return true;
	}

	return false;
}

bool GameScene::GameOverProcessing()
{
	return false;
}

void GameScene::DrawGameOver()
{
}
