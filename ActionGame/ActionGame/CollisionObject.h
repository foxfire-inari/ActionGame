#pragma once
#include"BaseObject.h"

#include"CollisionData.h"

/// <summary>
/// 当たり判定を持つキャラクター以外のクラス
/// </summary>
class CollisionObject :public BaseObject
{
public:
	/// <summary>
	/// オブジェクトを
	/// 基本サイズ（1ｘ1）かつ
	/// 座標を(0,0)かつ
	/// 速度を(0,0)で生成
	/// </summary>
	CollisionObject(BaseScene* baseScene, bool _isThrough, int tag);


	/// <summary>
	/// オブジェクトのステータスをセットしながら生成
	/// </summary>
	/// <param name="baseScene">ベースシーン</param>
	/// <param name="pos">座標</param>
	/// <param name="vel">速度</param>
	/// <param name="top">	当たり判定＿上</param>
	/// <param name="under">当たり判定＿下</param>
	/// <param name="left">	当たり判定＿左</param>
	/// <param name="right">当たり判定＿右</param>
	/// <param name="_isThrough">すり抜け床かどうか</param>
	/// <param name="tag">タグ</param>
	CollisionObject(BaseScene* baseScene, F_Vec2 pos, F_Vec2 vel,
		float top, float under, float left, float right, bool _isThrough,int tag);

	~CollisionObject();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// コリジョンデータを渡す
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData() { return collisionData; }

	/// <summary>
	/// すり抜け床かどうかを返す
	/// </summary>
	/// <returns></returns>
	bool GetIsThrough() { return isThrough; }

private:

	/// <summary>
	/// 当たり判定の情報
	/// </summary>
	CollisionData* collisionData;

	/*
	一応すり抜け床の定義
	・オブジェクトの当たり判定は上のみ
	・左右と下からの判定はしない
	・オブジェクトの下から上に乗ることができる
	*/

	/// <summary>
	/// すり抜け床かどうか
	/// </summary>
	bool isThrough;
};

