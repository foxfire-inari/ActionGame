#pragma once
#include"BaseManager.h"
class Bullet;
class Chara;
class CollisionData;

namespace
{
	//各弾の最大数
	static const int MAX_BULLET = 3;
}

class BulletManager : public BaseManager
{
public:
	BulletManager(BaseScene* baseScene);
	~BulletManager();

	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// BulletManagerに弾を追加する
	/// </summary>
	/// <param name="knd"></param>
	void AddBullet(int knd);

	/// <summary>
	/// 弾のフラグが必要数空いているか
	/// 主に敵などの絶対に弾を撃ってほしいオブジェクトが使う
	/// </summary>
	/// <param name="knd">弾の種類</param>
	/// <param name="minBullet">必要な数</param>
	/// <returns></returns>
	bool GetCanShot(int knd, int minBullet);

	/// <summary>
	/// 弾にステータスを入れて起動
	/// </summary>
	/// <param name="pos">発射地点</param>
	/// <param name="vec">発射方向</param>
	/// <param name="knd">弾の種類</param>
	/// <param name="owner">持ち主</param>
	void SetState(F_Vec2 pos, F_Vec2 vec, int knd, int owner);

	/// <summary>
	/// 敵に当たっているか
	/// </summary>
	/// <param name="charaPtr">敵のポインタ</param>
	/// <param name="colData">敵の当たり判定情報</param>
	/// <returns>与えるダメージ</returns>
	int HitCheckChara(Chara* charaPtr,CollisionData* colData);

	/// <summary>
	/// 近くにあるかの判定
	/// </summary>
	/// <param name="objPos">判定の中心になる座標</param>
	/// <param name="listPos">リスト内の判定する座標</param>
	/// <param name="dif"></param>
	/// <returns></returns>
	bool IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif);

	/// <summary>
	/// 弾の持ち主の判別用
	/// BaseObject::E_TAGと同じ並びにしてint型で比較できるようにした
	/// </summary>
	enum BULLET_OWNER
	{
		PLAYER,
		ENEMY,

		OWNER_MAX
	};

	/// <summary>
	// 弾の種類
	/// </summary>
	enum BULLET_KND
	{
		NORMAL,		//通常弾
		BALL,		//敵の丸い弾
		METAL,		//メタルブレード

		TYPE_MAX
	};

private:

	/// <summary>
	/// bulletListに弾を追加する
	/// </summary>
	template<class T>
	void CreateBullet(int knd)
	{
		//テンプレートで好きなBulletクラスを追加できるようにした
		for (int i = 0; i < MAX_BULLET; i++)
		{
			Bullet* bullet = new T(GetBaseScene(), knd);
			bulletList.emplace_back(bullet);
		}
	}

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

