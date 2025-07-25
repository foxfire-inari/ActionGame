#pragma once
class CollisionData
{
public:
	CollisionData(float _top, float _under, float _left, float _right);
	~CollisionData();

	/// <summary>
	/// コリジョンの上面を返す
	/// </summary>
	/// <returns></returns>
	float GetTop() { return Top; }
	/// <summary>
	/// コリジョンの底面を返す
	/// </summary>
	/// <returns></returns>
	float GetUnder() { return Under; }
	/// <summary>
	/// コリジョンの左面を返す
	/// </summary>
	/// <returns></returns>
	float GetLeft() { return Left; }
	/// <summary>
	/// コリジョンの右面を返す
	/// </summary>
	/// <returns></returns>
	float GetRight() { return Right; }

private:
	float Top;
	float Under;
	float Left;
	float Right;
};

