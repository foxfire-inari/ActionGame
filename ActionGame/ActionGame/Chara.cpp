#include "Chara.h"



Chara::Chara(BaseScene* baseScene,int hp,
	float top, float under, float left, float right,
	int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},tag}
{
	//Charaのコンストラクタ
	collisionData = new CollisionData{ top,under,left,right };
	fall = new Fall{};
	life = new Life{ hp };
	gravity = new Gravity{};
	positionSetter = new PositionSetter{};
	state = new State{};

	SetPosition(F_Vec2{ 100,100 });

	collisionManager = GetBaseScene()->GetManagerPtr<CollisionManager>(BaseManager::E_MANAGER_TAG::COLLISION);

}

Chara::~Chara()
{
}


