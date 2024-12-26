#pragma once
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"


/// <summary>
/// 全ての弾の継承元
/// </summary>
class Bullet : public BaseObject
{
	Bullet(BaseScene* _baseScene, float top, float under, float left, float right );
	~Bullet();

	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif);

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

	/// <summary>
	/// 地面との当たり判定用
	/// </summary>
	CollisionManager* collisionManager;

};

