#pragma once
#include"BaseObject.h"
#include"State.h"
#include"Gravity.h"
#include"PositionSetter.h"

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

	/// <summary>
	/// ���������@�\�̃e�X�g�p
	/// </summary>
	void TestUpdate();
protected:

	/// <summary>
	/// �X�e�[�g
	/// </summary>
	State* state;
	/// <summary>
	/// �d��
	/// </summary>
	Gravity* gravity;

	PositionSetter* positionSetter;


};

/// ���K�v�ȗv�f��
/// 
/// �����Ă��邩�̔���
/// �̗�
/// �����o�����̈ړ�����
/// 
/// (�摜�͊e�L�����N�^�[�Ŏ�������)
///