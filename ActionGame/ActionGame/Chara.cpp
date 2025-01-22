#include "Chara.h"



Chara::Chara(BaseScene* baseScene,int hp,
	float top, float under, float left, float right,
	int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},tag}
	, imageH{ -1 }

{
	//Charaのコンストラクタ
	collisionData = new CollisionData{ top,under,left,right };
	fall = new Fall{};
	life = new Life{ hp };
	gravity = new Gravity{};
	positionSetter = new PositionSetter{};
	state = new State{};
	animation = new Animation{};

	collisionManager = GetBaseScene()->GetManagerPtr<CollisionManager>(BaseManager::E_MANAGER_TAG::COLLISION);

}

Chara::~Chara()
{
	if (collisionData != nullptr)delete collisionData;
	if (fall != nullptr)delete fall;
	if (life != nullptr)delete life;
	if (gravity != nullptr)delete gravity;
	if (positionSetter != nullptr)delete positionSetter;
	if (state != nullptr)delete state;
	if (animation != nullptr)delete animation;

}


