#pragma once
class CollisionData
{
public:
	CollisionData(float top, float under, float left, float right);
	~CollisionData();

	/// <summary>
	/// �R���W�����̏�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetTop() { return Top; }
	/// <summary>
	/// �R���W�����̒�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetUnder() { return Under; }
	/// <summary>
	/// �R���W�����̍��ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetLeft() { return Left; }
	/// <summary>
	/// �R���W�����̉E�ʂ�Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetRight() { return Right; }

private:
	float Top;
	float Under;
	float Left;
	float Right;
};

