#pragma once
#include"Common.h"
class BaseObject;
class Fall;
class CollisionData;

class CollisionManager;


/// <summary>
/// キャラクターの移動に関係する処理を全て行う
/// </summary>
class PositionSetter
{
public:
	PositionSetter();
	~PositionSetter();

	/// <summary>
	/// 座標の更新(ブロックとの干渉有り)
	/// </summary>
	/// <param name="me">移動するオブジェクトのポインタ</param>
	/// <param name="colData">オブジェクトのコリジョンデータ</param>
	/// <param name="collisionManager">このシーンのコリジョンマネージャー</param>
	/// <param name="fall">落下してるか</param>
	void UpdatePos(BaseObject* me, CollisionData* colData, CollisionManager* collisionManager, Fall* fall);

	/// <summary>
	/// 座標の更新(ブロックとの干渉無し)
	/// </summary>
	/// <param name="me">移動するオブジェクトのポインタ</param>
	void UpdateNonInterPos(BaseObject* me);
};

