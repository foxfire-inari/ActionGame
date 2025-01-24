#include "Metall.h"
#include "BulletManager.h"
#include "EffectManager.h"
namespace
{
	//�̗�
	static const int START_HP = 1;

	//�X�s�[�h
	static const float RUN_SPEED = 3.f;

	//��x�Ɍ��e�̐�
	static const int BULLET_NUM = 3;

	//�R���W����
	static const int COL_TOP = -BLOCK_SIZE / 2;
	static const int COL_UNDER = BLOCK_SIZE / 2;
	static const int COL_LEFT = -BLOCK_SIZE / 2;
	static const int COL_RIGHT = BLOCK_SIZE / 2;

	//�摜
	static const float IMG_TOP = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT = COL_LEFT;
	static const float IMG_RIGHT = COL_RIGHT;

	//�X�e�[�g
	static const int STATE_IDLE = 0;
	static const int STATE_ATTACK = 1;
	static const int STATE_RUN = 2;
	static const int STATE_FALL = 3;
	static const int STATE_DAMAGE = 4;
	static const int STATE_DEATH = 5;

	//�p���[
	static const int POWER_BODY = 2;

	//�T�m�͈�
	static const float START_ATTACK_SIZE = 250.f;
}

Metall::Metall(BaseScene* baseScene, BulletManager* bulletManager, EffectManager* _effectManager, BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{ baseScene,bulletManager,_effectManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, imageH{ -1 }
	, moveAngle{ -1 }
	, moveCount{ 0 }
	, damageCount{ 0 }
	, isInvincible{ true }
{
	bulletManager->AddBullet(BulletManager::BULLET_KND::BALL);

	bodyPower = POWER_BODY;

	state->SetAllStateMember("Idle");
	state->SetAllStateMember("Attack");
	state->SetAllStateMember("Run");
	state->SetAllStateMember("Fall");
	state->SetAllStateMember("Damage");
	state->SetAllStateMember("Death");
}

Metall::~Metall()
{
}

void Metall::Update()
{
	if (life->GetIsDeath())return;

	gravity->AddGravity(velocity.y);

	state->ChangeState();

	animation->AddAnimCount(1.f);

	//moveCount�œ������Ǘ�����
	moveCount++;

	switch (state->GetNowState())
	{
	case STATE_IDLE:	UpdateIdle();		break;
	case STATE_ATTACK:	UpdateAttack();		break;
	case STATE_RUN:		UpdateRun();		break;
	case STATE_FALL:	UpdateFall();		break;
	case STATE_DAMAGE:	UpdateDamage();		break;
	case STATE_DEATH:	UpdateDeath();		break;

	default:			assert(false);
	}

	positionSetter->UpdatePos(this, collisionData, collisionManager, fall);
}

void Metall::Draw(F_Vec2 _camDif)
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
#ifdef _DEBUG
	if(isInvincible)
	{ 
		DrawBox
		(
			drawpos.x - _camDif.x + IMG_LEFT,
			drawpos.y - _camDif.y + IMG_TOP,
			drawpos.x - _camDif.x + IMG_RIGHT,
			drawpos.y - _camDif.y + IMG_UNDER,
			GetColor(100, 100, 255),
			false
		);
	}
	else
	{
		DrawBox
		(
			drawpos.x - _camDif.x + IMG_LEFT,
			drawpos.y - _camDif.y + IMG_TOP,
			drawpos.x - _camDif.x + IMG_RIGHT,
			drawpos.y - _camDif.y + IMG_UNDER,
			GetColor(255, 255, 255),
			false
		);
	}
#endif  _DEBUG
}

void Metall::UpdateIdle()
{
	//�A�j���[�V�����̐ݒ�
	{
		int angImage = animation->GetAngleImage(0, 1, moveAngle);
		imageH = Image::GetInstance()->GetMetallIdleH(angImage);
	}

	//�ҋ@���I������t���[��
	static const int MAX_IDLE_FRAME = 120;
	if (moveCount >= MAX_IDLE_FRAME)
	{
		//�v���C���[������̋����ȉ����A�e��BULLET_NUM���邩
		if (IsNearDistance() && IsCanShot())
		{
			AttackStart();
		}
	}
}

void Metall::UpdateAttack()
{
	//����ł܂ł̃t���[��
	static const int SHOT_FRAME = 30;

	//�A�j���[�V�����̐ݒ�
	{
		static const int ANIM = SHOT_FRAME+2;//���[�v���Ȃ��悤�ɒl���������₷
		int angImage = animation->GetAngleImage(0, 2, moveAngle);
		int animNum = animation->GetAnimation(ANIM, ANIM / 2);
		imageH = Image::GetInstance()->GetMetallUpH(animNum + angImage);
	}

	if (moveCount == SHOT_FRAME)
	{
		Attack();
		RunStart();
	}

	DamageStart();
}

void Metall::UpdateRun()
{
	//�A�j���[�V�����̐ݒ�
	{
		static const int ANIM = 30;
		int angImage = animation->GetAngleImage(0, 2, moveAngle);
		int animNum = animation->GetAnimation(ANIM, ANIM / 2);
		imageH = Image::GetInstance()->GetMetallRunH(animNum + angImage);
	}
	//�ړ����I������t���[��
	static const int MAX_RUN_FRAME = 90;

	if (moveCount >= MAX_RUN_FRAME)
	{
		//�ړ����~����
		velocity.x = 0;
		IdleStart();
	}
	//�n�ʂɏ���ĂȂ����Fall�ɍs��
	if (!fall->GetIsOnGround())FallStart();
	DamageStart();

}

void Metall::UpdateFall()
{
	//�n�ʂɂ��܂ŉ��ړ����ł��Ȃ��悤�ɂ���
	if (fall->GetIsOnGround())
	{
		velocity.x = moveAngle * RUN_SPEED;

		state->SetNextState("Run");
	}
	DamageStart();

}

void Metall::UpdateDamage()
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

void Metall::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);
	if (deathCount == Life::DEATH_EFFECT_FRAME)
	{
		effectManager->SetState(position, F_Vec2{ 0,0 });
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DISAPPEAR);
	}
}

