#include "Enemy.h"

Enemy::Enemy(BaseScene* baseScene, BulletManager* _bulletManager, BaseObject* _plBase,
	F_Vec2 pos, int _knd, int hp, float top, float under, float left, float right)
	:Chara{baseScene,hp,top,under,left,right,BaseObject::E_TAG::ENEMY}
	,bulletManager{ _bulletManager}
	,plBase{_plBase}
	,bodyPower{0}
	,knd{_knd}
	,flag{false}
{
	position = pos;
	
	assert(bulletManager != nullptr);
	assert(plBase != nullptr);
}

Enemy::~Enemy()
{
}
