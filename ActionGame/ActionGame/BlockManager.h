#pragma once
#include "BaseManager.h"

class CollisionObject;

/// <summary>
/// 全てのブロックを管理するクラス
/// </summary>
class BlockManager :public BaseManager
{
public:
	BlockManager(BaseScene* baseScene);
	~BlockManager();
	void Start()override;
	void Update()override;

private:
	std::list<CollisionObject*> BlockList;

	void SetObjectNewScene(BaseScene* _baseScene)override;
};

