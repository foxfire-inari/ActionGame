#include "BulletManager.h"
#include "NormalBullet.h"
#include "Enemy.h"
#include "Life.h"
#include "CollisionData.h"
#include "CollisionManager.h"
#include "EnemyManager.h"

namespace
{
	//弾の最大量
	static const int MAX_BULLET = 3;
	// 判定する距離
	static const float HIT_CHECK_DIF = 100.0f;
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

		//カメラの外に出ていたらフラグを倒す
		//Drawの中なのはカメラの座標を扱えるから
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
		//フラグが立ってる場合は動いてるので使えない
		if ((*it)->GetFlag())continue;

		(*it)->SetState(pos, vec);
		break;
	}
}

int BulletManager::HitCheckEnemy(Enemy* enemyPtr, CollisionData* colData)
{
	int damage = 0;

	F_Vec2 enePos = enemyPtr->GetPosition();

	//座標を考慮した当たり判定に変更
	CollisionData* nowObjCol = GetNowPositionCol(colData, enePos);

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;


	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{		
		//フラグが立っていなかったら次へ
		if (!(*it)->GetFlag())continue;

		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//600以上離れていたら次へ
		if (!IsNearDistance(listPos,enePos, HIT_CHECK_DIF))
			continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetCollisionData();

		//座標を足してコリジョンが存在する座標にする
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//対象に当たったかを確認
		if (IsHitObject(nowObjCol, nowlistCol))
		{
			//当たっていたらフラグを倒しダメージを与える
			(*it)->SetFlag(false);
			damage += (*it)->GetPower();
		}
	}

	return damage;
}
bool BulletManager::IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif)
{
	if (F_Vec2::VSize(listPos - objPos) < dif)
		return true;
	return false;
}

bool BulletManager::IsHitObject(CollisionData* objCol, CollisionData* listCol)
{
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

bool BulletManager::IsInCamera(F_Vec2 _camDif, Bullet* _listObj)
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
		(camCol->GetTop() <= nowListCol->GetUnder()  && nowListCol->GetUnder() <= camCol->GetUnder() ||
		 camCol->GetTop() <= nowListCol->GetTop()	 && nowListCol->GetTop()   <= camCol->GetUnder()) &&
		//画面のの縦に居るか
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
