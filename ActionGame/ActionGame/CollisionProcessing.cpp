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
	//�L�����N�^�[��X�����̑��x
	float objVel_X = obj->GetVelocity().x;

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


		//x�����������ňړ�
		objPos.x += objVel_X;

		//���ňړ������I�u�W�F�N�g���u���b�N�ɏd�Ȃ��Ă��邩
		bool isSideBlock = 
			(

				listCol->GetTop()  <= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder() ||
				listCol->GetTop()  <= objCol->GetTop()   && objCol->GetTop()   <= listCol->GetUnder() &&

				listCol->GetLeft() <= objCol->GetLeft()  && objCol->GetLeft()  <= listCol->GetRight() ||
				listCol->GetLeft() <= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight()
			);
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

bool CollisionProcessing::IsInBlock(CollisionData* objcol, CollisionData* listcol)
{
	//���ꂼ��̃|�W�V�������v�Z�Ɋ܂߂�K�v������
	return (
		//�u���b�N�̉��ɋ��邩
		listcol->GetTop()  <= objcol->GetUnder() && objcol->GetUnder() <= listcol->GetUnder() ||
		listcol->GetTop()  <= objcol->GetTop()   && objcol->GetTop()   <= listcol->GetUnder() &&
		//�u���b�N�̏c�ɋ��邩
		listcol->GetLeft() <= objcol->GetLeft()  && objcol->GetLeft()  <= listcol->GetRight() ||
		listcol->GetLeft() <= objcol->GetRight() && objcol->GetRight() <= listcol->GetRight()
		);
}
