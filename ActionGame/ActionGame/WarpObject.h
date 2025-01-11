#pragma once
#include "CollisionObject.h"
#include "Animation.h"

/// <summary>
/// �}�b�v�ړ�������I�u�W�F�N�g
/// �v���C���[�Ƃ̔���͎�肽���̂�CollisionObject���p��
/// </summary>
class WarpObject : public CollisionObject
{
public:
	WarpObject(BaseScene* baseScene,F_Vec2 pos ,std::string _nextMapName);
	~WarpObject();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// ���̃}�b�v�̖��O��Ԃ�
	/// </summary>
	/// <returns></returns>
	std::string GetNextMapName()const { return nextMapName; }

private:

	/// <summary>
	/// �Q�[�g�̗h�炢�ł銴���o������
	/// </summary>
	Animation* animation;

	/// <summary>
	/// ���ɓǂݍ���Csv�t�@�C���̖��O
	/// </summary>
	std::string nextMapName;

	/// <summary>
	/// �摜
	/// </summary>
	int imageH;
};

