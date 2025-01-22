#include "WarpManager.h"
#include "WarpObject.h"
#include "CollisionData.h"


namespace
{
	/// <summary>
	/// ���肷�鋗��
	/// </summary>
	static const float HIT_CHECK_DIF = 100.0f;
}

WarpManager::WarpManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{ baseScene ,BaseManager::E_MANAGER_TAG::WARP}
{
	F_Vec2 pos = {};
	int knd = 0;
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));
		if (knd == E_CSV_KND::CSV_WARP)
		{
			SetObject(pos, _info.at(i));
			WarpObject* warp = new WarpObject{ GetBaseScene(),pos,_info.at(i).at(3) };
			warpList.emplace_back(warp);
		}
	}
}

WarpManager::~WarpManager()
{
}

void WarpManager::Update()
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->Update();
	}
}

void WarpManager::Draw(F_Vec2 _camVec)
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->Draw(_camVec);
	}
}

std::string WarpManager::GetNextMapName(BaseObject* obj, CollisionData* objCol)
{
	//���̃}�b�v�̖��O��ێ�����
	std::string nextMapName = "";

	//�L�����N�^�[�̃|�W�V����
	F_Vec2 objPos = obj->GetPosition();

	//���W���l�����������蔻��ɕύX
	CollisionData* nowObjCol = GetNowPositionCol(objCol, objPos);

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos;
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		//���X�g�̃I�u�W�F�N�g�̍��W����
		listPos = (*it)->GetPosition();

		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		if (!IsNearDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetCollisionData();

		//���W�𑫂��ăR���W���������݂�����W�ɂ���
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(nowObjCol, nowlistCol))
		{
			nextMapName =(*it)->GetNextMapName();
		}
	}

	//���̃}�b�v����Ԃ�
	return nextMapName;
}

bool WarpManager::IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif)
{
	if (VSize(listPos - objPos) < dif)
		return true;
	return false;
}

CollisionData* WarpManager::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
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

bool WarpManager::IsInBlock(CollisionData* objCol, CollisionData* listCol)
{
	//�߂荞�ݕ␳
	static const float IN_DIF = 0.5f;
	//�e�ӂ̔�������
	return (
		//list���<=obj���
		listCol->GetTop() + IN_DIF <= objCol->GetUnder() &&
		//list���>=obj���
		listCol->GetUnder() - IN_DIF >= objCol->GetTop() &&
		//list����<=obj�E��
		listCol->GetLeft() + IN_DIF <= objCol->GetRight() &&
		//list�E��>=obj����
		listCol->GetRight() - IN_DIF >= objCol->GetLeft()
		);
}

void WarpManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}