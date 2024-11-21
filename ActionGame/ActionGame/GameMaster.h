#pragma once
#include "Common.h"
#include"SceneChange.h"
class GameScene;

//�[�[�[�[�[�[�e�X�g�p
#include "Player.h"
class Player;
//�[�[�[�[�[�[�e�X�g�p

class GameMaster : public SceneChange
{
	Player* player;
public:
	GameMaster();
	~GameMaster();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �V�[���ƃ}�b�v�̐؂�ւ����s��
	/// </summary>
	/// <param name="nextscenenum">���̃V�[���̔ԍ�</param>
	/// <param name="nextmapname">���̃}�b�v�̖��O</param>
	/// <param name="oldmapname">���X�����}�b�v�̖��O</param>
	/// <returns>�؂�ւ��ɐ���������true</returns>
	bool Change(int nextscenenum, std::string nextmapname, std::string oldmapname)override;

private:
	std::list<BaseScene*> scene;

};

