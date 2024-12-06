#include "PositionSetter.h"
#include "BaseObject.h"
#include "CollisionManager.h"
#include "CollisionProcessing.h"
#include "Fall.h"

PositionSetter::PositionSetter()
{
	//PositionSetter�̃R���X�g���N�^
}

PositionSetter::~PositionSetter()
{
	//PositionSetter�̃f�X�g���N�^
}

void PositionSetter::UpdatePos(BaseObject* me, CollisionManager* collisionManager,Fall* fall)
{	
	//����̑����
	//me->AddPosition(me->GetVelocity());

	//X�ړ�
	me->SetPosition(collisionManager->GetCollisionProcessing()->GetSideBlockPosition(me));

	//Y�ړ�
	me->SetPosition(collisionManager->GetCollisionProcessing()->GetOnBlockPosition(me, fall));
	
}
