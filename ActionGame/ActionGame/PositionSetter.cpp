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
	//これの代わりに
	//me->AddPosition(me->GetVelocity());

	me->SetPosition()
	
}
