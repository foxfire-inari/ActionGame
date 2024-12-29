#pragma once
#include "Bullet.h"

class NormalBullet : public Bullet
{
public:
	NormalBullet(BaseScene* baseScene);
	~NormalBullet();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	void SetState(F_Vec2 pos, F_Vec2 vec)override;
};

