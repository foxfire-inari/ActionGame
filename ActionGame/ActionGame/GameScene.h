#pragma once
#include"BaseScene.h"

/// <summary>
/// 主なゲームシーン
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
	/// ゲームオーバーかどうかと
	/// ゲームオーバーアニメのカウント
	/// </summary>
	//int gameOverCount;

	bool GameOverProcessing();

	void DrawGameOver();


};

