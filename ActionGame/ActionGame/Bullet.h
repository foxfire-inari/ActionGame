#pragma once
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"


/// <summary>
/// �S�Ă̒e�̌p����
/// </summary>
class Bullet : public BaseObject
{
public:
	Bullet(BaseScene* _baseScene, int _power, float top, float under, float left, float right );
	~Bullet();

	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

	/// <summary>
	/// �e�̗v�f��ݒ肷��
	/// </summary>
	/// <param name="pos">���˒n�_</param>
	/// <param name="vec">���˕���</param>
	/// <param name="_power">�_���[�W��</param>
	virtual void SetState(F_Vec2 pos,F_Vec2 vec) {};

	/// <summary>
	/// �t���O�������Ă��邩�Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// �t���O���Z�b�g
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }

	/// <summary>
	/// �R���W������Ԃ�
	/// HitCheckEnemy�p
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData()const { return collisionData; }

	/// <summary>
	/// �_���[�W��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetPower()const { return power; }

protected:

	/// <summary>
	/// ���̃_���[�W
	/// </summary>
	int power;

	/// <summary>
	/// ���̒e�������Ă邩�ǂ���
	/// </summary>
	bool flag;

	/// <summary>
	/// �����蔻��̏��
	/// </summary>
	CollisionData* collisionData;
};

