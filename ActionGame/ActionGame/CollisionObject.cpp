#include "CollisionObject.h"

CollisionObject::CollisionObject(BaseScene* baseScene, int tag)
	:BaseObject{ baseScene,tag }
{
	//CollisionObject�̃R���X�g���N�^
	collisionData = new CollisionData{ -BLOCK_SIZE/2,BLOCK_SIZE / 2,-BLOCK_SIZE / 2,BLOCK_SIZE / 2 };
}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, int tag)
	:BaseObject{baseScene,pos,F_Vec2{0,0},tag}
{
	//CollisionObject�̃R���X�g���N�^
	collisionData = new CollisionData{ -BLOCK_SIZE / 2,BLOCK_SIZE / 2,-BLOCK_SIZE / 2,BLOCK_SIZE / 2 };

}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, float top, float under, float left, float right, int tag)
	:BaseObject{ baseScene,pos,F_Vec2{0,0},tag }
{
	//CollisionObject�̃R���X�g���N�^
	collisionData = new CollisionData{ top,under,left,right };
}


CollisionObject::~CollisionObject()
{
}


