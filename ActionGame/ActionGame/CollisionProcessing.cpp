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
	//�L�����N�^�[��X�����̑��x
	float objVel_X = obj->GetVelocity().x;

	//x���������ړ�
	objPos.x += objVel_X;

	//�L�����N�^�[�̃R���W����
	CollisionData* objCol = obj->GetCollisionPos();

	//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
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
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetCollisionPos();
		
		//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
		CollisionData* nowlistCol = GetNowPositionColl(listCol, listPos);

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(nowobjCol, nowlistCol))
		{

			//assert(objVel_X != 0);

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

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, Fall* fall)
{
	//�L�����N�^�[�̃|�W�V����
	F_Vec2 objPos = obj->GetPosition();
	//�L�����N�^�[��X�����̑��x
	float objVel_Y = obj->GetVelocity().y;

	//y���������ړ�
	objPos.y += objVel_Y;

	//�L�����N�^�[���ړ�������̂̃R���W����
	CollisionData* objCol = obj->GetCollisionPos();
	//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
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
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetCollisionPos();
		//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
		CollisionData* nowlistCol = GetNowPositionColl(listCol, listPos);

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(nowobjCol, nowlistCol))
		{
			//�i�s�����ŉ����o���������Œ�
			if (objVel_Y > 0)					//�������ɓ����Ă����ꍇ
			{
				objPos.y = nowlistCol->GetTop() - objCol->GetUnder();
			}
			else								//������ɓ����Ă����ꍇ
			{
				objPos.y = nowlistCol->GetUnder() - objCol->GetTop();
			}
		}
	}

	return objPos;
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
		(listcol->GetTop()  <= objcol->GetUnder() && objcol->GetUnder() <= listcol->GetUnder() ||
		listcol->GetTop()  <= objcol->GetTop()   && objcol->GetTop()   <= listcol->GetUnder()) &&
		//�u���b�N�̏c�ɋ��邩
		(listcol->GetLeft() <= objcol->GetLeft()  && objcol->GetLeft()  <= listcol->GetRight() ||
		listcol->GetLeft() <= objcol->GetRight() && objcol->GetRight() <= listcol->GetRight())
		);
}

CollisionData* CollisionProcessing::GetNowPositionColl(CollisionData* colldata, F_Vec2 pos)
{
	//�O�̂��ߏ����_��؂�̂ĂĂ���int�^�ɕύX
	CollisionData* nowCol = new CollisionData
	{
		colldata->GetTop()	+ (int)floor(pos.y),
		colldata->GetUnder()+ (int)floor(pos.y),
		colldata->GetLeft()	+ (int)floor(pos.x),
		colldata->GetRight()+ (int)floor(pos.x)
	};
	return nowCol;
}