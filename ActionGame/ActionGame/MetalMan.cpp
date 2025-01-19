#include "MetalMan.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "KeyControlle.h"

namespace
{
	//HP
	static const int START_HP = 28;

	//�W�����v��
	static const float JUMP_LARGE	= 10.f;
	static const float JUMP_MEDIUM	= 8.f;
	static const float JUMP_SMALL	= 5.f;
	static const float JUMP_OVER	= 12.f;

	//�W�����v���Ƃ̍U����
	static const int ATTACK_LARGE	= 3;
	static const int ATTACK_MEDIUM	= 2;
	static const int ATTACK_SMALL	= 1;
	static const int ATTACK_OVER	= 1;

	//�X�s�[�h
	static const float WALK_SPEED = -3.f;

	//�R���W����
	static const float COL_TOP = -BLOCK_SIZE;
	static const float COL_UNDER = BLOCK_SIZE / 2;
	static const float COL_LEFT = -BLOCK_SIZE / 2;
	static const float COL_RIGHT = BLOCK_SIZE / 2;

	//�摜
	static const float IMG_TOP = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT = -32;
	static const float IMG_RIGHT = 32;

	//�X�e�[�g
	static const int STATE_IDLE = 0;
	static const int STATE_JUMP = 1;
	static const int STATE_ATTACK = 2;
	static const int STATE_DEATH = 3;

	//�p���[
	static const int POWER_BODY = 7;

	//�T�m�͈�
	static const float START_ATTACK_SIZE = 100.f;

}

MetalMan::MetalMan(BaseScene* baseScene, BulletManager* bulletManager, EffectManager* _effectManager, BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{ baseScene,bulletManager,_effectManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, imageH{ 0 }
	, moveKnd{ 0 }
	, moveAngle{ -1 }
	, moveCount{ 0 }
	, shotAngle{ 0 }
	, attackNum{ 0 }
	, attackCount{ 0 }
	, damageCount{ 0 }
	, isInvincible{ true }
{
	bodyPower = POWER_BODY;

	bulletManager->AddBullet(BulletManager::BULLET_KND::METAL);

	state->SetAllStateMember("Idle");
	state->SetAllStateMember("Jump");
	state->SetAllStateMember("Attack");
	state->SetAllStateMember("Death");
}

MetalMan::~MetalMan()
{
}

void MetalMan::Update()
{
	if (life->GetIsDeath())return;

	gravity->AddGravity(velocity.y);

	state->ChangeState();

	Invincible();

	//moveCount�œ������Ǘ�����
	moveCount++;

	switch (state->GetNowState())
	{
	case STATE_IDLE:	UpdateIdle();		break;
	case STATE_JUMP:	UpdateJump();		break;
	case STATE_ATTACK:	UpdateAttack();		break;
	case STATE_DEATH:	UpdateDeath();		break;

	default:			assert(false);
	}

	positionSetter->UpdatePos(this, collisionData, collisionManager, fall);

}

void MetalMan::Draw(F_Vec2 _camDif)
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

	///�f�o�b�O�p
	//����̉���
	DrawBox
	(
		drawpos.x - _camDif.x + collisionData->GetLeft(),
		drawpos.y - _camDif.y + collisionData->GetTop(),
		drawpos.x - _camDif.x + collisionData->GetRight(),
		drawpos.y - _camDif.y + collisionData->GetUnder(),
		GetColor(255, 255, 255),
		false
	);
}

void MetalMan::UpdateIdle()
{
	//�O�b�ԑ҂�
	static const int MOVE_WAIT = FPS * 3;

	//�T�m�͈͓��ɓ�������t���ɍs���n�߂�
	if (IsNearDistance())
	{
		moveKnd = E_MOVE_KND::OVER;
		JumpStart();
	}
	else if (GetAttackKey() || moveCount >= MOVE_WAIT)//�v���C���[���U�����邩MOVE_WAIT���z������U������
	{
		//�����܂Ő��m�ȃ����_�������K�v���Ȃ��̂Ł@std::rand()
		moveKnd = std::rand() % E_MOVE_KND::JUMP_RAND_MAX;
		JumpStart();
	}

	DamageStart();

}

void MetalMan::UpdateJump()
{
	//�������n�߂���U�����J�n����
	if (velocity.y < 0.f)
	{
		AttackStart();
	}

	DamageStart();

}

void MetalMan::UpdateAttack()
{
	//�U����񕪂̑S�̃t���[��
	static const int MAX_SHOT_FRAME = 30;
	//�e�����܂ł̒x��
	static const int SHOT_DELAY = 10;

	//����������Idle�ɕύX
	if (fall->GetIsOnGround())
	{
		//���ړ����~����
		velocity.x = 0;
		IdleStart();
	}

	//SHOT_DELAY�Œe������
	if (moveCount == SHOT_DELAY)
	{
		velocity.y = 0;
		attackCount++;
		Attack();
	}

	//�U�������I������猂�񐔂��m�F����
	if (moveCount == MAX_SHOT_FRAME)
	{
		if (attackCount < attackNum)
		{
			//�U�����邽�߂ɏ�����
			moveCount = 0;
		}
	}

	DamageStart();
}

void MetalMan::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);
	if (deathCount == Life::DEATH_EFFECT_FRAME)
	{
		effectManager->SetDeffusion(position);
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DISAPPEAR);
	}
}

