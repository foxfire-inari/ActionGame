#include "Chara.h"



Chara::Chara(BaseScene* baseScene,
	int top, int under, int left, int right,
	int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},top,under,left,right ,tag}
{
	//Charaのコンストラクタ
	fall = new Fall{};
	gravity = new Gravity{};
	positionSetter = new PositionSetter{};
	state = new State{};

	SetPosition(F_Vec2{ 100,100 });

}

Chara::~Chara()
{
}


