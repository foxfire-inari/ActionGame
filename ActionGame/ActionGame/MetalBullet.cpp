#include "MetalBullet.h"

namespace
{
	//’e‘¬
	static const float BULLET_SPEED = 5.f;

	//’e‚Ì‰Î—Í
	static const int BULLET_POWER = 3;

	//ƒRƒŠƒWƒ‡ƒ“
	static const int COL_TOP	= -10;
	static const int COL_UNDER	=  10;
	static const int COL_LEFT	= -10;
	static const int COL_RIGHT	=  10;
}

MetalBullet::MetalBullet(BaseScene* baseScene, int knd)
	:Bullet{ baseScene,BULLET_POWER,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,knd }
{
}

MetalBullet::~MetalBullet()
{
}

void MetalBullet::Update()
{
	position += velocity;
}

void MetalBullet::Draw(F_Vec2 _camDif)
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

void MetalBullet::SetState(F_Vec2 pos, F_Vec2 vec, int _owner)
{
	flag = true;
	SetPosition(pos);
	SetVelocity(vec * BULLET_SPEED);
	owner = _owner;
}
