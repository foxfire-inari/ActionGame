#include "EffectManager.h"
#include"Effect.h"

namespace
{
	//一度に生成できるエフェクトの最大値
	static const int MAX_EFFECT_NUM = 50;

	//飛び散るエフェクトの個数
	static const int DEFFUSION_OUTSIDE = 8;
	static const int DEFFUSION_INSIDE = 4;

}

EffectManager::EffectManager(BaseScene* baseScene)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::EFFECT }
{
	//printfDx("EffectManagerのコンストラクタ\n");

	for (int i = 0; i < MAX_EFFECT_NUM; i++)
	{
		Effect* eff = new Effect{ GetBaseScene(), this };
		effectList.emplace_back(eff);
	}
}

EffectManager::~EffectManager()
{
	//printfDx("EffectManagerのデストラクタ\n");
	for (auto it = effectList.begin(); it != effectList.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = effectList.erase(it);
		}
		else it++;
	}
}

void EffectManager::Start()
{
	Init();
}

void EffectManager::Update()
{
	for (auto it = effectList.begin(); it != effectList.end(); it++)
	{
		if (!(*it)->GetFlag())continue;

		(*it)->Update();
	}
}

void EffectManager::Draw(F_Vec2 _camDif)
{
	for (auto it = effectList.begin(); it != effectList.end(); it++)
	{
		if (!(*it)->GetFlag())continue;
		(*it)->Draw(_camDif);
	}
}

void EffectManager::SetState(F_Vec2 pos, F_Vec2 vel)
{
	for (auto it = effectList.begin(); it != effectList.end(); it++)
	{
		if ((*it)->GetFlag())continue;

		(*it)->SetState( pos, vel);
		break;
	}
}

void EffectManager::SetDeffusion(F_Vec2 pos)
{
	static const float OUTSIDE_SPEED = 3.f;
	static const float INSIDE_SPEED = 1.5f;
	F_Vec2 genvel = F_Vec2{ 0,0 };

	for (int i = 0; i <= DEFFUSION_OUTSIDE; i++)
	{
		float rad = PI / (DEFFUSION_OUTSIDE / 2) * i;
		SetGenVel(genvel,rad,OUTSIDE_SPEED);
		SetState(pos, genvel);
	}
	for (int i = 0; i <= DEFFUSION_INSIDE; i++)
	{
		float rad = PI / (DEFFUSION_INSIDE / 2) * i;
		SetGenVel(genvel, rad,INSIDE_SPEED);
		SetState(pos, genvel);
	}

}

void EffectManager::SetFlagFalse(int _knd)
{
	for (auto it = effectList.begin(); it != effectList.end(); it++)
	{
		(*it)->SetFlag(false);
	}
}

void EffectManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = effectList.begin(); it != effectList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}

void EffectManager::SetGenVel(F_Vec2& genVec, float rad,float speed)
{
	genVec.x = cosf(rad) * speed;
	genVec.y = sinf(rad) * speed;
}