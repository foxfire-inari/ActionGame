#include "BaseScene.h"
#include "Player.h"
#include "Camera.h"

BaseScene::~BaseScene()
{
	if (waveout != nullptr)delete waveout;
}

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

template BaseObject* BaseScene::GetOneObjectPtr(int _tag);
template Camera* BaseScene::GetOneObjectPtr(int _tag);

bool BaseScene::NextMapPlayer(std::string& nextMapName)
{
	if (common == nullptr)return false;

	if (nextMapName == "")
		nextMapName = common->GetPlayer()->GoNextMap();

	if (nextMapName != "")
	{
		if (waveout == nullptr)
		{
			//波で時間
			static const float WAVE_WAIT_SECOND = 1.2f;
			//波にしていく値
			static const float WAVE_ADD_VALUE = 7.f;

			waveout = new Waveout{ WAVE_WAIT_SECOND,WAVE_ADD_VALUE };
		}
		else
		{
			waveout->Update();
			if (waveout->GetIsWaveFinish())
				return true;
		}
	}

	return false;
}
