#pragma once
#include"BaseObject.h"

#include"Fall.h"
#include"Gravity.h"
#include"PositionSetter.h"
#include"State.h"

/// <summary>
/// �S�ẴL�����̌p����
/// </summary>
class Chara : public BaseObject
{
public:
	Chara(BaseScene* baseScene,
		int top, int under, int left, int right,
		int tag);
	~Chara();
	virtual void Update()override {}
	virtual void Draw()override {}

protected:

	/// <summary>
	/// �n�ʂɏ���Ă邩
	/// </summary>
	Fall* fall;

	/// <summary>
	/// �d��
	/// </summary>
	Gravity* gravity;

	/// <summary>
	/// �L�����ړ��Ɋւ���N���X
	/// </summary>
	PositionSetter* positionSetter;

	/// <summary>
	/// �X�e�[�g
	/// </summary>
	State* state;
};

/// ���K�v�ȗv�f��
/// 
/// �����Ă��邩�̔���
/// �̗�
/// �����o�����̈ړ�����
/// 
/// (�摜�͊e�L�����N�^�[�Ŏ�������)
///