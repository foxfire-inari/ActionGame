#include "Animation.h"

Animation::Animation()
	:animCount{ 0 }
{
}

Animation::~Animation()
{
}

int Animation::GetAngleImage(int right, int left, int moveAngle)
{
	//moveAngle��0��菬�����Ȃ�E�������Ă邽��right��������

	return moveAngle < 0 ? right : left;
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

void Animation::SetAnimNum(int setNum)
{
	animNum = setNum;

}
