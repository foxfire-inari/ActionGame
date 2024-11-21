#include "Gravity.h"
#include "common.h"

/// <summary>
/// �d�͂ɂ�闎�����x�̍ő�l
/// </summary>
const float Gravity::MAX_GRAVITY = 12.0f;

/// <summary>
/// 1�t���[�����Ƃ̏d�͉����x�i60�t���[���ōő呬�x�j
/// </summary>
const float Gravity::GRAVITY = Gravity::MAX_GRAVITY / 60.0f;

Gravity::Gravity()
{
	//Gravity�̃R���X�g���N�^
}

Gravity::~Gravity()
{
	//Gravity�̃f�X�g���N�^
}

void Gravity::AddGravity(float& velocityY)
{
	velocityY += GRAVITY;
	velocityY = min(velocityY, MAX_GRAVITY);
}
