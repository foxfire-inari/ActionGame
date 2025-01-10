#include "WarpManager.h"
#include "WarpObject.h"




WarpManager::WarpManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{ baseScene ,BaseManager::E_MANAGER_TAG::WARP}
{
}

WarpManager::~WarpManager()
{
}

void WarpManager::Update()
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->Update();
	}
}

void WarpManager::Draw(F_Vec2 _camVec)
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->Draw(_camVec);
	}
}

void WarpManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
