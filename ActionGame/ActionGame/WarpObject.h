#pragma once
#include "BaseObject.h"
#include "Animation.h"

/// <summary>
/// �}�b�v�ړ�������I�u�W�F�N�g
/// </summary>
class WarpObject : public BaseObject
{
public:
	WarpObject(BaseScene* baseScene,F_Vec2 pos ,std::string _nextMapName);
	~WarpObject();

private:

	/// <summary>
	/// ���ɓǂݍ���Csv�t�@�C���̖��O
	/// </summary>
	std::string nextMapName;

};

