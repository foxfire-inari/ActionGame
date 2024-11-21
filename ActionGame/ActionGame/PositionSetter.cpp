#include "PositionSetter.h"
#include "BaseObject.h"

PositionSetter::PositionSetter()
{
	//PositionSetterのコンストラクタ
}

PositionSetter::~PositionSetter()
{
	//PositionSetterのデストラクタ
}

void PositionSetter::UpdatePos(BaseObject* me)
{	
	me->AddPosition(me->GetVelocity());
}
