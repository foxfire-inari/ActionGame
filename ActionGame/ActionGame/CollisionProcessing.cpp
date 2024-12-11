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

	//x方向だけ移動
	objPos.x += objVel_X;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//キャラの近くないなら判定しない
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetNowCollisionPos();

		//ブロックと重なっているかを確認
		if (IsInBlock(objCol, listCol))
		{
			//進行方向で押し出す向きを固定
			if (objVel_X < 0)					//左向きに動いていた場合
			{
				objPos.x = listCol->GetRight() + listPos.x;
			}
			else								//右向きに動いていた場合
			{
				objPos.x = listCol->GetLeft() + listPos.x;
			}
		}
	}

	return objPos;
}

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, Fall* fall)
{
	//キャラクターのポジション
	F_Vec2 objPos = obj->GetPosition();
	//キャラクターのコリジョン
	CollisionData* objCol = obj->GetNowCollisionPos();
	//キャラクターのX方向の速度
	float objVel_Y = obj->GetVelocity().y;

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	bool isOnGround = false;

	//y方向だけ移動
	objPos.y += objVel_Y;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//キャラの近くないなら判定しない
		if (!IsNewrDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetNowCollisionPos();

		//ブロックと重なっているかを確認
		if (IsInBlock(objCol, listCol))
		{
			//進行方向で押し出す向きを固定
			if (objVel_Y < 0)					//下向きに動いていた場合
			{
				objPos.y = listCol->GetTop() + listPos.y;
			}
			else								//上向きに動いていた場合
			{
				objPos.y = listCol->GetUnder() + listPos.y;
			}
		}
	}

	return objPos;
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
