#include "Effect.h"
#include"Animation.h"
#include"Image.h"
#include"EffectManager.h"

Effect::Effect(BaseScene* baseScene, EffectManager* _effectManager)
	:BaseObject{ baseScene,BaseObject::E_TAG::EFFECT }
	, maxFrame{ 0 }
	, oneImageFrame{ 0 }
	, deffusionFlame{ 0 }
	, flag{ false }
	, effectManager{ _effectManager }
{
	animation = new Animation{};
}

Effect::~Effect()
{
	if (animation != nullptr)delete animation;

}

void Effect::Update()
{
	//��юU��G�t�F�N�g�̐�������
	static const int DEFFUSION_FRAME = FPS * 5;
	//��r���鑬�x
	static const float VELOCITY_DIF = 0.5f;

	animation->AddAnimCount(1);
	int animNum = animation->GetAnimation(maxFrame, oneImageFrame);
	animation->SetAnimNum(animNum);

	//fabsf�Ő�Βl���擾�AFLT_EPSILON��菬������Γ�����
	if (fabsf(velocity.x) <= FLT_EPSILON + VELOCITY_DIF &&
		fabsf(velocity.y) <= FLT_EPSILON + VELOCITY_DIF)
	{
		if (animation->GetAnimCount() >= maxFrame)flag = false;
	}
	else
	{
		deffusionFlame++;
		position += velocity;
		if (deffusionFlame > DEFFUSION_FRAME)
		{
			flag = false;
		}
	}

}

void Effect::Draw(F_Vec2 _camDif)
{
	if (!flag)return;

	int imageH = Image::GetInstance()->GetEffectH(animation->GetAnimNum());

	F_Vec2 drawpos = GetPosition();

	DrawExtendGraph
	(
		drawpos.x - _camDif.x - BLOCK_SIZE / 2,
		drawpos.y - _camDif.y - BLOCK_SIZE / 2,
		drawpos.x - _camDif.x + BLOCK_SIZE / 2,
		drawpos.y - _camDif.y + BLOCK_SIZE / 2,
		imageH,
		true
	);
}

void Effect::SetState(F_Vec2 pos, F_Vec2 vel)
{
	position = pos;
	flag = true;
	animation->SetAnimCount(0);
	velocity = vel;

	oneImageFrame = 4;
	maxFrame = oneImageFrame * 4;
}