#pragma once
class CollisionData
{
public:
	CollisionData(int top, int under, int left, int right);
	~CollisionData();

	/// <summary>
	/// コリジョンの上面を返す
	/// </summary>
	/// <returns></returns>
	int GetTop() { return Top; }
	/// <summary>
	/// コリジョンの底面を返す
	/// </summary>
	/// <returns></returns>
	int GetUnder() { return Under; }
	/// <summary>
	/// コリジョンの左面を返す
	/// </summary>
	/// <returns></returns>
	int GetLeft() { return Left; }
	/// <summary>
	/// コリジョンの右面を返す
	/// </summary>
	/// <returns></returns>
	int GetRight() { return Right; }

private:
	int Top;
	int Under;
	int Left;
	int Right;
};

