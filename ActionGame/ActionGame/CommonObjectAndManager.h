#pragma once
#include<vector>
#include<list>
#include<string>
class BlockManager;

class Player;
class Camera;

class BulletManager;
class EffectManager;
class CollisionManager;
class EnemyManager;
class WarpManager;

class BaseObject;
class BaseManager;
class BaseScene;

//使うクラスはここで前方宣言しとく

class CommonObjectAndManager
{
public:
	CommonObjectAndManager(BaseScene* nowScene
		, std::vector<std::vector<std::string>> information);
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
	/// エフェクトマネージャーを返す
	/// </summary>
	/// <returns></returns>
	EffectManager* GetEffectManager()& { return effectManager; }

	/// <summary>
	/// コリジョンマネージャーを返す
	/// </summary>
	/// <returns></returns>
	CollisionManager* GetCollisoinManager()& { return collisionManager; }

	/// <summary>
	/// エネミーマネージャーを返す
	/// </summary>
	/// <returns></returns>
	EnemyManager* GetEnemyManager()& { return enemyManager; }

	/// <summary>
	/// ブロックマネージャーを返す
	/// </summary>
	/// <returns></returns>
	BlockManager* GetBlockManager()& { return blockManager; }

	/// <summary>
	/// ワープマネージャーを返す
	/// </summary>
	/// <returns></returns>
	WarpManager* GetWarpManager()& { return warpManager; }

private:

	std::list<BaseManager*> managerList;
	std::list<BaseObject*> oneObjectList;

	Player* player;
	Camera* camera;

	BulletManager* bulletManager;
	EffectManager* effectManager;
	CollisionManager* collisionManager;
	EnemyManager* enemyManager;
	BlockManager* blockManager;
	WarpManager* warpManager;

};

