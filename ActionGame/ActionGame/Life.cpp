#include "Life.h"

const int Life::DEATH_FRAME = 1;
const int Life::DEATH_EFFECT_FRAME = 2;


Life::Life(int _hp)
	:hp{_hp}
	,isDeath{false}
{
}

Life::~Life()
{
}
