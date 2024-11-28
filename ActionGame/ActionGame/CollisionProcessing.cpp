#include "CollisionProcessing.h"
#include"CollisionObject.h"
#include"CollisionData.h"
#include"Fall.h"

namespace
{
	/// <summary>
	/// ”»’è‚·‚é‹——£
	/// </summary>
	static const float HIT_CHECK_DIF = 1000.0f;
}

CollisionProcessing::CollisionProcessing(std::list<CollisionObject*>& _collisionObjectList)
	:collisionObjectList{ _collisionObjectList }
{
}

CollisionProcessing::~CollisionProcessing()
{
	collisionObjectList.clear();
}

F_Vec2 CollisionProcessing::GetOnGroundPosition(BaseObject* obj, Fall* fall)
{
	F_Vec2 pos = obj->GetPosition();

	float top	= obj->GetCollisionData()->GetTop();
	float under	= obj->GetCollisionData()->GetUnder();
	float Left	= obj->GetCollisionData()->GetLeft();
	float Right	= obj->GetCollisionData()->GetRight();

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		if (!IsNewrDistance(*it, obj, HIT_CHECK_DIF))continue;

		//“–‚½‚è”»’è‚ÌÚ×‚Èˆ—‚ð‹Lq

	}

	return F_Vec2();
}



bool CollisionProcessing::IsNewrDistance(BaseObject* obj, BaseObject* player, float dif)
{
	if (F_Vec2::VSize(obj->GetPosition() - player->GetPosition()) < dif)
		return true;
	return false;
}
