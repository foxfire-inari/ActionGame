#pragma once
class CollisionData
{
public:
	CollisionData(int top, int under, int left, int right);
	~CollisionData();

	/// <summary>
	/// �R���W�����̏�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetTop() { return Top; }
	/// <summary>
	/// �R���W�����̒�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetUnder() { return Under; }
	/// <summary>
	/// �R���W�����̍��ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetLeft() { return Left; }
	/// <summary>
	/// �R���W�����̉E�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetRight() { return Right; }

private:
	int Top;
	int Under;
	int Left;
	int Right;
};

