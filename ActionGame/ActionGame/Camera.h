#pragma once
#include "BaseObject.h"

class Camera : public BaseObject
{
public:
	Camera(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
	~Camera();

	/// <summary>
	/// �J�����̒��S���W���Z�b�g
	/// </summary>
	/// <param name="_target"></param>
	void SetTarget(F_Vec2 _target);

	/// <summary>
	/// ���S���W��Ԃ�
	/// </summary>
	/// <returns></returns>
	F_Vec2 GetTarget()const { return target; }

	/// <summary>
	/// �������̍ő�l��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetMaxPosX()const { return maxPosX; }
	/// <summary>
	/// �������̍ŏ��l��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetMinPosX()const { return minPosX; }
	/// <summary>
	/// �c�����̍ő�l��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetMaxPosY()const { return maxPosY; }
	/// <summary>
	/// �c�����̍ŏ��l��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetMinPosY()const { return minPosY; }
private:
	/// <summary>
	/// �J�����̒��S�ɂȂ���W
	/// </summary>
	F_Vec2 target;

	/// <summary>
	/// �������̍ő�l
	/// </summary>
	float maxPosX;
	/// <summary>
	/// �������̍ŏ��l
	/// </summary>
	float minPosX;
	/// <summary>
	/// �c�����̍ő�l
	/// </summary>
	float maxPosY;
	/// <summary>
	/// �c�����̍ŏ��l
	/// </summary>
	float minPosY;


};

