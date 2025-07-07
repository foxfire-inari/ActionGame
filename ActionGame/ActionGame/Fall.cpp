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
	//1�t���[���O�ɒn�ʂɏ���Ă������Z�b�g
	oldIsOnGround = isOnGround;

	//���n�ʂɏ���Ă邩���Z�b�g
	isOnGround = _isOnGround;
}

bool Fall::FallStart(F_Vec2& vel)
{
	if (isOnGround || !oldIsOnGround)return false;

	// �I�u�W�F�N�g���牺�肽���ɂ������Ă���
	// �d��(�������̃x�N�g��)��������
	vel.y = VEL_Y;
	return true;
}
