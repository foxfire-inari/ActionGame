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
	virtual void Draw(F_Vec2 _camDif) {};

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
		BLOCK,				//�n�ʁi�u���b�N�j
		ENEMY,				//�G
		EFFECT,				//�G�t�F�N�g
		ITEM,				//�A�C�e��
		COLLISION,			//�R���W����
		BULLET,				//�e
		WARP,				//���[�v

		E_MANAGER_TAG_MAX	//�^�O�̍ő�l
	};

	/// <summary>
	/// csv�t�@�C���œǂݍ��񂾃f�[�^�̔��ʃ^�O
	/// </summary>
	enum E_CSV_KND
	{
		CSV_SKY = 0,		//�����u���Ȃ�(�w�i)
		CSV_BLOCK_WALL,		//�Ǔ��̃u���b�N
		CSV_BLOCK_GRASS,	//����ɂȂ�u���b�N
		CSV_PLAYER,			//�v���C���[
		CSV_ENEMY_TERRY,	//�G(�e���[)
		CSV_CAMERA_MAX_X,	//�J������X���W�̍ő�l
		CSV_CAMERA_MIN_X,	//�J������X���W�̍ŏ��l
		CSV_CAMERA_MAX_Y,	//�J������Y���W�̍ő�l
		CSV_CAMERA_MIN_Y,	//�J������Y���W�̍ŏ��l
		CSV_WARP,			//���[�v�I�u�W�F�N�g
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

	/// <summary>
	/// csv������W���̏����Z�b�g
	/// </summary>
	/// <param name="pos">csv�̍s�Ɨ�</param>
	/// <param name="info">�f�[�^</param>
	void SetObject(F_Vec2& pos, std::vector<std::string> info);

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

