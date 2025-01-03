#include "PositionSetter.h"
#include "BaseObject.h"
#include "CollisionData.h"
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

void PositionSetter::UpdatePos(BaseObject* me, CollisionData* colData, CollisionManager* collisionManager, Fall* fall)
{	
	//����̑����
	//me->AddPosition(me->GetVelocity());

	//X�ړ�
	me->SetPosition(collisionManager->GetCollisionProcessing()->GetSideBlockPosition(me,colData));

	//Y�ړ�
	me->SetPosition(collisionManager->GetCollisionProcessing()->GetOnBlockPosition(me,colData, fall));
	
}

void PositionSetter::UpdateNonInterPos(BaseObject* me)
{
	me->AddPosition(me->GetVelocity());
}
