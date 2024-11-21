#include "BaseScene.h"
#include "BaseObject.h" 
#include "BaseManager.h" 

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

