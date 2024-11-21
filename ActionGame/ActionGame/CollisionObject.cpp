#include "CollisionObject.h"

CollisionObject::CollisionObject(BaseScene* baseScene, bool _isThrough, int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},-32,32,-32,32,tag }
	, isThrough{ _isThrough }
{
}


CollisionObject::~CollisionObject()
{
}
