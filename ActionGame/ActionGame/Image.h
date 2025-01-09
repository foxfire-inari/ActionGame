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
	/// �v���C���[���U������Ƃ��̉摜��Ԃ�
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetPlayerAttackH(int index)const;

	/// <summary>
	/// �v���C���[���󒆂ɂ���Ƃ��̉摜��ς���
	/// </summary>
	/// <param name="index">�C���f�b�N�X</param>
	/// <returns></returns>
	int GetplayerFallH(int index)const;


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

private:
	
	//�v���C���[�̉摜

	//�ҋ@�p
	std::array<int, 2> playerIdleH;
	//���s�p
	std::array<int, 8> playerWalkH;
	//�U���p
	std::array<int, 8> playerAttackH;
	//�󒆂ɂ���Ƃ��p
	std::array<int, 2> playerFallH;

	//�e���[�̉摜
	//�e���[�͉�]���邾���Ȃ̂ł��ꂾ��
	std::array<int ,8> terryH;

	//�u���b�N�̉摜
	//�u���b�N�̐������ۑ�
	std::array<int, 64> BlockH;

};

