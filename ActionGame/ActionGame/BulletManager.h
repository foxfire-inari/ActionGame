#pragma once
#include"BaseManager.h"
class Bullet;
class Enemy;
class CollisionData;

class BulletManager : public BaseManager
{
public:
	BulletManager(BaseScene* baseScene);
	~BulletManager();

	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// 弾を生成
	/// </summary>
	/// <param name="pos">発射地点</param>
	/// <param name="vec">発射方向</param>
	/// <param name="_power">ダメージ量</param>
	void SetState(F_Vec2 pos, F_Vec2 vec);

	/// <summary>
	/// 敵に当たっているか
	/// </summary>
	/// <param name="enemyPtr">敵のポインタ</param>
	/// <param name="colData">敵の当たり判定情報</param>
	/// <returns>与えるダメージ</returns>
	int HitCheckEnemy(Enemy* enemyPtr,
		CollisionData* colData);

	/// <summary>
	/// 近くにあるかの判定
	/// </summary>
	/// <param name="objPos">判定の中心になる座標</param>
	/// <param name="listPos">リスト内の判定する座標</param>
	/// <param name="dif"></param>
	/// <returns></returns>
	bool IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif);

private:

	/// <summary>
	/// 対象に当たったか
	/// </summary>
	/// <param name="objCol">対象のコリジョン</param>
	/// <param name="listCol">リスト内のオブジェクトのコリジョン</param>
	/// <returns></returns>
	bool IsHitObject(CollisionData* objCol, CollisionData* listCol);

	/// <summary>
	/// 画面内に存在するか
	/// </summary>
	/// <param name="_camDif">カメラの座標</param>
	/// <param name="_listObj">リスト内の判定するオブジェクト</param>
	/// <returns></returns>
	bool IsInCamera(F_Vec2 _camDif, Bullet* _listObj);

	/// <summary>
	/// コリジョンの現在の座標を取得
	/// </summary>
	/// <param name="colData">コリジョンデータ</param>
	/// <param name="pos">持ち主の座標</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

	std::list<Bullet*> bulletList;

	void SetObjectNewScene(BaseScene* _baseScene)override;

};