void Metall::IdleStart()
{
	//���G��Ԃ��J�n
	isInvincible = true;
	//�X�e�[�g���ڍs���邩��moveCount��������
	moveCount = 0;
	
	state->SetNextState("Idle");
}

void Metall::AttackStart()
{
	//���G��Ԃ�����
	isInvincible = false;
	//�X�e�[�g���ڍs���邩��moveCount��������
	moveCount = 0;

	//moveAngle���Z�b�g
	SetMoveAngle();
	//�A�j���[�V������������
	animation->SetAnimCount(0);
	state->SetNextState("Attack");
}

void Metall::RunStart()
{
	//�X�e�[�g���ڍs���邩��moveCount��������
	moveCount = 0;

	//moveAngle���Z�b�g
	SetMoveAngle();

	velocity.x = moveAngle * RUN_SPEED;

	state->SetNextState("Run");
}

void Metall::FallStart()
{
	//�ړ���������X�e�[�g���ڍs���Ă�moveCount�͏��������Ȃ�
	//moveCount = 0;


	velocity.x = 0;
	state->SetNextState("Fall");
}

void Metall::DamageStart()
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

bool Metall::IsNearDistance()
{
	return VSize(plBase->GetPosition() - position) < START_ATTACK_SIZE;
}

bool Metall::IsCanShot()
{
	return bulletManager->GetCanShot(BulletManager::BULLET_KND::BALL, BULLET_NUM);
}

void Metall::Attack()
{
	//90�x���v�Z�Ɏg���̂Ő�ɐ錾
	static const float HALF_PI = PI / 2;
	//�㉺�ɑł������鎞�̊p�x
	static const float SIDE_PI = PI / 5;

	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * moveAngle),
		position.y
	};

	F_Vec2 genVec = F_Vec2{ 0,0 };

	//��������ݒ�
	float rad = HALF_PI * moveAngle;

	//BULLET_NUM���̒e������
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (i > 0)
		{
			//�ŏ��̈ꔭ�ȊO�͏㉺�ɑł�������(std::powf(-1, i)��1��-1�ŐU��������p)
			rad += std::powf(-1, i) * SIDE_PI * i;
		}
		SetGenVec(genVec, rad);

		bulletManager->SetState(genPos, genVec, BulletManager::BULLET_KND::BALL, BulletManager::BULLET_OWNER::ENEMY); 

	}


}

void Metall::SetGenVec(F_Vec2& genVec, float rad)
{
	//sinf��cosf�����ւ��邱�ƂŁA���E��-+�̈Ⴂ���o��
	genVec.x = sinf(rad);
	genVec.y = cosf(rad);
}

void Metall::SetMoveAngle()
{
	//�v���C���[���W���擾
	F_Vec2 plPos = plBase->GetPosition();
	//���g���E�������@���Ȃ�-1
	moveAngle = position.x - plPos.x > 0 ? -1 : 1;
}
