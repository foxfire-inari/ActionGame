#pragma once
#include "Enemy.h"

class Metall : public Enemy
{
public://���b�g�[���̃A�j���[�V�����ɓ���
	Metall(BaseScene* baseScene, 
		BulletManager* bulletManager, EffectManager* _effectManager,
		BaseObject* plBase, F_Vec2 pos, int knd);
	~Metall();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

private:

	/// <summary>
	/// �摜
	/// </summary>
	int imageH;

	/// <summary>
	/// �e��������
	/// ���E�ǂ����������Ă邩
	/// </summary>
	int moveAngle;

	/// <summary>
	/// ��Ԃ�؂�ւ���J�E���^�[
	/// </summary>
	int moveCount;

	/// <summary>
	/// �_���[�W���󂯂Ă���̃J�E���^�[
	/// </summary>
	int damageCount;

	/// <summary>
	/// ���G���ǂ���
	/// </summary>
	bool isInvincible;

	// --------�X�e�[�g���Ƃ̃A�b�v�f�[�g

	void UpdateIdle();		//�ҋ@��ԁi���G�j
	void UpdateAttack();	//�U��
	void UpdateRun();		//�ړ�
	void UpdateFall();		//����
	void UpdateDamage();	//�_���[�W
	void UpdateDeath();		//���S

	// --------�X�e�[�g���Ƃ̃X�^�[�g

	void IdleStart();
	void AttackStart();
	void RunStart();
	void FallStart();
	void DamageStart();

	/// <summary>
	/// �v���C���[�Ƃ̋������T�m�͈͈ȓ��Ȃ�true
	/// </summary>
	/// <returns></returns>
	bool IsNearDistance();

	/// <summary>
	/// �e�����Ă邩
	/// </summary>
	/// <returns></returns>
	bool IsCanShot();

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
};

