#include "BaseManager.h"
#include "BaseObject.h"


BaseManager::BaseManager(BaseScene* _baseScene, int _tag)
	:baseScene{ _baseScene }
	, tag{ _tag }
	, playerBase{ nullptr }
{
	//�������Ă���V�[���̃��X�g�Ɏ��g���i�[
	baseScene->SetAllManagerList(this);
}

void BaseManager::Start()
{
	Init();
}

void BaseManager::SetNewScene(BaseScene* _baseScene)
{
	//���̃V�[����ۑ�
	baseScene = _baseScene;
	//���̃V�[���Ɋi�[
	baseScene->SetAllManagerList(this);
	//�}�l�[�W���[�ɏ������Ă���I�u�W�F�N�g�������Ă���
	//�V�[�������̃V�[���ɕύX
	SetObjectNewScene(baseScene);
}

bool BaseManager::IsNearDistance(BaseObject* obj, float dif)
{

	//�v���C���[����dif���߂�������true
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
