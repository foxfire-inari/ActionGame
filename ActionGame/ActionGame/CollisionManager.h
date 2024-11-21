#pragma once
#include "BaseManager.h"
class CollisionObject;

/// <summary>
/// 全ての当たり判定を持つオブジェクトを持つ
/// マネージャー
/// </summary>
class CollisionManager :public BaseManager
{
	CollisionManager(BaseScene* baseScene);
	~CollisionManager();
	void Start()override;

	void SetObjectNewScene(BaseScene* _basescene)override {};
};

