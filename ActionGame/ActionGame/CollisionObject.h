#pragma once
#include"BaseObject.h"

#include"CollisionData.h"

/// <summary>
/// �����蔻������L�����N�^�[�ȊO�̃N���X
/// </summary>
class CollisionObject :public BaseObject
{
public:
	/// <summary>
	/// �I�u�W�F�N�g��
	/// �����蔻�����{�T�C�Y�i1��1�j����
	/// ���W��(0,0)����
	/// ���x��(0,0)�Ő���
	/// </summary>
	CollisionObject(BaseScene* baseScene, int tag);

	/// <summary>
	/// �I�u�W�F�N�g��
	/// �����蔻�����{�T�C�Y�i1��1�j����
	/// ���W���w�肵�Đ���
	/// </summary>
	/// <param name="baseScene">�x�[�X�V�[��</param>
	/// <param name="pos">���W</param>
	/// <param name="tag">�^�O</param>
	CollisionObject(BaseScene* baseScene, F_Vec2 pos,int tag);

	/// <summary>
	/// �I�t�W�F�N�g�̓����蔻��̃T�C�Y�ƍ��W���w�肵�Đ���
	/// </summary>
	/// <param name="baseScene"></param>
	/// <param name="pos"></param>
	/// <param name="top"></param>
	/// <param name="under"></param>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="tag"></param>
	CollisionObject(BaseScene* baseScene, F_Vec2 pos
		, float top, float under, float left, float right, int tag);


	~CollisionObject();

	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

	/// <summary>
	/// �R���W�����f�[�^��n��
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData() { return collisionData; }

protected:

	/// <summary>
	/// �����蔻��̏��
	/// </summary>
	CollisionData* collisionData;

	/*
	�ꉞ���蔲�����̒�`
	�E�I�u�W�F�N�g�̓����蔻��͏�̂�
	�E���E�Ɖ�����̔���͂��Ȃ�
	�E�I�u�W�F�N�g�̉������ɏ�邱�Ƃ��ł���
	*/
};

