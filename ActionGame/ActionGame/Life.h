#pragma once

/// <summary>
/// HP�Ǝ��������N���X
/// </summary>
class Life
{
public:
	Life(int _hp);
	~Life();

	/// <summary>
	/// hp�����炷
	/// </summary>
	/// <param name="decValue">���炷��</param>
	void DecHp(int decValue) { hp -= decValue; }

	/// <summary>
	/// hp�𑫂�
	/// </summary>
	/// <param name="addValue">�����l</param>
	void AddHp(int addValue) { hp += addValue; }

	/// <summary>
	/// hp��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetHp()const { return hp; }

	/// <summary>
	/// hp���Z�b�g
	/// </summary>
	/// <param name="_hp">�Z�b�g����l</param>
	void SetHp(int _hp) { hp = _hp; }

	/// <summary>
	/// isDeath���Z�b�g
	/// </summary>
	/// <param name="tof">TrueOrFalse</param>
	void SetIsDeath(bool tof) { isDeath = tof; }

	/// <summary>
	/// isDeath��Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetIsDeath()const { return isDeath; }

	static const int DEATH_FRAME;//���ł܂ł̃t���[��

private:
	int hp;
	bool isDeath;
};

