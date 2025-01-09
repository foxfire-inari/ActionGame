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
	/// ��{�T�C�Y�i1��1�j����
	/// ���W��(0,0)����
	/// ���x��(0,0)�Ő���
	/// </summary>
	CollisionObject(BaseScene* baseScene, int tag);


	/// <summary>
	/// �I�u�W�F�N�g�̃X�e�[�^�X���Z�b�g���Ȃ��琶��
	/// </summary>
	/// <param name="baseScene">�x�[�X�V�[��</param>
	/// <param name="pos">���W</param>
	/// <param name="vel">���x</param>
	/// <param name="top">	�����蔻��Q��</param>
	/// <param name="under">�����蔻��Q��</param>
	/// <param name="left">	�����蔻��Q��</param>
	/// <param name="right">�����蔻��Q�E</param>
	/// <param name="tag">�^�O</param>
	CollisionObject(BaseScene* baseScene, F_Vec2 pos, F_Vec2 vel,
		float top, float under, float left, float right,int tag);

	~CollisionObject();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// �R���W�����f�[�^��n��
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData() { return collisionData; }

private:

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

