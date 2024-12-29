#pragma once
#include"Common.h"
class BaseObject;
class CollisionObject;
class CollisionData;
class Fall;

class CollisionProcessing
{
public:
	CollisionProcessing(std::list<CollisionObject*>& _colObjectList);
	~CollisionProcessing();

	/// <summary>
	/// 横方向の移動処理と
	/// オブジェクトとブロックの横方向のめり込み補正
	/// </summary>
	/// <param name="obj">判定するオブジェクト</param>
	/// <param name="objCol">オブジェクトのコリジョンデータ</param>
	/// <returns></returns>
	F_Vec2 GetSideBlockPosition(BaseObject* obj, CollisionData* objCol);

	/// <summary>
	/// 縦方向の移動処理と
	/// オブジェクトがブロックの上にいるかとめり込み補正
	/// </summary>
	/// <param name="obj">判定するオブジェクト</param>
	/// <param name="objCol">オブジェクトのコリジョンデータ</param>
	/// <param name="fall">落ちているかをセット</param>
	/// <returns></returns>
	F_Vec2 GetOnBlockPosition(BaseObject* obj, CollisionData* objCol, Fall* fall = nullptr);

private:
	std::list<CollisionObject*> collisionObjectList;

	/// <summary>
	/// 近くにあるかの判定
	/// </summary>
	/// <param name="objPos">判定の中心になる座標</param>
	/// <param name="listPos">リスト内の判定する座標</param>
	/// <param name="dif"></param>
	/// <returns></returns>
	bool IsNearDistance( F_Vec2 objPos, F_Vec2 listPos, float dif);

	/// <summary>
	/// ブロックと重なっているか
	/// </summary>
	/// <param name="objcol">判定するオブジェクトのコリジョンデータ</param>
	/// <param name="listcol">リスト内のコリジョンデータ</param>
	/// <returns></returns>
	bool IsInBlock(CollisionData* objCol,CollisionData* listCol);

	/// <summary>
	/// コリジョンの現在の座標を取得
	/// </summary>
	/// <param name="colData">コリジョンデータ</param>
	/// <param name="pos">持ち主の座標</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

};

