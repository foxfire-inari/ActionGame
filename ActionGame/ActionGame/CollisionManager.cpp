#include "CollisionManager.h"
#include"CollisionProcessing.h"

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

	//当たり判定で押し出しをするオブジェクトを一つのリストに格納する
	std::list<CollisionObject*> collList;
	std::list<CollisionObject*> allCollList;


	//ここで各マネージャーからオブジェクトを取得する
	
	//allCollListに格納されたオブジェクトの当たり判定をするCollisionProcessingクラス
	collisionProcessing = new CollisionProcessing{ allCollList };

}
