#include "KeyControlle.h"

KeyControlle* KeyControlle::Singleton::instance = nullptr;

KeyControlle::KeyControlle()
{
	//�����L�[�̃L�[�z�u���Z�b�g
	keyboardID[UP]		= KEY_INPUT_W;		//17
	keyboardID[DOWN]	= KEY_INPUT_S;		//31
	keyboardID[LEFT]	= KEY_INPUT_A;		//30
	keyboardID[RIGHT]	= KEY_INPUT_D;		//32

	keyboardID[JUMP]	= KEY_INPUT_SPACE;	//57

	//���͂̏�����
	for (int i = 0; i < E_KEY_MAX; i++)
	{
		oldReInputValue.at(i) = 0;
		reInputValue.at(i) = 0;
	}
}

KeyControlle::~KeyControlle()
{
}

void KeyControlle::Update()
{
	//GetHitKeyStateAll�̂��߂ɕϐ��錾
	char key[KEY_NUM];
	GetHitKeyStateAll(key);
	for (int i = 0; i < KEY_NUM; i++)
	{
		if (key[i] != 0)
		{
			keyboard[i]++;
		}
		else keyboard[i] = 0;
	}

	//�L�[�̏�Ԃ��X�V
	for (int i = 0; i < E_KEY_MAX; i++)
	{
		oldReInputValue.at(i) = reInputValue.at(i);
		reInputValue.at(i) = keyboard[keyboardID[i]];
	}
}

int KeyControlle::GetPressingFrame(int keyCode)
{
	if (keyCode >= 0 && keyCode < E_KEY_MAX)
	{
		return reInputValue[keyCode];
	}
	return -1;
}

bool KeyControlle::GetNowPressing(int keyCode)
{
	if (keyCode >= 0 && keyCode < E_KEY_MAX)
	{
		if (GetPressingFrame(keyCode) == 1)
			return true;
	}

	return false;
}

bool KeyControlle::GetNowReleasing(int keyCode)
{
	if (keyCode >= 0 && keyCode < E_KEY_MAX)
	{
		if (reInputValue.at(keyCode) == 0 && oldReInputValue.at(keyCode) != 0)
			return true;
	}

	return false;
}
