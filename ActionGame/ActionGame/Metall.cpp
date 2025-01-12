#include "Metall.h"
#include "BulletManager.h"
#include "BallBullet.h"

namespace
{
	//�̗�
	static const int START_HP = 1;

	//�X�s�[�h
	static const float RUN_SPEED = -3.f;

	//��x�Ɍ��e�̐�
	static const int BULLET_NUM = 3;

	//�R���W����
	static const int COL_TOP = -BLOCK_SIZE / 2;
	static const int COL_UNDER = BLOCK_SIZE / 2;
	static const int COL_LEFT = -BLOCK_SIZE / 2;
	static const int COL_RIGHT = BLOCK_SIZE / 2;

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
	static const float START_ATTACK_SIZE = 50.f;
}

Metall::Metall(BaseScene* baseScene, BulletManager* bulletManager, BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{ baseScene,bulletManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, shotAngle{ -1 }
	, moveCount{ 0 }
	, isInvincible{ 0 }
{
	bulletManager->AddBulletList<BallBullet>(BulletManager::BULLET_KND::BALL);

	bodyPower = POWER_BODY;

	state->SetAllStateMember("Idle");
	state->SetAllStateMember("Attack");
	state->SetAllStateMember("Run");
	state->SetAllStateMember("Fall");
	state->SetAllStateMember("Damage");
	state->SetAllStateMember("DEATH");
}

Metall::~Metall()
{
}

void Metall::Update()
{
	if (life->GetIsDeath())return;

	gravity->AddGravity(velocity.y);

	state->ChangeState();

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
	if(isInvincible)
	{ 
		DrawBox
		(
			drawpos.x - _camDif.x + collisionData->GetLeft(),
			drawpos.y - _camDif.y + collisionData->GetTop(),
			drawpos.x - _camDif.x + collisionData->GetRight(),
			drawpos.y - _camDif.y + collisionData->GetUnder(),
			GetColor(100, 100, 255),
			true
		);
	}
	else
	{
		DrawBox
		(
			drawpos.x - _camDif.x + collisionData->GetLeft(),
			drawpos.y - _camDif.y + collisionData->GetTop(),
			drawpos.x - _camDif.x + collisionData->GetRight(),
			drawpos.y - _camDif.y + collisionData->GetUnder(),
			GetColor(255, 255, 255),
			true
		);
	}
}

void Metall::UpdateIdle()
{
	if (F_Vec2::VSize(plBase->GetPosition() - position) < START_ATTACK_SIZE)StartAttack();
}

void Metall::UpdateAttack()
{
	//�U�����I������t���[��
	static const int MAX_SHOT_FRAME = 60;
	//�e�����܂ł̒x��
	static const int SHOT_DELAY = 4;

	if (moveCount >= MAX_SHOT_FRAME)
	{
		StartRun();
	}

	if (moveCount == SHOT_DELAY)
	{
		Attack();
	}
}

void Metall::UpdateRun()
{
}

void Metall::UpdateFall()
{
}

void Metall::UpdateDamage()
{
}

void Metall::UpdateDeath()
{
}

void Metall::StartIdle()
{
}

void Metall::StartAttack()
{
	//���G��Ԃ�����
	isInvincible = false;
	//�X�e�[�g���ڍs���邩��moveCount��������
	moveCount = 0;

	//�v���C���[���W���擾
	F_Vec2 plPos = plBase->GetPosition();
	//���g���E�������@���Ȃ�-1
	shotAngle = position.x - plPos.x > 0 ? -1 : 1;

	state->SetNextState("Attack");

}

void Metall::StartRun()
{
}

void Metall::StartFall()
{
}

void Metall::StartDamage()
{
}

void Metall::StartDeath()
{
}

void Metall::Attack()
{
	//90�x���v�Z�Ɏg���̂Ő�ɐ錾
	static const float HALF_PI = PI / 2;

	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * shotAngle),
		position.y
	};

	F_Vec2 genVec = F_Vec2{ 0,0 };

	//��������ݒ�
	//����sinf�ŏo�����߁A-shotAngle�ɂ��Ă���
	float rad = HALF_PI * -shotAngle;

	//BULLET_NUM���̒e������
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (i > 0)
		{
			//�ŏ��̈ꔭ�ȊO�͏㉺�ɑł�������(std::powf(-1, i)��1��-1�ŐU��������p)
			rad += std::powf(-1, i) * PI / BULLET_NUM;
		}
		SetGenVec(genVec, rad);
	}

	bulletManager->SetState(genPos, genVec,BulletManager::BULLET_KND::BALL ,BulletManager::BULLET_OWNER::ENEMY);

}

void Metall::SetGenVec(F_Vec2& genVec, float rad)
{
	//sinf��cosf�����ւ��邱�ƂŁA���E��-+�̈Ⴂ���o��
	genVec.x = sinf(rad);
	genVec.y = cosf(rad);
}
