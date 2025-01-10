#pragma once

class Animation
{
public:
	Animation();
	~Animation();

	/// <summary>
	/// アニメーションを始める位置を向きによって決める関数
	/// </summary>
	/// <param name="right">右向きの時の開始位置</param>
	/// <param name="left">左向きの時の開始位置</param>
	/// <param name="moveAngle">向いている向き</param>
	/// <returns></returns>
	int GetAngleImage(int right, int left, int moveAngle);

	/// <summary>
	/// アニメーションの現在のフレーム数を返す
	/// </summary>
	/// <param name="animFrame">アニメーションの合計のフレーム数</param>
	/// <param name="oneFrame">一枚ごとのフレーム数</param>
	/// <returns></returns>
	int GetAnimation(int allFrame, int oneFrame);

	/// <summary>
	/// アニメーションのカウントを足す
	/// </summary>
	/// <param name="addCount">足すカウント数</param>
	void AddAnimCount(float addCount);

	/// <summary>
	/// アニメーションのカウントを固定する
	/// （Attackなどで初期化する用）
	/// </summary>
	/// <param name="setCount">固定する値</param>
	void SetAnimCount(float setCount);

private:

	/// <summary>
	/// アニメーションのカウンター
	/// </summary>
	float animCount;

};

