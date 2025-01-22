#include "WarpManager.h"
#include "WarpObject.h"
#include "CollisionData.h"


namespace
{
	/// <summary>
	/// 判定する距離
	/// </summary>
	static const float HIT_CHECK_DIF = 100.0f;
}

WarpManager::WarpManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{ baseScene ,BaseManager::E_MANAGER_TAG::WARP}
{
	F_Vec2 pos = {};
	int knd = 0;
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));
		if (knd == E_CSV_KND::CSV_WARP)
		{
			SetObject(pos, _info.at(i));
			WarpObject* warp = new WarpObject{ GetBaseScene(),pos,_info.at(i).at(3) };
			warpList.emplace_back(warp);
		}
	}
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

std::string WarpManager::GetNextMapName(BaseObject* obj, CollisionData* objCol)
{
	//次のマップの名前を保持する
	std::string nextMapName = "";

	//キャラクターのポジション
	F_Vec2 objPos = obj->GetPosition();

	//座標を考慮した当たり判定に変更
	CollisionData* nowObjCol = GetNowPositionCol(objCol, objPos);

	//リスト内のオブジェクトのポジション
	F_Vec2 listPos;
	//リスト内のオブジェクトのコリジョン
	CollisionData* listCol;

	bool isOnGround = false;

	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		//リストのオブジェクトの座標を代入
		listPos = (*it)->GetPosition();

		//キャラの近くないなら判定しない
		if (!IsNearDistance(listPos, objPos, HIT_CHECK_DIF))continue;

		//近くならコリジョンを代入
		listCol = (*it)->GetCollisionData();

		//座標を足してコリジョンが存在する座標にする
		CollisionData* nowlistCol = GetNowPositionCol(listCol, listPos);

		//ブロックと重なっているかを確認
		if (IsInBlock(nowObjCol, nowlistCol))
		{
			nextMapName =(*it)->GetNextMapName();
		}
	}

	//次のマップ名を返す
	return nextMapName;
}

bool WarpManager::IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif)
{
	if (VSize(listPos - objPos) < dif)
		return true;
	return false;
}

CollisionData* WarpManager::GetNowPositionCol(CollisionData* colData, F_Vec2 pos)
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

bool WarpManager::IsInBlock(CollisionData* objCol, CollisionData* listCol)
{
	//めり込み補正
	static const float IN_DIF = 0.5f;
	//各辺の判定を取る
	return (
		//list上辺<=obj底辺
		listCol->GetTop() + IN_DIF <= objCol->GetUnder() &&
		//list底辺>=obj上辺
		listCol->GetUnder() - IN_DIF >= objCol->GetTop() &&
		//list左辺<=obj右辺
		listCol->GetLeft() + IN_DIF <= objCol->GetRight() &&
		//list右辺>=obj左辺
		listCol->GetRight() - IN_DIF >= objCol->GetLeft()
		);
}

void WarpManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = warpList.begin(); it != warpList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}