#include "BallBullet.h"

namespace
{
	//’e‘¬
	static const float BULLET_SPEED = 3.f;

	//’e‚Ì‰Î—Í
	static const int BULLET_POWER = 2;

	//ƒRƒŠƒWƒ‡ƒ“
	static const int COL_TOP	= -8;
	static const int COL_UNDER	=  8;
	static const int COL_LEFT	= -8;
	static const int COL_RIGHT	=  8;

	//‰æ‘œ
	static const float IMG_TOP = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT = COL_LEFT;
	static const float IMG_RIGHT = COL_RIGHT;

}


BallBullet::BallBullet(BaseScene* baseScene, int knd)
	:Bullet{ baseScene,BULLET_POWER,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,knd }
{
	imageH = Image::GetInstance()->GetBulletH(knd);

}

BallBullet::~BallBullet()
{
}

void BallBullet::Update()
{
	position += velocity;
}

void BallBullet::Draw(F_Vec2 _camDif)
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

void BallBullet::SetState(F_Vec2 pos, F_Vec2 vec, int _owner)
{
	flag = true;
	SetPosition(pos);
	SetVelocity(vec * BULLET_SPEED);
	owner = _owner;
}
