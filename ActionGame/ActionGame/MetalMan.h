#pragma once
#include "Enemy.h"

class MetalMan : public Enemy
{
public:
	MetalMan(BaseScene* baseScene, 
		BulletManager* bulletManager, EffectManager* _effectManager,
		BaseObject* plBase, F_Vec2 pos, int knd);
	~MetalMan();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

private:

	int imageH;			// �摜

	int moveKnd;		// �s���̎��
	int moveAngle;		// ���E�ǂ����������Ă邩
	int moveCount;		// ��Ԃ�؂�ւ���J�E���^�[

	float shotAngle;	// �e��������

	int attackNum;		// �U���񐔂��Ǘ�
	int attackCount;	// �U���񐔂��J�E���g

	int damageCount;	// �_���[�W���󂯂Ă���̃J�E���^�[

	bool isInvincible;	// ���G���ǂ���

	// --------�X�e�[�g���Ƃ̃A�b�v�f�[�g

	void UpdateIdle();		//�ҋ@���
	void UpdateJump();		//���Α��ɑ�W�����v�����U��
	void UpdateAttack();	//�咆���W�����v���ā�321��U��
	void UpdateDeath();		//���S

	// --------�X�e�[�g���Ƃ̃X�^�[�g

	void IdleStart();
	void JumpStart();
	void AttackStart();
	void DamageStart();
	void DeathStart();

	/// <summary>
	/// ���G��Ԃ���莞�Ԃŉ���
	/// </summary>
	void Invincible();

	/// <summary>
	/// �v���C���[�Ƃ̋������T�m�͈͓��Ȃ�true
	/// </summary>
	/// <returns></returns>
	bool IsNearDistance();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	/// <summary>
	/// �e�̕������߂�֐�
	/// </summary>
	/// <param name="genVec">�e�̐������x�i�Q�Ɠn���j</param>
	/// <param name="rad">���ˊp�x</param>
	void SetGenVec(F_Vec2& genVec, float rad);

	/// <summary>
	/// moveAngle�Z�b�g����
	/// </summary>
	void SetMoveAngle();

	/// <summary>
	/// �v���C���[���U�����͂����Ă�����true
	/// �������`�`�Ŏg���ƒ�������֐��ɂ��ďȗ�
	/// </summary>
	/// <returns></returns>
	bool GetAttackKey();

	//�s���̎��
	enum E_MOVE_KND
	{
		LARGE,			//��W�����v
		MEDIUM,			//���W�����v
		SMALL,			//���W�����v
		JUMP_RAND_MAX,	//�����_���p�̍ő�l

		OVER,			//�t���ɍs���W�����v
	};
};

