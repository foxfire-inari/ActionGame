#pragma once
#include"BaseScene.h"

/// <summary>
/// ��ȃQ�[���V�[��
/// </summary>
class GameScene : public BaseScene
{
public:
	GameScene(SceneChange* sceneChange, std::string _nowMapName, std::string _oldMapName);
	~GameScene();
	bool Update()override;
	void Draw()override;

private:
	/// <summary>
	/// ���݂̃}�b�v�̖��O
	/// </summary>
	std::string nowMapName;
	
	/// <summary>
	/// �Q�[���I�[�o�[���ǂ�����
	/// �Q�[���I�[�o�[�A�j���̃J�E���g
	/// </summary>
	int gameOverCount;

	/// <summary>
	/// �Q�[���I�[�o�[�̓����x
	/// </summary>
	float alpha;

	/// <summary>
	/// ���̃}�b�v�֍s������
	/// </summary>
	/// <returns></returns>
	bool GoToNextMap();

	/// <summary>
	/// �Q�[���I�[�o�[��`�悳����
	/// ������󂯕t����֐�
	/// </summary>
	/// <returns></returns>
	bool GameOverProcessing();

	/// <summary>
	/// �Q�[���I�[�o�[��`�悷��
	/// </summary>
	void DrawGameOver();


};

