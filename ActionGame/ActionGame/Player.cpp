#include "Player.h"
#include "KeyControlle.h"

namespace
{
	//スピード
	static const float WALK_SPEED = -13.f;
	static const float DECELERATION_SPEED = 1.25f;


	//ステート
	static const int STATE_IDLE = 0;
	static const int STATE_RUN = 1;
	static const int STATE_JUMP = 2;
}

Player::Player(BaseScene* baseScene)
	:Chara{ baseScene,-32,32,-32,32,BaseObject::E_TAG::PLAYER }
	, inputRight{ 0 }
	, inputDown{ 0 }
	, inputAngle{ 0 }
	, moveSpeed{ 0 }
	, moveAngle{ 0 }
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
	velocity = F_Vec2{ 0,velocity.y };

	//何らかの方向キーが押されていたら歩き始める
	for (int i = 0; i < 4; i++)
	{
		if (KeyControlle::GetInstance()->GetPressingFrame(i))
			StartRun();
	}


	JumpStart();
	AttackStart();
	GetItem();
	DamageStart();

}

void Player::UpdateRun()
{
	SetInputAngle();

	bool isRun = Move(WALK_SPEED);
	if (!isRun)
	{
		MoveDeceletation();
		if (moveSpeed >= 0)state->SetNextState("Idle");
	}
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
	state->SetNextState("Run");
}

void Player::AttackStart()
{
}

void Player::SetInputAngle()
{
	inputRight = 0, inputDown = 0;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::UP))		inputDown = -1;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::DOWN))		inputDown = 1;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::LEFT))		inputRight = -1;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::RIGHT))	inputRight = 1;

	inputAngle = 0;
	if (inputRight != 0 || inputDown != 0)
	{
		//座標から傾きθを求める
		inputAngle = atan2f(static_cast<float>(-inputRight), static_cast<float>(inputDown));
	}
}

bool Player::Move(float speed)
{
	//加速度
	static const float ACCELERATION_SPEED = -1.5f;
	if (inputRight != 0)
	{
		moveAngle = -inputRight;
		if (moveSpeed > speed)
			moveSpeed += ACCELERATION_SPEED;
		F_Vec2 move = F_Vec2{ moveSpeed * moveAngle, velocity.y };
		velocity = move;
		return true;
	}
	return false;
}

void Player::MoveDeceletation()
{
	//減速
	moveSpeed += DECELERATION_SPEED;

	//0にする
	if (moveSpeed > 0)
	{
		moveSpeed = 0;
		moveAngle = 0;
	}
	F_Vec2 move = F_Vec2{ moveSpeed * moveAngle, velocity.y };
	velocity = move;
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