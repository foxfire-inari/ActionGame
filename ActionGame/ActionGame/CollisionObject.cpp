#include "CollisionObject.h"

CollisionObject::CollisionObject(BaseScene* baseScene, int tag)
	:BaseObject{ baseScene,tag }
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ -BLOCK_SIZE/2,BLOCK_SIZE / 2,-BLOCK_SIZE / 2,BLOCK_SIZE / 2 };
}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, int tag)
	:BaseObject{baseScene,pos,F_Vec2{0,0},tag}
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ -BLOCK_SIZE / 2,BLOCK_SIZE / 2,-BLOCK_SIZE / 2,BLOCK_SIZE / 2 };

}


CollisionObject::~CollisionObject()
{
}


