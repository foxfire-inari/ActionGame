#pragma once
#include"Common.h"
#include"SceneChange.h"
#include"BaseManager.h" 
#include"CommonObjectAndManager.h"

class BaseObject;	// �O���錾

/// <summary>
/// �S�ẴV�[���̌p����
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
	/// oneObjectList��emplace_back����
	/// </summary>
	/// <param name="obj">emplace_back����BaseObject�^�̃|�C���^</param>
	void SetOneObjectList(BaseObject* _obj) { oneObjectList.emplace_back(_obj); }

	/// <summary>
	/// allManagerList��emplace_back����
	/// </summary>
	/// <param name="manager">emplace_back����BaseManager�^�̃|�C���^</param>
	void SetAllManagerList(BaseManager* _manager) { allManagerList.emplace_back(_manager); }

	/// <summary>
	/// oneObjectList����^�ƃ^�O�������I�u�W�F�N�g�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <typeparam name="T">dynamic_cast����^</typeparam>
	/// <param name="_tag">���̌^�����^�O</param>
	/// <returns>�^�ƃ^�O�������Ȃ炻��̃|�C���^�[��Ԃ�</returns>
	template<class T>
	T* GetOneObjectPtr(int _tag);


	/// <summary>
	/// allManagerList����^�ƃ^�O�������I�u�W�F�N�g�̃|�C���^�[��Ԃ�
	/// </summary>
	/// <typeparam name="T">dynamic_cast����^</typeparam>
	/// <param name="_tag">���̌^�����^�O</param>
	/// <returns>�^�ƃ^�O�������Ȃ炻��̃|�C���^�[��Ԃ�</returns>
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
	/// ���g���Ǘ�����I�u�W�F�N�g��}�l�[�W���[���܂Ƃ߂�
	/// �N���X��Ԃ�
	/// </summary>
	/// <returns></returns>
	CommonObjectAndManager* GetCommonObjectAndManager()&
	{
		return common;
	}

protected:

	/// <summary>
	/// SceneChange�̃|�C���^�[��n��
	/// </summary>
	/// <returns>sceneChange�̃|�C���^�[</returns>
	SceneChange* GetSceneChange() const { return sceneChange; }

	/// <summary>
	/// ���ʂ���I�u�W�F�N�g��}�l�[�W���[
	/// </summary>
	CommonObjectAndManager* common;


	/// <summary>
	/// ���̃}�b�v�̖��O
	/// </summary>
	std::string nextMapName;

	/// <summary>
	/// �v���C���[�����[�v�I�u�W�F�N�g�ɓ�����������
	/// �ʂ̃}�b�v�Ɉړ����鏈��
	/// </summary>
	/// <param name="nextMapName">���̃}�b�v�����i�[���邽�ߎQ�Ɠn��</param>
	/// <returns></returns>
	bool NextMapPlayer(std::string& nextMapName);

private:
	/// <summary>
	/// �}�b�v�ړ��⃁�j���[��ʂɎg��
	/// </summary>
	SceneChange* sceneChange;

	/// <summary>
	/// ��Ƀv���C���[�Ȃǂ̃V�[����1�����̂��̂��i�[����
	/// </summary>
	std::list<BaseObject*> oneObjectList;

	/// <summary>
	/// �V�[���ɂ���S�Ă�Manager���i�[����
	/// </summary>
	std::list<BaseManager*> allManagerList;

};

