#include "CollisionManager.h"

CollisionManager::CollisionManager(BaseScene* baseScene)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::COLLISION }
{
}
CollisionManager::~CollisionManager()
{
}

void CollisionManager::Start()
{
	Init();

	//ここで各マネージャーからオブジェクトを取得する
}
