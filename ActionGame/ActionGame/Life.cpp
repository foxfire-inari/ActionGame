#include "Life.h"

const int Life::DEATH_FRAME = 5;


Life::Life(int _hp)
	:hp{_hp}
	,isDeath{false}
{
}

Life::~Life()
{
}
