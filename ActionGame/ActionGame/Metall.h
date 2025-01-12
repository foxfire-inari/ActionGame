#pragma once
#include "Enemy.h"


class Metall : public Enemy
{
public:
	Metall(BaseScene* baseScene, BulletManager* bulletManager,
		BaseObject* plBase, F_Vec2 pos, int knd);
	~Metall();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

private:

	/// <summary>
	/// 弾を撃つ方向
	/// 左右どっちを向いてるか
	/// </summary>
	int shotAngle;

	/// <summary>
	/// 状態を切り替えるカウンター
	/// </summary>
	int moveCount;

	/// <summary>
	/// 無敵かどうか
	/// </summary>
	bool isInvincible;

	// --------ステートごとのアップデート

	void UpdateIdle();		//待機状態（無敵）
	void UpdateAttack();	//攻撃
	void UpdateRun();		//移動
	void UpdateFall();		//落下
	void UpdateDamage();	//ダメージ
	void UpdateDeath();		//死亡

	// --------ステートごとのスタート

	void StartIdle();
	void StartAttack();
	void StartRun();
	void StartFall();
	void StartDamage();
	void StartDeath();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 弾の方向を定める関数
	/// </summary>
	/// <param name="genVec">弾の生成速度（参照渡し）</param>
	/// <param name="rad">発射角度</param>
	void SetGenVec(F_Vec2& genVec, float rad);
};

