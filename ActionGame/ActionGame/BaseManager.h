#pragma once
#include"Common.h"

class BaseScene;	//�O���錾�̂�
class BaseObject;	//�O���錾�̂�

/// <summary>
/// �S�Ẵ}�l�[�W���[�̌p����
/// </summary>
class BaseManager
{
public:
	BaseManager(BaseScene* _baseScene, int _tag);
	virtual ~BaseManager() {};
	virtual void Start();
	virtual void Update() {};
	virtual void Draw() {};

	/// <summary>
	/// ���g�̃^�O�̔ԍ���Ԃ�
	/// </summary>
	/// <returns>tag</returns>
	int GetTag()const { return tag; }

	/// <summary>
	/// �V�[���ԂŃ}�l�[�W���[�������p���Ƃ��A
	/// ���̏�������V�[���ɐݒ肵�Ȃ���
	/// </summary>
	/// <param name="_baseScene">���̃V�[��</param>
	void SetNewScene(BaseScene* _baseScene);

	/// <summary>
	/// �}�l�[�W���[�𔻕ʂ���^�O
	/// </summary>
	enum E_MANAGER_TAG
	{
		Ground,				//�n�ʁi�u���b�N�j
		ENEMY,				//�G
		EFFECT,				//�G�t�F�N�g
		ITEM,				//�A�C�e��
		COLLISION,			//�R���W����

		E_MANAGER_TAG_MAX	//�^�O�̍ő�l
	};


protected:
	/// <summary>
	/// �������Ă���V�[����Ԃ�
	/// </summary>
	/// <returns>BaseScene�N���X�̃|�C���^��Ԃ�</returns>
	BaseScene* GetBaseScene()const { return baseScene; }

	static const float DRAW_DIF;//�`��͈̔�

	/// <summary>
	/// obj��player�̋�����dif��菬����������true
	/// </summary>
	/// <param name="obj">�m�F����I�u�W�F�N�g</param>
	/// <param name="dif">����</param>
	/// <returns></returns>
	bool IsNearDistance(BaseObject* obj, float dif = DRAW_DIF);

	//���W�A�p�x��csv����ǂݍ���ŃZ�b�g
	//void SetObject(VECTOR& pos, VECTOR& rot, std::vector<std::string> info);

	/// <summary>
	/// �v���C���[���V�[���Ɋi�[
	/// </summary>
	void Init();

	/// <summary>
/// ���̃}�l�[�W���[�ɏ������Ă���I�u�W�F�N�g�B��
/// �������Ă���V�[�����ݒ肵�Ȃ���
/// </summary>
/// <param name="_baseScene">�V������������V�[��</param>
	virtual void SetObjectNewScene(BaseScene* _baseScene) = 0;

	BaseObject* playerBase;
private:
	BaseScene* baseScene;

	/// <summary>
	/// �}�l�[�W���[���ʗp�̃^�O
	/// </summary>

	int tag;
};

