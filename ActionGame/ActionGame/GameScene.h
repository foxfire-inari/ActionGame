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
	/// <summary>
	/// 現在のマップの名前
	/// </summary>
	std::string nowMapName;
	
	/// <summary>
	/// ゲームオーバーかどうかと
	/// ゲームオーバーアニメのカウント
	/// </summary>
	//int gameOverCount;

	/// <summary>
	/// 次のマップへ行く処理
	/// </summary>
	/// <returns></returns>
	bool GoToNextMap();

	bool GameOverProcessing();

	void DrawGameOver();


};

