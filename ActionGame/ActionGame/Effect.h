#pragma once
#include "BaseObject.h"
class Animation;
class EffectManager;

/// <summary>
/// エフェクトクラス
/// </summary>
class Effect : public BaseObject
{
public:
	Effect(BaseScene* baseScene, EffectManager* _effectManager);
	~Effect();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;


	/// <summary>
	/// エフェクトの発生
	/// </summary>
	/// <param name="pos">発生させる位地</param>
	/// <param name="vel">移動速度</param>
	void SetState(F_Vec2 pos, F_Vec2 vel);

	/// <summary>
	/// フラグを返す
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// フラグをセット
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }

private:
	Animation* animation;

	EffectManager* effectManager;//自身を管理するマネージャーのポインタ

	int maxFrame;		//描画の最大フレーム
	int oneImageFrame;	//画像一枚のフレーム数
	int deffusionFlame; //飛び散っている時間
	bool flag;			//動いているか
};

