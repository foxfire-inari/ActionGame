#pragma once
#include "Chara.h"
class Camera;
class BulletManager;
class WarpManager;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player :public Chara
{
public:
	Player(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
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
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// �Q�[���V�[���ł�UI�`��
	/// </summary>
	void DrawUI();
	void DrawData();

	/// <summary>
	/// ���̃}�b�v�ɍs�����ǂ���
	/// </summary>
	/// <returns></returns>
	std::string GoNextMap();

	/// <summary>
	/// �Q�[���I�[�o�[���ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetIsGameOver()const { return isGameOver; }

private:
	Camera* camera;
	BulletManager* bulletManager;
	EnemyManager* enemyManager;
	WarpManager* warpManager;

	//�J�����̍��W
	F_Vec2 camPos;

	//1�t���[���O�̍��W
	F_Vec2 oldPos;

	int jumpCount; //�W�����v�����������Ă���t���[����
	int shotCount; //�U���܂ł̃J�E���^�[
	int damageCount;//�_���[�W���󂯂Ă���̃J�E���^�[

	int inputRight;	//�E�����ւ̓��͗�
	int inputDown;	//�������ւ̓��͗�
	int imageH;		//�摜

	int moveAngle;		//�i�s����
	float moveSpeed;	//�ړ����x
	
	int sideShotAngle;	//����̔��˕���
	float allShotAngle;	//���͊p�x(�ł���������p)

	/// <summary>
	/// ���G��
	/// </summary>
	bool isInvincible;

	/// <summary>
	/// �Q�[���I�[�o�[���ǂ���
	/// </summary>
	bool isGameOver;

	/// <summary>
	/// �{�X�킩�ǂ���
	/// </summary>
	bool isBossButtle;

	/// <summary>
	/// �J�����̍��W�A�����_�̃Z�b�g
	/// </summary>
	void SetCameraTarget();

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

	/// <summary>
	/// ���̃}�b�v�ɍs���܂ł̏���
	/// </summary>
	void UpdateNextMapWait();

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
	/// ���G��Ԃ���莞�Ԃŉ���
	/// </summary>
	void Invincible();

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
