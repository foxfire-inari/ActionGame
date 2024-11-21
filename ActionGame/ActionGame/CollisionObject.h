#pragma once
#include"BaseObject.h"

/// <summary>
/// 当たり判定を持つキャラクター以外のクラス
/// </summary>
class CollisionObject : BaseObject
{
public:
	/// <summary>
	/// オブジェクトのの基本サイズ（1ｘ1）で生成
	/// </summary>
	CollisionObject(BaseScene* _baseScene, bool _isThrough, int _tag);
	~CollisionObject();

	/// <summary>
	/// すり抜け床かどうかを返す
	/// </summary>
	/// <returns></returns>
	bool GetIsThrough() { return isThrough; }

private:

	/*
	一応すり抜け床の定義
	・オブジェクトの当たり判定は上のみ
	・左右と下からの判定はしない
	*/

	/// <summary>
	/// すり抜け床かどうか
	/// </summary>
	bool isThrough;
};

