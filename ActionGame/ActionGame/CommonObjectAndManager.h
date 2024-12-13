#pragma once
#include<vector>
#include<string>
class BaseScene;

class CollisionManager;
class BlockManager;

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

	/// <summary>
	/// ブロックマネージャーを返す
	/// </summary>
	/// <returns></returns>
	BlockManager* GetBlockManager()& { return blockManager; }

	/// <summary>
	/// コリジョンマネージャーを返す
	/// </summary>
	/// <returns></returns>
	CollisionManager* GetCollisoinManager()& { return collisionManager; }

private:
	Player* player;

	CollisionManager* collisionManager;
	BlockManager* blockManager;


};

