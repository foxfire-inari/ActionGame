#include "Enemy.h"
#include "BulletManager.h"
#include "EffectManager.h"

Enemy::Enemy(BaseScene* baseScene, 
	BulletManager* _bulletManager, EffectManager* _effectManager, BaseObject* _plBase,
	F_Vec2 pos, int _knd, int hp, float top, float under, float left, float right)
	:Chara{baseScene,hp,top,under,left,right,BaseObject::E_TAG::ENEMY}
	,bulletManager{ _bulletManager}
	, effectManager{ _effectManager }
	,plBase{_plBase}
	,bodyPower{0}
	,knd{_knd}
	, deathCount{ 0 }
	,flag{false}
{
	position = pos;
	
	assert(bulletManager != nullptr);
	assert(effectManager != nullptr);
	assert(plBase != nullptr);
}

Enemy::~Enemy()
{
}
