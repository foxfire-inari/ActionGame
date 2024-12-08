#include "CommonObjectAndManager.h"
#include "Player.h"

#include "CollisionManager.h"

//ヘッダーで前方宣言したクラスはここでインクルードする

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	player = new Player{ nowScene };

	collisionManager = new CollisionManager{ nowScene };


	player->Start();
	collisionManager->Start();
}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
