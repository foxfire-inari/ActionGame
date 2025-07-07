#include "Fall.h"

namespace
{
	static const float VEL_Y = 0.2;
}

Fall::Fall()
	:isOnGround{ false }
	, oldIsOnGround{ false }
{
}

Fall::~Fall()
{
}

void Fall::SetIsOnGround(bool _isOnGround)
{
	//1フレーム前に地面に乗ってたかをセット
	oldIsOnGround = isOnGround;

	//今地面に乗ってるかをセット
	isOnGround = _isOnGround;
}

bool Fall::FallStart(F_Vec2& vel)
{
	if (isOnGround || !oldIsOnGround)return false;

	// オブジェクトから下りた時にかかっていた
	// 重力(下方向のベクトル)を初期化
	vel.y = VEL_Y;
	return true;
}
