#include "BulletManager.h"
#include "NormalBullet.h"
#include "CollisionManager.h"
namespace
{
	//íeÇÃç≈ëÂó 
	static const int MAX_BULLET = 3;
}

BulletManager::BulletManager(BaseScene* baseScene)
	:BaseManager{baseScene,BaseManager::E_MANAGER_TAG::BULLET}
{

}

BulletManager::~BulletManager()
{
	for (auto it = bulletList.begin(); it != bulletList.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = bulletList.erase(it);
		}
		else it++;
	}
}

void BulletManager::Start()
{
	Init();

	for (int i = 0; i < MAX_BULLET; i++)
	{
		NormalBullet* bullet = new NormalBullet(GetBaseScene());
		bulletList.emplace_back(bullet);
	}
}

void BulletManager::Update()
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		if (!(*it)->GetFlag())continue;
		(*it)->Update();
	}
}

void BulletManager::Draw(F_Vec2 _camDif)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		if (!(*it)->GetFlag())continue;

		//ÉJÉÅÉâÇÃäOÇ…èoÇƒÇ¢ÇΩÇÁÉtÉâÉOÇì|Ç∑
		//DrawÇÃíÜÇ»ÇÃÇÕÉJÉÅÉâÇÃç¿ïWÇàµÇ¶ÇÈÇ©ÇÁ
		if (!IsInCamera(_camDif, (*it)))
		{
			(*it)->SetFlag(false);
			continue;
		}

		(*it)->Draw(_camDif);
	}
}

void BulletManager::SetState(F_Vec2 pos, F_Vec2 vec)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		//ÉtÉâÉOÇ™óßÇ¡ÇƒÇÈèÍçáÇÕìÆÇ¢ÇƒÇÈÇÃÇ≈égÇ¶Ç»Ç¢
		if ((*it)->GetFlag())continue;

		(*it)->SetState(pos, vec);
		break;
	}
}

bool BulletManager::IsInCamera(F_Vec2 _camDif, Bullet* _listObj)
{
	//ç¿ïWÇçló∂ÇµÇΩìñÇΩÇËîªíËÇìoò^
	CollisionData* nowListCol = GetNowPositionCol(_listObj->GetCollisionData(), _listObj->GetPosition());

	//ï`âÊîÕàÕÇìñÇΩÇËîªíËÇ∆ÇµÇƒìoò^
	CollisionData* camCol = new CollisionData
	{
		_camDif.y,
		_camDif.y + WINDOW_Y,
		_camDif.x,
		_camDif.x + WINDOW_X
	};

	return (
		//âÊñ ÇÃâ°Ç…ãèÇÈÇ©
		(camCol->GetTop() <= nowListCol->GetUnder()  && nowListCol->GetUnder() <= camCol->GetUnder() ||
		 camCol->GetTop() <= nowListCol->GetTop()	 && nowListCol->GetTop()   <= camCol->GetUnder()) &&
		//âÊñ ÇÃÇÃècÇ…ãèÇÈÇ©
		(camCol->GetLeft() <= nowListCol->GetLeft()	 && nowListCol->GetLeft()  <= camCol->GetRight() ||
		 camCol->GetLeft() <= nowListCol->GetRight() && nowListCol->GetRight() <= camCol->GetRight())
		);
}

CollisionData* BulletManager::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colData->GetTop()	+ pos.y,
		colData->GetUnder() + pos.y,
		colData->GetLeft()	+ pos.x,
		colData->GetRight() + pos.x
	};
	return nowCol;
}

void BulletManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
