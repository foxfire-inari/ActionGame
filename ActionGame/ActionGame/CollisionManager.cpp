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

	//���̃V�[���̃}�l�[�W���[���擾
	BlockManager* block = GetBaseScene()->GetManagerPtr<BlockManager>(BaseManager::E_MANAGER_TAG::BLOCK);
	assert(block != nullptr);

	//�����蔻��ŉ����o��������I�u�W�F�N�g����̃��X�g�Ɋi�[����
	std::list<CollisionObject*> collList;
	std::list<CollisionObject*> allCollList;


	//�����Ŋe�}�l�[�W���[����I�u�W�F�N�g���擾����
	//CollisionObject*�^�Ŋi�[
	{
		collList = block->GetCollisionObjList();
		for (auto it = collList.begin(); it != collList.end(); it++)
		{
			allCollList.emplace_back(*it);
		}
		collList.clear();

	}
	
	//allCollList�Ɋi�[���ꂽ�I�u�W�F�N�g�̓����蔻�������CollisionProcessing�N���X
	collisionProcessing = new CollisionProcessing{ allCollList };

}
