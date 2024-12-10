#pragma once
#include<vector>
#include<string>
class BaseScene;

class CollisionManager;


class Player;

//使うクラスはここで前方宣言しとく

class CommonObjectAndManager
{
public:
	CommonObjectAndManager(BaseScene* nowScene);
	~CommonObjectAndManager();

	/// <summary>
	/// プレイヤーを返す
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer()& { return player; }

	CollisionManager* GetCollisoinManager()& { return collisionManager; }

private:
	Player* player;

	CollisionManager* collisionManager;


};

