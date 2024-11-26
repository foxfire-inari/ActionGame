#pragma once
#include"Common.h"

class Fall
{
public:
	Fall();
	~Fall();

	/// <summary>
	/// �n�ʂɏ���Ă邩���Z�b�g
	/// </summary>
	/// <param name="_isOnGround">����Ă邩</param>
	void SetIsOnGround(bool _isOnGround);

	/// <summary>
	/// �������n�߂邩���Z�b�g
	/// </summary>
	/// <param name="vel">velocity�̎Q�Ɠn��</param>
	/// <returns></returns>
	bool FallStart(F_Vec2& vel);

	/// <summary>
	/// �n�ʂɏ���Ă邩�ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetIsOnGround()const { return isOnGround; }

	/// <summary>
	/// 1�t���[���O�ɒn�ʏ���Ă����ǂ���
	/// </summary>
	/// <returns></returns>
	bool GetOldIsOnGround()const { return oldIsOnGround; }
private:

	/// <summary>
	/// �n�ʂɏ���Ă邩�ǂ���
	/// </summary>
	bool isOnGround;

	/// <summary>
	/// 1�t���[���O�ɒn�ʂɏ���Ă����ǂ���
	/// </summary>
	bool oldIsOnGround;

};

