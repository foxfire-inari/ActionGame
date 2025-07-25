#include "EnemyManager.h"
#include "Terry.h"
#include "Metall.h"
#include "MetalMan.h"
#include "BulletManager.h"
#include "EffectManager.h"
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

EnemyManager::EnemyManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{baseScene,BaseManager::E_MANAGER_TAG::ENEMY}
{
	information = _info;
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

	EffectManager* effectManager = GetBaseScene()->GetManagerPtr<EffectManager>(BaseManager::E_MANAGER_TAG::EFFECT);
	assert(effectManager != nullptr);

	Init();

	F_Vec2 pos = {};

	//読み込んだデータでブロックを生成する
	int knd = 0;
	for (int i = 0; i < information.size(); i++)
	{
		knd = std::stoi(information.at(i).at(0));

		if (knd == E_CSV_KND::CSV_ENEMY_TERRY)
		{
			SetObject(pos, information.at(i));
			Terry* enemy = new Terry{ GetBaseScene(),bulletManager,effectManager,playerBase,pos, Enemy::E_ENEMY_KND::TERRY };
			enemyList.emplace_back(enemy);
			continue;
		}
		if (knd == E_CSV_KND::CSV_ENEMY_METALL)
		{
			SetObject(pos, information.at(i));
			Metall* enemy = new Metall{ GetBaseScene(),bulletManager,effectManager,playerBase,pos, Enemy::E_ENEMY_KND::METALL };
			enemyList.emplace_back(enemy);
			continue;
		}

		if (knd == E_CSV_KND::CSV_BOSS_METALMAN)
		{
			SetObject(pos, information.at(i));
			MetalMan* enemy = new MetalMan{ GetBaseScene(),bulletManager,effectManager,playerBase,pos, Enemy::E_BOSS_KND::METAL_MAN };
			enemyList.emplace_back(enemy);
			continue;
		}
	}
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

int EnemyManager::CheckPlayerHit(CollisionData* colData)
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
			return (*it)->GetBodyPower();
		}
	}

	return -1;
}

bool EnemyManager::IsBossButtle()
{
	for (auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		//種類がボスなら
		if ((*it)->GetKnd() >= Enemy::E_BOSS_KND::METAL_MAN)
		{
			return true;
		}
	}

	return false;
}

bool EnemyManager::IsHitPlayer(CollisionData* objCol, CollisionData* listCol)
{
	//それぞれのポジションを計算に含める必要がある
	//各辺の判定を取る
	return (
		//list上辺<=obj底辺
		listCol->GetTop()	<= objCol->GetUnder()	&&
		//list底辺>=obj上辺
		listCol->GetUnder()	>= objCol->GetTop()		&&
		//list左辺<=obj右辺
		listCol->GetLeft()	<= objCol->GetRight()	&&
		//list右辺>=obj左辺
		listCol->GetRight()	>= objCol->GetLeft()
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

	//各辺の判定を取る
	return (
		//list上辺<=obj底辺
		camCol->GetTop()	<= nowListCol->GetUnder() &&
		//list底辺>=obj上辺
		camCol->GetUnder()	>= nowListCol->GetTop() &&
		//list左辺<=obj右辺
		camCol->GetLeft()	<= nowListCol->GetRight() &&
		//list右辺>=obj左辺
		camCol->GetRight()	>= nowListCol->GetLeft()
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
