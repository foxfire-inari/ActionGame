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

CollisionProcessing::CollisionProcessing(std::list<CollisionObject*>& _collisionObjectList)
	:collisionObjectList{ _collisionObjectList }
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

	CollisionData* nowobjCol = GetNowPositionColl(objCol, objPos);

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
		listCol = (*it)->GetCollisionPos();
		
		//���W�𑫂��ăR���W���������݂�����W�ɂ���
		CollisionData* nowlistCol = GetNowPositionColl(listCol, listPos);

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(nowobjCol, nowlistCol))
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
	float objVel_Y = obj->GetVelocity().y;

	//y���������ړ�
	objPos.y -= objVel_Y;

	//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
	CollisionData* nowobjCol = GetNowPositionColl(objCol, objPos);

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
		listCol = (*it)->GetCollisionPos();
		//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
		CollisionData* nowlistCol = GetNowPositionColl(listCol, listPos);

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(nowobjCol, nowlistCol))
		{

			assert(objVel_Y != 0);

			//�i�s�����ŉ����o���������Œ�
			if (objVel_Y < 0)					//�������ɓ����Ă����ꍇ
			{
				objPos.y = nowlistCol->GetTop() - objCol->GetUnder();
				isOnGround = true;
			}
			else								//������ɓ����Ă����ꍇ
			{
				objPos.y = nowlistCol->GetUnder() - objCol->GetTop();
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



bool CollisionProcessing::IsNearDistance(F_Vec2 colpos,F_Vec2 objpos, float dif)
{
	if (F_Vec2::VSize(colpos - objpos) < dif)
		return true;
	return false;
}

bool CollisionProcessing::IsInBlock(CollisionData* objcol, CollisionData* listcol)
{
	//�߂荞�ݕ␳
	static const float IN_DIF = 0.5f;
	//���ꂼ��̃|�W�V�������v�Z�Ɋ܂߂�K�v������
	return (
		//�u���b�N�̉��ɋ��邩
		(listcol->GetTop()+IN_DIF	<= objcol->GetUnder() && objcol->GetUnder() <= listcol->GetUnder() ||
		 listcol->GetTop()			<= objcol->GetTop()   && objcol->GetTop()   <= listcol->GetUnder()-IN_DIF) &&
		//�u���b�N�̏c�ɋ��邩
		(listcol->GetLeft()			<= objcol->GetLeft()  && objcol->GetLeft()  <= listcol->GetRight()-IN_DIF ||
		 listcol->GetLeft()+IN_DIF	<= objcol->GetRight() && objcol->GetRight() <= listcol->GetRight())
		);
}

CollisionData* CollisionProcessing::GetNowPositionColl(CollisionData* colldata, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colldata->GetTop()	+ pos.y,
		colldata->GetUnder()+ pos.y,
		colldata->GetLeft()	+ pos.x,
		colldata->GetRight()+ pos.x
	};
	return nowCol;
}