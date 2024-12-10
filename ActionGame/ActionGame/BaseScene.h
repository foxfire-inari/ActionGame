#pragma once
#include"Common.h"
#include"SceneChange.h"
#include"BaseManager.h" 
#include"CommonObjectAndManager.h"

class BaseObject;	// 前方宣言

/// <summary>
/// 全てのシーンの継承元
/// </summary>
class BaseScene
{
public:
	BaseScene(SceneChange* _scenechange)
		:sceneChange{ _scenechange }, common{ nullptr }, nextMapName{ "" } {}

	virtual ~BaseScene() {};
	virtual void Start() {};
	virtual bool Update() { return false; }
	virtual void Draw() {};

	/// <summary>
	/// oneObjectListにemplace_backする
	/// </summary>
	/// <param name="obj">emplace_backするBaseObject型のポインタ</param>
	void SetOneObjectList(BaseObject* _obj) { oneObjectList.emplace_back(_obj); }

	/// <summary>
	/// allManagerListにemplace_backする
	/// </summary>
	/// <param name="manager">emplace_backするBaseManager型のポインタ</param>
	void SetAllManagerList(BaseManager* _manager) { allManagerList.emplace_back(_manager); }

	/// <summary>
	/// oneObjectListから型とタグが同じオブジェクトのポインターを返す
	/// </summary>
	/// <typeparam name="T">dynamic_castする型</typeparam>
	/// <param name="_tag">その型が持つタグ</param>
	/// <returns>型とタグが同じならそれのポインターを返す</returns>
	template<class T>
	T* GetOneObjectPtr(int _tag)
	{
		//渡すポインターを入れる変数
		T* reObj = nullptr;
		//リストのnullチェック
		if (oneObjectList.empty())return nullptr;
		//リストの中を全部探す
		for (auto it = oneObjectList.begin(); it != oneObjectList.end();)
		{
			//タグが一致するかを確認
			if ((*it)->GetTag() != _tag)
			{
				it++;
				continue;
			}
			//キャストを行っている
			//dynamic_castなのはstatic_castだとダウンキャストだった場合危険だから
			reObj = dynamic_cast<T*>(*it);
			if (reObj != nullptr)return reObj;
		}
		return nullptr;
	}

	/// <summary>
	/// allManagerListから型とタグが同じオブジェクトのポインターを返す
	/// </summary>
	/// <typeparam name="T">dynamic_castする型</typeparam>
	/// <param name="_tag">その型が持つタグ</param>
	/// <returns>型とタグが同じならそれのポインターを返す</returns>
	template<class T>
	T* GetManagerPtr(int _tag)
	{
		T* reManager = nullptr;
		if (allManagerList.empty())return nullptr;
		for (auto it = allManagerList.begin(); it != allManagerList.end();)
		{
			if ((*it)->GetTag() != _tag)
			{
				it++;
				continue;
			}
			reManager = dynamic_cast<T*>(*it);
			if (reManager != nullptr)return reManager;
		}
		return nullptr;
	}

	/// <summary>
	/// 自身が管理するオブジェクトやマネージャーをまとめた
	/// クラスを返す
	/// </summary>
	/// <returns></returns>
	CommonObjectAndManager* GetCommonObjectAndManager()&
	{
		return common;
	}

protected:

	/// <summary>
	/// SceneChangeのポインターを渡す
	/// </summary>
	/// <returns>sceneChangeのポインター</returns>
	SceneChange* GetSceneChange() const { return sceneChange; }

	/// <summary>
	/// 共通するオブジェクトやマネージャー
	/// </summary>
	CommonObjectAndManager* common;


	/// <summary>
	/// 次のマップの名前
	/// </summary>
	std::string nextMapName;



private:
	/// <summary>
	/// マップ移動やメニュー画面に使う
	/// </summary>
	SceneChange* sceneChange;

	/// <summary>
	/// 主にプレイヤーなどのシーンに1つだけのものを格納する
	/// </summary>
	std::list<BaseObject*> oneObjectList;

	/// <summary>
	/// シーンにある全てのManagerを格納する
	/// </summary>
	std::list<BaseManager*> allManagerList;

};


