#include "BaseScene.h"
#include "BaseObject.h" 
#include "BaseManager.h" 

template<class T>
T* BaseScene::GetOneObjectPtr(int _tag)
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

template<class T>
T* BaseScene::GetManagerPtr(int _tag)
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

