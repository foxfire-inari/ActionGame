#include "CollisionManager.h"
#include"CollisionObject.h"
#include"BlockManager.h"
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

	//今のシーンのマネージャーを取得
	BlockManager* block = GetBaseScene()->GetManagerPtr<BlockManager>(BaseManager::E_MANAGER_TAG::BLOCK);
	assert(block != nullptr);

	//当たり判定で押し出しをするオブジェクトを一つのリストに格納する
	std::list<CollisionObject*> collList;
	std::list<CollisionObject*> allCollList;


	//ここで各マネージャーからオブジェクトを取得する
	//CollisionObject*型で格納
	{
		collList = block->GetCollisionObjList();
		for (auto it = collList.begin(); it != collList.end(); it++)
		{
			allCollList.emplace_back(*it);
		}
		collList.clear();

	}
	
	//allCollListに格納されたオブジェクトの当たり判定をするCollisionProcessingクラス
	collisionProcessing = new CollisionProcessing{ allCollList };

}
