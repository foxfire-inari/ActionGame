#include "Player.h"
#include "KeyControlle.h"
#include "Camera.h"

namespace
{
	//�W�����v��
	static const float JUMP_POWER = 8.f;

	//�X�s�[�h
	static const float WALK_SPEED = -3.f;
	static const float DECELERATION_SPEED = 0.5f;


	//�X�e�[�g
	static const int STATE_IDLE = 0;
	static const int STATE_RUN = 1;
	static const int STATE_JUMP = 2;
}

Player::Player(BaseScene* baseScene)
	:Chara{ baseScene,-32,32,-32,32,BaseObject::E_TAG::PLAYER }
	, camPos{}
	, jumpCount{ 0 }
	, inputRight{ 0 }
	, inputDown{ 0 }
	, inputAngle{ 0 }
	, moveSpeed{ 0 }
	, moveAngle{ 0 }
	, isInvincible{ false }
	, isGameOver{ false }

{
	GetBaseScene()->SetOneObjectList(this);

	oldPos = position;

	camera = GetBaseScene()->GetOneObjectPtr<Camera>(BaseObject::E_TAG::CAMERA);
	assert(camera != nullptr);
	camPos = position;


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

	positionSetter->UpdatePos(this,collisionData, collisionManager, fall);

	SetCameraPositionAndTarget();
}

void Player::Draw(F_Vec2 _camDif)
{
	F_Vec2 drawpos = GetPosition();
	DrawBox
	(
		drawpos.x - _camDif.x + collisionData->GetLeft(),
		drawpos.y - _camDif.y + collisionData->GetTop(),
		drawpos.x - _camDif.x + collisionData->GetRight(),
		drawpos.y - _camDif.y + collisionData->GetUnder(),
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

void Player::SetCameraPositionAndTarget()
{
	camera->SetTarget(position);


}

void Player::UpdateIdle()
{
	velocity = F_Vec2{ 0,velocity.y };

	//���炩�̕����L�[��������Ă���������n�߂�
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
	JumpStart();
	AttackStart();
	FallStart();
	GetItem();	
	DamageStart();
}

void Player::UpdateJump()
{
	SetInputAngle();

	bool isMove = Move(WALK_SPEED);
	if (!isMove)MoveDeceletation();

	//���n
	if (velocity.y < 0 && fall->GetIsOnGround())
	{
		if (moveSpeed != 0)	StartRun();
		else state->SetNextState("Idle");
	}

	AttackStart();
	GetItem();
	DamageStart();

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
	static const int MAX_LITTLE_JUMP_FRAME = 4;

	if (!fall->GetIsOnGround())
	{
		if (jumpCount != 0)jumpCount = 0;
		return;
	}

	//�������ŃW�����v���Ȃ��悤�ɂ���
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP) > MAX_LITTLE_JUMP_FRAME + 1)return;

	//�W�����v�{�^���������Ă��Ēn�ʂɂ���Ȃ�W�����v�J�E���g���{�^���������Ă��镪�t���[���ɂ���
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP) != 0 && fall->GetIsOnGround())
		jumpCount = KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP);

	//���W�����v
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP) == 0 &&
		jumpCount != 0)
	{
		//�W�����v�{�^����MAX_LITTLE_JUMP_FRAME�ȓ��ɗ������珬�W�����v
		if (jumpCount <= MAX_LITTLE_JUMP_FRAME)
		{
			state->SetNextState("Jump");
			velocity.y = JUMP_POWER / 1.5f;
			jumpCount = 0;
		}
	}
	//�W�����v�{�^����MAX_LITTLE_JUMP_FRAME�ȏ㉟���Ă������W�����v
	else if (jumpCount > MAX_LITTLE_JUMP_FRAME)
	{
		state->SetNextState("Jump");
		velocity.y = JUMP_POWER;
		jumpCount = 0;
	}


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
	//�n�ʂɂ��Ȃ��A1�t���[���O�ɒn�ʂɂ���Ȃ�
	//velocity.y��ς��A�ɂ��ăX�e�[�g��Jump�ɂ���
	if (fall->FallStart(velocity))
		state->SetNextState("Jump");
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
		//���W����X���Ƃ����߂�
		inputAngle = atan2f(static_cast<float>(-inputRight), static_cast<float>(inputDown));
	}
}

bool Player::Move(float speed)
{
	//�����x
	static const float ACCELERATION_SPEED = -0.5f;
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
	//����
	moveSpeed += DECELERATION_SPEED;

	//0�ɂ���
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