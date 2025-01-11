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
	/// オブジェクトの
	/// 当たり判定を基本サイズ（1ｘ1）かつ
	/// 座標を(0,0)かつ
	/// 速度を(0,0)で生成
	/// </summary>
	CollisionObject(BaseScene* baseScene, int tag);

	/// <summary>
	/// オブジェクトの
	/// 当たり判定を基本サイズ（1ｘ1）かつ
	/// 座標を指定して生成
	/// </summary>
	/// <param name="baseScene">ベースシーン</param>
	/// <param name="pos">座標</param>
	/// <param name="tag">タグ</param>
	CollisionObject(BaseScene* baseScene, F_Vec2 pos,int tag);

	/// <summary>
	/// オフジェクトの当たり判定のサイズと座標を指定して生成
	/// </summary>
	/// <param name="baseScene"></param>
	/// <param name="pos"></param>
	/// <param name="top"></param>
	/// <param name="under"></param>
	/// <param name="left"></param>
	/// <param name="right"></param>
	/// <param name="tag"></param>
	CollisionObject(BaseScene* baseScene, F_Vec2 pos
		, float top, float under, float left, float right, int tag);


	~CollisionObject();

	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

	/// <summary>
	/// コリジョンデータを渡す
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData() { return collisionData; }

protected:

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
};

