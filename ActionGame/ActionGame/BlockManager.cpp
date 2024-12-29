#include "BlockManager.h"
#include "CollisionObject.h"


BlockManager::BlockManager(BaseScene* baseScene)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::BLOCK }
{
	CollisionObject* block = new CollisionObject{ GetBaseScene(),F_Vec2{150,500},F_Vec2{0,0},
												-32,32,-32,32,false,BaseObject::E_TAG::BLOCK };
	blockList.emplace_back(block);
	for (int i = 0; i < 20; i++)
	{
		block = new CollisionObject{ GetBaseScene(),F_Vec2{(float)(214+64*i),436},F_Vec2{0,0},
													-32,32,-32,32,false,BaseObject::E_TAG::BLOCK };
		blockList.emplace_back(block);
	}

	block = new CollisionObject{ GetBaseScene(),F_Vec2{300,200},F_Vec2{0,0},
											-32,32,-32,32,false,BaseObject::E_TAG::BLOCK };
	blockList.emplace_back(block);

}

BlockManager::~BlockManager()
{
	for (auto it = blockList.begin(); it != blockList.end();)
	{
		//nullptr����Ȃ���Ώ���
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			//�����ŗv�f�������Ă邩��O�l�߂����
			it = blockList.erase(it);
		}
		else it++;//�v�f���Ȃ���΃C���N�������g��end�ɂ���
	}
}

void BlockManager::Start()
{
	Init();

}

void BlockManager::Update()
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		(*it)->Update();
	}
}

void BlockManager::Draw(F_Vec2 _camDif)
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		(*it)->Draw(_camDif);
	}
}

const std::list<CollisionObject*> BlockManager::GetCollisionObjList() const
{
	std::list<CollisionObject*> collObjList;

	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		collObjList.emplace_back(*it);
	}

	return collObjList;
}

void BlockManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
