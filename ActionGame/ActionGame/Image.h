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
	/// プレイヤーが攻撃するときの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetPlayerAttackH(int index)const;

	/// <summary>
	/// プレイヤーが空中にいるときの画像を変えす
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetplayerFallH(int index)const;


	/// <summary>
	/// テリーの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetTerryH(int index)const;

	/// <summary>
	/// ブロックの画像を返す
	/// </summary>
	/// <param name="index">インデックス</param>
	/// <returns></returns>
	int GetBlockH(int index)const;

private:
	
	//プレイヤーの画像

	//待機用
	std::array<int, 2> playerIdleH;
	//歩行用
	std::array<int, 8> playerWalkH;
	//攻撃用
	std::array<int, 8> playerAttackH;
	//空中にいるとき用
	std::array<int, 2> playerFallH;

	//テリーの画像
	//テリーは回転するだけなのでこれだけ
	std::array<int ,8> terryH;

	//ブロックの画像
	//ブロックの数だけ保存
	std::array<int, 64> BlockH;

};

