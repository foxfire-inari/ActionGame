#pragma once
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"
#include "Image.h"


/// <summary>
/// �S�Ă̒e�̌p����
/// </summary>
class Bullet : public BaseObject
{
public:
	Bullet(BaseScene* _baseScene, int _power, float top, float under, float left, float right,int _knd );
	~Bullet();

	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

	/// <summary>
	/// �e�̗v�f��ݒ肷��
	/// </summary>
	/// <param name="pos">���˒n�_</param>
	/// <param name="vec">���˕���</param>
	/// <param name="_owner">������</param>
	virtual void SetState(F_Vec2 pos,F_Vec2 vec,int _owner) {};

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
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData()const { return collisionData; }

	/// <summary>
	/// �_���[�W��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetPower()const { return power; }

	/// <summary>
	/// �������Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetOwner()const { return owner; }

	/// <summary>
	/// ��������Z�b�g����
	/// �e�𒵂˕Ԃ����Ɏg��
	/// </summary>
	/// <param name="_owner"></param>
	/// <returns></returns>
	void SetOwner(int _owner) { owner = _owner; }

	/// <summary>
	/// �e�̎�ނ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetKnd()const { return knd; }

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
	/// �e�̎�����i�v���C���[���G���j
	/// </summary>
	int owner;

	/// <summary>
	/// ���̒e���ǂ̎�ނ�
	/// </summary>
	int knd;

	int imageH;		//�摜


	/// <summary>
	/// �����蔻��̏��
	/// </summary>
	CollisionData* collisionData;
};

