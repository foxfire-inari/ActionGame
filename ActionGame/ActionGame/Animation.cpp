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
	//moveAngle‚ª0‚æ‚è¬‚³‚¢‚È‚ç¶‚ğŒü‚¢‚Ä‚é‚½‚ßleft‚ğ‘ã“ü‚·‚é
	angleNum = moveAngle < 0 ? left : right;

	return angleNum;
}

int Animation::GetAnimation(int allFrame, int oneFrame)
{
	//animFrame‚ª0‚Ìê‡‚Í
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
