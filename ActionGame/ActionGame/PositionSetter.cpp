#include "PositionSetter.h"
#include "BaseObject.h"

PositionSetter::PositionSetter()
{
	//PositionSetter�̃R���X�g���N�^
}

PositionSetter::~PositionSetter()
{
	//PositionSetter�̃f�X�g���N�^
}

void PositionSetter::UpdatePos(BaseObject* me)
{	
	me->AddPosition(me->GetVelocity());
}
