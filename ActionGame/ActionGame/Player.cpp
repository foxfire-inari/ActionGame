#include "Player.h"
#include "KeyControlle.h"
#include "Camera.h"
#include "BulletManager.h"
#include "EnemyManager.h"

namespace
{
	//HP
	static const int MAX_HP = 100;
	//�W�����v��
	static const float JUMP_POWER = 9.f;

	//�X�s�[�h
	static const float WALK_SPEED = -3.f;
	static const float DECELERATION_SPEED = 0.5f;

	//�R���W����
	static const int COL_TOP = -32;
	static const int COL_UNDER = 32;
	static const int COL_LEFT = -32;
	static const int COL_RIGHT = 32;

	//�X�e�[�g
	static const int STATE_IDLE = 0;
	static const int STATE_RUN = 1;
	static const int STATE_JUMP = 2;
	static const int STATE_ATTACK = 3;
	static const int STATE_DAMAGE = 4;
}

Player::Player(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:Chara{ baseScene,MAX_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,BaseObject::E_TAG::PLAYER }
	, camPos{}
	, jumpCount{ 0 }
	, shotCount{ 0 }
	, inputRight{ 0 }
	, inputDown{ 0 }
	, sideShotAngle{ 1 }//�v���C���[�̍ŏ��̌����ɏ�����
	, allShotAngle{ PI / 2 }
	, moveSpeed{ 0 }
	, moveAngle{ 0 }
	, isInvincible{ false }
	, isGameOver{ false }

{
	//���g��o�^
	GetBaseScene()->SetOneObjectList(this);

	F_Vec2 pos = {};

	//���W���Z�b�g�ς݂�
	bool isSet = false;
	//�ǂݍ��񂾃f�[�^�ō��W���Z�b�g����
	int knd = 0;
	for (int y = 0; y < _info.size(); y++)
	{
		for (int x = 0; x < _info.at(y).size(); x++)
		{
			knd = std::stoi(_info.at(y).at(x));

			if (knd == BaseManager::E_CSV_KND::CSV_PLAYER)
			{
				assert(!isSet);//�����Ŏ~�܂����ꍇ��Csv�ɂQ��2���ȏ゠��
				pos = { static_cast<float>(x * 64),static_cast<float>(y * 64) };
				SetPosition(pos);
				isSet = true;
				continue;
			}
		}
	}


	oldPos = position;

	//�J������o�^
	camera = GetBaseScene()->GetOneObjectPtr<Camera>(BaseObject::E_TAG::CAMERA);
	assert(camera != nullptr);
	camPos = position;

	//���̃V�[���̃}�l�[�W���[�擾
	GetNowSceneManager();

	state->SetAllStateMember("Idle");
	state->SetAllStateMember("Run");
	state->SetAllStateMember("Jump");
	state->SetAllStateMember("Attack");
	state->SetAllStateMember("Damage");
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

	Invincible();

	switch (state->GetNowState())
	{
	case STATE_IDLE:			UpdateIdle();			break;

	case STATE_RUN:				UpdateRun();			break;

	case STATE_JUMP:			UpdateJump();			break;

	case STATE_ATTACK:			UpdateAttack();			break;

	case STATE_DAMAGE:			UpdateDamage();			break;
	}

	positionSetter->UpdatePos(this,collisionData, collisionManager, fall);

	SetCameraTarget();
}

void Player::Draw(F_Vec2 _camDif)
{
	//���G�Ȃ�_��
	if (isInvincible && damageCount % 10 <= 3)
		return;


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

void Player::SetCameraTarget()
{
	F_Vec2 camPos = position;

	camPos.x = max(camPos.x, camera->GetMinPosX());
	camPos.x = min(camPos.x, camera->GetMaxPosX());
	camPos.y = max(camPos.y, camera->GetMinPosY());
	camPos.y = min(camPos.y, camera->GetMaxPosY());

	camera->SetTarget(camPos);


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
	shotCount++;

	//�U�����I������t���[��
	static const int MAX_SHOT_FRAME = 12;

	if (shotCount >= MAX_SHOT_FRAME)
	{
		//shotCount�̓��Z�b�g
		shotCount = 0;

		//�U���{�^����������Ă�����X�e�[�g�͍U���̂܂�
		if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::ATTACK) != 0)return;

		//�����󒆂ɂ�����X�e�[�g�̓W�����v
		if (!fall->GetIsOnGround())
		{
			state->SetNextState("Jump");
			return;
		}

		//velocity��0����Ȃ��Ȃ�X�e�[�g�̓���
		if (static_cast<int>(velocity.x) != 0)
		{
			StartRun();
			return;
		}
		//velocity��0�Ȃ�X�e�[�g�̓A�C�h��
		else
		{
			state->SetNextState("Idle");
			return;
		}
	}

	//���͕����̃Z�b�g
	SetInputAngle();

	//�U������������悤�ɂ��A�����L�[�̓��͂����邩���擾
	bool isRun = Move(WALK_SPEED);
	//���͂��Ȃ���Ύ~�܂�
	if (!isRun)
		MoveDeceletation();

	if (shotCount == 1)
	{
		Attack();
	}

	JumpStart();
	FallStart();
}

