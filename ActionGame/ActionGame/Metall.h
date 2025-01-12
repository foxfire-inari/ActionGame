#pragma once
#include "Enemy.h"


class Metall : public Enemy
{
public:
	Metall(BaseScene* baseScene, BulletManager* bulletManager,
		BaseObject* plBase, F_Vec2 pos, int knd);
	~Metall();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

private:

	/// <summary>
	/// �e��������
	/// ���E�ǂ����������Ă邩
	/// </summary>
	int shotAngle;

	/// <summary>
	/// ��Ԃ�؂�ւ���J�E���^�[
	/// </summary>
	int moveCount;

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

	void StartIdle();
	void StartAttack();
	void StartRun();
	void StartFall();
	void StartDamage();
	void StartDeath();

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
};

