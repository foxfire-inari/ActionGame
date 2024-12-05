#include "CollisionProcessing.h"
#include"CollisionObject.h"
#include"CollisionData.h"
#include"Fall.h"

namespace
{
	/// <summary>
	/// ���肷�鋗��
	/// </summary>
	static const float HIT_CHECK_DIF = 1000.0f;
}

CollisionProcessing::CollisionProcessing(std::list<CollisionObject*>& _collisionObjectList)
	:collisionObjectList{ _collisionObjectList }
{
}

CollisionProcessing::~CollisionProcessing()
{
	collisionObjectList.clear();
}

F_Vec2 CollisionProcessing::GetSideBlockPosition(BaseObject* obj)
{
	//�L�����N�^�[�̃|�W�V����
	F_Vec2 objPos = obj->GetPosition();
	//�L�����N�^�[�̃R���W����
	CollisionData* objCol = obj->GetNowCollisionPos();

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos;
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		listPos = (*it)->GetPosition();

		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetNowCollisionPos();






	}

	return F_Vec2();
}

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, Fall* fall)
{
	//�L�����N�^�[�̃R���W����
	CollisionData* objCol = obj->GetNowCollisionPos();
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		//if (!IsNewrDistance(*it, obj, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetNowCollisionPos();

		




	}

	return F_Vec2();
}



bool CollisionProcessing::IsNewrDistance(F_Vec2 colpos,F_Vec2 objpos, float dif)
{
	if (F_Vec2::VSize(colpos - objpos) < dif)
		return true;
	return false;
}
