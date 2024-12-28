#include "Bullet.h"

Bullet::Bullet(BaseScene* _baseScene, float top, float under, float left, float right)
	:BaseObject{ _baseScene ,BaseObject::E_TAG::BULLET }
	, power{ 0 }
	, flag{ false }
{
	collisionData = new CollisionData{ top,under,left,right };
}


Bullet::~Bullet()
{
	if (collisionData != nullptr)delete collisionData;
}
