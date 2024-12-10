#pragma once
#include<vector>
#include<string>
class BaseScene;

class CollisionManager;


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

	CollisionManager* GetCollisoinManager()& { return collisionManager; }

private:
	Player* player;

	CollisionManager* collisionManager;


};

