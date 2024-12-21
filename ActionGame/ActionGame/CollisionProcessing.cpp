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

CollisionProcessing::CollisionProcessing(std::list<CollisionObject*>& _collisionObjectList)
	:collisionObjectList{ _collisionObjectList }
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

	CollisionData* nowobjCol = GetNowPositionColl(objCol, objPos);

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
		listCol = (*it)->GetCollisionPos();
		
		//座標を足してコリジョンが存在する座標にする
		CollisionData* nowlistCol = GetNowPositionColl(listCol, listPos);

		//ブロックと重なっているかを確認
		if (IsInBlock(nowobjCol, nowlistCol))
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
	float objVel_Y = obj->GetVelocity().y;

	//y方向だけ移動
	objPos.y -= objVel_Y;

	//念のため小数点を切り捨ててからint型に変更
	CollisionData* nowobjCol = GetNowPositionColl(objCol, objPos);

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
		listCol = (*it)->GetCollisionPos();
		//念のため小数点を切り捨ててからint型に変更
		CollisionData* nowlistCol = GetNowPositionColl(listCol, listPos);

		//ブロックと重なっているかを確認
		if (IsInBlock(nowobjCol, nowlistCol))
		{

			assert(objVel_Y != 0);

			//進行方向で押し出す向きを固定
			if (objVel_Y < 0)					//下向きに動いていた場合
			{
				objPos.y = nowlistCol->GetTop() - objCol->GetUnder();
				isOnGround = true;
			}
			else								//上向きに動いていた場合
			{
				objPos.y = nowlistCol->GetUnder() - objCol->GetTop();
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



bool CollisionProcessing::IsNearDistance(F_Vec2 colpos,F_Vec2 objpos, float dif)
{
	if (F_Vec2::VSize(colpos - objpos) < dif)
		return true;
	return false;
}

bool CollisionProcessing::IsInBlock(CollisionData* objcol, CollisionData* listcol)
{
	//めり込み補正
	static const float IN_DIF = 0.5f;
	//それぞれのポジションを計算に含める必要がある
	return (
		//ブロックの横に居るか
		(listcol->GetTop()+IN_DIF	<= objcol->GetUnder() && objcol->GetUnder() <= listcol->GetUnder() ||
		 listcol->GetTop()			<= objcol->GetTop()   && objcol->GetTop()   <= listcol->GetUnder()-IN_DIF) &&
		//ブロックの縦に居るか
		(listcol->GetLeft()			<= objcol->GetLeft()  && objcol->GetLeft()  <= listcol->GetRight()-IN_DIF ||
		 listcol->GetLeft()+IN_DIF	<= objcol->GetRight() && objcol->GetRight() <= listcol->GetRight())
		);
}

CollisionData* CollisionProcessing::GetNowPositionColl(CollisionData* colldata, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colldata->GetTop()	+ pos.y,
		colldata->GetUnder()+ pos.y,
		colldata->GetLeft()	+ pos.x,
		colldata->GetRight()+ pos.x
	};
	return nowCol;
}