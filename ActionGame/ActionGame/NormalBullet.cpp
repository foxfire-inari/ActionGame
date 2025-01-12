#include "NormalBullet.h"

namespace
{
	//’e‘¬
	static const float BULLET_SPEED = 10.f;

	//’e‚Ì‰Î—Í
	static const int BULLET_POWER = 1;

	//ƒRƒŠƒWƒ‡ƒ“
	static const int COL_TOP	= -5;
	static const int COL_UNDER	=  5;
	static const int COL_LEFT	= -10;
	static const int COL_RIGHT	=  10;
}


NormalBullet::NormalBullet(BaseScene* baseScene,int knd)
	:Bullet{ baseScene,BULLET_POWER,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,knd }
{
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Update()
{
	position += velocity;
}

void NormalBullet::Draw(F_Vec2 _camDif)
{
	F_Vec2 drawpos = GetPosition();
	DrawBox
	(
		drawpos.x - _camDif.x + collisionData->GetLeft(),
		drawpos.y - _camDif.y + collisionData->GetTop(),
		drawpos.x - _camDif.x + collisionData->GetRight(),
		drawpos.y - _camDif.y + collisionData->GetUnder(),
		GetColor(255, 100, 100),
		true
	);
}

void NormalBullet::SetState(F_Vec2 pos, F_Vec2 vec, int _owner)
{
	flag = true;
	SetPosition(pos);
	SetVelocity(vec * BULLET_SPEED);
	owner = _owner;
}
