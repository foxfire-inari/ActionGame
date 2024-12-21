#include "BlockManager.h"
#include "CollisionObject.h"


BlockManager::BlockManager(BaseScene* baseScene)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::BLOCK }
{
	CollisionObject* block = new CollisionObject{ GetBaseScene(),F_Vec2{150,500},F_Vec2{0,0},
												-32,32,-32,32,false,BaseObject::E_TAG::BLOCK };
	BlockList.emplace_back(block);
	for (int i = 0; i < 5; i++)
	{
		block = new CollisionObject{ GetBaseScene(),F_Vec2{(float)(214+64*i),436},F_Vec2{0,0},
													-32,32,-32,32,false,BaseObject::E_TAG::BLOCK };
		BlockList.emplace_back(block);
	}
	block = new CollisionObject{ GetBaseScene(),F_Vec2{(float)(214 + 64 * 5),500},F_Vec2{0,0},
											-32,32,-32,32,false,BaseObject::E_TAG::BLOCK };
	BlockList.emplace_back(block);

}

BlockManager::~BlockManager()
{
	for (auto it = BlockList.begin(); it != BlockList.end();)
	{
		//nullptr‚¶‚á‚È‚¯‚ê‚ÎÁ‚·
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			//‚±‚±‚Å—v‘f‚ðÁ‚µ‚Ä‚é‚©‚ç‘O‹l‚ß‚³‚ê‚é
			it = BlockList.erase(it);
		}
		else it++;//—v‘f‚ª‚È‚¯‚ê‚ÎƒCƒ“ƒNƒŠƒƒ“ƒg‚Åend‚É‚·‚é
	}
}

void BlockManager::Start()
{
	Init();

}

void BlockManager::Update()
{
	for (auto it = BlockList.begin(); it != BlockList.end(); it++)
	{
		(*it)->Update();
	}
}

void BlockManager::Draw(F_Vec2 _camDif)
{
	for (auto it = BlockList.begin(); it != BlockList.end(); it++)
	{
		(*it)->Draw(_camDif);
	}
}

const std::list<CollisionObject*> BlockManager::GetCollisionObjList() const
{
	std::list<CollisionObject*> collObjList;

	for (auto it = BlockList.begin(); it != BlockList.end(); it++)
	{
		collObjList.emplace_back(*it);
	}

	return collObjList;
}

void BlockManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = BlockList.begin(); it != BlockList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
