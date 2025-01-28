#pragma once
#include "BaseObject.h"
#include "CollisionData.h"
#include "CollisionManager.h"
#include "Image.h"


/// <summary>
/// 全ての弾の継承元
/// </summary>
class Bullet : public BaseObject
{
public:
	Bullet(BaseScene* _baseScene, int _power, float top, float under, float left, float right,int _knd );
	~Bullet();

	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

	/// <summary>
	/// 弾の要素を設定する
	/// </summary>
	/// <param name="pos">発射地点</param>
	/// <param name="vec">発射方向</param>
	/// <param name="_owner">持ち主</param>
	virtual void SetState(F_Vec2 pos,F_Vec2 vec,int _owner) {};

	/// <summary>
	/// フラグが立っているか返す
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// フラグをセット
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }

	/// <summary>
	/// コリジョンを返す
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData()const { return collisionData; }

	/// <summary>
	/// ダメージを返す
	/// </summary>
	/// <returns></returns>
	int GetPower()const { return power; }

	/// <summary>
	/// 持ち主を返す
	/// </summary>
	/// <returns></returns>
	int GetOwner()const { return owner; }

	/// <summary>
	/// 持ち主をセットする
	/// 弾を跳ね返す時に使う
	/// </summary>
	/// <param name="_owner"></param>
	/// <returns></returns>
	void SetOwner(int _owner) { owner = _owner; }

	/// <summary>
	/// 弾の種類を返す
	/// </summary>
	/// <returns></returns>
	int GetKnd()const { return knd; }

protected:

	/// <summary>
	/// 球のダメージ
	/// </summary>
	int power;

	/// <summary>
	/// この弾が動いてるかどうか
	/// </summary>
	bool flag;

	/// <summary>
	/// 弾の持ち主（プレイヤーか敵か）
	/// </summary>
	int owner;

	/// <summary>
	/// この弾がどの種類か
	/// </summary>
	int knd;

	int imageH;		//画像


	/// <summary>
	/// 当たり判定の情報
	/// </summary>
	CollisionData* collisionData;
};

