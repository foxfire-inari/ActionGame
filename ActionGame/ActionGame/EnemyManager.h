#pragma once
#include "BaseManager.h"
class Enemy;
class Life;
class CollisionData;

class EnemyManager : public BaseManager
{
public:
	EnemyManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
	~EnemyManager();
	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// プレイヤーと敵が当たっていたらダメージを返す
	/// 当たっていなかったら－1
	/// </summary>
	/// <param name="collInfo">プレイヤーの当たり判定情報</param>
	/// <param name="damageVel">ダメージで飛ぶ方向</param>
	/// <returns></returns>
	int CheckPlayerHit(CollisionData* colData, int& damageVel);

private:
	std::list<Enemy*> enemyList;
	std::vector<std::vector<std::string>> information;//生成情報を格納

	/// <summary>
	/// プレイヤーに当たったか
	/// </summary>
	/// <param name="objcol">判定するオブジェクトのコリジョンデータ</param>
	/// <param name="listcol">リスト内のコリジョンデータ</param>
	/// <returns></returns>
	bool IsHitPlayer(CollisionData* objCol, CollisionData* listCol);


	/// <summary>
	/// 画面内に存在するか
	/// </summary>
	/// <param name="_camDif">カメラの座標</param>
	/// <param name="_listObj">リスト内の判定するオブジェクト</param>
	/// <returns></returns>
	bool IsInCamera(F_Vec2 _camDif, Enemy* _listObj);

	/// <summary>
	/// コリジョンの現在の座標を取得
	/// </summary>
	/// <param name="colData">コリジョンデータ</param>
	/// <param name="pos">持ち主の座標</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

	/// <summary>
	/// このマネージャーに所属しているオブジェクト達の
	/// 所属しているシーンも設定しなおす
	/// </summary>
	/// <param name="_baseScene">新しく所属するシーン</param>
	void SetObjectNewScene(BaseScene* _baseScene)override;



};

