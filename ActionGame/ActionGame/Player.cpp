#include "Player.h"
#include "KeyControlle.h"
#include "Camera.h"
#include "BulletManager.h"
#include "EnemyManager.h"

namespace
{
	//HP
	static const int MAX_HP = 100;
	//ジャンプ力
	static const float JUMP_POWER = 9.f;

	//スピード
	static const float WALK_SPEED = -3.f;
	static const float DECELERATION_SPEED = 0.5f;

	//コリジョン
	static const int COL_TOP = -32;
	static const int COL_UNDER = 32;
	static const int COL_LEFT = -32;
	static const int COL_RIGHT = 32;

	//ステート
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
	, sideShotAngle{ 1 }//プレイヤーの最初の向きに準ずる
	, allShotAngle{ PI / 2 }
	, moveSpeed{ 0 }
	, moveAngle{ 0 }
	, isInvincible{ false }
	, isGameOver{ false }

{
	//自身を登録
	GetBaseScene()->SetOneObjectList(this);

	F_Vec2 pos = {};

	//座標をセット済みか
	bool isSet = false;
	//読み込んだデータで座標をセットする
	int knd = 0;
	for (int y = 0; y < _info.size(); y++)
	{
		for (int x = 0; x < _info.at(y).size(); x++)
		{
			knd = std::stoi(_info.at(y).at(x));

			if (knd == BaseManager::E_CSV_KND::CSV_PLAYER)
			{
				assert(!isSet);//ここで止まった場合はCsvに２が2こ以上ある
				pos = { static_cast<float>(x * 64),static_cast<float>(y * 64) };
				SetPosition(pos);
				isSet = true;
				continue;
			}
		}
	}


	oldPos = position;

	//カメラを登録
	camera = GetBaseScene()->GetOneObjectPtr<Camera>(BaseObject::E_TAG::CAMERA);
	assert(camera != nullptr);
	camPos = position;

	//今のシーンのマネージャー取得
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
	//無敵なら点滅
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

	//着地
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

	//攻撃を終了するフレーム
	static const int MAX_SHOT_FRAME = 12;

	if (shotCount >= MAX_SHOT_FRAME)
	{
		//shotCountはリセット
		shotCount = 0;

		//攻撃ボタンが押されていたらステートは攻撃のまま
		if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::ATTACK) != 0)return;

		//もし空中にいたらステートはジャンプ
		if (!fall->GetIsOnGround())
		{
			state->SetNextState("Jump");
			return;
		}

		//velocityが0じゃないならステートはラン
		if (static_cast<int>(velocity.x) != 0)
		{
			StartRun();
			return;
		}
		//velocityが0ならステートはアイドル
		else
		{
			state->SetNextState("Idle");
			return;
		}
	}

	//入力方向のセット
	SetInputAngle();

	//攻撃中も動けるようにし、方向キーの入力があるかを取得
	bool isRun = Move(WALK_SPEED);
	//入力がなければ止まる
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

	//地面につくかMAX_DAMAGE_FRAMEたったらステートをIdleにする
	if (damageCount >= MAX_DAMAGE_FRAME)
	{
		//hpが0以下なら死
		if (life->GetHp() <= 0)
		{
			DeathStart();
			return;
		}
		//それ以外ならIdleへ
		state->SetNextState("Idle");
		//Idle移行後飛ばないようjumpCountを0にする
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

	//長押しでジャンプしないようにする
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP) > MAX_LITTLE_JUMP_FRAME + 1)return;

	//ジャンプボタンを押していて地面にいるならジャンプカウントをボタンを押している分フレームにする
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP) != 0 && fall->GetIsOnGround())
		jumpCount = KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP);

	//小ジャンプ
	if (KeyControlle::GetInstance()->GetPressingFrame(E_KEY::JUMP) == 0 &&
		jumpCount != 0)
	{
		//ジャンプボタンをMAX_LITTLE_JUMP_FRAME以内に離したら小ジャンプ
		if (jumpCount <= MAX_LITTLE_JUMP_FRAME)
		{
			state->SetNextState("Jump");
			velocity.y = JUMP_POWER / 1.5f;
			jumpCount = 0;
		}
	}
	//ジャンプボタンをMAX_LITTLE_JUMP_FRAME以上押していたら大ジャンプ
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

	//無敵なら判定をしない
	if (isInvincible)return;

	//参照で渡して飛ばす方向を貰う
	int vel;

	int damage = enemyManager->CheckPlayerHit(collisionData, vel);

	//当たっていなかったらreturn
	if (damage <= 0)return;

	//移動速度を0にする
	moveSpeed = 0;

	//受け取った方向をDAMAGE_VEL_SIZE倍にする
	vel *= DAMAGE_VEL_SIZE;

	//ダメージを受ける
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
	//地面にいなく、1フレーム前に地面にいるなら
	//velocity.yを変え、にしてステートをJumpにする
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

	//allShotAngleを更新
	if (inputRight != 0 || inputDown != 0)
	{
		//座標から傾きθを求める
		allShotAngle = atan2f(static_cast<float>(inputRight), static_cast<float>(inputDown));
	}
	else
	{
		allShotAngle = allShotAngle > 0 ? PI / 2 : -PI / 2;
	}

	//sideShotAngleを更新
	sideShotAngle = inputRight != 0 ? static_cast<float>(inputRight) : sideShotAngle;


}

bool Player::Move(float speed)
{
	//加速度
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
	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * inputRight),
		position.y
	};

	F_Vec2 genVec = F_Vec2
	{
		static_cast<float>(sideShotAngle),
		//NormalBulletは左右にのみ移動するのでYは0にしておく
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