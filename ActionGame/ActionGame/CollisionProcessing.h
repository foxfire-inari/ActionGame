#pragma once
#include"Common.h"
class BaseObject;
class CollisionObject;
class CollisionData;
class Fall;

class CollisionProcessing
{
public:
	CollisionProcessing(std::list<CollisionObject*>& _colObjectList);
	~CollisionProcessing();

	/// <summary>
	/// �������̈ړ�������
	/// �I�u�W�F�N�g�ƃu���b�N�̉������̂߂荞�ݕ␳
	/// </summary>
	/// <param name="obj">���肷��I�u�W�F�N�g</param>
	/// <param name="objCol">�I�u�W�F�N�g�̃R���W�����f�[�^</param>
	/// <returns></returns>
	F_Vec2 GetSideBlockPosition(BaseObject* obj, CollisionData* objCol);

	/// <summary>
	/// �c�����̈ړ�������
	/// �I�u�W�F�N�g���u���b�N�̏�ɂ��邩�Ƃ߂荞�ݕ␳
	/// </summary>
	/// <param name="obj">���肷��I�u�W�F�N�g</param>
	/// <param name="objCol">�I�u�W�F�N�g�̃R���W�����f�[�^</param>
	/// <param name="fall">�����Ă��邩���Z�b�g</param>
	/// <returns></returns>
	F_Vec2 GetOnBlockPosition(BaseObject* obj, CollisionData* objCol, Fall* fall = nullptr);

private:
	std::list<CollisionObject*> collisionObjectList;

	/// <summary>
	/// �߂��ɂ��邩�̔���
	/// </summary>
	/// <param name="objPos">����̒��S�ɂȂ���W</param>
	/// <param name="listPos">���X�g���̔��肷����W</param>
	/// <param name="dif"></param>
	/// <returns></returns>
	bool IsNearDistance( F_Vec2 objPos, F_Vec2 listPos, float dif);

	/// <summary>
	/// �u���b�N�Əd�Ȃ��Ă��邩
	/// </summary>
	/// <param name="objcol">���肷��I�u�W�F�N�g�̃R���W�����f�[�^</param>
	/// <param name="listcol">���X�g���̃R���W�����f�[�^</param>
	/// <returns></returns>
	bool IsInBlock(CollisionData* objCol,CollisionData* listCol);

	/// <summary>
	/// �R���W�����̌��݂̍��W���擾
	/// </summary>
	/// <param name="colData">�R���W�����f�[�^</param>
	/// <param name="pos">������̍��W</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

};

