#include "Player.h"
#include "Image.h"
#include "KeyControlle.h"
#include "Camera.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "EnemyManager.h"
#include "WarpManager.h"
#include "Waveout.h"

namespace
{
	//HP
	static const int MAX_HP = 28;

	//�W�����v��
	static const float JUMP_POWER = 8.f;

	//�X�s�[�h
	static const float WALK_SPEED = -2.f;
	static const float DECELERATION_SPEED = 0.5f;

	//�R���W����
	static const float COL_TOP		= -BLOCK_SIZE;
	static const float COL_UNDER	=  BLOCK_SIZE / 2;
	static const float COL_LEFT		= -BLOCK_SIZE / 2;
	static const float COL_RIGHT	=  BLOCK_SIZE / 2;

	//�摜
	static const float IMG_TOP		= COL_TOP;
	static const float IMG_UNDER	= COL_UNDER;
	static const float IMG_LEFT		= -32;
	static const float IMG_RIGHT	= 32;


	//�X�e�[�g
	static const int STATE_IDLE = 0;
	static const int STATE_RUN = 1;
	static const int STATE_JUMP = 2;
	static const int STATE_ATTACK = 3;
	static const int STATE_DAMAGE = 4;
	static const int STATE_DEATH = 5;
	static const int STATE_NEXT_MAP_WAIT = 6;
	
}

Player::Player(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:Chara{ baseScene,MAX_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,BaseObject::E_TAG::PLAYER }
	, camPos{}
	, jumpCount{ 0 }
	, shotCount{ 0 }
	, damageCount{ 0 }
	, deathCount{ 0 }
	, inputRight{ 0 }
	, inputDown{ 0 }
	, imageH{ -1 }
	, sideShotAngle{ 1 }//�v���C���[�̍ŏ��̌����ɏ�����
	, allShotAngle{ PI / 2 }
	, moveSpeed{ 0 }
	, moveAngle{ 0 }
	, isInvincible{ false }
	, isGameOver{ false }
	, isBossButtle{ false }

{
	//���g��o�^
	GetBaseScene()->SetOneObjectList(this);

	F_Vec2 pos = {};

	//���W���Z�b�g�ς݂�
	bool isSet = false;
	//�ǂݍ��񂾃f�[�^�Ńu���b�N�𐶐�����
	int knd = 0;
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));

		if (knd == BaseManager::E_CSV_KND::CSV_PLAYER)
		{
			assert(!isSet);//�����Ŏ~�܂����ꍇ��Csv��3��2���ȏ゠��
			pos.x = std::stoi(_info.at(i).at(1)) * BLOCK_SIZE;
			pos.y = std::stoi(_info.at(i).at(2)) * BLOCK_SIZE;

			SetPosition(pos);
			isSet = true;
			continue;
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
	state->SetAllStateMember("Death");
	state->SetAllStateMember("NextMapWait");
}

Player::~Player()
{
	if (waveout != nullptr)delete waveout;
}

void Player::Start()
{
	//�{�X�킩���擾����
	isBossButtle = enemyManager->IsBossButtle();
}

void Player::Update()
{
	oldPos = position;
	animation->AddAnimCount(1);
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

	case STATE_DEATH:			UpdateDeath();			break;

	case STATE_NEXT_MAP_WAIT:	UpdateNextMapWait();	break;

	default:					assert(false);			break;
	}

	positionSetter->UpdatePos(this,collisionData, collisionManager, fall);

	SetCameraTarget();
}

void Player::Draw(F_Vec2 _camDif)
{
	//���G�Ȃ�_��
	if (isInvincible && damageCount % 10 <= 3)
		return;

	//���񂾂�f���Ȃ�
	if (deathCount > Life::DEATH_FRAME)return;

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

	//�X�e�[�^�X�̉���
	DrawFormatString(50, 50, GetColor(255, 255, 255),
		"velocity:%f,%f", GetVelocity().x, GetVelocity().y);
#endif  _DEBUG

}

void Player::DrawWaveout()
{
	if (waveout == nullptr)return;

	//�Ó]�`��
	waveout->Draw();
}

void Player::DrawUI()
{
}

void Player::DrawData()
{
}

