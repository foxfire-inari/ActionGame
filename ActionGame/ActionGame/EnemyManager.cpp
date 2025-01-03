#include "EnemyManager.h"
#include "Terry.h"
#include "BulletManager.h"
#include "Life.h"
#include "CollisionData.h"
#include "CollisionManager.h"

namespace
{
	/// <summary>
	/// ���肷�鋗��
	/// </summary>
	static const float HIT_CHECK_DIF = 100.0f;
}

EnemyManager::EnemyManager(BaseScene* baseScene)
	:BaseManager{baseScene,BaseManager::E_MANAGER_TAG::ENEMY}
{
}

EnemyManager::~EnemyManager()
{
	for (auto it = enemyList.begin(); it != enemyList.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = enemyList.erase(it);
		}
		else it++;
	}
}

void EnemyManager::Start()
{
	CollisionManager* collision = GetBaseScene()->GetManagerPtr<CollisionManager>(BaseManager::E_MANAGER_TAG::COLLISION);
	assert(collision != nullptr);

	BulletManager* bulletManager = GetBaseScene()->GetManagerPtr<BulletManager>(BaseManager::E_MANAGER_TAG::BULLET);
	assert(bulletManager != nullptr);

	Init();

	Terry* terry = new Terry{ GetBaseScene(),bulletManager,playerBase,F_Vec2{400,100},0 };
	enemyList.emplace_back(terry);

	Terry* terry1 = new Terry{ GetBaseScene(),bulletManager,playerBase,F_Vec2{500,100},0 };
	enemyList.emplace_back(terry1);

	Terry* terry2 = new Terry{ GetBaseScene(),bulletManager,playerBase,F_Vec2{600,500},0 };
	enemyList.emplace_back(terry2);

}

void EnemyManager::Update()
{
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		if (!(*it)->GetFlag())
		{
			it++;
			continue;
		}

		(*it)->Update();
		
		if ((*it)->GetLifePtr()->GetIsDeath())
		{
			delete* it;
			*it = nullptr;
			it = enemyList.erase(it);
		}
		else
			it++;
	}
}

void EnemyManager::Draw(F_Vec2 _camDif)
{
	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		//�J�����̊O�ɏo�Ă�����t���O��|��
		//Draw�̒��Ȃ̂̓J�����̍��W�������邩��
		if (!IsInCamera(_camDif, (*it)))
		{
			(*it)->SetFlag(false);
			continue;
		}
		if(!(*it)->GetFlag())			
			(*it)->SetFlag(true);

		(*it)->Draw(_camDif);
	}
}

int EnemyManager::CheckPlayerHit(CollisionData* colData, int& damageVel)
{
	F_Vec2 plPos = playerBase->GetPosition();

	//���W���l�����������蔻��ɕύX
	CollisionData* nowObjCol = GetNowPositionCol(colData, plPos);

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos; 
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol; 


	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		//100�ȏ㗣��Ă����玟��
		if (!IsNearDistance(*it, HIT_CHECK_DIF))
			continue;
		//����ł����玟��
		if ((*it)->GetLifePtr()->GetHp() <= 0)continue;


		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetCollisionData();
		//���X�g�̃I�u�W�F�N�g�̍��W����
		listPos = (*it)->GetPosition();

		//���W�𑫂��ăR���W���������݂�����W�ɂ���
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//�v���C���[�ɓ������������m�F
		if (IsHitPlayer(nowObjCol, nowlistCol))
		{
			//���W����E�ɔ�΂������ɔ�΂�����Ԃ�
			damageVel = plPos.x - listPos.x >= 0 ? 1 : -1;
			return (*it)->GetPower();
		}
	}

	return -1;
}

bool EnemyManager::IsHitPlayer(CollisionData* objCol, CollisionData* listCol)
{
	//���ꂼ��̃|�W�V�������v�Z�Ɋ܂߂�K�v������
	return (
		//�v���C���[�̉��ɋ��邩
		(listCol->GetTop()<= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder() ||
			listCol->GetTop() <= objCol->GetTop() && objCol->GetTop() <= listCol->GetUnder() ) &&
		//�v���C���[�̏c�ɋ��邩
		(listCol->GetLeft() <= objCol->GetLeft() && objCol->GetLeft() <= listCol->GetRight() ||
			listCol->GetLeft() <= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight())
		);
}

bool EnemyManager::IsInCamera(F_Vec2 _camDif, Enemy* _listObj)
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
		(camCol->GetTop() <= nowListCol->GetUnder() && nowListCol->GetUnder() <= camCol->GetUnder() ||
			camCol->GetTop() <= nowListCol->GetTop() && nowListCol->GetTop() <= camCol->GetUnder()) &&
		//��ʂ̂̏c�ɋ��邩
		(camCol->GetLeft() <= nowListCol->GetLeft() && nowListCol->GetLeft() <= camCol->GetRight() ||
			camCol->GetLeft() <= nowListCol->GetRight() && nowListCol->GetRight() <= camCol->GetRight())
		);
}

CollisionData* EnemyManager::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colData->GetTop() + pos.y,
		colData->GetUnder() + pos.y,
		colData->GetLeft() + pos.x,
		colData->GetRight() + pos.x
	};
	return nowCol;
}

void EnemyManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
