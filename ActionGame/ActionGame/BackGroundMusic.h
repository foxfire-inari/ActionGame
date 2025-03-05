#pragma once
#include "Singleton.h"

/// <summary>
/// BGM����������V���O���g���N���X
/// </summary>
class BackGroundMusic : public Singleton<BackGroundMusic>
{
public:
	BackGroundMusic();
	~BackGroundMusic();

	//���̃V���O���g���N���X�ƈႢ
	//BGM�N���X���ŏ������������Ă��邽��
	//�N���X����enum�����

	//BGM�̎��
	enum E_BGM_KND
	{
		TITLE,
		MAP_01,
		BOSS,
	};

	/// <summary>
	/// BGM�𗬂�
	/// </summary>
	/// <param name="_bgmKnd">����BGM�̎��</param>
	void PlayBGM(E_BGM_KND _bgmKnd);

	/// <summary>
	/// BGM���~�߂�
	/// </summary>
	void StopBGM(E_BGM_KND _bgmKnd);

private:
	//���E_BGM_KND�Ɠ������R�ő��ƕۑ����@���Ⴄ

	/// <summary>
	/// �eBGM��pair��vector�^�ŕۑ�
	/// </summary>
	std::vector<std::pair<E_BGM_KND, int>> bgmVec;

	void LoadSound(const char* fileName, E_BGM_KND _knd);


};