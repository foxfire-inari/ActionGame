#pragma once
#include "Bullet.h"

/// <summary>
/// ƒƒ^ƒ‹‚È’e‚ÌƒNƒ‰ƒX
/// </summary>
class MetalBullet : public Bullet
{
public:
	MetalBullet(BaseScene* baseScene, int knd);
	~MetalBullet();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	void SetState(F_Vec2 pos, F_Vec2 vec, int _owner)override;
};

