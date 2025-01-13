#pragma once
#include "Enemy.h"
/// <summary>
/// 敵(テリー)のクラス
/// </summary>
class Terry : public Enemy
{
public:
	Terry(BaseScene* baseScene,
		BulletManager* bulletManager, EffectManager* _effectManager,
		BaseObject* plBase, F_Vec2 pos, int knd);
	~Terry();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

private:

	float moveAngle;
	int damageCount;//ダメージを受けてからのカウンター

	void UpdateRun();
	void UpdateDamage();
	void UpdateDeath();

	void RunStart();
	void DamageStart();

};

