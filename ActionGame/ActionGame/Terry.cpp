#include "Terry.h"
#include"Image.h"
#include "BulletManager.h"
#include"EffectManager.h"

namespace
{
	//�̗�
	static const int START_HP = 1;

	//�ړ����x
	static const float MOVE_SPEED = 0.5f;

	//�R���W����
	static const int COL_TOP = -BLOCK_SIZE / 2;
	static const int COL_UNDER = BLOCK_SIZE / 2;
	static const int COL_LEFT = -BLOCK_SIZE / 2;
	static const int COL_RIGHT = BLOCK_SIZE / 2;

	//�摜
	static const float IMG_TOP   = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT  = COL_LEFT;
	static const float IMG_RIGHT = COL_RIGHT;

	//�X�e�[�g
	static const int STATE_RUN = 0;
	static const int STATE_DAMAGE = 1;
	static const int STATE_DEATH = 2;

	//�p���[
	static const int POWER_BODY = 2;

	//�ړ���������t���[����
	static const int MOVE_FRAME = FPS;
}

Terry::Terry(BaseScene* baseScene, BulletManager* bulletManager, EffectManager* _effectManager,
	BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{baseScene,bulletManager,_effectManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, moveAngle{ 0 }
	, damageCount{ 0 }
	, moveCount{ MOVE_FRAME }//��ʂɉf�����u�Ԃɓ����Ăق���
{
	bodyPower = POWER_BODY;

	state->SetAllStateMember("Run");
	state->SetAllStateMember("Damage");
	state->SetAllStateMember("Death");
}

Terry::~Terry()
{
}

void Terry::Update()
{
	if (life->GetIsDeath())return;

	//�����Ă��邽�ߏd�͂𖳎�����
	//gravity->AddGravity(velocity.y);

	state->ChangeState();

	switch (state->GetNowState())
	{
	case STATE_RUN:		UpdateRun();		break;
	case STATE_DAMAGE:	UpdateDamage();		break;
	case STATE_DEATH:	UpdateDeath();		break;

	default:			assert(false);
	}

	positionSetter->UpdateNonInterPos(this);


}

void Terry::Draw(F_Vec2 _camDif)
{
	F_Vec2 drawpos = GetPosition();

	DrawExtendGraph
	(
		drawpos.x - _camDif.x + IMG_LEFT,
		drawpos.y - _camDif.y + IMG_TOP,
		drawpos.x - _camDif.x + IMG_RIGHT,
		drawpos.y - _camDif.y + IMG_UNDER,
		imageH,
		true
	);
}

void Terry::UpdateRun()
{
	//�A�j���[�V�����̐ݒ�
	{
		static const int ANIM = 48;
		int animNum = animation->GetAnimation(ANIM, ANIM / 4);
		imageH = Image::GetInstance()->GetTerryH(animNum);
	}

	moveCount++;

	//��莞�Ԉړ�������ړ��������X�V
	if (moveCount >= MOVE_FRAME)
	{
		//�v���C���[���W���擾
		F_Vec2 plPos = plBase->GetPosition();
		//���Ίp�x���v�Z
		moveAngle = atan2f(plPos.y - position.y, plPos.x - position.x);

		//�i�ޕ������v�Z
		F_Vec2 vel = F_Vec2{ cos(moveAngle), sin(moveAngle) };

		//------------------���x�ɈႢ���o�Ȃ��悤�Ƀx�N�g���̌������㉺���E�̎l�����ɌŒ肵����

		//�ǂ����̐�Βl���傫�������r���đ傫���x�N�g����D�悷��
		if (fabsf(vel.x) > fabsf(vel.y))
		{
			vel.x *= MOVE_SPEED;
			vel.y *= 0;
		}
		else
		{
			vel.x *= 0;
			vel.y *= MOVE_SPEED;
		}

		//velocity���Z�b�g
		SetVelocity(vel);
		moveCount = 0;
	}

	DamageStart();
}

void Terry::UpdateDamage()
{
	static const int DAMAGE_MAX_FRAME = 6;
	damageCount++;
	if (damageCount >= DAMAGE_MAX_FRAME)
	{
		//hp��0�ȉ��Ȃ玀
		if (life->GetHp() <= 0)
		{
			state->SetNextState("Death");
			return;
		}
		RunStart();
	}
	DamageStart();
}

void Terry::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);
	if (deathCount == Life::DEATH_EFFECT_FRAME)
	{
 		effectManager->SetState(position, F_Vec2{ 0,0 });
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DISAPPEAR);
	}
}

void Terry::RunStart()
{
	state->SetNextState("Run");
}

void Terry::DamageStart()
{
	if (life->GetHp() <= 0)return;
	int bulletDamage = bulletManager->HitCheckChara(this, collisionData);
	if (bulletDamage != 0)
	{
		//�_���[�W����
		life->DecHp(bulletDamage);

		damageCount = 0;

		state->SetNextState("Damage");
	}
}
