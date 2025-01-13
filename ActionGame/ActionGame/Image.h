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

private:
	
	//�v���C���[�̉摜

	//�ҋ@�p
	std::array<int, 2> playerIdleH;
	//���s�p
	std::array<int, 8> playerWalkH;
	//�󒆂ɂ���Ƃ��p
	std::array<int, 2> playerFallH;
	//�_���[�W�p
	std::array<int, 2> playerDamageH;

	//�e���[�̉摜
	//�e���[�͉�]���邾���Ȃ̂ł��ꂾ��
	std::array<int ,8> terryH;

	//�u���b�N�̉摜
	//�u���b�N�̐������ۑ�
	std::array<int, 2> blockH;

	//���[�v�̉摜
	std::array<int, 4> warpH;

	//���[�v���̉摜
	std::array<int, 4> waveH;

	//�ėp�G�t�F�N�g
	std::array<int, 4> effectH;
};

