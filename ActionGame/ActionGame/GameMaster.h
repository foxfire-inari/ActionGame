#pragma once
<<<<<<< Updated upstream
=======
#include"Common.h"
>>>>>>> Stashed changes
#include"SceneChange.h"
#include<list>
class BaseScene;

class GameMaster : public SceneChange
{

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
	bool Change(int nextSceneNum, std::string nextMapName, std::string oldMapName)override;

private:
	std::list<BaseScene*> scene;

};

