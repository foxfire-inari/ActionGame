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

F_Vec2 CollisionProcessing::GetOnGroundPosition(BaseObject* obj, Fall* fall)
{
	//�L�����N�^�[�̃R���W����
	CollisionData* objCol = obj->GetNowCollisionPos();
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		if (!IsNewrDistance(*it, obj, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetNowCollisionPos();

		//�L�������u���b�N�̏㉺�ɂ���
		bool isInBlock_X =
			(
				//�L�����̉E�����I�u�W�F�N�g�͈͓̔���
				listCol->GetLeft() + 5 <= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight() - 5 ||
				//�L�����̍������I�u�W�F�N�g�͈͓̔���
				listCol->GetLeft() + 5 <= objCol->GetLeft()  && objCol->GetLeft()  <= listCol->GetRight() - 5
			);

		//fabsf(this->x - vec.x) <= FLT_EPSILON
		//���g���ׂ����ۂ�

		//�L�������u���b�N�ɏd�Ȃ��Ă���
		bool isOnBlock = isInBlock_X &&
			listCol->GetTop() <= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder();



	}

	return F_Vec2();
}



bool CollisionProcessing::IsNewrDistance(BaseObject* obj, BaseObject* chara, float dif)
{
	if (F_Vec2::VSize(obj->GetPosition() - chara->GetPosition()) < dif)
		return true;
	return false;
}
