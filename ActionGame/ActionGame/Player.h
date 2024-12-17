#pragma once
#include "Chara.h"


/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public Chara
{
public:
	Player(BaseScene* baseScene);
	~Player();

	 /// <summary>
	 /// コンストラクタ以外で最初に一回呼ぶ処理
	 /// </summary>
	void Start()override;

	/// <summary>
	/// ゲームシーンでのアップデート
	/// </summary>
	void Update()override;

	/// <summary>
	/// ゲームシーンでの描画
	/// </summary>
	void Draw()override;

	/// <summary>
	/// ゲームシーンでのUI描画
	/// </summary>
	void DrawUI();
	void DrawData();

	/// <summary>
	/// ゲームオーバーかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsGameOver()const { return isGameOver; }

private:

	int inputRight;	//右方向への入力量
	int inputDown;	//下方向への入力量

	float inputAngle;	//入力角度
	float moveSpeed;	//移動速度
	int moveAngle;		//進行方向

	/// <summary>
	/// 無敵か
	/// </summary>
	bool isInvincible;

	/// <summary>
	/// ゲームオーバーかどうか
	/// </summary>
	bool isGameOver;

	// --------ステートごとのアップデート

	/// <summary>
	/// 待機状態
	/// </summary>
	void UpdateIdle();

	/// <summary>
	/// 歩行状態
	/// </summary>
	void UpdateRun();

	/// <summary>
	/// 空中にいる状態
	/// </summary>
	void UpdateJump();

	/// <summary>
	/// 攻撃状態
	/// </summary>
	void UpdateAttack();

	/// <summary>
	/// 被ダメージ状態
	/// </summary>
	void UpdateDamage();

	/// <summary>
	/// 死亡状態
	/// </summary>
	void UpdateDeath();

	// --------ステートごとのスタート

	/// <summary>
	/// ジャンプ開始
	/// </summary>
	void JumpStart();

	/// <summary>
	/// ダメージ開始
	/// </summary>
	void DamageStart();

	/// <summary>
	/// 死亡開始
	/// </summary>
	void DeathStart();

	/// <summary>
	/// 無敵常態を一定時間で解除
	/// </summary>
	void Invincible();

	/// <summary>
	/// 地面から飛び出して落ちていたら
	/// velocity.yを0にしてジャンプに移行
	/// </summary>
	void FallStart();

	/// <summary>
	/// 走り、歩き開始
	/// </summary>
	void StartRun();

	/// <summary>
	/// 攻撃開始
	/// </summary>
	void AttackStart();

	/// <summary>
	/// 入力方向とプレイヤーの向きのセット
	/// </summary>
	void SetInputAngle();

	/// <summary>
	/// 移動していたらtrueを返す加速処理
	/// </summary>
	/// <param name="speed"></param>
	/// <returns></returns>
	bool Move(float speed);

	/// <summary>
	/// 減速
	/// </summary>
	void MoveDeceletation();

	/// <summary>
	/// アイテムの取得
	/// </summary>
	void GetItem();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// 現在のステータスを出力
	/// </summary>
	void SetStatus();

	/// <summary>
	/// 今のシーンのマネージャーを取得
	/// </summary>
	void GetNowSceneManager();
};
