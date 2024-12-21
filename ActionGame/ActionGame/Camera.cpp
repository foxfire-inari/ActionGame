#include "Camera.h"

Camera::Camera(BaseScene* baseScene)
	:BaseObject{baseScene,BaseObject::E_TAG::CAMERA}
	,target{0,0}
	,maxPosX{0}
	,minPosX{0}
	,maxPosY{0}
	,minPosY{0}
{
	GetBaseScene()->SetOneObjectList(this);




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

