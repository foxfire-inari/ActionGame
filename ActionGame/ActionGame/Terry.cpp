#include "Terry.h"
#include"Image.h"
#include "BulletManager.h"
#include"EffectManager.h"

namespace
{
	//体力
	static const int START_HP = 1;

	//移動速度
	static const float MOVE_SPEED = 0.5f;

	//コリジョン
	static const int COL_TOP = -BLOCK_SIZE / 2;
	static const int COL_UNDER = BLOCK_SIZE / 2;
	static const int COL_LEFT = -BLOCK_SIZE / 2;
	static const int COL_RIGHT = BLOCK_SIZE / 2;

	//画像
	static const float IMG_TOP   = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT  = COL_LEFT;
	static const float IMG_RIGHT = COL_RIGHT;

	//ステート
	static const int STATE_RUN = 0;
	static const int STATE_DAMAGE = 1;
	static const int STATE_DEATH = 2;

	//パワー
	static const int POWER_BODY = 2;

	//移動し続けるフレーム数
	static const int MOVE_FRAME = FPS;

	//アニメーションの合計フレーム数
	static const int ANIM = 48;
	//一枚ごとのフレーム数
	static const int ONE_FRAME = ANIM / 4;

	//進行方向
	static const float LEFT_ANGLE = PI;
	static const float RIGHT_ANGLE = 0.f;
	static const float DOWN_ANGLE = PI / 2;
	static const float UP_ANGLE = -PI / 2;

	static const int DAMAGE_MAX_FRAME = 6;

}

Terry::Terry(BaseScene* baseScene, BulletManager* bulletManager, EffectManager* _effectManager,
	BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{baseScene,bulletManager,_effectManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, moveAngle{ 0 }
	, damageCount{ 0 }
	, moveCount{ MOVE_FRAME }//画面に映った瞬間に動いてほしい
{
	bodyPower = POWER_BODY;

	state->SetAllStateMember("Run");
	state->SetAllStateMember("Damage");
	state->SetAllStateMember("Death");
}

Terry::~Terry()
{
}

void Terry::Update()
{
	if (life->GetIsDeath())return;

	//浮いているため重力を無視する
	//gravity->AddGravity(velocity.y);

	animation->AddAnimCount(0.5f);

	state->ChangeState();

	switch (state->GetNowState())
	{
	case STATE_RUN:		UpdateRun();		break;
	case STATE_DAMAGE:	UpdateDamage();		break;
	case STATE_DEATH:	UpdateDeath();		break;

	default:			assert(false);
	}

	positionSetter->UpdateNonInterPos(this);


}

void Terry::Draw(F_Vec2 _camDif)
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
}

void Terry::UpdateRun()
{
	//アニメーションの設定
	{
		int animNum = animation->GetAnimation(ANIM,ONE_FRAME);
		imageH = Image::GetInstance()->GetTerryH(animNum);
	}

	moveCount++;

	//一定時間移動したら移動方向を更新
	if (moveCount >= MOVE_FRAME)
	{
		//プレイヤー座標を取得
		F_Vec2 plPos = plBase->GetPosition();
		//相対角度を計算
		moveAngle = atan2f(plPos.y - position.y, plPos.x - position.x);//Max:3.141593

		//速度に違いが出ないようにベクトルの向きを上下左右の四方向に固定
		if (fabsf(moveAngle) > 3 * PI / 4)
		{
			moveAngle = LEFT_ANGLE;//左
		}
		else if (fabsf(moveAngle) < PI / 4)
		{
			moveAngle = RIGHT_ANGLE;//右
		}
		else if (moveAngle > 0)
		{
			moveAngle = DOWN_ANGLE;//下
		}
		else
		{
			moveAngle = UP_ANGLE;//上
		}

		//進む方向を計算
		F_Vec2 vel = F_Vec2{ cos(moveAngle), sin(moveAngle) };

		vel *= MOVE_SPEED;

		//velocityをセット
		SetVelocity(vel);
		moveCount = 0;
	}
	DamageStart();
}

void Terry::UpdateDamage()
{
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

void Terry::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);
	if (deathCount == Life::DEATH_EFFECT_FRAME)
	{
 		effectManager->SetState(position, F_Vec2{ 0,0 });
		//SoundEffect::GetInstance()->PlaySoundEffect(SoundEffect::E_SOUND_KND::DISAPPEAR);
	}
}

void Terry::RunStart()
{
	state->SetNextState("Run");
}

void Terry::DamageStart()
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
