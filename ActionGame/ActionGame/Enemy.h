#pragma once
#include "Chara.h"

/// <summary>
/// 敵の継承元
/// </summary>
class Enemy : public Chara
{
public:
	Enemy(BaseScene* baseScene, BulletManager* _bulletManager, BaseObject* _plBase,
		F_Vec2 pos, int _knd, int hp, float top, float under, float left, float right);
	~Enemy();
	virtual void Update()override {};
	virtual void Draw(F_Vec2 _camDif)override {};

	/// <summary>
	/// 敵の種類
	/// </summary>
	enum E_ENEMY_KND
	{
		TERRY = 0,
		METALL,

	};

	/// <summary>
	/// ボスの種類
	/// </summary>
	enum E_BOSS_KND
	{
		BIG_CHICKEN = 10000,
	};

	/// <summary>
	/// Lifeのポインタを返す
	/// constだと外部から値を変更されない
	/// </summary>
	/// <returns></returns>
	const Life* GetLifePtr()const { return life; }

	/// <summary>
	/// コリジョンを返す
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData()const { return collisionData; }

	/// <summary>
	/// パワーを返す
	/// </summary>
	/// <returns></returns>
	int GetBodyPower()const { return bodyPower; }

	/// <summary>
	/// 自身の種類を返す
	/// </summary>
	/// <returns></returns>
	int GetKnd()const { return knd; }

	/// <summary>
	/// フラグが立っているか返す
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// フラグをセット
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }


protected:

	/// <summary>
	/// 弾との当たり判定
	/// </summary>
	BulletManager* bulletManager;

	/// <summary>
	/// プレイヤーのBaseObject型のポインタ
	/// </summary>
	BaseObject* plBase;

	/// <summary>
	/// 直接触れたときのパワー
	/// </summary>
	int bodyPower;

	/// <summary>
	/// 自身の種類
	/// </summary>
	int knd;

	/// <summary>
	/// 消滅までのカウント
	/// </summary>
	int deathCount;

	/// <summary>
	/// 画面内にいるかどうか
	/// </summary>
	bool flag;

};

