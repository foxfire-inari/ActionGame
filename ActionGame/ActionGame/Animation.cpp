#include "Animation.h"

Animation::Animation()
	:animCount{ 0 }
{
}

Animation::~Animation()
{
}

int Animation::GetAngleImage(int left, int right, int moveAngle)
{
	int angleNum = 0;
	//moveAngle��0��菬�����Ȃ獶�������Ă邽��left��������
	angleNum = moveAngle < 0 ? left : right;

	return angleNum;
}

int Animation::GetAnimation(int allFrame, int oneFrame)
{
	//animFrame��0�̏ꍇ��
	if (allFrame <= 0)return 0;
	return static_cast<int>(animCount) % allFrame / oneFrame;
}

void Animation::AddAnimCount(float addCount)
{
	animCount += addCount;
}

void Animation::SetAnimCount(float setCount)
{
	animCount = setCount;
}
