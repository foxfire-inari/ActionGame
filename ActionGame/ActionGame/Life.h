#pragma once

/// <summary>
/// HPと死を扱うクラス
/// </summary>
class Life
{
public:
	Life(int _hp);
	~Life();

	/// <summary>
	/// hpを減らす
	/// </summary>
	/// <param name="decValue">減らす量</param>
	void DecHp(int decValue) { hp -= decValue; }

	/// <summary>
	/// hpを足す
	/// </summary>
	/// <param name="addValue">足す値</param>
	void AddHp(int addValue) { hp += addValue; }

	/// <summary>
	/// hpを返す
	/// </summary>
	/// <returns></returns>
	int GetHp()const { return hp; }

	/// <summary>
	/// hpをセット
	/// </summary>
	/// <param name="_hp">セットする値</param>
	void SetHp(int _hp) { hp = _hp; }

	/// <summary>
	/// isDeathをセット
	/// </summary>
	/// <param name="tof">TrueOrFalse</param>
	void SetIsDeath(bool tof) { isDeath = tof; }

	/// <summary>
	/// isDeathを返す
	/// </summary>
	/// <returns></returns>
	bool GetIsDeath()const { return isDeath; }

	static const int DEATH_FRAME;//消滅までのフレーム

private:
	int hp;
	bool isDeath;
};

