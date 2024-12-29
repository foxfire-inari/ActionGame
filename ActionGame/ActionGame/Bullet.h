#pragma once
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"


/// <summary>
/// 全ての弾の継承元
/// </summary>
class Bullet : public BaseObject
{
public:
	Bullet(BaseScene* _baseScene, int _power, float top, float under, float left, float right );
	~Bullet();

	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

	/// <summary>
	/// 弾の要素を設定する
	/// </summary>
	/// <param name="pos">発射地点</param>
	/// <param name="vec">発射方向</param>
	/// <param name="_power">ダメージ量</param>
	virtual void SetState(F_Vec2 pos,F_Vec2 vec) {};

	/// <summary>
	/// フラグが立っているか返す
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// フラグをセット
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }

	/// <summary>
	/// コリジョンを返す
	/// HitCheckEnemy用
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData()const { return collisionData; }

	/// <summary>
	/// ダメージを返す
	/// </summary>
	/// <returns></returns>
	int GetPower()const { return power; }

protected:

	/// <summary>
	/// 球のダメージ
	/// </summary>
	int power;

	/// <summary>
	/// この弾が動いてるかどうか
	/// </summary>
	bool flag;

	/// <summary>
	/// 当たり判定の情報
	/// </summary>
	CollisionData* collisionData;
};

