#pragma once
#include "BaseManager.h"
class Effect;

class EffectManager : public BaseManager
{
public:
	EffectManager(BaseScene* baseScene);
	~EffectManager();
	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// エフェクトの発生
	/// </summary>
	/// <param name="pos">発生させる位地</param>
	/// <param name="vel">移動速度</param>
	void SetState(F_Vec2 pos, F_Vec2 vel);

	/// <summary>
	/// 飛び散るエフェクトの発生
	/// プレイヤーやボスがやられたときの演出
	/// </summary>
	/// <param name="pos">発生させる位置</param>
	void SetDeffusion(F_Vec2 pos);

	/// <summary>
	/// 強制的にエフェクトを消す
	/// </summary>
	/// <param name="_knd">消すエフェクトの種類</param>
	void SetFlagFalse(int _knd);

private:
	std::list<Effect*> effectList;

	/// <summary>
	/// このマネージャーに所属しているオブジェクト達の
	/// 所属しているシーンも設定しなおす
	/// </summary>
	/// <param name="_baseScene">新しく所属するシーン</param>
	void SetObjectNewScene(BaseScene* _baseScene)override;

	/// <summary>
	/// 弾の方向を定める関数
	/// </summary>
	/// <param name="genVec">弾の生成速度（参照渡し）</param>
	/// <param name="rad">発射角度</param>
	/// <param name="speed">生成速度</param>
	void SetGenVel(F_Vec2& genVec, float rad,float speed);


};

