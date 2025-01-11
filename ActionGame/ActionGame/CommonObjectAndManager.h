#pragma once
#include<vector>
#include<string>
class BlockManager;

class Player;
class Camera;

class BulletManager;
class CollisionManager;
class EnemyManager;
class WarpManager;

class BaseScene;

//�g���N���X�͂����őO���錾���Ƃ�

class CommonObjectAndManager
{
public:
	CommonObjectAndManager(BaseScene* nowScene
		, std::vector<std::vector<std::string>> information);
	~CommonObjectAndManager();

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
	Player* player;
	Camera* camera;

	BulletManager* bulletManager;
	CollisionManager* collisionManager;
	EnemyManager* enemyManager;
	BlockManager* blockManager;
	WarpManager* warpManager;

};

