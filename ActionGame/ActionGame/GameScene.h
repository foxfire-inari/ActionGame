#pragma once
#include"BaseScene.h"

/// <summary>
/// 主なゲームシーン
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
	/// 現在のマップの名前
	/// </summary>
	std::string nowMapName;
	
	/// <summary>
	/// ゲームオーバーかどうかと
	/// ゲームオーバーアニメのカウント
	/// </summary>
	int gameOverCount;

	/// <summary>
	/// ゲームオーバーの透明度
	/// </summary>
	float alpha;

	/// <summary>
	/// 次のマップへ行く処理
	/// </summary>
	/// <returns></returns>
	bool GoToNextMap();

	/// <summary>
	/// ゲームオーバーを描画させる
	/// 操作を受け付ける関数
	/// </summary>
	/// <returns></returns>
	bool GameOverProcessing();

	/// <summary>
	/// ゲームオーバーを描画する
	/// </summary>
	void DrawGameOver();


};

