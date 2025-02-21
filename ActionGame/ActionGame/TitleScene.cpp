#include "TitleScene.h"
#include "Image.h"
#include "KeyControlle.h"
namespace
{
	//�^�C�g���T�C�Y
	static const int TITLE_TOP		= 0;
	static const int TITLE_UNDER	= BLOCK_SIZE * 8;
	static const int TITLE_LEFT		= BLOCK_SIZE * 2;
	static const int TITLE_RIGHT	= TITLE_LEFT + BLOCK_SIZE * 12;

	//�n�ʂ̃T�C�Y
	static const float GROUND_TOP	= BLOCK_SIZE * 9;
	static const float GROUND_UNDER	= BLOCK_SIZE * 13;
	static const float GROUND_LEFT	= BLOCK_SIZE * 10;
	static const float GROUND_RIGHT	= BLOCK_SIZE * 16;

	//�v���C���[�̃T�C�Y
	static const float PLAYER_TOP	= BLOCK_SIZE * 12;
	static const float PLAYER_UNDER = BLOCK_SIZE * 7.5f;
	static const float PLAYER_LEFT	= BLOCK_SIZE * 12 + 64;
	static const float PLAYER_RIGHT = BLOCK_SIZE * 9;

	//�e�L�X�g�̍��W
	static const float TEXT_TOP = BLOCK_SIZE * 4;
	static const float TEXT_UNDER = BLOCK_SIZE * 9;

	//�v���C���[�̃A�j���[�V�����̐ݒ�
	static const int ANIM = 48;

	//�_�ł̃t���[��
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

	//�����������Ȃ��悤�ɓo�^
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

	//���͂ŃX�^�[�g����
	if (KeyControlle::GetInstance()->GetNowPressing(E_KEY::ATTACK))
	{
		isStart = true;
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DECISION);
	}

	if (isStart)
	{
		animation->AddAnimCount(0.5f);//����������

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
	//�w�i�͈�
	DrawExtendGraph
	(
		0, 0,
		WINDOW_X,
		WINDOW_Y,
		skyH,
		true
		);

	//�^�C�g���͈�
	DrawExtendGraph
	(
		TITLE_LEFT,
		TITLE_TOP,
		TITLE_RIGHT,
		TITLE_UNDER,
		titleH,
		true
	);

	//�u���b�N�͈�
	DrawExtendGraph
	(
		GROUND_LEFT,
		GROUND_TOP,
		GROUND_RIGHT,
		GROUND_UNDER,
		groundH,
		true
	);

	//�v���C���[
	DrawExtendGraph
	(
		BLOCK_SIZE * 12,
		BLOCK_SIZE * 7.5f,
		BLOCK_SIZE * 12 + 64,
		BLOCK_SIZE * 9,
		playerH,
		true
	);



	//gameOverCount��NOY_DRAW_FRAME�ȉ��Ȃ�return
	if (animNum % MAX_FRAME >= NOY_DRAW_FRAME)return;

	//�_�ł����镶��
	DrawString(
		BLOCK_SIZE * 4,
		BLOCK_SIZE * 9,
		"Push Shot Button",
		GetColor(255, 255, 255)
	);
}

void TitleScene::SetImageH()
{
	//�v���C���[�͓����̂ł����ł͏��O

	titleH  = Image::GetInstance()->GetTitleH();
	groundH = Image::GetInstance()->GetTitleGroundH();
	skyH = Image::GetInstance()->GetTitleSkyH();
}
