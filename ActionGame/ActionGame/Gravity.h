#pragma once

/// <summary>
/// 移動量に重力を追加するクラス
/// </summary>
class Gravity
{
public:
	Gravity();
	~Gravity();

	/// <summary>
	/// Y軸の加速度に重力加速度分追加する
	/// </summary>
	/// <param name="velocityY">Y軸の加速度（参照渡し）</param>
	void AddGravity(float& velocityY);

private:

	static const float MAX_GRAVITY;
	static const float GRAVITY;
};

