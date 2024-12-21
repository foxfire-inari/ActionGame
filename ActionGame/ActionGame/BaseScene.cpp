#include "BaseScene.h"
#include "Player.h"
#include "Camera.h"
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

// h�t�@�C���Ɋ֐���u���Ƃ�BaseObject��F�����Ă���Ȃ��̂�
// cpp�t�@�C���Ɋ֐����ڂ�����Ŗ����I�C���X�^���X���������B
// �Ȃ����F������悤�ɂȂ������G���[���N���Ă��Ȃ�
template BaseObject* BaseScene::GetOneObjectPtr(int _tag);
template Camera* BaseScene::GetOneObjectPtr(int _tag);