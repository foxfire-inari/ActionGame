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

EnemyManager::EnemyManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{baseScene,BaseManager::E_MANAGER_TAG::ENEMY}
{
	information = _info;
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

	F_Vec2 pos = {};

	//�ǂݍ��񂾃f�[�^�Ńu���b�N�𐶐�����
	int knd = 0;
	for (int y = 0; y < information.size(); y++)
	{
		for (int x = 0; x < information.at(y).size(); x++)
		{
			knd = std::stoi(information.at(y).at(x));

			if (knd == E_CSV_KND::CSV_ENEMY_TERRY)
			{
				pos = { static_cast<float>(x),static_cast<float>(y) };
				SetObject(pos, information.at(y));
				Terry* enemy = new Terry{ GetBaseScene(),bulletManager,playerBase,pos, Enemy::E_ENEMY_KND::TERRY};
				enemyList.emplace_back(enemy);
				continue;
			}
		}
	}
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

int EnemyManager::CheckPlayerHit(CollisionData* colData)
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
			return (*it)->GetPower();
		}
	}

	return -1;
}

bool EnemyManager::IsHitPlayer(CollisionData* objCol, CollisionData* listCol)
{
	//���ꂼ��̃|�W�V�������v�Z�Ɋ܂߂�K�v������
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

	//�e�ӂ̔�������
	return (
		//list���<=obj���
		camCol->GetTop()	<= nowListCol->GetUnder() &&
		//list���>=obj���
		camCol->GetUnder()	>= nowListCol->GetTop() &&
		//list����<=obj�E��
		camCol->GetLeft()	<= nowListCol->GetRight() &&
		//list�E��>=obj����
		camCol->GetRight()	>= nowListCol->GetLeft()
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
