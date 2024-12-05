#pragma once
#include"Common.h"
class BaseObject;
class CollisionObject;
class CollisionData;
class Fall;

class CollisionProcessing
{
public:
	CollisionProcessing(std::list<CollisionObject*>& _collObjectList);
	~CollisionProcessing();

	/// <summary>
	/// オブジェクトとブロックの横方向のめり込み補正
	/// </summary>
	/// <param name="obj">判定するオブジェクト</param>
	/// <returns></returns>
	F_Vec2 GetSideBlockPosition(BaseObject* obj);

	/// <summary>
	/// オブジェクトがブロックの上にいるかとめり込み補正
	/// </summary>
	/// <param name="obj">判定するオブジェクト</param>
	/// <param name="fall">落ちているかをセット</param>
	/// <returns></returns>
	F_Vec2 GetOnBlockPosition(BaseObject* obj, Fall* fall = nullptr);

private:
	std::list<CollisionObject*> collisionObjectList;

	/// <summary>
	/// 近くにあるかの判定
	/// </summary>
	/// <param name="obj">対象のオブジェクト</param>
	/// <param name="chara">キャラ</param>
	/// <param name="dif">距離</param>
	/// <returns></returns>
	bool IsNewrDistance(F_Vec2 colpos, F_Vec2 objpos, float dif);

};

