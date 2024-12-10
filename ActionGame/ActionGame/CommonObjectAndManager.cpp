#include "CommonObjectAndManager.h"
#include "CollisionManager.h"

#include "Player.h"


//ヘッダーで前方宣言したクラスはここでインクルードする

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	collisionManager = new CollisionManager{ nowScene };

	player = new Player{ nowScene };



	collisionManager->Start();
	player->Start();

}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
