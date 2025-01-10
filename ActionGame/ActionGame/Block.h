#pragma once
#include "CollisionObject.h"

class Block : public CollisionObject
{
public:
	Block(BaseScene* baseScene,F_Vec2 pos,int knd);
	~Block();

	void Update()override;
	void Draw(F_Vec2 _camDif)override;
private:
	/// <summary>
	/// ‰æ‘œ
	/// </summary>
	int imageH;
};

