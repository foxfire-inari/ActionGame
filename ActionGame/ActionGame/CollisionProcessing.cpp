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

F_Vec2 CollisionProcessing::GetSideBlockPosition(BaseObject* obj)
{
	//キャラクターのポジション
	F_Vec2 objPos = obj->GetPosition();
	//キャラクターのコリジョン
	CollisionData* objCol = obj->GetNowCollisionPos();
	//キャラクターのX方向の速度
	float objVel_X = obj->GetVelocity().x;

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		listPos = (*it)->GetPosition();

		//キャラの近くないなら判定しない
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetNowCollisionPos();


		//x方向だけ仮で移動
		objPos.x += objVel_X;

		//仮で移動したオブジェクトがブロックに重なっているか
		bool isSideBlock = 
			(

				listCol->GetTop()  <= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder() ||
				listCol->GetTop()  <= objCol->GetTop()   && objCol->GetTop()   <= listCol->GetUnder() &&

				listCol->GetLeft() <= objCol->GetLeft()  && objCol->GetLeft()  <= listCol->GetRight() ||
				listCol->GetLeft() <= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight()
			);
	}

	return F_Vec2();
}

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, Fall* fall)
{
	//キャラクターのコリジョン
	CollisionData* objCol = obj->GetNowCollisionPos();
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//キャラの近くないなら判定しない
		//if (!IsNewrDistance(*it, obj, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetNowCollisionPos();

		




	}

	return F_Vec2();
}



bool CollisionProcessing::IsNewrDistance(F_Vec2 colpos,F_Vec2 objpos, float dif)
{
	if (F_Vec2::VSize(colpos - objpos) < dif)
		return true;
	return false;
}

bool CollisionProcessing::IsInBlock(CollisionData* objcol, CollisionData* listcol)
{
	//それぞれのポジションを計算に含める必要がある
	return (
		//ブロックの横に居るか
		listcol->GetTop()  <= objcol->GetUnder() && objcol->GetUnder() <= listcol->GetUnder() ||
		listcol->GetTop()  <= objcol->GetTop()   && objcol->GetTop()   <= listcol->GetUnder() &&
		//ブロックの縦に居るか
		listcol->GetLeft() <= objcol->GetLeft()  && objcol->GetLeft()  <= listcol->GetRight() ||
		listcol->GetLeft() <= objcol->GetRight() && objcol->GetRight() <= listcol->GetRight()
		);
}
