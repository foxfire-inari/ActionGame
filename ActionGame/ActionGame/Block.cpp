#include "Block.h"




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
		drawpos.x - _camDif.x - BLOCK_SIZE / 2,
		drawpos.y - _camDif.y - BLOCK_SIZE / 2,
		drawpos.x - _camDif.x + BLOCK_SIZE / 2,
		drawpos.y - _camDif.y + BLOCK_SIZE / 2,
		imageH,
		true
	);
}
