#pragma once
#include "Singleton.h"

/// <summary>
/// �S�Ẳ摜�����V���O���g���N���X
/// </summary>
class Image : public Singleton<Image>
{
public:
	Image();
	~Image();

	/// <summary>
	/// �v���C���[���ҋ@���Ă���Ƃ��̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetPlayerIdleH(int index)const;

	/// <summary>
	/// �v���C���[�������Ă���Ƃ��̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetPlayerWalkH(int index)const;

	/// <summary>
	/// �v���C���[���󒆂ɂ���Ƃ��̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetPlayerFallH(int index)const;

	/// <summary>
	/// �v���C���[���_���[�W���󂯂����̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetPlayerDamageH(int index)const;


	/// <summary>
	/// �e���[�̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetTerryH(int index)const;


	/// <summary>
	/// ���b�g�[���̑ҋ@�摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetMetallIdleH(int index)const;

	/// <summary>
	/// ���b�g�[���̑����Ă�摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetMetallRunH(int index)const;

	/// <summary>
	/// ���b�g�[���̍U���J�n���̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetMetallUpH(int index)const;

	/// <summary>
	/// ���^���}���̑ҋ@���̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetMetalManIdleH(int index)const;

	/// <summary>
	/// ���^���}�����󒆂ɂ���Ƃ��̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetMetalManJumpH(int index)const;

	/// <summary>
	/// �e�̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetBulletH(int index)const;


	/// <summary>
	/// �u���b�N�̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetBlockH(int index)const;

	/// <summary>
	/// ���[�v�̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetWarpH(int index)const;

	/// <summary>
	/// ���[�v���̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetWaveH(int index)const;

	/// <summary>
	/// �G�t�F�N�g�̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetEffectH(int index)const;

	/// <summary>
	/// ��̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetSkyH(int index)const;

	/// <summary>
	/// �^�C�g���摜��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetTitleH()const { return titleH; }

	/// <summary>
	/// �^�C�g����ʂ̒n�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetTitleGroundH()const { return titleGroundH; }

	/// <summary>
	/// �^�C�g����ʂ̔w�i��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetTitleSkyH()const { return titleSkyH; }

	/// <summary>
	/// �Q�[���I�[�o�[�摜��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetGameOverH()const { return gameOverH; }



private:
	
	//�[�[�[�[�v���C���[�̉摜
	//�ҋ@�p
	std::array<int, 2> playerIdleH;
	//���s�p
	std::array<int, 8> playerWalkH;
	//�󒆂ɂ���Ƃ��p
	std::array<int, 2> playerFallH;
	//�_���[�W�p
	std::array<int, 2> playerDamageH;

	//�[�[�[�[�e���[�̉摜
	std::array<int ,4> terryH;

	//�[�[�[�[���b�g�[���̉摜
	//�ҋ@�p
	std::array<int, 2> metallIdleH;
	//���s�p
	std::array<int, 4> metallRunH;
	//�U���J�n�p
	std::array<int, 4> metallUpH;

	//�[�[�[�[���^���}���̉摜
	//�ҋ@�p
	std::array<int, 8> metalManIdleH;
	//�󒆂ɂ���Ƃ��p
	std::array<int, 2> metalManJumpH;

	//�[�[�[�[�e�̉摜
	//�e�̐������ۑ�
	std::array<int, 3> bulletH;

	//�[�[�[�[�u���b�N�̉摜
	//�u���b�N�̐������ۑ�
	std::array<int, 2> blockH;

	//�[�[�[�[���[�v�̉摜
	//���[�v�I�u�W�F�N�g�p
	std::array<int, 4> warpH;
	//���[�v���̉摜
	std::array<int, 4> waveH;

	//�[�[�[�[�ėp�G�t�F�N�g
	//�L�����N�^�[�̏��ŗp
	std::array<int, 4> effectH;


	//�[�[�[�[1���G
	// 	//��̉摜
	std::array<int, 2> skyH;
	//�^�C�g�����
	int titleH;
	//�^�C�g����ʂ̒n��
	int titleGroundH;
	//�^�C�g����ʂ̔w�i
	int titleSkyH;
	//�Q�[���I�[�o�[�i�ꖇ�����Ȃ̂�int�^�j
	int gameOverH;
};

