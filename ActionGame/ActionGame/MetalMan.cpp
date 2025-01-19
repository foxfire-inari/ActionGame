#include "MetalMan.h"
#include "BulletManager.h"
#include "EffectManager.h"
#include "KeyControlle.h"

namespace
{
	//HP
	static const int START_HP = 28;

	//ジャンプ力
	static const float JUMP_LARGE	= 10.f;
	static const float JUMP_MEDIUM	= 8.f;
	static const float JUMP_SMALL	= 5.f;
	static const float JUMP_OVER	= 12.f;

	//ジャンプごとの攻撃回数
	static const int ATTACK_LARGE	= 3;
	static const int ATTACK_MEDIUM	= 2;
	static const int ATTACK_SMALL	= 1;
	static const int ATTACK_OVER	= 1;

	//スピード
	static const float WALK_SPEED = -3.f;

	//コリジョン
	static const float COL_TOP = -BLOCK_SIZE;
	static const float COL_UNDER = BLOCK_SIZE / 2;
	static const float COL_LEFT = -BLOCK_SIZE / 2;
	static const float COL_RIGHT = BLOCK_SIZE / 2;

	//画像
	static const float IMG_TOP = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT = -32;
	static const float IMG_RIGHT = 32;

	//ステート
	static const int STATE_IDLE = 0;
	static const int STATE_JUMP = 1;
	static const int STATE_ATTACK = 2;
	static const int STATE_DEATH = 3;

	//パワー
	static const int POWER_BODY = 7;

	//探知範囲
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

	//moveCountで動きを管理する
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

	///デバッグ用
	//判定の可視化
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
	//三秒間待つ
	static const int MOVE_WAIT = FPS * 3;

	//探知範囲内に入ったら逆側に行き始める
	if (IsNearDistance())
	{
		moveKnd = E_MOVE_KND::OVER;
		JumpStart();
	}
	else if (GetAttackKey() || moveCount >= MOVE_WAIT)//プレイヤーが攻撃するかMOVE_WAITを越えたら攻撃する
	{
		//そこまで正確なランダムを作る必要もないので　std::rand()
		moveKnd = std::rand() % E_MOVE_KND::JUMP_RAND_MAX;
		JumpStart();
	}

	DamageStart();

}

void MetalMan::UpdateJump()
{
	//落下し始めたら攻撃を開始する
	if (velocity.y < 0.f)
	{
		AttackStart();
	}

	DamageStart();

}

void MetalMan::UpdateAttack()
{
	//攻撃一回分の全体フレーム
	static const int MAX_SHOT_FRAME = 30;
	//弾を撃つまでの遅延
	static const int SHOT_DELAY = 10;

	//着陸したらIdleに変更
	if (fall->GetIsOnGround())
	{
		//横移動を停止する
		velocity.x = 0;
		IdleStart();
	}

	//SHOT_DELAYで弾を撃つ
	if (moveCount == SHOT_DELAY)
	{
		velocity.y = 0;
		attackCount++;
		Attack();
	}

	//攻撃が一回終わったら撃つ回数を確認する
	if (moveCount == MAX_SHOT_FRAME)
	{
		if (attackCount < attackNum)
		{
			//攻撃するために初期化
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
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;
	//moveAngleをセット
	SetMoveAngle();

	state->SetNextState("Idle");
}

void MetalMan::JumpStart()
{
	switch (moveKnd)
	{
	case E_MOVE_KND::LARGE:		velocity.y = JUMP_LARGE;	break;	//大ジャンプ
	case E_MOVE_KND::MEDIUM:	velocity.y = JUMP_MEDIUM;	break;	//中ジャンプ
	case E_MOVE_KND::SMALL:		velocity.y = JUMP_SMALL;	break;	//小ジャンプ

	case E_MOVE_KND::OVER:		//逆サイドに行くジャンプ
		velocity.x = WALK_SPEED * -moveAngle;
		velocity.y = JUMP_OVER;		
		break;

	default:					assert(false);				break;
	}

	state->SetNextState("Jump");

}

void MetalMan::AttackStart()
{
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;

	//attackCountも初期化
	attackCount = 0;

	switch (moveKnd)
	{
	case E_MOVE_KND::LARGE:		attackNum = ATTACK_LARGE;	break;	//大ジャンプ
	case E_MOVE_KND::MEDIUM:	attackNum = ATTACK_MEDIUM;	break;	//中ジャンプ
	case E_MOVE_KND::SMALL:		attackNum = ATTACK_SMALL;	break;	//小ジャンプ
	case E_MOVE_KND::OVER:		attackNum = ATTACK_OVER;	break;	//逆サイドに行くジャンプ

	default:					assert(false);				break;
	}

	state->SetNextState("Attack");

}

void MetalMan::DamageStart()
{
	//無敵なら判定をしない
	if (isInvincible)return;

	int bulletDamage = bulletManager->HitCheckChara(this, collisionData);
	if (bulletDamage != 0)
	{
		//ダメージ処理
		life->DecHp(bulletDamage);
		//無敵になる
		isInvincible = true;
		damageCount = 0;

		//hpが0以下なら死
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
	//moveAngleをセット
	SetMoveAngle();

	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * moveAngle),
		position.y
	};

	F_Vec2 genVec = F_Vec2{ 0,0 };

	//プレイヤー座標を取得
	F_Vec2 plPos = plBase->GetPosition();
	//相対角度を計算
	shotAngle = atan2f(plPos.y - position.y, plPos.x - position.x);
	//撃つ方向を計算
	SetGenVec(genVec, shotAngle);
	
	//弾を発射
	bulletManager->SetState(genPos, genVec, BulletManager::BULLET_KND::METAL, BulletManager::BULLET_OWNER::ENEMY);

}

void MetalMan::SetGenVec(F_Vec2& genVec, float rad)
{
	//sinfとcosfを入れ替えることで、左右で-+の違いが出る
	genVec.x = cosf(rad);
	genVec.y = sinf(rad);
}

void MetalMan::SetMoveAngle()
{
	//プレイヤー座標を取得
	F_Vec2 plPos = plBase->GetPosition();
	//自身より右か左か　左なら-1
	moveAngle = position.x - plPos.x > 0 ? -1 : 1;
}

bool MetalMan::GetAttackKey()
{
	return KeyControlle::GetInstance()->GetNowPressing(E_KEY::ATTACK);
}
