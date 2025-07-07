#include "GameScene.h"
#include "KeyControlle.h"
#include"CsvFile.h"
#include"Player.h"
#include"Camera.h"
#include"Sky.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include"BlockManager.h"
#include"WarpManager.h"
#include "Image.h"

namespace
{
	static const int DRAW_GAMEOVER_ALPHA = 200;//push shot buttonの表示を始めるaplha値
	//アルファ値を追加する速度
	static const float ALPHA_SPEED = 1.5f;

	static const float WAIT_TIME = 0.3f;
	static const float WAVEOUT_SPEED = 3.f;

	//ゲームオーバーのイメージ座標
	static const int IMAGE_LEFT_EDGE = 0;
	static const int IMAGE_TOP_EDGE = 0;

	//点滅のフレーム
	static const int MAX_FRAME = 100;
	static const int NOY_DRAW_FRAME = 10;

	//文字列の座標
	static const int STR_X = 250;
	static const int STR_Y = 500;
}

GameScene::GameScene(SceneChange* sceneChange, std::string _nowMapName, std::string _oldMapName)
	:BaseScene{sceneChange}
	,nowMapName{_nowMapName}
	, gameOverCount{ 0 }
	, alpha{ 0 }
{

	//マップの生成情報
	std::string fileName = "Data/Csv/" + nowMapName + ".csv";

	std::vector<std::vector<std::string>> information =
		CsvFile::GetInstance()->Input(fileName.c_str());

	common = new CommonObjectAndManager{ this ,information };
}

GameScene::~GameScene()
{
}

bool GameScene::Update()
{
	common->GetPlayer()->Update();

	common->Update();

	//次のマップに行くならtrue
	if (GoToNextMap())return true;

	//ゲームオーバーが終わったらtrue
	if (GameOverProcessing())return true;

	return false;
}

void GameScene::Draw()
{
	F_Vec2 camDif = common->GetCamera()->GetTarget();

	common->GetSky()->Draw(camDif);

	common->GetPlayer()->Draw(camDif);

	common->Draw(camDif);

	common->GetPlayer()->DrawWaveout();

	//ゲームオーバー表示
	DrawGameOver();

	if (waveout != nullptr)
		waveout->Draw();
}

bool GameScene::GoToNextMap()
{
	if (NextMapPlayer(nextMapName))
	{
		GetSceneChange()->Change(E_SCENE::GAME, nextMapName, nowMapName);
		return true;
	}

	return false;
}

bool GameScene::GameOverProcessing()
{
	//プレイヤーがゲームオーバーじゃないならreturn
	if (!common->GetPlayer()->GetIsGameOver())return false;

	//alphaを足す
	alpha += ALPHA_SPEED;
	alpha = min(alpha, 255);
	if (alpha >= DRAW_GAMEOVER_ALPHA)
		gameOverCount++;

	//ATTACKが押され、かつalphaがDRAW_GAMEOVER_ALPHAより大きい時
	if (KeyControlle::GetInstance()->GetNowPressing(E_KEY::ATTACK) && alpha >= DRAW_GAMEOVER_ALPHA)
	{
		//blackoutを生成
		if (waveout == nullptr)
		{
			waveout = new Waveout{ WAIT_TIME,WAVEOUT_SPEED };
			//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DECISION);
		}
	}

	//生成されていないならreturn
	if (waveout == nullptr)return false;

	//暗転が終了したらタイトルシーンへ行き、trueを返す
	waveout->Update();
	if (waveout->GetIsWaveFinish())
	{
		GetSceneChange()->Change(E_SCENE::TITLE);
		return true;
	}

	return false;
}

void GameScene::DrawGameOver()
{
	//プレイヤーがゲームオーバーじゃなければreturn
	if (!common->GetPlayer()->GetIsGameOver())return;

	//ゲームオーバー画像描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(IMAGE_LEFT_EDGE, IMAGE_TOP_EDGE, Image::GetInstance()->GetGameOverH(), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//alphaがDRAW_GAMEOVER_ALPHA未満ならreturn
	if (alpha < DRAW_GAMEOVER_ALPHA)return;

	//波中ならreturn
	if (waveout != nullptr)return;

	//gameOverCountがNOY_DRAW_FRAME以下ならreturn
	if (gameOverCount % MAX_FRAME <= NOY_DRAW_FRAME)return;

	//文字列の描画
	DrawString(STR_X, STR_Y, "Push Shot Button", GetColor(255, 255, 255));

}
