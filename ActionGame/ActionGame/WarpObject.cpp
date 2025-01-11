#include "WarpObject.h"
#include "Image.h"

namespace
{
	//コリジョン
	static const float COL_TOP   = -BLOCK_SIZE / 2;
	static const float COL_UNDER =  BLOCK_SIZE / 2;
	static const float COL_LEFT  = -BLOCK_SIZE / 14;	//ゲートの中に入った感を出したいので横判定を狭くする
	static const float COL_RIGHT =  BLOCK_SIZE / 14;	//ゲートの中に入った感を出したいので横判定を狭くする

	//画像
	static const float IMG_TOP   =  COL_TOP;
	static const float IMG_UNDER =  COL_UNDER;
	static const float IMG_LEFT  = -BLOCK_SIZE / 2;
	static const float IMG_RIGHT =  BLOCK_SIZE / 2;
}

WarpObject::WarpObject(BaseScene* baseScene, F_Vec2 pos, std::string _nextMapName)
	:CollisionObject{ baseScene,pos,COL_TOP,COL_UNDER,COL_LEFT,COL_RIGHT,BaseObject::E_TAG::WARP }
	, nextMapName{ _nextMapName }
	, imageH{ -1 }
{
	position = pos;
	animation = new Animation{};
}

WarpObject::~WarpObject()
{
}

void WarpObject::Update()
{
	static const int ANIM = 48;

	//アニメーションの設定
	{
		animation->AddAnimCount(1);
		int animNum = animation->GetAnimation(ANIM, ANIM / 4);
		imageH = Image::GetInstance()->GetWarpH(animNum);
	}
}

void WarpObject::Draw(F_Vec2 _camDif)
{
	F_Vec2 drawpos = GetPosition();

	DrawExtendGraph
	(
		drawpos.x - _camDif.x + IMG_LEFT,
		drawpos.y - _camDif.y + IMG_TOP,
		drawpos.x - _camDif.x + IMG_RIGHT,
		drawpos.y - _camDif.y + IMG_UNDER,
		imageH,
		true
	);

	///デバッグ用
	//判定の可視化
	DrawBox
	(
		drawpos.x - _camDif.x + collisionData->GetLeft(),
		drawpos.y - _camDif.y + collisionData->GetTop(),
		drawpos.x - _camDif.x + collisionData->GetRight(),
		drawpos.y - _camDif.y + collisionData->GetUnder(),
		GetColor(255, 255, 255),
		false
	);


}
