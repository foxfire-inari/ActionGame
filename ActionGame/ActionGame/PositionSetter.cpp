#include "PositionSetter.h"
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"
#include "CollisionProcessing.h"
#include "Fall.h"

PositionSetter::PositionSetter()
{
	//PositionSetterのコンストラクタ
}

PositionSetter::~PositionSetter()
{
	//PositionSetterのデストラクタ
}

void PositionSetter::UpdatePos(BaseObject* me, CollisionData* colData, CollisionManager* collisionManager, Fall* fall)
{	
	//これの代わりに
	//me->AddPosition(me->GetVelocity());

	//X移動
	me->SetPosition(collisionManager->GetCollisionProcessing()->GetSideBlockPosition(me,colData));

	//Y移動
	me->SetPosition(collisionManager->GetCollisionProcessing()->GetOnBlockPosition(me,colData, fall));
	
}

void PositionSetter::UpdateNonInterPos(BaseObject* me)
{
	me->AddPosition(me->GetVelocity());
}
