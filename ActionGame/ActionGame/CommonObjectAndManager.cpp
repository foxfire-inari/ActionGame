#include "CommonObjectAndManager.h"

#include "BlockManager.h"

#include "Player.h"
#include "Camera.h"

#include "BulletManager.h"
#include "CollisionManager.h"


//ヘッダーで前方宣言したクラスはここでインクルードする

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	bulletManager = new BulletManager{nowScene};
	collisionManager = new CollisionManager{ nowScene };
	blockManager = new BlockManager{ nowScene };

	camera = new Camera{ nowScene };
	player = new Player{ nowScene };


	bulletManager->Start();
	collisionManager->Start();
	blockManager->Start();

	player->Start();

}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
