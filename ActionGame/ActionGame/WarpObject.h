#pragma once
#include "CollisionObject.h"
#include "Animation.h"

/// <summary>
/// マップ移動をするオブジェクト
/// プレイヤーとの判定は取りたいのでCollisionObjectを継承
/// </summary>
class WarpObject : public CollisionObject
{
public:
	WarpObject(BaseScene* baseScene,F_Vec2 pos ,std::string _nextMapName);
	~WarpObject();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// 次のマップの名前を返す
	/// </summary>
	/// <returns></returns>
	std::string GetNextMapName()const { return nextMapName; }

private:

	/// <summary>
	/// ゲートの揺らいでる感を出すため
	/// </summary>
	Animation* animation;

	/// <summary>
	/// 次に読み込むCsvファイルの名前
	/// </summary>
	std::string nextMapName;

	/// <summary>
	/// 画像
	/// </summary>
	int imageH;
};

