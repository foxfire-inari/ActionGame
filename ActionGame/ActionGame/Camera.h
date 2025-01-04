#pragma once
#include "BaseObject.h"

class Camera : public BaseObject
{
public:
	Camera(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
	~Camera();

	/// <summary>
	/// カメラの中心座標をセット
	/// </summary>
	/// <param name="_target"></param>
	void SetTarget(F_Vec2 _target);

	/// <summary>
	/// 中心座標を返す
	/// </summary>
	/// <returns></returns>
	F_Vec2 GetTarget()const { return target; }

	/// <summary>
	/// 横方向の最大値を返す
	/// </summary>
	/// <returns></returns>
	float GetMaxPosX()const { return maxPosX; }
	/// <summary>
	/// 横方向の最小値を返す
	/// </summary>
	/// <returns></returns>
	float GetMinPosX()const { return minPosX; }
	/// <summary>
	/// 縦方向の最大値を返す
	/// </summary>
	/// <returns></returns>
	float GetMaxPosY()const { return maxPosY; }
	/// <summary>
	/// 縦方向の最小値を返す
	/// </summary>
	/// <returns></returns>
	float GetMinPosY()const { return minPosY; }
private:
	/// <summary>
	/// カメラの中心になる座標
	/// </summary>
	F_Vec2 target;

	/// <summary>
	/// 横方向の最大値
	/// </summary>
	float maxPosX;
	/// <summary>
	/// 横方向の最小値
	/// </summary>
	float minPosX;
	/// <summary>
	/// 縦方向の最大値
	/// </summary>
	float maxPosY;
	/// <summary>
	/// 縦方向の最小値
	/// </summary>
	float minPosY;


};

