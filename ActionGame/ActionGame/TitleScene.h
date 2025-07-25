#pragma once
#include "BaseScene.h"
#include "Animation.h"
#include "Player.h"
class TitleScene : public BaseScene
{
public:
	TitleScene(SceneChange* sceneChange);
	~TitleScene();
	bool Update()override;
	void Draw()override;
private:	

	Animation* animation;
	int animNum;//全てのアニメーションを管理する

	//イメージ
	int titleH;
	int playerH;
	int groundH;
	int skyH;

	bool isStart;//スタートしたか
	int startCount;//スタートしてからのカウント

	void SetImageH();	//描画する物をセットする

};

