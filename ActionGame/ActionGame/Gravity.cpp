#include "Gravity.h"
#include "common.h"

/// <summary>
/// 重力による落下速度の最大値
/// </summary>
const float Gravity::MAX_GRAVITY = 12.0f;

/// <summary>
/// 1フレームごとの重力加速度（60フレームで最大速度）
/// </summary>
const float Gravity::GRAVITY = Gravity::MAX_GRAVITY / 60.0f;

Gravity::Gravity()
{
	//Gravityのコンストラクタ
}

Gravity::~Gravity()
{
	//Gravityのデストラクタ
}

void Gravity::AddGravity(float& velocityY)
{
	velocityY += GRAVITY;
	velocityY = min(velocityY, MAX_GRAVITY);
}
