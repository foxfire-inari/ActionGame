#pragma once
#include"Common.h"
class BaseObject;
class Fall;
class CollisionManager;


/// <summary>
/// �L�����N�^�[�̈ړ��Ɋ֌W���鏈����S�čs��
/// </summary>
class PositionSetter
{
public:
	PositionSetter();
	~PositionSetter();
	void UpdatePos(BaseObject* me, CollisionManager* collisionManager, Fall* fall);
};