void MetalMan::IdleStart()
{
	//�X�e�[�g���ڍs���邩��moveCount��������
	moveCount = 0;
	//moveAngle���Z�b�g
	SetMoveAngle();

	state->SetNextState("Idle");
}

void MetalMan::JumpStart()
{
	switch (moveKnd)
	{
	case E_MOVE_KND::LARGE:		velocity.y = JUMP_LARGE;	break;	//��W�����v
	case E_MOVE_KND::MEDIUM:	velocity.y = JUMP_MEDIUM;	break;	//���W�����v
	case E_MOVE_KND::SMALL:		velocity.y = JUMP_SMALL;	break;	//���W�����v

	case E_MOVE_KND::OVER:		//�t�T�C�h�ɍs���W�����v
		velocity.x = WALK_SPEED * -moveAngle;
		velocity.y = JUMP_OVER;		
		break;

	default:					assert(false);				break;
	}

	state->SetNextState("Jump");

}

void MetalMan::AttackStart()
{
	//�X�e�[�g���ڍs���邩��moveCount��������
	moveCount = 0;

	//attackCount��������
	attackCount = 0;

	switch (moveKnd)
	{
	case E_MOVE_KND::LARGE:		attackNum = ATTACK_LARGE;	break;	//��W�����v
	case E_MOVE_KND::MEDIUM:	attackNum = ATTACK_MEDIUM;	break;	//���W�����v
	case E_MOVE_KND::SMALL:		attackNum = ATTACK_SMALL;	break;	//���W�����v
	case E_MOVE_KND::OVER:		attackNum = ATTACK_OVER;	break;	//�t�T�C�h�ɍs���W�����v

	default:					assert(false);				break;
	}

	state->SetNextState("Attack");

}

void MetalMan::DamageStart()
{
	//���G�Ȃ画������Ȃ�
	if (isInvincible)return;

	int bulletDamage = bulletManager->HitCheckChara(this, collisionData);
	if (bulletDamage != 0)
	{
		//�_���[�W����
		life->DecHp(bulletDamage);
		//���G�ɂȂ�
		isInvincible = true;
		damageCount = 0;

		//hp��0�ȉ��Ȃ玀
		if (life->GetHp() <= 0)
		{
			state->SetNextState("Death");
			return;
		}
	}
}

void MetalMan::DeathStart()
{

}

void MetalMan::Invincible()
{
	static const int MAX_INVINCIBLE_FRAME = FPS / 2;

	if (isInvincible)
	{
		damageCount++;
		if (damageCount > MAX_INVINCIBLE_FRAME)
			isInvincible = false;
	}
}

bool MetalMan::IsNearDistance()
{
	return F_Vec2::VSize(plBase->GetPosition() - position) < START_ATTACK_SIZE;
}

void MetalMan::Attack()
{
	//moveAngle���Z�b�g
	SetMoveAngle();

	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * moveAngle),
		position.y
	};

	F_Vec2 genVec = F_Vec2{ 0,0 };

	//�v���C���[���W���擾
	F_Vec2 plPos = plBase->GetPosition();
	//���Ίp�x���v�Z
	shotAngle = atan2f(plPos.y - position.y, plPos.x - position.x);
	//���������v�Z
	SetGenVec(genVec, shotAngle);
	
	//�e�𔭎�
	bulletManager->SetState(genPos, genVec, BulletManager::BULLET_KND::METAL, BulletManager::BULLET_OWNER::ENEMY);

}

void MetalMan::SetGenVec(F_Vec2& genVec, float rad)
{
	//sinf��cosf�����ւ��邱�ƂŁA���E��-+�̈Ⴂ���o��
	genVec.x = cosf(rad);
	genVec.y = sinf(rad);
}

void MetalMan::SetMoveAngle()
{
	//�v���C���[���W���擾
	F_Vec2 plPos = plBase->GetPosition();
	//���g���E�������@���Ȃ�-1
	moveAngle = position.x - plPos.x > 0 ? -1 : 1;
}

bool MetalMan::GetAttackKey()
{
	return KeyControlle::GetInstance()->GetNowPressing(E_KEY::ATTACK);
}
