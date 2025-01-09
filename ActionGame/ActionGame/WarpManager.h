#pragma once
#include "BaseManager.h"
class WarpObject;

/// <summary>
/// 全てのワープオフジェクトを管理するクラス
/// 押し出し判定は取らないのでCollisionManagerには登録しない
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

