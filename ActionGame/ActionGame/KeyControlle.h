#pragma once
#include"Singleton.h"

/// <summary>
/// �Q�[���ň����L�[
/// </summary>
enum E_KEY
{
	UP = 0,		//0�ŌŒ�
	DOWN,
	LEFT,
	RIGHT,
	JUMP,
	ATTACK,
	START,
	E_KEY_MAX
};

/// <summary>
/// �L�[���͂���������V���O���g���N���X
/// </summary>
class KeyControlle : public Singleton<KeyControlle>
{
public:

	KeyControlle();
	~KeyControlle();
	void Update();

	/// <summary>
	/// ������Ă���t���[�������擾
	/// </summary>
	/// <param name="keyCode">E_KEY</param>
	/// <returns></returns>
	int GetPressingFrame(int keyCode);

	/// <summary>
	/// ���̃t���[���ŉ����Ă��邩�̔���
	/// </summary>
	/// <param name="keyCode">E_KEY</param>
	/// <returns></returns>
	bool GetNowPressing(int keyCode);

	/// <summary>
	/// ���̃t���[���ŗ����Ă��邩�̔���
	/// </summary>
	/// <param name="keyCode">E_KEY</param>
	/// <returns></returns>
	bool GetNowReleasing(int keyCode);

private:
	/// <summary>
	/// ���͂���Ă���L�[�Ƃ��̃t���[����
	/// </summary>
	std::array<int, E_KEY_MAX> reInputValue;
	/// <summary>
	/// 1�t���[���O�ɓ��͂���Ă����L�[�Ƃ��̃t���[����
	/// </summary>
	std::array<int, E_KEY_MAX> oldReInputValue;

	/// <summary>
	/// GetHitKeyStateAll�Ŏg������256
	/// </summary>
	static const int KEY_NUM = 256;
	/// <summary>
	/// �L�[�{�[�h�̏��
	/// </summary>
	std::array<int, KEY_NUM> keyboard = {};
	/// <summary>
	/// �L�[�R���t�B�O�Ŋ��蓖�Ă�ꂽ�L�[��ۑ�
	/// </summary>
	std::array<int, E_KEY_MAX> keyboardID = {};


};
