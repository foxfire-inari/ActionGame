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

	//�J�����̍s����ő���W�A�ŏ����W��ǂݍ���
	int knd;
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));

		//�����ł��擾���������킩��₷���悤��E_CSV_KND�𕪂��Ă���
		if (knd == BaseManager::E_CSV_KND::CSV_CAMERA_MAX_X)
		{
			maxPosX = std::stoi(_info.at(i).at(1));
			continue;
		}
		if (knd == BaseManager::E_CSV_KND::CSV_CAMERA_MIN_X)
		{
			minPosX = std::stoi(_info.at(i).at(1));
			continue;
		}
		if (knd == BaseManager::E_CSV_KND::CSV_CAMERA_MAX_Y)
		{
			maxPosY = std::stoi(_info.at(i).at(2));
			continue;
		}
		if (knd == BaseManager::E_CSV_KND::CSV_CAMERA_MIN_Y)
		{
			minPosY = std::stoi(_info.at(i).at(2));
			continue;
		}

	}

}

Camera::~Camera()
{
}

void Camera::SetTarget(F_Vec2 _target)
{
	target.x = _target.x - WINDOW_MID_X;
	target.y = _target.y - WINDOW_MID_Y;
}

