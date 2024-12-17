#pragma once
#include "Chara.h"


/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player :public Chara
{
public:
	Player(BaseScene* baseScene);
	~Player();

	 /// <summary>
	 /// �R���X�g���N�^�ȊO�ōŏ��Ɉ��Ăԏ���
	 /// </summary>
	void Start()override;

	/// <summary>
	/// �Q�[���V�[���ł̃A�b�v�f�[�g
	/// </summary>
	void Update()override;

	/// <summary>
	/// �Q�[���V�[���ł̕`��
	/// </summary>
	void Draw()override;

	/// <summary>
	/// �Q�[���V�[���ł�UI�`��
	/// </summary>
	void DrawUI();
	void DrawData();

	/// <summary>
	/// �Q�[���I�[�o�[���ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetIsGameOver()const { return isGameOver; }

private:

	int inputRight;	//�E�����ւ̓��͗�
	int inputDown;	//�������ւ̓��͗�

	float inputAngle;	//���͊p�x
	float moveSpeed;	//�ړ����x
	int moveAngle;		//�i�s����

	/// <summary>
	/// ���G��
	/// </summary>
	bool isInvincible;

	/// <summary>
	/// �Q�[���I�[�o�[���ǂ���
	/// </summary>
	bool isGameOver;

	// --------�X�e�[�g���Ƃ̃A�b�v�f�[�g

	/// <summary>
	/// �ҋ@���
	/// </summary>
	void UpdateIdle();

	/// <summary>
	/// ���s���
	/// </summary>
	void UpdateRun();

	/// <summary>
	/// �󒆂ɂ�����
	/// </summary>
	void UpdateJump();

	/// <summary>
	/// �U�����
	/// </summary>
	void UpdateAttack();

	/// <summary>
	/// ��_���[�W���
	/// </summary>
	void UpdateDamage();

	/// <summary>
	/// ���S���
	/// </summary>
	void UpdateDeath();

	// --------�X�e�[�g���Ƃ̃X�^�[�g

	/// <summary>
	/// �W�����v�J�n
	/// </summary>
	void JumpStart();

	/// <summary>
	/// �_���[�W�J�n
	/// </summary>
	void DamageStart();

	/// <summary>
	/// ���S�J�n
	/// </summary>
	void DeathStart();

	/// <summary>
	/// ���G��Ԃ���莞�Ԃŉ���
	/// </summary>
	void Invincible();

	/// <summary>
	/// �n�ʂ����яo���ė����Ă�����
	/// velocity.y��0�ɂ��ăW�����v�Ɉڍs
	/// </summary>
	void FallStart();

	/// <summary>
	/// ����A�����J�n
	/// </summary>
	void StartRun();

	/// <summary>
	/// �U���J�n
	/// </summary>
	void AttackStart();

	/// <summary>
	/// ���͕����ƃv���C���[�̌����̃Z�b�g
	/// </summary>
	void SetInputAngle();

	/// <summary>
	/// �ړ����Ă�����true��Ԃ���������
	/// </summary>
	/// <param name="speed"></param>
	/// <returns></returns>
	bool Move(float speed);

	/// <summary>
	/// ����
	/// </summary>
	void MoveDeceletation();

	/// <summary>
	/// �A�C�e���̎擾
	/// </summary>
	void GetItem();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	/// <summary>
	/// ���݂̃X�e�[�^�X���o��
	/// </summary>
	void SetStatus();

	/// <summary>
	/// ���̃V�[���̃}�l�[�W���[���擾
	/// </summary>
	void GetNowSceneManager();
};
