#pragma once
#include "BaseManager.h"
class WarpObject;

/// <summary>
/// �S�Ẵ��[�v�I�t�W�F�N�g���Ǘ�����N���X
/// �����o������͎��Ȃ��̂�CollisionManager�ɂ͓o�^���Ȃ�
/// </summary>
class WarpManager : public BaseManager
{
public:
	WarpManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
	~WarpManager();
	void Update() override;
	void Draw(F_Vec2 _camVec) override;

private:

	std::vector<WarpObject*> warpList;

	void SetObjectNewScene(BaseScene* _baseScene)override;

};

