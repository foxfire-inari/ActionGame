#pragma once
#include "Enemy.h"

class MetalMan : public Enemy
{
public:
	MetalMan(BaseScene* baseScene, 
		BulletManager* bulletManager, EffectManager* _effectManager,
		BaseObject* plBase, F_Vec2 pos, int knd);
	~MetalMan();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

private:

	int imageH;			// 画像

	int moveKnd;		// 行動の種類
	int moveAngle;		// 左右どっちを向いてるか
	int moveCount;		// 状態を切り替えるカウンター

	float shotAngle;	// 弾を撃つ方向

	int attackNum;		// 攻撃回数を管理
	int attackCount;	// 攻撃回数をカウント

	int damageCount;	// ダメージを受けてからのカウンター

	bool isInvincible;	// 無敵かどうか

	// --------ステートごとのアップデート

	void UpdateIdle();		//待機状態
	void UpdateJump();		//反対側に大ジャンプ＆一回攻撃
	void UpdateAttack();	//大中小ジャンプして＆321回攻撃
	void UpdateDeath();		//死亡

	// --------ステートごとのスタート

	void IdleStart();
	void JumpStart();
	void AttackStart();
	void DamageStart();
	void DeathStart();

	/// <summary>
	/// 無敵常態を一定時間で解除
	/// </summary>
	void Invincible();

	/// <summary>
	/// プレイヤーとの距離が探知範囲内ならtrue
	/// </summary>
	/// <returns></returns>
	bool IsNearDistance();

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

	/// <summary>
	/// moveAngleセットする
	/// </summary>
	void SetMoveAngle();

	/// <summary>
	/// プレイヤーが攻撃入力をしていたらtrue
	/// ○○かつ～～で使うと長いから関数にして省略
	/// </summary>
	/// <returns></returns>
	bool GetAttackKey();

	//行動の種類
	enum E_MOVE_KND
	{
		LARGE,			//大ジャンプ
		MEDIUM,			//中ジャンプ
		SMALL,			//小ジャンプ
		JUMP_RAND_MAX,	//ランダム用の最大値

		OVER,			//逆側に行くジャンプ
	};
};

