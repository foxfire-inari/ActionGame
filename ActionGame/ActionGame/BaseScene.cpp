#include "BaseScene.h"
#include "Player.h"
#include "Camera.h"
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

// hファイルに関数を置くととBaseObjectを認識してくれないので
// cppファイルに関数を移した上で明示的インスタンス化をした。
// なぜか認識するようになったしエラーも起きていない
template BaseObject* BaseScene::GetOneObjectPtr(int _tag);
template Camera* BaseScene::GetOneObjectPtr(int _tag);