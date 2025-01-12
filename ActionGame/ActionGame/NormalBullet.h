#pragma once
#include "Bullet.h"

/// <summary>
/// �f�t�H���g�̒e�N���X
/// </summary>
class NormalBullet : public Bullet
{
public:
	NormalBullet(BaseScene* baseScene,int knd);
	~NormalBullet();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	void SetState(F_Vec2 pos, F_Vec2 vec, int _owner)override;
};

