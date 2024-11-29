#include "BaseObject.h"


BaseObject::BaseObject(BaseScene* _baseScene, F_Vec2 _pos, F_Vec2 _vel,
	int _top, int _under, int _left, int _right,
	int _tag)
	:position{ _pos }
	, baseScene{ _baseScene }
	, velocity{ _vel }
	, tag{ _tag }
{
	ColData = new CollisionData{ _top,_under,_left,_right };
}

BaseObject::~BaseObject()
{
}

CollisionData* BaseObject::GetNowCollisionPos()
{
	CollisionData* nowColPos = new CollisionData
	{
		ColData->GetTop()	+ position.y,
		ColData->GetUnder() + position.y,
		ColData->GetLeft()	+ position.x,
		ColData->GetRight()	+ position.x
	};
	return nowColPos;
}

void BaseObject::SetNewScene(BaseScene* _baseScene, bool isOneObject)
{
	baseScene = _baseScene;

	if (isOneObject)
	{
		//Ž©g‚ðˆø‚«Œp‚ª‚¹‚é‚±‚Æ‚Åî•ñ‚ð•ÛŽ‚µ‚½‚Ü‚ÜƒV[ƒ“‚ðØ‚è‘Ö‚¦‚ç‚ê‚é
		baseScene->SetOneObjectList(this);
	}
}