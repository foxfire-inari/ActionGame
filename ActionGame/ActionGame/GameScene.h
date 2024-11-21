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
	std::string nowMapName;
	
	/// <summary>
	/// �Q�[���I�[�o�[���ǂ�����
	/// �Q�[���I�[�o�[�A�j���̃J�E���g
	/// </summary>
	//int gameOverCount;

	bool GameOverProcessing();

	void DrawGameOver();


};

