#include "CommonObjectAndManager.h"

#include "BlockManager.h"

#include "Player.h"
#include "Camera.h"

#include "BulletManager.h"
#include "EffectManager.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "WarpManager.h"

//ヘッダーで前方宣言したクラスはここでインクルードする

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene, std::vector<std::vector<std::string>> information)
{
	bulletManager = new BulletManager{nowScene};
	effectManager = new EffectManager{ nowScene };
	collisionManager = new CollisionManager{ nowScene };
	blockManager = new BlockManager{ nowScene , information };
	enemyManager = new EnemyManager{ nowScene , information };
	warpManager = new WarpManager{ nowScene,information };

	camera = new Camera{ nowScene , information };
	player = new Player{ nowScene , information };


	bulletManager->Start();
	effectManager->Start();
	collisionManager->Start();
	enemyManager->Start();
	blockManager->Start();
	warpManager->Start();

	player->Start();

}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
