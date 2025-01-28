#include "CommonObjectAndManager.h"
#include "Common.h"

#include "BlockManager.h"

#include "Player.h"
#include "Camera.h"

#include "BulletManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"
#include "CollisionManager.h"
#include "WarpManager.h"

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene, std::vector<std::vector<std::string>> information)
{
	//各マネージャーを生成＆リストに登録
	blockManager = new BlockManager{ nowScene , information };
	managerList.emplace_back(blockManager);
	bulletManager = new BulletManager{nowScene};
	managerList.emplace_back(bulletManager);
	effectManager = new EffectManager{ nowScene };
	managerList.emplace_back(effectManager);
	enemyManager = new EnemyManager{ nowScene , information };
	managerList.emplace_back(enemyManager);
	warpManager = new WarpManager{ nowScene,information };
	managerList.emplace_back(warpManager);

	//コリジョンマネージャーはUpdate、Draw関数がないので登録しない
	collisionManager = new CollisionManager{ nowScene };

	camera = new Camera{ nowScene , information };
	player = new Player{ nowScene , information };



	collisionManager->Start();
	player->Start();

	for (auto it = managerList.begin(); it != managerList.end(); it++)
	{
		(*it)->Start();
	}
}

CommonObjectAndManager::~CommonObjectAndManager()
{

}

void CommonObjectAndManager::Update()
{
	for (auto it = managerList.begin(); it != managerList.end(); it++)
	{
		(*it)->Update();
	}
}

void CommonObjectAndManager::Draw(F_Vec2 camDif)
{
	for (auto it = managerList.begin(); it != managerList.end(); it++)
	{
		(*it)->Draw(camDif);
	}
}


