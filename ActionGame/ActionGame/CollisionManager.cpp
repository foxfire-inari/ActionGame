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

	//�����蔻��ŉ����o��������I�u�W�F�N�g����̃��X�g�Ɋi�[����
	std::list<CollisionObject*> collList;
	std::list<CollisionObject*> allCollList;


	//�����Ŋe�}�l�[�W���[����I�u�W�F�N�g���擾����
	
	//allCollList�Ɋi�[���ꂽ�I�u�W�F�N�g�̓����蔻�������CollisionProcessing�N���X
	collisionProcessing = new CollisionProcessing{ allCollList };

}
