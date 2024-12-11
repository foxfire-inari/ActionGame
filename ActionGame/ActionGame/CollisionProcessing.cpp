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

	//x���������ړ�
	objPos.x += objVel_X;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//���X�g�̃I�u�W�F�N�g�̍��W����
		listPos = (*it)->GetPosition();

		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetNowCollisionPos();

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(objCol, listCol))
		{
			//�i�s�����ŉ����o���������Œ�
			if (objVel_X < 0)					//�������ɓ����Ă����ꍇ
			{
				objPos.x = listCol->GetRight() + listPos.x;
			}
			else								//�E�����ɓ����Ă����ꍇ
			{
				objPos.x = listCol->GetLeft() + listPos.x;
			}
		}
	}

	return objPos;
}

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, Fall* fall)
{
	//�L�����N�^�[�̃|�W�V����
	F_Vec2 objPos = obj->GetPosition();
	//�L�����N�^�[�̃R���W����
	CollisionData* objCol = obj->GetNowCollisionPos();
	//�L�����N�^�[��X�����̑��x
	float objVel_Y = obj->GetVelocity().y;

	//���X�g���̃I�u�W�F�N�g�̃|�W�V����
	F_Vec2 listPos;
	//���X�g���̃I�u�W�F�N�g�̃R���W����
	CollisionData* listCol;

	bool isOnGround = false;

	//y���������ړ�
	objPos.y += objVel_Y;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//���X�g�̃I�u�W�F�N�g�̍��W����
		listPos = (*it)->GetPosition();

		//�L�����̋߂��Ȃ��Ȃ画�肵�Ȃ�
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//�߂��Ȃ�R���W��������
		listCol = (*it)->GetNowCollisionPos();

		//�u���b�N�Əd�Ȃ��Ă��邩���m�F
		if (IsInBlock(objCol, listCol))
		{
			//�i�s�����ŉ����o���������Œ�
			if (objVel_Y < 0)					//�������ɓ����Ă����ꍇ
			{
				objPos.y = listCol->GetTop() + listPos.y;
			}
			else								//������ɓ����Ă����ꍇ
			{
				objPos.y = listCol->GetUnder() + listPos.y;
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
		listcol->GetTop()  <= objcol->GetUnder() && objcol->GetUnder() <= listcol->GetUnder() ||
		listcol->GetTop()  <= objcol->GetTop()   && objcol->GetTop()   <= listcol->GetUnder() &&
		//�u���b�N�̏c�ɋ��邩
		listcol->GetLeft() <= objcol->GetLeft()  && objcol->GetLeft()  <= listcol->GetRight() ||
		listcol->GetLeft() <= objcol->GetRight() && objcol->GetRight() <= listcol->GetRight()
		);
}
