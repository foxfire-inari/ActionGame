#include "Player.h"

namespace
{
	static const int STATE_IDLE = 0;
	static const int STATE_RUN = 1;
	static const int STATE_JUMP = 2;
}

Player::Player(BaseScene* baseScene)
	:Chara{baseScene,-32,32,-32,32,BaseObject::E_TAG::PLAYER}
	, isInvincible{ false }
	, isGameOver{ false }
{
	GetBaseScene()->SetOneObjectList(this);

	state->SetAllStateMember("Idle");
	state->SetAllStateMember("Run");
	state->SetAllStateMember("Jump");
}

Player::~Player()
{
}

void Player::Start()
{
}

void Player::Update()
{
	gravity->AddGravity(velocity.y);
	state->ChangeState();

	switch (state->GetNowState())
	{
	case STATE_IDLE:			UpdateIdle();			break;

	case STATE_RUN:				UpdateRun();			break;

	case STATE_JUMP:			UpdateJump();			break;
	}

	positionSetter->UpdatePos(this, collisionManager, fall);
}

void Player::Draw()
{
	F_Vec2 drawpos = GetPosition();
	DrawBox
	(
		drawpos.x + ColData->GetLeft(),
		drawpos.y + ColData->GetTop(),
		drawpos.x + ColData->GetRight(),
		drawpos.y + ColData->GetUnder(),
		GetColor(255, 255, 255),
		true
	);
	DrawFormatString(50, 50, GetColor(255, 255, 255),
		"velocity:%f,%f", GetVelocity().x, GetVelocity().y);
}

void Player::DrawUI()
{
}

void Player::DrawData()
{
}

void Player::UpdateIdle()
{
}

void Player::UpdateRun()
{
}

void Player::UpdateJump()
{
}

void Player::UpdateAttack()
{
}

void Player::UpdateDamage()
{
}

void Player::UpdateDeath()
{
}

void Player::JumpStart()
{
}

void Player::DamageStart()
{
}

void Player::DeathStart()
{
}

void Player::Invincible()
{
}

void Player::FallStart()
{
}

void Player::StartRun()
{
}

void Player::AttackStart()
{
}

void Player::SetInputAngle()
{
}

bool Player::Move(float speed)
{
	return false;
}

void Player::MoveDeceletation()
{
}

void Player::GetItem()
{
}

void Player::Attack()
{
}

void Player::SetStatus()
{
}

void Player::GetNowSceneManager()
{
}