#pragma once
#include"Common.h"
class BaseObject;
class Fall;
class CollisionData;

class CollisionManager;


/// <summary>
/// �L�����N�^�[�̈ړ��Ɋ֌W���鏈����S�čs��
/// </summary>
class PositionSetter
{
public:
	PositionSetter();
	~PositionSetter();
	void UpdatePos(BaseObject* me, CollisionData* colData, CollisionManager* collisionManager, Fall* fall);
};

