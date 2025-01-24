#include "Metall.h"
#include "BulletManager.h"
#include "EffectManager.h"
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

	//画像
	static const float IMG_TOP = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT = COL_LEFT;
	static const float IMG_RIGHT = COL_RIGHT;

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

Metall::Metall(BaseScene* baseScene, BulletManager* bulletManager, EffectManager* _effectManager, BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{ baseScene,bulletManager,_effectManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, imageH{ -1 }
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

	animation->AddAnimCount(1.f);

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
	if(isInvincible)
	{ 
		DrawBox
		(
			drawpos.x - _camDif.x + IMG_LEFT,
			drawpos.y - _camDif.y + IMG_TOP,
			drawpos.x - _camDif.x + IMG_RIGHT,
			drawpos.y - _camDif.y + IMG_UNDER,
			GetColor(100, 100, 255),
			false
		);
	}
	else
	{
		DrawBox
		(
			drawpos.x - _camDif.x + IMG_LEFT,
			drawpos.y - _camDif.y + IMG_TOP,
			drawpos.x - _camDif.x + IMG_RIGHT,
			drawpos.y - _camDif.y + IMG_UNDER,
			GetColor(255, 255, 255),
			false
		);
	}
#endif  _DEBUG
}

void Metall::UpdateIdle()
{
	//アニメーションの設定
	{
		int angImage = animation->GetAngleImage(0, 1, moveAngle);
		imageH = Image::GetInstance()->GetMetallIdleH(angImage);
	}

	//待機を終了するフレーム
	static const int MAX_IDLE_FRAME = 120;
	if (moveCount >= MAX_IDLE_FRAME)
	{
		//プレイヤーが特定の距離以下かつ、弾がBULLET_NUM個あるか
		if (IsNearDistance() && IsCanShot())
		{
			AttackStart();
		}
	}
}

void Metall::UpdateAttack()
{
	//球を打つまでのフレーム
	static const int SHOT_FRAME = 30;

	//アニメーションの設定
	{
		static const int ANIM = SHOT_FRAME+2;//ループしないように値を少し増やす
		int angImage = animation->GetAngleImage(0, 2, moveAngle);
		int animNum = animation->GetAnimation(ANIM, ANIM / 2);
		imageH = Image::GetInstance()->GetMetallUpH(animNum + angImage);
	}

	if (moveCount == SHOT_FRAME)
	{
		Attack();
		RunStart();
	}

	DamageStart();
}

void Metall::UpdateRun()
{
	//アニメーションの設定
	{
		static const int ANIM = 30;
		int angImage = animation->GetAngleImage(0, 2, moveAngle);
		int animNum = animation->GetAnimation(ANIM, ANIM / 2);
		imageH = Image::GetInstance()->GetMetallRunH(animNum + angImage);
	}
	//移動を終了するフレーム
	static const int MAX_RUN_FRAME = 90;

	if (moveCount >= MAX_RUN_FRAME)
	{
		//移動を停止する
		velocity.x = 0;
		IdleStart();
	}
	//地面に乗ってなければFallに行く
	if (!fall->GetIsOnGround())FallStart();
	DamageStart();

}

void Metall::UpdateFall()
{
	//地面につくまで横移動ができないようにする
	if (fall->GetIsOnGround())
	{
		velocity.x = moveAngle * RUN_SPEED;

		state->SetNextState("Run");
	}
	DamageStart();

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
		RunStart();
	}
	DamageStart();
}

void Metall::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);
	if (deathCount == Life::DEATH_EFFECT_FRAME)
	{
		effectManager->SetState(position, F_Vec2{ 0,0 });
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DISAPPEAR);
	}
}

void Metall::IdleStart()
{
	//無敵状態を開始
	isInvincible = true;
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;
	
	state->SetNextState("Idle");
}

void Metall::AttackStart()
{
	//無敵状態を解除
	isInvincible = false;
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;

	//moveAngleをセット
	SetMoveAngle();
	//アニメーションを初期化
	animation->SetAnimCount(0);
	state->SetNextState("Attack");
}

void Metall::RunStart()
{
	//ステートを移行するからmoveCountを初期化
	moveCount = 0;

	//moveAngleをセット
	SetMoveAngle();

	velocity.x = moveAngle * RUN_SPEED;

	state->SetNextState("Run");
}

void Metall::FallStart()
{
	//移動中だからステートを移行してもmoveCountは初期化しない
	//moveCount = 0;


	velocity.x = 0;
	state->SetNextState("Fall");
}

void Metall::DamageStart()
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

bool Metall::IsNearDistance()
{
	return VSize(plBase->GetPosition() - position) < START_ATTACK_SIZE;
}

bool Metall::IsCanShot()
{
	return bulletManager->GetCanShot(BulletManager::BULLET_KND::BALL, BULLET_NUM);
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

void Metall::SetMoveAngle()
{
	//プレイヤー座標を取得
	F_Vec2 plPos = plBase->GetPosition();
	//自身より右か左か　左なら-1
	moveAngle = position.x - plPos.x > 0 ? -1 : 1;
}
