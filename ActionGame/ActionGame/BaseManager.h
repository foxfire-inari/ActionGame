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
	virtual void Draw(F_Vec2 _camDif) {};

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
		BLOCK,				//地面（ブロック）
		ENEMY,				//敵
		EFFECT,				//エフェクト
		ITEM,				//アイテム
		COLLISION,			//コリジョン
		BULLET,				//弾
		WARP,				//ワープ

		E_MANAGER_TAG_MAX	//タグの最大値
	};

	/// <summary>
	/// csvファイルで読み込んだデータの判別タグ
	/// </summary>
	enum E_CSV_KND
	{
		CSV_SKY = 0,		//何も置かない(背景)
		CSV_BLOCK_WALL,		//壁等のブロック
		CSV_BLOCK_GRASS,	//足場になるブロック
		CSV_PLAYER,			//プレイヤー
		CSV_ENEMY_TERRY,	//敵(テリー)
		CSV_CAMERA_MAX_X,	//カメラのX座標の最大値
		CSV_CAMERA_MIN_X,	//カメラのX座標の最小値
		CSV_CAMERA_MAX_Y,	//カメラのY座標の最大値
		CSV_CAMERA_MIN_Y,	//カメラのY座標の最小値
		CSV_WARP,			//ワープオブジェクト
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

	/// <summary>
	/// csvから座標等の情報をセット
	/// </summary>
	/// <param name="pos">csvの行と列</param>
	/// <param name="info">データ</param>
	void SetObject(F_Vec2& pos, std::vector<std::string> info);

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

