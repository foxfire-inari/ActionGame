#include "CollisionProcessing.h"
#include"CollisionObject.h"
#include"CollisionData.h"
#include"Fall.h"

namespace
{
	/// <summary>
	/// 判定する距離
	/// </summary>
	static const float HIT_CHECK_DIF = 100.0f;
}

CollisionProcessing::CollisionProcessing(std::list<CollisionObject*>& _colObjectList)
	:collisionObjectList{ _colObjectList }
{
}

CollisionProcessing::~CollisionProcessing()
{
	collisionObjectList.clear();
}

F_Vec2 CollisionProcessing::GetSideBlockPosition(BaseObject* obj,CollisionData* objCol)
{
	//キャラクターのポジション
	F_Vec2 objPos = obj->GetPosition();
	//キャラクターのX方向の速度
	float objVel_X = obj->GetVelocity().x;

	//x方向だけ移動
	objPos.x += objVel_X;

	//座標を考慮した当たり判定に変更
	CollisionData* nowObjCol = GetNowPositionCol(objCol, objPos);

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//キャラの近くないなら判定しない
		if (!IsNearDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetCollisionData();
		
		//座標を足してコリジョンが存在する座標にする
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//ブロックと重なっているかを確認
		if (IsInBlock(nowObjCol, nowlistCol))
		{

			assert(objVel_X != 0);

			//進行方向で押し出す向きを固定
			if (objVel_X < 0)					//左向きに動いていた場合
			{
 				objPos.x = nowlistCol->GetRight() - objCol->GetLeft();
			}
			else if (objVel_X > 0)				//右向きに動いていた場合
			{
				objPos.x = nowlistCol->GetLeft() - objCol->GetRight();
			}

		}
	}

	return objPos;
}

F_Vec2 CollisionProcessing::GetOnBlockPosition(BaseObject* obj, CollisionData* objCol, Fall* fall)
{
	//キャラクターのポジション
	F_Vec2 objPos = obj->GetPosition();
	//キャラクターのX方向の速度
	F_Vec2 objVel = obj->GetVelocity();

	//y方向だけ移動
	objPos.y -= objVel.y;

	//座標を考慮した当たり判定に変更
	CollisionData* nowObjCol = GetNowPositionCol(objCol, objPos);

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	//地面に経っているかを記録
	bool isOnGround = false;

	for (auto it = collisionObjectList.begin(); it != collisionObjectList.end(); it++)
	{
		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//キャラの近くないなら判定しない
		if (!IsNearDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetCollisionData();
		//念のため小数点を切り捨ててからint型に変更
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//ブロックと重なっているかを確認
		if (IsInBlock(nowObjCol, nowlistCol))
		{

			assert(objVel.y != 0);

			//進行方向で押し出す向きを固定
			if (objVel.y < 0)					//下向きに動いていた場合
			{
				objPos.y = nowlistCol->GetTop() - objCol->GetUnder();
				isOnGround = true;
			}
			else								//上向きに動いていた場合
			{
				objPos.y = nowlistCol->GetUnder() - objCol->GetTop();
				//Y方向の速度を0にする
				obj->SetVelocity(F_Vec2{ objVel.x,0 });
			}
		}
	}

	if (fall != nullptr)
	{
		//地面に立っているかを保存
		fall->SetIsOnGround(isOnGround);
	}

	return objPos;
}



bool CollisionProcessing::IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif)
{
	if (F_Vec2::VSize(listPos - objPos) < dif)
		return true;
	return false;
}

bool CollisionProcessing::IsInBlock(CollisionData* objCol, CollisionData* listCol)
{
	//めり込み補正
	static const float IN_DIF = 0.5f;
	//それぞれのポジションを計算に含める必要がある
	return (
		//ブロックの横に居るか
		(listCol->GetTop()+IN_DIF	<= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder() ||
		 listCol->GetTop()			<= objCol->GetTop()   && objCol->GetTop()   <= listCol->GetUnder()-IN_DIF) &&
		//ブロックの縦に居るか
		(listCol->GetLeft()			<= objCol->GetLeft()  && objCol->GetLeft()  <= listCol->GetRight()-IN_DIF ||
		 listCol->GetLeft()+IN_DIF	<= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight())
		);
}

CollisionData* CollisionProcessing::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colData->GetTop()	+ pos.y,
		colData->GetUnder()+ pos.y,
		colData->GetLeft()	+ pos.x,
		colData->GetRight()+ pos.x
	};
	return nowCol;
}