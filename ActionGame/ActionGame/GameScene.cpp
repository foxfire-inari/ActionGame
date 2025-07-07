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
	static const int DRAW_GAMEOVER_ALPHA = 200;//push shot button�̕\�����n�߂�aplha�l
	//�A���t�@�l��ǉ����鑬�x
	static const float ALPHA_SPEED = 1.5f;

	static const float WAIT_TIME = 0.3f;
	static const float WAVEOUT_SPEED = 3.f;

	//�Q�[���I�[�o�[�̃C���[�W���W
	static const int IMAGE_LEFT_EDGE = 0;
	static const int IMAGE_TOP_EDGE = 0;

	//�_�ł̃t���[��
	static const int MAX_FRAME = 100;
	static const int NOY_DRAW_FRAME = 10;

	//������̍��W
	static const int STR_X = 250;
	static const int STR_Y = 500;
}

GameScene::GameScene(SceneChange* sceneChange, std::string _nowMapName, std::string _oldMapName)
	:BaseScene{sceneChange}
	,nowMapName{_nowMapName}
	, gameOverCount{ 0 }
	, alpha{ 0 }
{

	//�}�b�v�̐������
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

	//���̃}�b�v�ɍs���Ȃ�true
	if (GoToNextMap())return true;

	//�Q�[���I�[�o�[���I�������true
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

	//�Q�[���I�[�o�[�\��
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
	//�v���C���[���Q�[���I�[�o�[����Ȃ��Ȃ�return
	if (!common->GetPlayer()->GetIsGameOver())return false;

	//alpha�𑫂�
	alpha += ALPHA_SPEED;
	alpha = min(alpha, 255);
	if (alpha >= DRAW_GAMEOVER_ALPHA)
		gameOverCount++;

	//ATTACK��������A����alpha��DRAW_GAMEOVER_ALPHA���傫����
	if (KeyControlle::GetInstance()->GetNowPressing(E_KEY::ATTACK) && alpha >= DRAW_GAMEOVER_ALPHA)
	{
		//blackout�𐶐�
		if (waveout == nullptr)
		{
			waveout = new Waveout{ WAIT_TIME,WAVEOUT_SPEED };
			//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DECISION);
		}
	}

	//��������Ă��Ȃ��Ȃ�return
	if (waveout == nullptr)return false;

	//�Ó]���I��������^�C�g���V�[���֍s���Atrue��Ԃ�
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
	//�v���C���[���Q�[���I�[�o�[����Ȃ����return
	if (!common->GetPlayer()->GetIsGameOver())return;

	//�Q�[���I�[�o�[�摜�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(IMAGE_LEFT_EDGE, IMAGE_TOP_EDGE, Image::GetInstance()->GetGameOverH(), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//alpha��DRAW_GAMEOVER_ALPHA�����Ȃ�return
	if (alpha < DRAW_GAMEOVER_ALPHA)return;

	//�g���Ȃ�return
	if (waveout != nullptr)return;

	//gameOverCount��NOY_DRAW_FRAME�ȉ��Ȃ�return
	if (gameOverCount % MAX_FRAME <= NOY_DRAW_FRAME)return;

	//������̕`��
	DrawString(STR_X, STR_Y, "Push Shot Button", GetColor(255, 255, 255));

}
