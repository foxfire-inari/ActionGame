#pragma once
#include "BaseManager.h"
class WarpObject;
class CollisionData;
class BaseObject;

/// <summary>
/// 全てのワープオフジェクトを管理するクラス
/// 押し出し判定は取らないのでCollisionManagerには登録しない
/// </summary>
class WarpManager : public BaseManager
{
public:
	WarpManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
	~WarpManager();
	void Update() override;
	void Draw(F_Vec2 _camVec) override;

	/// <summary>
	/// プレイヤーとWarpObjectが接触していたら
	/// 次のマップの名前を返す
	/// そうでない場合は""を返す
	/// </summary>
	/// <param name="obj">プレイヤ―の</param>
	/// <param name="objCol"></param>
	/// <returns></returns>
	std::string GetNextMapName(BaseObject* obj, CollisionData* objCol);

private:

	std::vector<WarpObject*> warpList;

	bool IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif);

	/// <summary>
	/// コリジョンの現在の座標を取得
	/// </summary>
	/// <param name="colData">コリジョンデータ</param>
	/// <param name="pos">持ち主の座標</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

	/// <summary>
	/// ブロックと重なっているか
	/// </summary>
	/// <param name="objcol">判定するオブジェクトのコリジョンデータ</param>
	/// <param name="listcol">リスト内のコリジョンデータ</param>
	/// <returns></returns>
	bool IsInBlock(CollisionData* objCol, CollisionData* listCol);


	void SetObjectNewScene(BaseScene* _baseScene)override;

};

