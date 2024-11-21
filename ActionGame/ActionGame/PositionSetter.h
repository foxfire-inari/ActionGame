#pragma once
#include"Common.h"
class BaseObject;

/// <summary>
/// キャラクターの移動に関係する処理を全て行う
/// </summary>
class PositionSetter
{
public:
	PositionSetter();
	~PositionSetter();
	void UpdatePos(BaseObject* me);
};

