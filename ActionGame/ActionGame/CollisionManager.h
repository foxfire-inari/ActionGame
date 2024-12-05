#pragma once
#include "BaseManager.h"
class CollisionObject;
class CollisionProcessing;

/// <summary>
/// 全ての当たり判定を持つオブジェクトを持つ
/// マネージャー
/// </summary>
class CollisionManager :public BaseManager
{
public:
	CollisionManager(BaseScene* baseScene);
	~CollisionManager();
	void Start()override;

	/// <summary>
	/// 実際の判定はCollisionProcessingが行う
	/// </summary>
	/// <returns></returns>
	CollisionProcessing* GetCollisionProcessing()const
	{
		return collisionProcessing;
	}

private:
	CollisionProcessing* collisionProcessing;

	void SetObjectNewScene(BaseScene* _basescene)override {};
};

