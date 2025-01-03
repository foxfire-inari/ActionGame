#include "Terry.h"
#include "BulletManager.h"

namespace
{
	//体力
	static const int START_HP = 10;

	//移動速度
	static const float MOVE_SPEED = 0.5f;

	//コリジョン
	static const int COL_TOP = -32;
	static const int COL_UNDER = 32;
	static const int COL_LEFT = -32;
	static const int COL_RIGHT = 32;

	//ステート
	static const int STATE_RUN = 0;
	static const int STATE_DAMAGE = 1;
	static const int STATE_DEATH = 2;
}

Terry::Terry(BaseScene* baseScene, BulletManager* bulletManager,
	BaseObject* plBase, F_Vec2 pos, int knd)
	:Enemy{baseScene,bulletManager,plBase,pos,knd,START_HP,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT }
	, MoveAngle{ 0 }
{
	bodyPower = 2;

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

void Terry::UpdateRun()
{
	//プレイヤー座標を取得
	F_Vec2 plPos = plBase->GetPosition();
	//相対角度を計算
	MoveAngle = atan2f(plPos.y - position.y, plPos.x - position.x);
	//進む方向を計算
	F_Vec2 vel = F_Vec2{ MOVE_SPEED * cos(MoveAngle), MOVE_SPEED * sin(MoveAngle) };
	//velocityをセット
	SetVelocity(vel);

	StartDamage();
}

void Terry::UpdateDamage()
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

void Terry::UpdateDeath()
{
	deathCount++;
	if (deathCount > Life::DEATH_FRAME)life->SetIsDeath(true);

}

void Terry::StartRun()
{
	state->SetNextState("Damage");
}

void Terry::StartDamage()
{
	if (life->GetHp() <= 0)return;
	int bulletDamage = bulletManager->HitCheckEnemy(this, collisionData);
	if (bulletDamage != 0)
	{
		//ダメージ処理
		life->DecHp(bulletDamage);

		damageCount = 0;

		state->SetNextState("Damage");
	}
}
