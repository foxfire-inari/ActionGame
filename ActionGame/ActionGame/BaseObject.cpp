#include "BaseObject.h"


BaseObject::BaseObject(BaseScene* _baseScene, F_Vec2 _pos, F_Vec2 _vel, int _tag)
	:baseScene{ _baseScene }
	, position{ _pos }
	, velocity{ _vel }
	, tag{ _tag }
{
}

BaseObject::~BaseObject()
{
}

void BaseObject::SetNewScene(BaseScene* _baseScene, bool isOneObject)
{
	baseScene = _baseScene;

	if (isOneObject)
	{
		//自身を引き継がせることで情報を保持したままシーンを切り替えられる
		baseScene->SetOneObjectList(this);
	}
}