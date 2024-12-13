#pragma once
#include"Common.h"
#include"BaseScene.h"

#include"CollisionData.h"

/// <summary>
/// 全てのオブジェクトの継承元
/// </summary>
class BaseObject
{
public:
	BaseObject(BaseScene* _baseScene,F_Vec2 _pos, F_Vec2 _vel,
		int _top,int _under,int _left,int _right,
		int _tag);
	~BaseObject();
	virtual void Start() {}
	virtual void Update() {};
	virtual void Draw() {};

	/// <summary>
	/// 自分の座標を返す
	/// </summary>
	/// <returns></returns>
	F_Vec2 GetPosition()const { return position; }

	/// <summary>
	/// 自分の座標をセット
	/// 座標の初期化やめり込みを直すのに使う
	/// </summary>
	/// <param name="_pos"></param>
	void SetPosition(F_Vec2 _pos) { position = _pos; }

	/// <summary>
	/// 座標を足す（移動させる）
	/// </summary>
	/// <param name="_pos"></param>
	void AddPosition(F_Vec2 _pos) { position += _pos; }

	/// <summary>
	/// 自分の速度を返す
	/// </summary>
	/// <returns></returns>
	F_Vec2 GetVelocity()const { return velocity; }

	/// <summary>
	/// 自分の速度をセット
	/// </summary>
	/// <param name="_vel"></param>
	void SetVelocity(F_Vec2 _vel) { velocity = _vel; }

	/// <summary>
	/// 自分のタグを返す
	/// </summary>
	/// <returns></returns>
	int GetTag()const { return tag; }

	CollisionData* GetCollisionPos() { return ColData; }

	/// <summary>
	/// ゲーム内に1つだけのオブジェクトを
	/// 次のシーンに引き継がせる
	/// </summary>
	/// <param name="_baseScene">次のシーン</param>
	/// <param name="isOneObject">プレイヤー等のシーンに1つだけのオブジェクトか</param>
	void SetNewScene(BaseScene* _baseScene, bool isOneObject = false);

	/// <summary>
	/// オブジェクトを判別するタグ
	/// </summary>
	enum E_TAG
	{
		PLAYER,				//プレイヤー
		BLOCK,				//ブロック
		ENEMY,				//敵
		ITEM,				//アイテム
		EFFECT,				//エフェクト
	};

protected:

	/// <summary>
	/// 所属しているシーンを返す
	/// </summary>
	/// <returns>BaseSceneクラスのポインタ</returns>
	BaseScene* GetBaseScene()const { return baseScene; }


	/// <summary>
	/// オブジェクトの中心座標
	/// </summary>
	F_Vec2 position;

	/// <summary>
	/// 速度
	/// </summary>
	F_Vec2 velocity;

	/// <summary>
	/// 当たり判定の情報
	/// </summary>
	CollisionData* ColData;

	/// <summary>
	/// オブジェクト判別用のタグ
	/// </summary>
	int tag;
private:
	/// <summary>
	/// シーンのリストに自身を登録するときに必要
	/// </summary>
	BaseScene* baseScene;
};
