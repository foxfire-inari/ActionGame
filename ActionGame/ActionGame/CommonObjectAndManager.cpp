#include "CommonObjectAndManager.h"

#include "BlockManager.h"

#include "Player.h"
#include "Camera.h"

#include "CollisionManager.h"


//ヘッダーで前方宣言したクラスはここでインクルードする

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	collisionManager = new CollisionManager{ nowScene };
	blockManager = new BlockManager{ nowScene };

	camera = new Camera{ nowScene };
	player = new Player{ nowScene };



	collisionManager->Start();
	blockManager->Start();

	player->Start();

}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
