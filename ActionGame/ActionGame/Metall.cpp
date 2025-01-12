#include "Metall.h"
#include "BulletManager.h"
#include "BallBullet.h"

namespace
{
	//体力
	static const int START_HP = 1;

	//スピード
	static const float RUN_SPEED = 3.f;

	//一度に撃つ弾の数
	static const int BULLET_NUM = 3;

	//コリジョン
	static const int COL_TOP = -BLOCK_SIZE / 2;
	static const int COL_UNDER = BLOCK_SIZE / 2;
	static const int COL_LEFT = -BLOCK_SIZE / 2;
	static const int COL_RIGHT = BLOCK_SIZE / 2;

	//ステート
	static const int STATE_IDLE = 0;
	static const int STATE_ATTACK = 1;
	static const int STATE_RUN = 2;
	static const int STATE_FALL = 3;
	static const int STATE_DAMAGE = 4;
	static const int STATE_DEATH = 5;

	//パワー
	static const int POWER_BODY = 2;

	//探知範囲
	static const float START_ATTACK_SIZE = 250.f;
}

Metall::Metall(BaseScene* baseScene, BulletManager* bulletManager, BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{ baseScene,bulletManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
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

	//moveCountで動きを管理する
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
	//待機を終了するフレーム
	static const int MAX_IDLE_FRAME = 120;
	if (moveCount >= MAX_IDLE_FRAME)
	{
		//プレイヤーが特定の距離以下かつ、弾がBULLET_NUM個あるか
		if (F_Vec2::VSize(plBase->GetPosition() - position) < START_ATTACK_SIZE &&
			bulletManager->GetCanShot(BulletManager::BULLET_KND::BALL, BULLET_NUM))StartAttack();

	}
}

void Metall::UpdateAttack()
{
	//攻撃を終了するフレーム
	static const int MAX_SHOT_FRAME = 60;
	//弾を撃つまでの遅延
	static const int SHOT_DELAY = 4;

	if (moveCount >= MAX_SHOT_FRAME)
	{
		StartRun();
	}

	if (moveCount == SHOT_DELAY)
	{
		Attack();
	}

	StartDamage();
}

void Metall::UpdateRun()
{
	//移動を終了するフレーム
	static const int MAX_RUN_FRAME = 90;

	if (moveCount >= MAX_RUN_FRAME)
	{
		//移動を停止する
		velocity.x = 0;
		StartIdle();
	}
	//地面に乗ってなければFallに行く
	if (!fall->GetIsOnGround())StartFall();
	StartDamage();

}

void Metall::UpdateFall()
{
	//地面につくまで横移動ができないようにする
	if (fall->GetIsOnGround())
	{
		velocity.x = moveAngle * RUN_SPEED;

		state->SetNextState("Run");
	}
	StartDamage();

}

void Metall::UpdateDamage()
{
	static const int DAMAGE_MAX_FRAME = 6;
	damageCount++;
	if (damageCount >= DAMAGE_MAX_FRAME)
	{
		//hpが0以下なら死
		if (life->GetHp() <= 0)
		{
			state->SetNextState("Death");
			return;
		}
		StartRun();
	}
	StartDamage();
}

void Metall::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);

}

void Metall::StartIdle()
{
	//無敵状態を開始
	isInvincible = true;
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;
	
	state->SetNextState("Idle");
}

void Metall::StartAttack()
{
	//無敵状態を解除
	isInvincible = false;
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;

	//プレイヤー座標を取得
	F_Vec2 plPos = plBase->GetPosition();
	//自身より右か左か　左なら-1
	moveAngle = position.x - plPos.x > 0 ? -1 : 1;

	state->SetNextState("Attack");

}

void Metall::StartRun()
{
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;

	//プレイヤー座標を取得
	F_Vec2 plPos = plBase->GetPosition();
	//自身より右か左か　左なら-1
	moveAngle = position.x - plPos.x > 0 ? -1 : 1;

	velocity.x = moveAngle * RUN_SPEED;

	state->SetNextState("Run");
}

void Metall::StartFall()
{
	//移動中だからステートを移行してもmoveCountは初期化しない
	//moveCount = 0;


	velocity.x = 0;
	state->SetNextState("Fall");
}

void Metall::StartDamage()
{
	if (life->GetHp() <= 0)return;
	int bulletDamage = bulletManager->HitCheckChara(this, collisionData);
	if (bulletDamage != 0)
	{
		//ダメージ処理
		life->DecHp(bulletDamage);

		damageCount = 0;

		state->SetNextState("Damage");
	}
}

void Metall::StartDeath()
{
}

void Metall::Attack()
{
	//90度を計算に使うので先に宣言
	static const float HALF_PI = PI / 2;
	//上下に打ち分ける時の角度
	static const float SIDE_PI = PI / 5;

	F_Vec2 genPos = F_Vec2
	{
		position.x + (collisionData->GetRight() * moveAngle),
		position.y
	};

	F_Vec2 genVec = F_Vec2{ 0,0 };

	//撃つ方向を設定
	float rad = HALF_PI * moveAngle;

	//BULLET_NUM発の弾を撃つ
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (i > 0)
		{
			//最初の一発以外は上下に打ち分ける(std::powf(-1, i)は1と-1で振動させる用)
			rad += std::powf(-1, i) * SIDE_PI * i;
		}
		SetGenVec(genVec, rad);

		bulletManager->SetState(genPos, genVec, BulletManager::BULLET_KND::BALL, BulletManager::BULLET_OWNER::ENEMY); 

	}


}

void Metall::SetGenVec(F_Vec2& genVec, float rad)
{
	//sinfとcosfを入れ替えることで、左右で-+の違いが出る
	genVec.x = sinf(rad);
	genVec.y = cosf(rad);
}
