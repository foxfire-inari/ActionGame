#pragma once

/// <summary>
/// �ړ��ʂɏd�͂�ǉ�����N���X
/// </summary>
class Gravity
{
public:
	Gravity();
	~Gravity();

	/// <summary>
	/// Y���̉����x�ɏd�͉����x���ǉ�����
	/// </summary>
	/// <param name="velocityY">Y���̉����x�i�Q�Ɠn���j</param>
	void AddGravity(float& velocityY);

private:

	static const float MAX_GRAVITY;
	static const float GRAVITY;
};

