#include "BaseManager.h"
#include "BaseObject.h"


BaseManager::BaseManager(BaseScene* _baseScene, int _tag)
	:baseScene{ _baseScene }
	, tag{ _tag }
	, playerBase{ nullptr }
{
	//所属しているシーンのリストに自身を格納
	baseScene->SetAllManagerList(this);
}

void BaseManager::Start()
{
	Init();
}

void BaseManager::SetNewScene(BaseScene* _baseScene)
{
	//次のシーンを保存
	baseScene = _baseScene;
	//次のシーンに格納
	baseScene->SetAllManagerList(this);
	//マネージャーに所属しているオブジェクトが持っている
	//シーンを次のシーンに変更
	SetObjectNewScene(baseScene);
}

bool BaseManager::IsNearDistance(BaseObject* obj, float dif)
{

	//プレイヤーからdifより近かったらtrue
	if (F_Vec2::VSize(obj->GetPosition() - playerBase->GetPosition()) < dif)
		return true;

	return false;
}

void BaseManager::SetObject(F_Vec2& pos, std::vector<std::string> info)
{
	pos.x *= BLOCK_SIZE;
	pos.y *= BLOCK_SIZE;
}

void BaseManager::Init()
{
	playerBase = GetBaseScene()->GetOneObjectPtr<BaseObject>(BaseObject::E_TAG::PLAYER);
	assert(playerBase != nullptr);
}
