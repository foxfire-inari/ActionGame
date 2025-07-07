#include "CollisionObject.h"

namespace
{
	static const float TOP_COLLISION	= -BLOCK_SIZE / 2;
	static const float UNDER_COLLISION	=  BLOCK_SIZE / 2;
	static const float LEFT_COLLISION	= -BLOCK_SIZE / 2;
	static const float RIGHT_COLLISION	=  BLOCK_SIZE / 2;
}

CollisionObject::CollisionObject(BaseScene* baseScene, int tag)
	:BaseObject{ baseScene,tag }
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ TOP_COLLISION,UNDER_COLLISION,LEFT_COLLISION,RIGHT_COLLISION };
}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, int tag)
	:BaseObject{baseScene,pos,F_Vec2{0,0},tag}
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ TOP_COLLISION,UNDER_COLLISION,LEFT_COLLISION,RIGHT_COLLISION };

}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, float top, float under, float left, float right, int tag)
	:BaseObject{ baseScene,pos,F_Vec2{0,0},tag }
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ top,under,left,right };
}


CollisionObject::~CollisionObject()
{
}


