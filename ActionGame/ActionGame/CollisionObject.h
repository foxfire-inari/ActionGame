#pragma once
#include"BaseObject.h"

/// <summary>
/// �����蔻������L�����N�^�[�ȊO�̃N���X
/// </summary>
class CollisionObject : BaseObject
{
public:
	/// <summary>
	/// �I�u�W�F�N�g�̂̊�{�T�C�Y�i1��1�j�Ő���
	/// </summary>
	CollisionObject(BaseScene* _baseScene, bool _isThrough, int _tag);
	~CollisionObject();

	/// <summary>
	/// ���蔲�������ǂ�����Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetIsThrough() { return isThrough; }

private:

	/*
	�ꉞ���蔲�����̒�`
	�E�I�u�W�F�N�g�̓����蔻��͏�̂�
	�E���E�Ɖ�����̔���͂��Ȃ�
	*/

	/// <summary>
	/// ���蔲�������ǂ���
	/// </summary>
	bool isThrough;
};

