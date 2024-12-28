#include "NormalBullet.h"

namespace
{
	//’e‘¬
	static const float BULLET_SPEED = 5.f;
}


NormalBullet::NormalBullet(BaseScene* baseScene)
	:Bullet{baseScene,5,5,10,10}
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

void NormalBullet::SetState(F_Vec2 pos, F_Vec2 vec, int _power)
{
	flag = true;
	SetPosition(pos);
	SetVelocity(vec * BULLET_SPEED);
	power = _power;
}
