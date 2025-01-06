#include "Camera.h"

Camera::Camera(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseObject{baseScene,BaseObject::E_TAG::CAMERA}
	,target{0,0}
	,maxPosX{0}
	,minPosX{0}
	,maxPosY{0}
	,minPosY{0}
{
	GetBaseScene()->SetOneObjectList(this);

	//最大値を一時保存
	F_Vec2 maxPos = {};

	maxPos.x = _info.at(0).size() * 64;
	maxPos.y = _info.size() * 64;

	maxPosX = maxPos.x - WINDOW_X / 2 - 32;
	maxPosY = maxPos.y - WINDOW_Y / 2 - 32;

	//最小値はマップによらず全て固定
	minPosX = WINDOW_X / 2 - 32;
	minPosY = WINDOW_Y / 2 - 32;

}

Camera::~Camera()
{
}

void Camera::SetTarget(F_Vec2 _target)
{
	target.x = _target.x - WINDOW_X / 2;
	target.y = _target.y - WINDOW_Y / 2;
	DrawFormatString(50, 100, GetColor(255, 255, 255),
		"camPos:%f,%f", target.x, target.y);
}

