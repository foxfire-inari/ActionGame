#include "MetalBullet.h"

namespace
{
	//’e‘¬
	static const float BULLET_SPEED = 5.5f;

	//’e‚Ì‰Î—Í
	static const int BULLET_POWER = 3;

	//ƒRƒŠƒWƒ‡ƒ“
	static const int COL_TOP	= -20;
	static const int COL_UNDER	=  20;
	static const int COL_LEFT	= -20;
	static const int COL_RIGHT	=  20;

	//‰æ‘œ
	static const float IMG_TOP = COL_TOP;
	static const float IMG_UNDER = COL_UNDER;
	static const float IMG_LEFT = COL_LEFT;
	static const float IMG_RIGHT = COL_RIGHT;
}

MetalBullet::MetalBullet(BaseScene* baseScene, int knd)
	:Bullet{ baseScene,BULLET_POWER,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,knd }
{
	imageH = Image::GetInstance()->GetBulletH(knd);

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

void MetalBullet::SetState(F_Vec2 pos, F_Vec2 vec, int _owner)
{
	flag = true;
	SetPosition(pos);
	SetVelocity(vec * BULLET_SPEED);
	owner = _owner;
}
