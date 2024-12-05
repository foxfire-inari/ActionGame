#pragma once
#include "BaseManager.h"
class CollisionObject;
class CollisionProcessing;

/// <summary>
/// �S�Ă̓����蔻������I�u�W�F�N�g������
/// �}�l�[�W���[
/// </summary>
class CollisionManager :public BaseManager
{
public:
	CollisionManager(BaseScene* baseScene);
	~CollisionManager();
	void Start()override;

	/// <summary>
	/// ���ۂ̔����CollisionProcessing���s��
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

