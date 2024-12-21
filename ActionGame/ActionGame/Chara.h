#pragma once
#include"BaseObject.h"

#include"CollisionData.h"
#include"Fall.h"
#include"Gravity.h"
#include"PositionSetter.h"
#include"State.h"
#include"CollisionManager.h"

/// <summary>
/// 全てのキャラの継承元
/// </summary>
class Chara : public BaseObject
{
public:
	Chara(BaseScene* baseScene,
		float top, float under, float left, float right,
		int tag);
	~Chara();
	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

protected:

	/// <summary>
	/// 当たり判定の情報
	/// </summary>
	CollisionData* collisionData;

	/// <summary>
	/// 地面に乗ってるか
	/// </summary>
	Fall* fall;

	/// <summary>
	/// 重力
	/// </summary>
	Gravity* gravity;

	/// <summary>
	/// キャラ移動に関するクラス
	/// </summary>
	PositionSetter* positionSetter;

	/// <summary>
	/// ステート
	/// </summary>
	State* state;

	CollisionManager* collisionManager;

};

/// ＜必要な要素＞
/// 
/// 
/// 体力
/// 
/// 
/// (画像は各キャラクターで実装する)
///