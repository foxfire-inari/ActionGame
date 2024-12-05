#pragma once
#include"Common.h"
class BaseObject;
class CollisionObject;
class CollisionData;
class Fall;

class CollisionProcessing
{
public:
	CollisionProcessing(std::list<CollisionObject*>& _collObjectList);
	~CollisionProcessing();

	/// <summary>
	/// �I�u�W�F�N�g�ƃu���b�N�̉������̂߂荞�ݕ␳
	/// </summary>
	/// <param name="obj">���肷��I�u�W�F�N�g</param>
	/// <returns></returns>
	F_Vec2 GetSideBlockPosition(BaseObject* obj);

	/// <summary>
	/// �I�u�W�F�N�g���u���b�N�̏�ɂ��邩�Ƃ߂荞�ݕ␳
	/// </summary>
	/// <param name="obj">���肷��I�u�W�F�N�g</param>
	/// <param name="fall">�����Ă��邩���Z�b�g</param>
	/// <returns></returns>
	F_Vec2 GetOnBlockPosition(BaseObject* obj, Fall* fall = nullptr);

private:
	std::list<CollisionObject*> collisionObjectList;

	/// <summary>
	/// �߂��ɂ��邩�̔���
	/// </summary>
	/// <param name="obj">�Ώۂ̃I�u�W�F�N�g</param>
	/// <param name="chara">�L����</param>
	/// <param name="dif">����</param>
	/// <returns></returns>
	bool IsNewrDistance(F_Vec2 colpos, F_Vec2 objpos, float dif);

};

