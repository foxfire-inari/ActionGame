#include "CollisionObject.h"

CollisionObject::CollisionObject(BaseScene* baseScene, bool _isThrough, int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},-32,32,-32,32,tag }
	, isThrough{ _isThrough }
{
	//CollisionObjectのコンストラクタ
}

CollisionObject::CollisionObject(BaseScene* baseScene, F_Vec2 pos, F_Vec2 vel, 
								 int top, int under, int left, int right, bool _isThrough, int tag)
	:BaseObject{baseScene,pos,vel,top,under,left,right,tag}
	, isThrough{ _isThrough }
{
	//CollisionObjectのコンストラクタ
}


CollisionObject::~CollisionObject()
{
}

void CollisionObject::Update()
{
}

void CollisionObject::Draw()
{
	F_Vec2 drawpos = GetPosition();
	DrawBox
	(
		drawpos.x + ColData->GetLeft(),
		drawpos.y + ColData->GetTop(),
		drawpos.x + ColData->GetRight(),
		drawpos.y + ColData->GetUnder(),
		GetColor(100, 255, 255),
		true
	);
}
