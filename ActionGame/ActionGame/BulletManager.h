#pragma once
#include"BaseManager.h"
class Bullet;
class CollisionData;

class BulletManager : public BaseManager
{
	BulletManager(BaseScene* baseScene);
	~BulletManager();

	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;
private:
	std::list<Bullet*> bulletList;

};