std::string Player::GoNextMap()
{
	//���̃}�b�v�̖��O���擾����
	std::string nextMapName = warpManager->GetNextMapName(this, collisionData);

	if (nextMapName != "")
	{
		state->SetNextState("NextMapWait");
	}

	//���̃}�b�v����Ԃ�
	return nextMapName;
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

	//�A�j���[�V�����̐ݒ�
	{
		int angImage = animation->GetAngleImage(0,1,moveAngle);
		imageH = Image::GetInstance()->GetPlayerIdleH(angImage);
	}

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

	//�A�j���[�V�����̐ݒ�
	{
		static const int ANIM = 48;
		int angImage = animation->GetAngleImage(0, 4, moveAngle);
		int animNum = animation->GetAnimation(ANIM, ANIM / 4);
		imageH = Image::GetInstance()->GetPlayerWalkH(animNum + angImage);
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

	static const float FAST_FALL = -5.f;

	bool isMove = Move(WALK_SPEED);
	if (!isMove)MoveDeceletation();

	//���n
	if (velocity.y < 0 && fall->GetIsOnGround())
	{
		if (moveSpeed != 0)	StartRun();
		else state->SetNextState("Idle");
	}

	//�A�j���[�V�����̐ݒ�
	if (velocity.y > FAST_FALL && !fall->GetIsOnGround())
	{
		int angImage = animation->GetAngleImage(1, 4, moveAngle);
		imageH = Image::GetInstance()->GetPlayerWalkH(angImage);
	}
	else
	{
		int angImage = animation->GetAngleImage(0, 1, moveAngle);
		imageH = Image::GetInstance()->GetPlayerFallH(angImage);
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
	//�e�����܂ł̒x��
	static const int SHOT_DELAY = 1;

	if (shotCount >= MAX_SHOT_FRAME)
	{
		//shotCount�̓��Z�b�g
		shotCount = 0;


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

	if (shotCount == SHOT_DELAY)
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
		//����ȊO�Ȃ�Idle��
		state->SetNextState("Idle");
		//Idle�ڍs���΂Ȃ��悤jumpCount��0�ɂ���
		jumpCount = 0;
	}
	//�A�j���[�V�����̐ݒ�
	{
		int angImage = animation->GetAngleImage(0, 1, moveAngle);
		imageH = Image::GetInstance()->GetPlayerDamageH(angImage);
	}
}

void Player::UpdateDeath()
{
	static const int GAME_OVER_FRAME = Life::DEATH_EFFECT_FRAME + 120;
	static const float WAIT_TIME = 1.f;
	static const float BLACKOUT_SPEED = 4.f;

	deathCount++;

	//���S�J�E���g��DEATH_EFFECT_FRAME�ɂȂ�����G�t�F�N�g����
	if (deathCount == Life::DEATH_EFFECT_FRAME)
	{
		effectManager->SetDeffusion(position);
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::GAME_OVER);
	}

	//���S�J�E���g��GAME_OVER_FRAME�ɂȂ������ʂ𖄂ߎn�߂�
	if (deathCount >= GAME_OVER_FRAME && waveout == nullptr)
	{
		waveout = new Waveout{ WAIT_TIME,BLACKOUT_SPEED };
	}

	//��ʂ����܂�����isGameOver��true�ɂ���
	if (waveout != nullptr)
	{
		waveout->Update();

		if (waveout->GetIsWaveFinish())
		{
			isGameOver = true;
		}
	}

	//�ړ��x�N�g�����d�͈ȊO������
	velocity = F_Vec2{ 0, velocity.y };
}

void Player::UpdateNextMapWait()
{
	//�ړ��x�N�g�����d�͈ȊO������
	velocity = F_Vec2{ 0,velocity.y };

	//�A�j���[�V�����̐ݒ�
	{
		int angImage = animation->GetAngleImage(0, 1, moveAngle);
		imageH = Image::GetInstance()->GetPlayerIdleH(angImage);
	}
}

void Player::JumpStart()
{
	static const int MAX_LITTLE_JUMP_FRAME = 6;

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

	//�_���[�W���󂯂������󂯎��(�G�{��)
	int damage = enemyManager->CheckPlayerHit(collisionData);

	//�_���[�W���󂯂������󂯎��(�G�̒e)
	int bulletDamage = bulletManager->HitCheckChara(this, collisionData);

	if (bulletDamage > 0) //�_���[�W���󂯂Ă�����㏑��
	{
		damage = bulletDamage;
	}

	//�������Ă��Ȃ�������return
	if (damage <= 0)return;

	//�ړ����x��0�ɂ���
	moveSpeed = 0;

	//�󂯎����������DAMAGE_VEL_SIZE�{�ɂ���
	vel = moveAngle * DAMAGE_VEL_SIZE;

	//�_���[�W���󂯂�
	life->DecHp(damage);

	//hp��0�ȉ��Ȃ玀
	if (life->GetHp() <= 0)
	{
		DeathStart();
		return;
	}
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
		//moveAngle = 0;
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

	bulletManager->SetState(genPos, genVec,
		BulletManager::BULLET_KND::NORMAL ,BulletManager::BULLET_OWNER::PLAYER);
}

void Player::SetStatus()
{
}

void Player::GetNowSceneManager()
{
	bulletManager = GetBaseScene()->GetManagerPtr<BulletManager>(BaseManager::E_MANAGER_TAG::BULLET);
	assert(bulletManager != nullptr);

	effectManager = GetBaseScene()->GetManagerPtr<EffectManager>(BaseManager::E_MANAGER_TAG::EFFECT);
	assert(effectManager != nullptr);

	enemyManager = GetBaseScene()->GetManagerPtr<EnemyManager>(BaseManager::E_MANAGER_TAG::ENEMY);
	assert(enemyManager != nullptr);

	warpManager = GetBaseScene()->GetManagerPtr<WarpManager>(BaseManager::E_MANAGER_TAG::WARP);
	assert(warpManager != nullptr);
}