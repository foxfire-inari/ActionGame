#include "Waveout.h"
#include "Common.h"
#include "Image.h"

namespace
{
	//�g�̑傫��
	static const int WAVE_SIZE = 50;
	//�g�ׂ̍���
	static const float WAVE_FINENESS = 2.0f;
	//��ʓ��ŉ���g�ł�
	static const float MAKE_WAVE_NUM = WINDOW_X / 2.0f;
	//�g�̃J�E���g�𑝂₷��
	static const float ADD_WAVE_COUNT = 1.f;
}

Waveout::Waveout(float _waitSecond, float _addVal)
	: imageH{ -1 }
	, count{ 0 }
	, waveCount{ 0.f }
	, alpha{ 0 }
	, oldAlpha{ alpha }
	, addVal{ _addVal }
	, waitSecond{ _waitSecond }
	, isWaveFinish{ false }
	, isReturnFinish{ false }
	, isReversal{ false }
{
	animation = new Animation{};
}

Waveout::~Waveout()
{
}

void Waveout::Update()
{

	static const int ANIM = 48;

	//�A�j���[�V�����̐ݒ�
	{
		animation->AddAnimCount(1);
		int animNum = animation->GetAnimation(ANIM, ANIM / 4);
		imageH = Image::GetInstance()->GetWaveH(animNum);
	}

	waveCount += ADD_WAVE_COUNT;

	oldAlpha = alpha;

	if (isReversal)
	{
		alpha -= addVal;
		alpha = max(0, alpha);
		if (alpha > 1)return;
	}
	else
	{
		alpha += addVal;
		alpha = min(255, alpha);
		if (alpha < 255)return;
	}

	count++;

	//���]��false�ő҂����Ԉȏ�Â�������true
	if (count >= waitSecond * FPS && !isReversal)
	{
		isWaveFinish = true;
	}
	//���]�Ȃ�ҋ@������true
	else if (isReversal)
		isReturnFinish = true;
}

void Waveout::Draw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

	for (int i = 0; i < WINDOW_Y; i++)
	{
		int area = static_cast<int>(WAVE_SIZE * sinf(WAVE_FINENESS * PI * (waveCount / FPS - i / MAKE_WAVE_NUM)));

		area += WAVE_SIZE;

		//��ʓ���XY���W�AimageH�̒���XY���W�AimageH�̒��̕`�悵�����͈́AimageH
		DrawRectGraph(0, i, area, i, WINDOW_X, 1, imageH, false);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Waveout::SetIsReversal(bool _isReversal)
{
	isWaveFinish = false;
	isReversal = _isReversal;
}

bool Waveout::GetNowMaxAlpha() const
{
	if (alpha < 255)return false;

	if (alpha >= 255 && oldAlpha < 255)return true;

	return false;
}
