#pragma once
#include"Common.h"
class BlockManager;

class Player;
class Camera;

class BulletManager;
class EnemyManager;
class EffectManager;
class CollisionManager;
class WarpManager;

class BaseObject;
class BaseManager;
class BaseScene;

//�g���N���X�͂����őO���錾���Ƃ�

class CommonObjectAndManager
{
public:
	CommonObjectAndManager(BaseScene* nowScene
		, std::vector<std::vector<std::string>> information);
	~CommonObjectAndManager();

	/// <summary>
	/// ���X�g���̃}�l�[�W���[�����ׂ�Update����
	/// </summary>
	void Update();

	/// <summary>
	/// ���X�g���̃}�l�[�W���[��S��Draw����
	/// </summary>
	/// <param name="camDif"></param>
	void Draw(F_Vec2 camDif);

	/// <summary>
	/// �v���C���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer()& { return player; }

	/// <summary>
	/// �J������Ԃ�
	/// </summary>
	/// <returns></returns>
	Camera* GetCamera()& { return camera; }

	/// <summary>
	/// �o���b�g�}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	BulletManager* GetBulletManager()& { return bulletManager; }

	/// <summary>
	/// �G�t�F�N�g�}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	EffectManager* GetEffectManager()& { return effectManager; }

	/// <summary>
	/// �R���W�����}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	CollisionManager* GetCollisoinManager()& { return collisionManager; }

	/// <summary>
	/// �G�l�~�[�}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	EnemyManager* GetEnemyManager()& { return enemyManager; }

	/// <summary>
	/// �u���b�N�}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	BlockManager* GetBlockManager()& { return blockManager; }

	/// <summary>
	/// ���[�v�}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	WarpManager* GetWarpManager()& { return warpManager; }

private:

	std::list<BaseManager*> managerList;

	Player* player;
	Camera* camera;

	BulletManager* bulletManager;
	EffectManager* effectManager;
	CollisionManager* collisionManager;
	EnemyManager* enemyManager;
	BlockManager* blockManager;
	WarpManager* warpManager;

};

