#include "BulletManager.h"
#include "NormalBullet.h"
#include "BallBullet.h"
#include "Chara.h"
#include "Life.h"
#include "CollisionData.h"
#include "CollisionManager.h"
#include "EnemyManager.h"

namespace
{
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

	//最低でもプレイヤーはいるので通常弾だけ登録
	for (int i = 0; i < MAX_BULLET; i++)
	{
		Bullet* bullet = new NormalBullet(GetBaseScene(), BULLET_KND::NORMAL);
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

void BulletManager::AddBullet(int knd)
{
	switch (knd)
	{
		case BULLET_KND::NORMAL:	CreateBullet<NormalBullet>(knd);	break;
		case BULLET_KND::BALL:		CreateBullet<BallBullet>(knd);		break;
		//case BULLET_KND::METAL:		CreateBullet<>(knd);			break;
		default:					assert(false);						break;
			
	}

}

bool BulletManager::GetCanShot(int knd, int minBullet)
{
	int canShotCount = 0;
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		//タイプが違う場合はやり直し
		if ((*it)->GetKnd() != knd)continue;
		//フラグが立ってる場合は動いてるので使えない
		if ((*it)->GetFlag())continue;
		//撃てる弾が合ったらインクリメント
		canShotCount++;
	}
	//minBullet以上あるか
	if (canShotCount >= minBullet)
	{
		return true;
	}
	return false;
}

void BulletManager::SetState(F_Vec2 pos, F_Vec2 vec, int knd, int owner)
{
	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		//種類が違う場合はやり直し
		if ((*it)->GetKnd() != knd)continue;

		//フラグが立ってる場合は動いてるので使えない
		if ((*it)->GetFlag())continue;

		(*it)->SetState(pos, vec, owner);
		break;
	}
}

int BulletManager::HitCheckChara(Chara* charaPtr, CollisionData* colData)
{
	int damage = 0;

	F_Vec2 enePos = charaPtr->GetPosition();

	//座標を考慮した当たり判定に変更
	CollisionData* nowObjCol = GetNowPositionCol(colData, enePos);

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;


	for (auto it = bulletList.begin(); it != bulletList.end(); it++)
	{
		//持ち主と判定の対象が同じならやり直し
		if ((*it)->GetOwner() == charaPtr->GetTag())continue;

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
