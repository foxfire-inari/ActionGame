#include "KeyControlle.h"

KeyControlle* KeyControlle::instance = nullptr;

bool KeyControlle::FindKeyLog(int KEY_INPUT)
{
	return std::find(KeyLog.begin(), KeyLog.end(), KEY_INPUT) != KeyLog.end();
}

void KeyControlle::DeletKeyLog(int KEY_INPUT)
{
	if (FindKeyLog(KEY_INPUT))
	{
		KeyLog.erase(std::remove(KeyLog.begin(), KeyLog.end(), KEY_INPUT), KeyLog.end());
	}
}

bool KeyControlle::GetKeyDown(int KEY_INPUT)
{
	if (CheckHitKey(KEY_INPUT))
	{
		if (!FindKeyLog(KEY_INPUT))
		{
			//ë∂ç›ÇµÇ»Ç©Ç¡ÇΩèÍçá
			KeyLog.push_back(KEY_INPUT);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		DeletKeyLog(KEY_INPUT);
		return false;
	}
}

bool KeyControlle::GetKeyPressed(int KEY_INPUT)
{
	if (CheckHitKey(KEY_INPUT))
	{
		if (FindKeyLog(KEY_INPUT))
		{
			//ë∂ç›ÇµÇΩèÍçá
			return true;
		}
		else
		{
			//ë∂ç›ÇµÇ»Ç≠ÇƒÇ‡ï€ë∂
			KeyLog.push_back(KEY_INPUT);
			return false;
		}
	}
	else
	{
		DeletKeyLog(KEY_INPUT);
		return false;
	}
}

void KeyControlle::Create()
{
	if (instance == nullptr)
	{
		instance = new KeyControlle;
	}
}

void KeyControlle::Destroy()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

