#pragma once
#include"Common.h"
class BaseObject;
class Fall;
class CollisionData;

class CollisionManager;


/// <summary>
/// �L�����N�^�[�̈ړ��Ɋ֌W���鏈����S�čs��
/// </summary>
class PositionSetter
{
public:
	PositionSetter();
	~PositionSetter();

	/// <summary>
	/// ���W�̍X�V(�u���b�N�Ƃ̊��L��)
	/// </summary>
	/// <param name="me">�ړ�����I�u�W�F�N�g�̃|�C���^</param>
	/// <param name="colData">�I�u�W�F�N�g�̃R���W�����f�[�^</param>
	/// <param name="collisionManager">���̃V�[���̃R���W�����}�l�[�W���[</param>
	/// <param name="fall">�������Ă邩</param>
	void UpdatePos(BaseObject* me, CollisionData* colData, CollisionManager* collisionManager, Fall* fall);

	/// <summary>
	/// ���W�̍X�V(�u���b�N�Ƃ̊�����)
	/// </summary>
	/// <param name="me">�ړ�����I�u�W�F�N�g�̃|�C���^</param>
	void UpdateNonInterPos(BaseObject* me);
};

