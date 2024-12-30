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
		//Draw�̒��Ȃ̂̓J�����̍��W�������邩��
		if (!IsInCamera(_camDif, (*it)))
		{
			(*it)->SetFlag(false);
			continue;
		}

		(*it)->Draw(_camDif);
	}
}

void BulletManager::SetState(F_Vec2 pos, F_Vec2 vec)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		//�t���O�������Ă�ꍇ�͓����Ă�̂Ŏg���Ȃ�
		if ((*it)->GetFlag())continue;

		(*it)->SetState(pos, vec);
		break;
	}
}

bool BulletManager::IsInCamera(F_Vec2 _camDif, Bullet* _listObj)
{
	//���W���l�����������蔻���o�^
	CollisionData* nowListCol = GetNowPositionCol(_listObj->GetCollisionData(), _listObj->GetPosition());

	//�`��͈͂𓖂��蔻��Ƃ��ēo�^
	CollisionData* camCol = new CollisionData
	{
		_camDif.y,
		_camDif.y + WINDOW_Y,
		_camDif.x,
		_camDif.x + WINDOW_X
	};

	return (
		//��ʂ̉��ɋ��邩
		(camCol->GetTop() <= nowListCol->GetUnder()  && nowListCol->GetUnder() <= camCol->GetUnder() ||
		 camCol->GetTop() <= nowListCol->GetTop()	 && nowListCol->GetTop()   <= camCol->GetUnder()) &&
		//��ʂ̂̏c�ɋ��邩
		(camCol->GetLeft() <= nowListCol->GetLeft()	 && nowListCol->GetLeft()  <= camCol->GetRight() ||
		 camCol->GetLeft() <= nowListCol->GetRight() && nowListCol->GetRight() <= camCol->GetRight())
		);
}

CollisionData* BulletManager::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colData->GetTop()	+ pos.y,
		colData->GetUnder() + pos.y,
		colData->GetLeft()	+ pos.x,
		colData->GetRight() + pos.x
	};
	return nowCol;
}

void BulletManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
