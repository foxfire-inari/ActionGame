#pragma once
#include "BaseManager.h"
class CollisionObject;

/// <summary>
/// �S�Ă̓����蔻������I�u�W�F�N�g������
/// �}�l�[�W���[
/// </summary>
class CollisionManager :public BaseManager
{
	CollisionManager(BaseScene* baseScene);
	~CollisionManager();
	void Start()override;

	void SetObjectNewScene(BaseScene* _basescene)override {};
};

