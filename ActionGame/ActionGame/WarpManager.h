#pragma once
#include "BaseManager.h"
class WarpObject;
class CollisionData;
class BaseObject;

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

	/// <summary>
	/// �v���C���[��WarpObject���ڐG���Ă�����
	/// ���̃}�b�v�̖��O��Ԃ�
	/// �����łȂ��ꍇ��""��Ԃ�
	/// </summary>
	/// <param name="obj">�v���C���\��</param>
	/// <param name="objCol"></param>
	/// <returns></returns>
	std::string GetNextMapName(BaseObject* obj, CollisionData* objCol);

private:

	std::vector<WarpObject*> warpList;

	bool IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif);

	/// <summary>
	/// �R���W�����̌��݂̍��W���擾
	/// </summary>
	/// <param name="colData">�R���W�����f�[�^</param>
	/// <param name="pos">������̍��W</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

	/// <summary>
	/// �u���b�N�Əd�Ȃ��Ă��邩
	/// </summary>
	/// <param name="objcol">���肷��I�u�W�F�N�g�̃R���W�����f�[�^</param>
	/// <param name="listcol">���X�g���̃R���W�����f�[�^</param>
	/// <returns></returns>
	bool IsInBlock(CollisionData* objCol, CollisionData* listCol);


	void SetObjectNewScene(BaseScene* _baseScene)override;

};

