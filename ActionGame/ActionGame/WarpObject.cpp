#include "WarpObject.h"

WarpObject::WarpObject(BaseScene* baseScene, F_Vec2 pos, std::string _nextMapName)
	:BaseObject{ baseScene,pos,F_Vec2{0,0},BaseObject::E_TAG::WARP }
	, nextMapName{ _nextMapName }
{
	position = pos;
}

WarpObject::~WarpObject()
{
}
