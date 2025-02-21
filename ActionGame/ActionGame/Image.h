#pragma once
#include "Singleton.h"

/// <summary>
/// 全ての画像をもつシングルトンクラス
/// </summary>
class Image : public Singleton<Image>
{
public:
	Image();
	~Image();

	/// <summary>
	/// プレイヤーが待機しているときの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetPlayerIdleH(int index)const;

	/// <summary>
	/// プレイヤーが歩いているときの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetPlayerWalkH(int index)const;

	/// <summary>
	/// プレイヤーが空中にいるときの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetPlayerFallH(int index)const;

	/// <summary>
	/// プレイヤーがダメージを受けた時の画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetPlayerDamageH(int index)const;


	/// <summary>
	/// テリーの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetTerryH(int index)const;


	/// <summary>
	/// メットールの待機画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetMetallIdleH(int index)const;

	/// <summary>
	/// メットールの走ってる画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetMetallRunH(int index)const;

	/// <summary>
	/// メットールの攻撃開始時の画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetMetallUpH(int index)const;

	/// <summary>
	/// メタルマンの待機時の画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetMetalManIdleH(int index)const;

	/// <summary>
	/// メタルマンが空中にいるときの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetMetalManJumpH(int index)const;

	/// <summary>
	/// 弾の画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetBulletH(int index)const;


	/// <summary>
	/// ブロックの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetBlockH(int index)const;

	/// <summary>
	/// ワープの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetWarpH(int index)const;

	/// <summary>
	/// ワープ中の画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetWaveH(int index)const;

	/// <summary>
	/// エフェクトの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetEffectH(int index)const;

	/// <summary>
	/// 空の画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetSkyH(int index)const;

	/// <summary>
	/// タイトル画像を返す
	/// </summary>
	/// <returns></returns>
	int GetTitleH()const { return titleH; }

	/// <summary>
	/// タイトル画面の地面を返す
	/// </summary>
	/// <returns></returns>
	int GetTitleGroundH()const { return titleGroundH; }

	/// <summary>
	/// タイトル画面の背景を返す
	/// </summary>
	/// <returns></returns>
	int GetTitleSkyH()const { return titleSkyH; }

	/// <summary>
	/// ゲームオーバー画像を返す
	/// </summary>
	/// <returns></returns>
	int GetGameOverH()const { return gameOverH; }



private:
	
	//ーーーープレイヤーの画像
	//待機用
	std::array<int, 2> playerIdleH;
	//歩行用
	std::array<int, 8> playerWalkH;
	//空中にいるとき用
	std::array<int, 2> playerFallH;
	//ダメージ用
	std::array<int, 2> playerDamageH;

	//ーーーーテリーの画像
	std::array<int ,4> terryH;

	//ーーーーメットールの画像
	//待機用
	std::array<int, 2> metallIdleH;
	//歩行用
	std::array<int, 4> metallRunH;
	//攻撃開始用
	std::array<int, 4> metallUpH;

	//ーーーーメタルマンの画像
	//待機用
	std::array<int, 8> metalManIdleH;
	//空中にいるとき用
	std::array<int, 2> metalManJumpH;

	//ーーーー弾の画像
	//弾の数だけ保存
	std::array<int, 3> bulletH;

	//ーーーーブロックの画像
	//ブロックの数だけ保存
	std::array<int, 2> blockH;

	//ーーーーワープの画像
	//ワープオブジェクト用
	std::array<int, 4> warpH;
	//ワープ中の画像
	std::array<int, 4> waveH;

	//ーーーー汎用エフェクト
	//キャラクターの消滅用
	std::array<int, 4> effectH;


	//ーーーー1枚絵
	// 	//空の画像
	std::array<int, 2> skyH;
	//タイトル画面
	int titleH;
	//タイトル画面の地面
	int titleGroundH;
	//タイトル画面の背景
	int titleSkyH;
	//ゲームオーバー（一枚だけなのでint型）
	int gameOverH;
};

