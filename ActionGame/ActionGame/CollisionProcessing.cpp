#include "CollisionProcessing.h"
#include"CollisionObject.h"
#include"CollisionData.h"
#include"Fall.h"

namespace
{
	/// <summary>
	/// ���肷�鋗��
	/// </summary>
	static const float HIT_CHECK_DIF = 100.0f;
}

CollisionProcessing::CollisionProcessing(std::list<CollisionObject*>& _colObjectList)
	:collisionObjectList{ _colObjectList }
{
}

CollisionProcessing::~CollisionProcessing()
{
	collisionObjectList.clear();
}

F_Vec2 CollisionProcessing::GetSideBlockPosition(BaseObject* obj,CollisionData* objCol)
{
	//�L�����N�^�[�̃|�W�V����
	F_Vec2 objPos = obj->GetPosition();
	//�L�����N�^�[��X�����̑��x
	float objVel_X = obj->GetVelocity().x;

	//x���������ړ�
	objPos.x += objVel_X;

	//���W���l�����������蔻��ɕύX
	CollisionData* nowObjCol = GetNowPositionCol(objCol, objPos);

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos;
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
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

			assert(objVel_X != 0);

			//�i�s�����ŉ����o���������Œ�
			if (objVel_X < 0)					//�������ɓ����Ă����ꍇ
			{
 				objPos.x = nowlistCol->GetRight() - objCol->GetLeft();
			}
			else if (objVel_X > 0)				//�E�����ɓ����Ă����ꍇ
			{
				objPos.x = nowlistCol->GetLeft() - objCol->GetRight();
			}

		}
	}

	return objPos;
}

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, CollisionData* objCol, Fall* fall)
{
	//�L�����N�^�[�̃|�W�V����
	F_Vec2 objPos = obj->GetPosition();
	//�L�����N�^�[��X�����̑��x
	F_Vec2 objVel = obj->GetVelocity();

	//y���������ړ�
	objPos.y -= objVel.y;

	//���W���l�����������蔻��ɕύX
	CollisionData* nowObjCol = GetNowPositionCol(objCol, objPos);

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos;
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	//�n�ʂɌo���Ă��邩���L�^
	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//���X�g�̃I�u�W�F�N�g�̍��W����
		listPos = (*it)->GetPosition();

		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		if (!IsNearDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetCollisionData();
		//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(nowObjCol, nowlistCol))
		{

			assert(objVel.y != 0);

			//�i�s�����ŉ����o���������Œ�
			if (objVel.y < 0)					//�������ɓ����Ă����ꍇ
			{
				objPos.y = nowlistCol->GetTop() - objCol->GetUnder();
				isOnGround = true;
			}
			else								//������ɓ����Ă����ꍇ
			{
				objPos.y = nowlistCol->GetUnder() - objCol->GetTop();
				//Y�����̑��x��0�ɂ���
				obj->SetVelocity(F_Vec2{ objVel.x,0 });
			}
		}
	}

	if (fall != nullptr)
	{
		//�n�ʂɗ����Ă��邩��ۑ�
		fall->SetIsOnGround(isOnGround);
	}

	return objPos;
}



bool CollisionProcessing::IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif)
{
	if (F_Vec2::VSize(listPos - objPos) < dif)
		return true;
	return false;
}

bool CollisionProcessing::IsInBlock(CollisionData* objCol, CollisionData* listCol)
{
	//�߂荞�ݕ␳
	static const float IN_DIF = 0.5f;
	//���ꂼ��̃|�W�V�������v�Z�Ɋ܂߂�K�v������
	return (
		//�u���b�N�̉��ɋ��邩
		(listCol->GetTop()+IN_DIF	<= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder() ||
		 listCol->GetTop()			<= objCol->GetTop()   && objCol->GetTop()   <= listCol->GetUnder()-IN_DIF) &&
		//�u���b�N�̏c�ɋ��邩
		(listCol->GetLeft()			<= objCol->GetLeft()  && objCol->GetLeft()  <= listCol->GetRight()-IN_DIF ||
		 listCol->GetLeft()+IN_DIF	<= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight())
		);
}

CollisionData* CollisionProcessing::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colData->GetTop()	+ pos.y,
		colData->GetUnder()+ pos.y,
		colData->GetLeft()	+ pos.x,
		colData->GetRight()+ pos.x
	};
	return nowCol;
}