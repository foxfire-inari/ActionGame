#pragma once
#include"Common.h"
#include"BaseScene.h"

#include"CollisionData.h"

/// <summary>
/// �S�ẴI�u�W�F�N�g�̌p����
/// </summary>
class BaseObject
{
public:
	BaseObject(BaseScene* _baseScene,F_Vec2 _pos, F_Vec2 _vel,
		int _top,int _under,int _left,int _right,
		int _tag);
	~BaseObject();
	virtual void Start() {}
	virtual void Update() {};
	virtual void Draw() {};

	/// <summary>
	/// �����̍��W��Ԃ�
	/// </summary>
	/// <returns></returns>
	F_Vec2 GetPosition()const { return position; }

	/// <summary>
	/// �����̍��W���Z�b�g
	/// ���W�̏�������߂荞�݂𒼂��̂Ɏg��
	/// </summary>
	/// <param name="_pos"></param>
	void SetPosition(F_Vec2 _pos) { position = _pos; }

	/// <summary>
	/// ���W�𑫂��i�ړ�������j
	/// </summary>
	/// <param name="_pos"></param>
	void AddPosition(F_Vec2 _pos) { position += _pos; }

	/// <summary>
	/// �����̑��x��Ԃ�
	/// </summary>
	/// <returns></returns>
	F_Vec2 GetVelocity()const { return velocity; }

	/// <summary>
	/// �����̑��x���Z�b�g
	/// </summary>
	/// <param name="_vel"></param>
	void SetVelocity(F_Vec2 _vel) { velocity = _vel; }

	/// <summary>
	/// �����̃^�O��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetTag()const { return tag; }

	CollisionData* GetCollisionPos() { return ColData; }

	/// <summary>
	/// �Q�[������1�����̃I�u�W�F�N�g��
	/// ���̃V�[���Ɉ����p������
	/// </summary>
	/// <param name="_baseScene">���̃V�[��</param>
	/// <param name="isOneObject">�v���C���[���̃V�[����1�����̃I�u�W�F�N�g��</param>
	void SetNewScene(BaseScene* _baseScene, bool isOneObject = false);

	/// <summary>
	/// �I�u�W�F�N�g�𔻕ʂ���^�O
	/// </summary>
	enum E_TAG
	{
		PLAYER,				//�v���C���[
		BLOCK,				//�u���b�N
		ENEMY,				//�G
		ITEM,				//�A�C�e��
		EFFECT,				//�G�t�F�N�g
	};

protected:

	/// <summary>
	/// �������Ă���V�[����Ԃ�
	/// </summary>
	/// <returns>BaseScene�N���X�̃|�C���^</returns>
	BaseScene* GetBaseScene()const { return baseScene; }


	/// <summary>
	/// �I�u�W�F�N�g�̒��S���W
	/// </summary>
	F_Vec2 position;

	/// <summary>
	/// ���x
	/// </summary>
	F_Vec2 velocity;

	/// <summary>
	/// �����蔻��̏��
	/// </summary>
	CollisionData* ColData;

	/// <summary>
	/// �I�u�W�F�N�g���ʗp�̃^�O
	/// </summary>
	int tag;
private:
	/// <summary>
	/// �V�[���̃��X�g�Ɏ��g��o�^����Ƃ��ɕK�v
	/// </summary>
	BaseScene* baseScene;
};
