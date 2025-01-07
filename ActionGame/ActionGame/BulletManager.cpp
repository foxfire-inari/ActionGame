#include "BulletManager.h"
#include "NormalBullet.h"
#include "Enemy.h"
#include "Life.h"
#include "CollisionData.h"
#include "CollisionManager.h"
#include "EnemyManager.h"

namespace
{
	//�e�̍ő��
	static const int MAX_BULLET = 3;
	// ���肷�鋗��
	static const float HIT_CHECK_DIF = 100.0f;
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

int BulletManager::HitCheckEnemy(Enemy* enemyPtr, CollisionData* colData)
{
	int damage = 0;

	F_Vec2 enePos = enemyPtr->GetPosition();

	//���W���l�����������蔻��ɕύX
	CollisionData* nowObjCol = GetNowPositionCol(colData, enePos);

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos;
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;


	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{		
		//�t���O�������Ă��Ȃ������玟��
		if (!(*it)->GetFlag())continue;

		//���X�g�̃I�u�W�F�N�g�̍��W����
		listPos = (*it)->GetPosition();

		//600�ȏ㗣��Ă����玟��
		if (!IsNearDistance(listPos,enePos, HIT_CHECK_DIF))
			continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetCollisionData();

		//���W�𑫂��ăR���W���������݂�����W�ɂ���
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//�Ώۂɓ������������m�F
		if (IsHitObject(nowObjCol, nowlistCol))
		{
			//�������Ă�����t���O��|���_���[�W��^����
			(*it)->SetFlag(false);
			damage += (*it)->GetPower();
		}
	}

	return damage;
}
bool BulletManager::IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif)
{
	if (F_Vec2::VSize(listPos - objPos) < dif)
		return true;
	return false;
}

bool BulletManager::IsHitObject(CollisionData* objCol, CollisionData* listCol)
{
	//�e�ӂ̔�������
	return (
		//list���<=obj���
		listCol->GetTop()	<= objCol->GetUnder()	&&
		//list���>=obj���
		listCol->GetUnder()	>= objCol->GetTop()		&&
		//list����<=obj�E��
		listCol->GetLeft()	<= objCol->GetRight()	&&
		//list�E��>=obj����
		listCol->GetRight()	>= objCol->GetLeft()
		);
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
