#include "CollisionObject.h"

CollisionObject::CollisionObject(BaseScene* baseScene, int tag)
	:BaseObject{ baseScene,tag }
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ -BLOCK_SIZE/2,BLOCK_SIZE / 2,-BLOCK_SIZE / 2,BLOCK_SIZE / 2 };
}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, F_Vec2 vel, 
								 float top, float under, float left, float right, int tag)
	:BaseObject{baseScene,pos,vel,tag}
{
	//CollisionObjectのコンストラクタ
	collisionData = new CollisionData{ top,under,left,right };

}


CollisionObject::~CollisionObject()
{
}

void CollisionObject::Update()
{
}

void CollisionObject::Draw(F_Vec2 _camDif)
{
	F_Vec2 drawpos = GetPosition();
	DrawBox
	(
		drawpos.x - _camDif.x + collisionData->GetLeft(),
		drawpos.y - _camDif.y + collisionData->GetTop(),
		drawpos.x - _camDif.x + collisionData->GetRight(),
		drawpos.y - _camDif.y + collisionData->GetUnder(),
		GetColor(100, 255, 255),
		true
	);
}
