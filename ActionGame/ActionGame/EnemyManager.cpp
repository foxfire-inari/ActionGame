#include "EnemyManager.h"
#include "Terry.h"
#include "BulletManager.h"
#include "Life.h"
#include "CollisionData.h"
#include "CollisionManager.h"

namespace
{
	/// <summary>
	/// 判定する距離
	/// </summary>
	static const float HIT_CHECK_DIF = 100.0f;
}

EnemyManager::EnemyManager(BaseScene* baseScene)
	:BaseManager{baseScene,BaseManager::E_MANAGER_TAG::ENEMY}
{
}

EnemyManager::~EnemyManager()
{
	for (auto it = enemyList.begin(); it != enemyList.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = enemyList.erase(it);
		}
		else it++;
	}
}

void EnemyManager::Start()
{
	CollisionManager* collision = GetBaseScene()->GetManagerPtr<CollisionManager>(BaseManager::E_MANAGER_TAG::COLLISION);
	assert(collision != nullptr);

	BulletManager* bulletManager = GetBaseScene()->GetManagerPtr<BulletManager>(BaseManager::E_MANAGER_TAG::BULLET);
	assert(bulletManager != nullptr);

	Init();

	Terry* terry = new Terry{ GetBaseScene(),bulletManager,playerBase,F_Vec2{400,100},0 };
	enemyList.emplace_back(terry);

	Terry* terry1 = new Terry{ GetBaseScene(),bulletManager,playerBase,F_Vec2{500,100},0 };
	enemyList.emplace_back(terry1);

	Terry* terry2 = new Terry{ GetBaseScene(),bulletManager,playerBase,F_Vec2{600,500},0 };
	enemyList.emplace_back(terry2);

}

void EnemyManager::Update()
{
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		if (!(*it)->GetFlag())
		{
			it++;
			continue;
		}

		(*it)->Update();
		
		if ((*it)->GetLifePtr()->GetIsDeath())
		{
			delete* it;
			*it = nullptr;
			it = enemyList.erase(it);
		}
		else
			it++;
	}
}

void EnemyManager::Draw(F_Vec2 _camDif)
{
	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		//カメラの外に出ていたらフラグを倒す
		//Drawの中なのはカメラの座標を扱えるから
		if (!IsInCamera(_camDif, (*it)))
		{
			(*it)->SetFlag(false);
			continue;
		}
		if(!(*it)->GetFlag())			
			(*it)->SetFlag(true);

		(*it)->Draw(_camDif);
	}
}

int EnemyManager::CheckPlayerHit(CollisionData* colData, int& damageVel)
{
	F_Vec2 plPos = playerBase->GetPosition();

	//座標を考慮した当たり判定に変更
	CollisionData* nowObjCol = GetNowPositionCol(colData, plPos);

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos; 
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol; 


	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		//100以上離れていたら次へ
		if (!IsNearDistance(*it, HIT_CHECK_DIF))
			continue;
		//死んでいたら次へ
		if ((*it)->GetLifePtr()->GetHp() <= 0)continue;


		//近くならコリジョンを代入
		listCol = (*it)->GetCollisionData();
		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//座標を足してコリジョンが存在する座標にする
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//プレイヤーに当たったかを確認
		if (IsHitPlayer(nowObjCol, nowlistCol))
		{
			//座標から右に飛ばすか左に飛ばすかを返す
			damageVel = plPos.x - listPos.x >= 0 ? 1 : -1;
			return (*it)->GetPower();
		}
	}

	return -1;
}

bool EnemyManager::IsHitPlayer(CollisionData* objCol, CollisionData* listCol)
{
	//それぞれのポジションを計算に含める必要がある
	return (
		//プレイヤーの横に居るか
		(listCol->GetTop()<= objCol->GetUnder() && objCol->GetUnder() <= listCol->GetUnder() ||
			listCol->GetTop() <= objCol->GetTop() && objCol->GetTop() <= listCol->GetUnder() ) &&
		//プレイヤーの縦に居るか
		(listCol->GetLeft() <= objCol->GetLeft() && objCol->GetLeft() <= listCol->GetRight() ||
			listCol->GetLeft() <= objCol->GetRight() && objCol->GetRight() <= listCol->GetRight())
		);
}

bool EnemyManager::IsInCamera(F_Vec2 _camDif, Enemy* _listObj)
{
	//座標を考慮した当たり判定を登録
	CollisionData* nowListCol = GetNowPositionCol(_listObj->GetCollisionData(), _listObj->GetPosition());

	//描画範囲を当たり判定として登録
	CollisionData* camCol = new CollisionData
	{
		_camDif.y,
		_camDif.y + WINDOW_Y,
		_camDif.x,
		_camDif.x + WINDOW_X
	};

	return (
		//画面の横に居るか
		(camCol->GetTop() <= nowListCol->GetUnder() && nowListCol->GetUnder() <= camCol->GetUnder() ||
			camCol->GetTop() <= nowListCol->GetTop() && nowListCol->GetTop() <= camCol->GetUnder()) &&
		//画面のの縦に居るか
		(camCol->GetLeft() <= nowListCol->GetLeft() && nowListCol->GetLeft() <= camCol->GetRight() ||
			camCol->GetLeft() <= nowListCol->GetRight() && nowListCol->GetRight() <= camCol->GetRight())
		);
}

CollisionData* EnemyManager::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
{
	CollisionData* nowCol = new CollisionData
	{
		colData->GetTop() + pos.y,
		colData->GetUnder() + pos.y,
		colData->GetLeft() + pos.x,
		colData->GetRight() + pos.x
	};
	return nowCol;
}

void EnemyManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
