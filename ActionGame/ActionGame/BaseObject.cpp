#include "BaseObject.h"


BaseObject::BaseObject(BaseScene* _baseScene, F_Vec2 _pos, F_Vec2 _vel,
	int _top, int _under, int _left, int _right,
	int _tag)
	:position{ _pos }
	, baseScene{ _baseScene }
	, velocity{ _vel }
	, tag{ _tag }
{
	ColData = new CollisionData{ _top,_under,_left,_right };
}

BaseObject::~BaseObject()
{
}

void BaseObject::SetNewScene(BaseScene* _baseScene, bool isOneObject)
{
	baseScene = _baseScene;

	if (isOneObject)
	{
		//���g�������p�����邱�Ƃŏ���ێ������܂܃V�[����؂�ւ�����
		baseScene->SetOneObjectList(this);
	}
}