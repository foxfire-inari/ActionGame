#pragma once
#include "Bullet.h"

/// <summary>
/// �G���g���f�t�H���g�̒e�N���X
/// </summary>
class BallBullet : public Bullet
{
public:
	BallBullet(BaseScene* baseScene, int knd);
	~BallBullet();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	void SetState(F_Vec2 pos, F_Vec2 vec, int _owner)override;
};

