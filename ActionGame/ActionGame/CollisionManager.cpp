#include "CollisionManager.h"

CollisionManager::CollisionManager(BaseScene* baseScene)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::COLLISION }
	, collisionProcessing{ nullptr }
{
}
CollisionManager::~CollisionManager()
{
	if (collisionProcessing != nullptr)delete collisionProcessing;
}

void CollisionManager::Start()
{
	Init();

	//ここで各マネージャーからオブジェクトを取得する
}
