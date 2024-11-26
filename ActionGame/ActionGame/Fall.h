#pragma once
#include"Common.h"

class Fall
{
public:
	Fall();
	~Fall();

	/// <summary>
	/// 地面に乗ってるかをセット
	/// </summary>
	/// <param name="_isOnGround">乗ってるか</param>
	void SetIsOnGround(bool _isOnGround);

	/// <summary>
	/// 落下を始めるかをセット
	/// </summary>
	/// <param name="vel">velocityの参照渡し</param>
	/// <returns></returns>
	bool FallStart(F_Vec2& vel);

	/// <summary>
	/// 地面に乗ってるかどうか
	/// </summary>
	/// <returns></returns>
	bool GetIsOnGround()const { return isOnGround; }

	/// <summary>
	/// 1フレーム前に地面乗ってたかどうか
	/// </summary>
	/// <returns></returns>
	bool GetOldIsOnGround()const { return oldIsOnGround; }
private:

	/// <summary>
	/// 地面に乗ってるかどうか
	/// </summary>
	bool isOnGround;

	/// <summary>
	/// 1フレーム前に地面に乗ってたかどうか
	/// </summary>
	bool oldIsOnGround;

};

