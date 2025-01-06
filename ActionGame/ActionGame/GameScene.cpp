#include "GameScene.h"
#include"CsvFile.h"
#include"Player.h"
#include"Camera.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include"BlockManager.h"

GameScene::GameScene(SceneChange* sceneChange, std::string _nowMapName)
	:BaseScene{sceneChange}
	,nowMapName{_nowMapName}
{
	//ƒ}ƒbƒv‚Ì¶¬î•ñ
	std::vector<std::vector<std::string>> information =
		CsvFile::GetInstance()->Input("Data/Csv/Map01_01.csv");

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

	return false;
}

void GameScene::Draw()
{
	F_Vec2 camDif = common->GetCamera()->GetTarget();
	common->GetPlayer()->Draw(camDif);
	common->GetBlockManager()->Draw(camDif);
	common->GetBulletManager()->Draw(camDif);
	common->GetEnemyManager()->Draw(camDif);

}

bool GameScene::GameOverProcessing()
{
	return false;
}

void GameScene::DrawGameOver()
{
}
