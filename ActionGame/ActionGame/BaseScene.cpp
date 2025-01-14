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
	//�n���|�C���^�[������ϐ�
	T* reObj = nullptr;
	//���X�g��null�`�F�b�N
	if (oneObjectList.empty())return nullptr;
	//���X�g�̒���S���T��
	for (auto it = oneObjectList.begin(); it != oneObjectList.end();)
	{
		//�^�O����v���邩���m�F
		if ((*it)->GetTag() != _tag)
		{
			it++;
			continue;
		}
		//�L���X�g���s���Ă���
		//dynamic_cast�Ȃ̂�static_cast���ƃ_�E���L���X�g�������ꍇ�댯������
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
			//�g�Ŏ���
			static const float WAVE_WAIT_SECOND = 1.2f;
			//�g�ɂ��Ă����l
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
