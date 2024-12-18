#include "Chara.h"



Chara::Chara(BaseScene* baseScene,
	float top, float under, float left, float right,
	int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},top,under,left,right ,tag}
{
	//Charaのコンストラクタ
	fall = new Fall{};
	gravity = new Gravity{};
	positionSetter = new PositionSetter{};
	state = new State{};

	SetPosition(F_Vec2{ 100,100 });

	collisionManager = GetBaseScene()->GetManagerPtr<CollisionManager>(BaseManager::E_MANAGER_TAG::COLLISION);

}

Chara::~Chara()
{
}


