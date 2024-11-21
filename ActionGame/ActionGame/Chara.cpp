#include "Chara.h"



Chara::Chara(BaseScene* baseScene,
	int top, int under, int left, int right,
	int tag)
	:BaseObject{ baseScene, F_Vec2{0,0},F_Vec2{0,0},top,under,left,right ,tag}
{
	//Charaのコンストラクタ
	gravity = new Gravity{};
	positionSetter = new PositionSetter{};

	SetPosition(F_Vec2{ 100,100 });

}

Chara::~Chara()
{
}

void Chara::TestUpdate()
{
	gravity->AddGravity(velocity.y);

	positionSetter->UpdatePos(this);

	F_Vec2 drawpos = GetPosition();
	DrawBox
	(
		drawpos.x + CollData->GetLeft(),
		drawpos.y + CollData->GetTop(),
		drawpos.x + CollData->GetRight(),
		drawpos.y + CollData->GetUnder(),
		GetColor(255, 255, 255),
		true
	);
	DrawFormatString(50, 50, GetColor(255, 255, 255),
		"velocity:%f,%f",GetVelocity().x, GetVelocity().y);

}
