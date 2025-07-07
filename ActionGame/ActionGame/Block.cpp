#include "Block.h"

namespace
{
	//中心から描画した時のサイズ
	static const float HALF_DRAW_BOX = BLOCK_SIZE / 2;
}

Block::Block(BaseScene* baseScene, F_Vec2 pos,int knd)
	:CollisionObject{ baseScene,pos,BaseObject::E_TAG::BLOCK }
	, imageH{ knd }
{


}

Block::~Block()
{
}

void Block::Update()
{
}

void Block::Draw(F_Vec2 _camDif)
{
	F_Vec2 drawpos = GetPosition();

	DrawExtendGraph
	(
		drawpos.x - _camDif.x - HALF_DRAW_BOX,
		drawpos.y - _camDif.y - HALF_DRAW_BOX,
		drawpos.x - _camDif.x + HALF_DRAW_BOX,
		drawpos.y - _camDif.y + HALF_DRAW_BOX,
		imageH,
		true
	);
}
