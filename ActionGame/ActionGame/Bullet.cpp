#include "Bullet.h"

Bullet::Bullet(BaseScene* _baseScene, int _power, float top, float under, float left, float right)
	:BaseObject{ _baseScene ,BaseObject::E_TAG::BULLET }
	, power{ _power }
	, flag{ false }
{
	collisionData = new CollisionData{ top,under,left,right };
}


Bullet::~Bullet()
{
	if (collisionData != nullptr)delete collisionData;
}
