#include "Bullet.h"

Bullet::Bullet(BaseScene* _baseScene, float top, float under, float left, float right)
	:BaseObject{ _baseScene ,BaseObject::E_TAG::BULLET }
	, power{ 0 }
	, flag{ false }
{
	collisionData = new CollisionData{ top,under,left,right };
	collisionManager = GetBaseScene()->GetManagerPtr<CollisionManager>(BaseManager::E_MANAGER_TAG::COLLISION);
}


Bullet::~Bullet()
{
}

void Bullet::Start()
{
}

void Bullet::Update()
{
}

void Bullet::Draw(F_Vec2 _camDif)
{
}
