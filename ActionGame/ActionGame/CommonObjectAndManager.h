#pragma once
#include<vector>
#include<string>
class BlockManager;

class Player;
class Camera;

class BulletManager;
class CollisionManager;

class BaseScene;

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
	/// カメラを返す
	/// </summary>
	/// <returns></returns>
	Camera* GetCamera()& { return camera; }

	/// <summary>
	/// バレットマネージャーを返す
	/// </summary>
	/// <returns></returns>
	BulletManager* GetBulletManager()& { return bulletManager; }

	/// <summary>
	/// コリジョンマネージャーを返す
	/// </summary>
	/// <returns></returns>
	CollisionManager* GetCollisoinManager()& { return collisionManager; }

	/// <summary>
	/// ブロックマネージャーを返す
	/// </summary>
	/// <returns></returns>
	BlockManager* GetBlockManager()& { return blockManager; }


private:
	Player* player;
	Camera* camera;

	BulletManager* bulletManager;
	CollisionManager* collisionManager;
	BlockManager* blockManager;


};

