#pragma once
#include"Common.h"
#include"SceneChange.h"

class BaseObject;	// �O���錾
class BaseManager;	// �O���錾

/// <summary>
/// �S�ẴV�[���̌p����
/// </summary>
class BaseScene
{
public:
	BaseScene(SceneChange* _scenechange)
		:sceneChange{ _scenechange }, nextMapName{ "" } {}

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
	T* GetManagerPtr(int _tag);


protected:

	/// <summary>
	/// SceneChange�̃|�C���^�[��n��
	/// </summary>
	/// <returns>sceneChange�̃|�C���^�[</returns>
	SceneChange* GetSceneChange() const { return sceneChange; }

	/// <summary>
	/// ���̃}�b�v�̖��O
	/// </summary>
	std::string nextMapName;
	


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


