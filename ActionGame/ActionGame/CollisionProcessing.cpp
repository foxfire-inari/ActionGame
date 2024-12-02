#include "CollisionProcessing.h"
#include"CollisionObject.h"
#include"CollisionData.h"
#include"Fall.h"

namespace
{
	/// <summary>
	/// 判定する距離
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
	//キャラクターのコリジョン
	CollisionData* objCol = obj->GetNowCollisionPos();
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//キャラの近くないなら判定しない
		if (!IsNewrDistance(*it, obj, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetNowCollisionPos();

		//キャラがブロックの上下にいる
		bool isInBlock_X =
			(
				//キャラの右側がオブジェクトの範囲内か
				listCol->GetLeft() + 5 <= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight() - 5 ||
				//キャラの左側がオブジェクトの範囲内か
				listCol->GetLeft() + 5 <= objCol->GetLeft()  && objCol->GetLeft()  <= listCol->GetRight() - 5
			);

		//fabsf(this->x - vec.x) <= FLT_EPSILON
		//を使うべきか否か

		//キャラがブロックに重なっている
		bool isOnBlock = isInBlock_X &&
			listCol->GetTop() <= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder();



	}

	return F_Vec2();
}



bool CollisionProcessing::IsNewrDistance(BaseObject* obj, BaseObject* chara, float dif)
{
	if (F_Vec2::VSize(obj->GetPosition() - chara->GetPosition()) < dif)
		return true;
	return false;
}
