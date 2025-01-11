#pragma once
#include"BaseScene.h"

/// <summary>
/// ��ȃQ�[���V�[��
/// </summary>
class GameScene : public BaseScene
{
public:
	GameScene(SceneChange* sceneChange, std::string _nowMapName);
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
	//int gameOverCount;

	/// <summary>
	/// ���̃}�b�v�֍s������
	/// </summary>
	/// <returns></returns>
	bool GoToNextMap();

	bool GameOverProcessing();

	void DrawGameOver();


};

