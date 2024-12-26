#pragma once
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"


/// <summary>
/// �S�Ă̒e�̌p����
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
	/// ���̃_���[�W
	/// </summary>
	int power;

	/// <summary>
	/// ���̒e�������Ă邩�ǂ���
	/// </summary>
	bool flag;

	/// <summary>
	/// �����蔻��̏��
	/// </summary>
	CollisionData* collisionData;

	/// <summary>
	/// �n�ʂƂ̓����蔻��p
	/// </summary>
	CollisionManager* collisionManager;

};

