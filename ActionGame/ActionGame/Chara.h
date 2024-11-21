#pragma once
#include"BaseObject.h"
#include"State.h"
#include"Gravity.h"
#include"PositionSetter.h"

/// <summary>
/// 全てのキャラの継承元
/// </summary>
class Chara : public BaseObject
{
public:
	Chara(BaseScene* baseScene,
		int top, int under, int left, int right,
		int tag);
	~Chara();
	virtual void Update()override {}
	virtual void Draw()override {}

	/// <summary>
	/// 実装した機能のテスト用
	/// </summary>
	void TestUpdate();
protected:

	/// <summary>
	/// ステート
	/// </summary>
	State* state;
	/// <summary>
	/// 重力
	/// </summary>
	Gravity* gravity;

	PositionSetter* positionSetter;


};

/// ＜必要な要素＞
/// 
/// 立っているかの判定
/// 体力
/// 押し出し等の移動処理
/// 
/// (画像は各キャラクターで実装する)
///