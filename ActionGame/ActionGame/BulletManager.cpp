#include "BulletManager.h"
#include "NormalBullet.h"
#include "CollisionManager.h"
namespace
{
	//�e�̍ő��
	static const int MAX_BULLET = 3;
}

BulletManager::BulletManager(BaseScene* baseScene)
	:BaseManager{baseScene,BaseManager::E_MANAGER_TAG::BULLET}
{

}

BulletManager::~BulletManager()
{
	for (auto it = bulletList.begin(); it != bulletList.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = bulletList.erase(it);
		}
		else it++;
	}
}

void BulletManager::Start()
{
	Init();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		NormalBullet* bullet = new NormalBullet(GetBaseScene());
		bulletList.emplace_back(bullet);
	}
}

void BulletManager::Update()
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		if (!(*it)->GetFlag())continue;
		(*it)->Update();
	}
}

void BulletManager::Draw(F_Vec2 _camDif)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		if (!(*it)->GetFlag())continue;

		//�J�����̊O�ɏo�Ă�����t���O��|��
		//if (CheckCameraViewClip((*it)->GetPosition()) == TRUE)
		//{
		//	(*it)->SetFlag(false);
		//	continue;
		//}

		(*it)->Draw(_camDif);
	}
}
