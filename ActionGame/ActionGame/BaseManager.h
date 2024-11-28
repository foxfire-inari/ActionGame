#pragma once
#include"Common.h"

class BaseScene;	//前方宣言のみ
class BaseObject;	//前方宣言のみ

/// <summary>
/// 全てのマネージャーの継承元
/// </summary>
class BaseManager
{
public:
	BaseManager(BaseScene* _baseScene, int _tag);
	virtual ~BaseManager() {};
	virtual void Start();
	virtual void Update() {};
	virtual void Draw() {};

	/// <summary>
	/// 自身のタグの番号を返す
	/// </summary>
	/// <returns>tag</returns>
	int GetTag()const { return tag; }

	/// <summary>
	/// シーン間でマネージャーを引き継ぐとき、
	/// 次の所属するシーンに設定しなおす
	/// </summary>
	/// <param name="_baseScene">次のシーン</param>
	void SetNewScene(BaseScene* _baseScene);

	/// <summary>
	/// マネージャーを判別するタグ
	/// </summary>
	enum E_MANAGER_TAG
	{
		Ground,				//地面（ブロック）
		ENEMY,				//敵
		EFFECT,				//エフェクト
		ITEM,				//アイテム
		COLLISION,			//コリジョン

		E_MANAGER_TAG_MAX	//タグの最大値
	};


protected:
	/// <summary>
	/// 所属しているシーンを返す
	/// </summary>
	/// <returns>BaseSceneクラスのポインタを返す</returns>
	BaseScene* GetBaseScene()const { return baseScene; }

	static const float DRAW_DIF;//描画の範囲

	/// <summary>
	/// objとplayerの距離がdifより小さかったらtrue
	/// </summary>
	/// <param name="obj">確認するオブジェクト</param>
	/// <param name="dif">距離</param>
	/// <returns></returns>
	bool IsNearDistance(BaseObject* obj, float dif = DRAW_DIF);

	//座標、角度をcsvから読み込んでセット
	//void SetObject(VECTOR& pos, VECTOR& rot, std::vector<std::string> info);

	/// <summary>
	/// プレイヤーをシーンに格納
	/// </summary>
	void Init();

	/// <summary>
/// このマネージャーに所属しているオブジェクト達の
/// 所属しているシーンも設定しなおす
/// </summary>
/// <param name="_baseScene">新しく所属するシーン</param>
	virtual void SetObjectNewScene(BaseScene* _baseScene) = 0;

	BaseObject* playerBase;
private:
	BaseScene* baseScene;

	/// <summary>
	/// マネージャー判別用のタグ
	/// </summary>

	int tag;
};

