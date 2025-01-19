#pragma once
#include"Singleton.h"

/// <summary>
/// ゲームで扱うキー
/// </summary>
enum E_KEY
{
	UP = 0,		//0で固定
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	ATTACK,
	START,
	E_KEY_MAX
};

/// <summary>
/// キー入力を処理するシングルトンクラス
/// </summary>
class KeyControlle : public Singleton<KeyControlle>
{
public:

	KeyControlle();
	~KeyControlle();
	void Update();

	/// <summary>
	/// 押されているフレーム数を取得
	/// </summary>
	/// <param name="keyCode">E_KEY</param>
	/// <returns></returns>
	int GetPressingFrame(int keyCode);

	/// <summary>
	/// このフレームで押しているかの判定
	/// </summary>
	/// <param name="keyCode">E_KEY</param>
	/// <returns></returns>
	bool GetNowPressing(int keyCode);

	/// <summary>
	/// このフレームで離しているかの判定
	/// </summary>
	/// <param name="keyCode">E_KEY</param>
	/// <returns></returns>
	bool GetNowReleasing(int keyCode);

private:
	/// <summary>
	/// 入力されているキーとそのフレーム数
	/// </summary>
	std::array<int, E_KEY_MAX> reInputValue;
	/// <summary>
	/// 1フレーム前に入力されていたキーとそのフレーム数
	/// </summary>
	std::array<int, E_KEY_MAX> oldReInputValue;

	/// <summary>
	/// GetHitKeyStateAllで使うから256
	/// </summary>
	static const int KEY_NUM = 256;
	/// <summary>
	/// キーボードの状態
	/// </summary>
	std::array<int, KEY_NUM> keyboard = {};
	/// <summary>
	/// キーコンフィグで割り当てられたキーを保存
	/// </summary>
	std::array<int, E_KEY_MAX> keyboardID = {};


};
