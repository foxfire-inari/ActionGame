#pragma once
#include<vector>
#include<string>
class BaseScene;

class CollisionManager;
class BlockManager;

class Player;

//�g���N���X�͂����őO���錾���Ƃ�

class CommonObjectAndManager
{
public:
	CommonObjectAndManager(BaseScene* nowScene);
	~CommonObjectAndManager();

	/// <summary>
	/// �v���C���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer()& { return player; }

	/// <summary>
	/// �u���b�N�}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	BlockManager* GetBlockManager()& { return blockManager; }

	/// <summary>
	/// �R���W�����}�l�[�W���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	CollisionManager* GetCollisoinManager()& { return collisionManager; }

private:
	Player* player;

	CollisionManager* collisionManager;
	BlockManager* blockManager;


};

