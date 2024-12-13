#pragma once
#include "BaseManager.h"

class CollisionObject;

/// <summary>
/// �S�Ẵu���b�N���Ǘ�����N���X
/// </summary>
class BlockManager :public BaseManager
{
public:
	BlockManager(BaseScene* baseScene);
	~BlockManager();
	void Start()override;
	void Update()override;
	void Draw()override;

	const std::list<CollisionObject*> GetCollisionObjList() const;

private:
	std::list<CollisionObject*> BlockList;

	void SetObjectNewScene(BaseScene* _baseScene)override;
};