void Player::UpdateDamage()
{
	static const int MAX_DAMAGE_FRAME = 60;

	//�n�ʂɂ���MAX_DAMAGE_FRAME��������X�e�[�g��Idle�ɂ���
	if (damageCount >= MAX_DAMAGE_FRAME)
	{
		//hp��0�ȉ��Ȃ玀
		if (life->GetHp() <= 0)
		{
			DeathStart();
			return;
		}
		//����ȊO�Ȃ�Idle��
		state->SetNextState("Idle");
		//Idle�ڍs���΂Ȃ��悤jumpCount��0�ɂ���
		jumpCount = 0;
	}
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
	static const float DAMAGE_VEL_SIZE = 1.f;

	//���G�Ȃ画������Ȃ�
	if (isInvincible)return;

	//�Q�Ƃœn���Ĕ�΂�������Ⴄ
	int vel;

	int damage = enemyManager->CheckPlayerHit(collisionData, vel);

	//�������Ă��Ȃ�������return
	if (damage <= 0)return;

	//�ړ����x��0�ɂ���
	moveSpeed = 0;

	//�󂯎����������DAMAGE_VEL_SIZE�{�ɂ���
	vel *= DAMAGE_VEL_SIZE;

	//�_���[�W���󂯂�
	life->DecHp(damage);

	velocity = { static_cast<float>(vel),0 };
	damageCount = 0;
	jumpCount = 0;
	isInvincible = true;
	state->SetNextState("Damage");

}

void Player::DeathStart()
{
	isInvincible = false;
	damageCount = 0;
	life->SetIsDeath(true);
	state->SetNextState("Death");

}

void Player::Invincible()
{
	static const int MAX_INVINCIBLE_FRAME = 120;

	if (isInvincible)
	{
		damageCount++;
		if (damageCount > MAX_INVINCIBLE_FRAME)
			isInvincible = false;
	}
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
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::ATTACK) != 0)
	{
		state->SetNextState("Attack");
		shotCount = 0;
	}
}

void Player::SetInputAngle()
{
	inputRight = 0, inputDown = 0;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::UP))		inputDown = -1;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::DOWN))		inputDown = 1;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::LEFT))		inputRight = -1;
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::RIGHT))	inputRight = 1;

	//allShotAngle���X�V
	if (inputRight != 0 || inputDown != 0)
	{
		//���W����X���Ƃ����߂�
		allShotAngle = atan2f(static_cast<float>(inputRight), static_cast<float>(inputDown));
	}
	else
	{
		allShotAngle = allShotAngle > 0 ? PI / 2 : -PI / 2;
	}

	//sideShotAngle���X�V
	sideShotAngle = inputRight != 0 ? static_cast<float>(inputRight) : sideShotAngle;


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
	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * inputRight),
		position.y
	};

	F_Vec2 genVec = F_Vec2
	{
		static_cast<float>(sideShotAngle),
		//NormalBullet�͍��E�ɂ݈̂ړ�����̂�Y��0�ɂ��Ă���
		0//cosf(inputAngle)
	};

	bulletManager->SetState(genPos, genVec);
}

void Player::SetStatus()
{
}

void Player::GetNowSceneManager()
{
	bulletManager = GetBaseScene()->GetManagerPtr<BulletManager>(BaseManager::E_MANAGER_TAG::BULLET);
	assert(bulletManager != nullptr);

	enemyManager = GetBaseScene()->GetManagerPtr<EnemyManager>(BaseManager::E_MANAGER_TAG::ENEMY);
	assert(enemyManager != nullptr);

}