#include "TitleScene.h"
#include "Image.h"
#include "KeyControlle.h"
namespace
{
	//タイトルサイズ
	static const int TITLE_TOP		= 0;
	static const int TITLE_UNDER	= BLOCK_SIZE * 8;
	static const int TITLE_LEFT		= BLOCK_SIZE * 2;
	static const int TITLE_RIGHT	= TITLE_LEFT + BLOCK_SIZE * 12;

	//地面のサイズ
	static const float GROUND_TOP	= BLOCK_SIZE * 9;
	static const float GROUND_UNDER	= BLOCK_SIZE * 13;
	static const float GROUND_LEFT	= BLOCK_SIZE * 10;
	static const float GROUND_RIGHT	= BLOCK_SIZE * 16;

	//プレイヤーのサイズ
	static const float PLAYER_TOP	= BLOCK_SIZE * 12;
	static const float PLAYER_UNDER = BLOCK_SIZE * 7.5f;
	static const float PLAYER_LEFT	= BLOCK_SIZE * 12 + 64;
	static const float PLAYER_RIGHT = BLOCK_SIZE * 9;

	//テキストの座標
	static const float TEXT_TOP = BLOCK_SIZE * 4;
	static const float TEXT_UNDER = BLOCK_SIZE * 9;

	//プレイヤーのアニメーションの設定
	static const int ANIM = 48;

	//点滅のフレーム
	static const int MAX_FRAME = 4;
	static const int NOY_DRAW_FRAME = MAX_FRAME / 2;
}


TitleScene::TitleScene(SceneChange* sceneChange)
	:BaseScene{ sceneChange }
	, animNum{ 0 }
	, isStart{ false }
{
	SetImageH();

	animation = new Animation{};

	//何も生成しないように登録
	std::vector<std::vector<std::string>> information = {};
	common = new CommonObjectAndManager{ this ,information };

}
TitleScene::~TitleScene()
{
}

bool TitleScene::Update()
{
	static const int MAX_STARTCOUNT = FPS * 3;

	animation->AddAnimCount(0.5f);
	playerH = Image::GetInstance()->GetPlayerWalkH(animNum);

	//入力でスタートする
	if (KeyControlle::GetInstance()->GetNowPressing(E_KEY::ATTACK))
	{
		isStart = true;
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DECISION);
	}

	if (isStart)
	{
		animation->AddAnimCount(0.5f);//加速させる

		startCount++;
		if (startCount >= MAX_STARTCOUNT)
		{
			GetSceneChange()->Change(E_SCENE::GAME,"Map01","Title");
			return true;

		}
	}

	animNum = animation->GetAnimation(ANIM, ANIM / 4);

	return false;
}

void TitleScene::Draw()
{
	//背景範囲
	DrawExtendGraph
	(
		0, 0,
		WINDOW_X,
		WINDOW_Y,
		skyH,
		true
		);

	//タイトル範囲
	DrawExtendGraph
	(
		TITLE_LEFT,
		TITLE_TOP,
		TITLE_RIGHT,
		TITLE_UNDER,
		titleH,
		true
	);

	//ブロック範囲
	DrawExtendGraph
	(
		GROUND_LEFT,
		GROUND_TOP,
		GROUND_RIGHT,
		GROUND_UNDER,
		groundH,
		true
	);

	//プレイヤー
	DrawExtendGraph
	(
		BLOCK_SIZE * 12,
		BLOCK_SIZE * 7.5f,
		BLOCK_SIZE * 12 + 64,
		BLOCK_SIZE * 9,
		playerH,
		true
	);



	//gameOverCountがNOY_DRAW_FRAME以下ならreturn
	if (animNum % MAX_FRAME >= NOY_DRAW_FRAME)return;

	//点滅させる文字
	DrawString(
		BLOCK_SIZE * 4,
		BLOCK_SIZE * 9,
		"Push Shot Button",
		GetColor(255, 255, 255)
	);
}

void TitleScene::SetImageH()
{
	//プレイヤーは動くのでここでは除外

	titleH  = Image::GetInstance()->GetTitleH();
	groundH = Image::GetInstance()->GetTitleGroundH();
	skyH = Image::GetInstance()->GetTitleSkyH();
}
