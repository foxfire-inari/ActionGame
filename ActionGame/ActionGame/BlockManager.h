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
	void Draw(F_Vec2 _camDif)override;

	const std::list<CollisionObject*> GetCollisionObjList() const;

private:
	std::list<CollisionObject*> blockList;

	void SetObjectNewScene(BaseScene* _baseScene)override;
};

