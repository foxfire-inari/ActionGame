#pragma once
#include"BaseManager.h"
class Bullet;
class Chara;
class CollisionData;

namespace
{
	//�e�e�̍ő吔
	static const int MAX_BULLET = 3;
}

class BulletManager : public BaseManager
{
public:
	BulletManager(BaseScene* baseScene);
	~BulletManager();

	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// BulletManager�ɒe��ǉ�����
	/// </summary>
	/// <param name="knd"></param>
	void AddBullet(int knd);

	/// <summary>
	/// �e�̃t���O���K�v���󂢂Ă��邩
	/// ��ɓG�Ȃǂ̐�΂ɒe�������Ăق����I�u�W�F�N�g���g��
	/// </summary>
	/// <param name="knd">�e�̎��</param>
	/// <param name="minBullet">�K�v�Ȑ�</param>
	/// <returns></returns>
	bool GetCanShot(int knd, int minBullet);

	/// <summary>
	/// �e�ɃX�e�[�^�X�����ċN��
	/// </summary>
	/// <param name="pos">���˒n�_</param>
	/// <param name="vec">���˕���</param>
	/// <param name="knd">�e�̎��</param>
	/// <param name="owner">������</param>
	void SetState(F_Vec2 pos, F_Vec2 vec, int knd, int owner);

	/// <summary>
	/// �G�ɓ������Ă��邩
	/// </summary>
	/// <param name="charaPtr">�G�̃|�C���^</param>
	/// <param name="colData">�G�̓����蔻����</param>
	/// <returns>�^����_���[�W</returns>
	int HitCheckChara(Chara* charaPtr,CollisionData* colData);

	/// <summary>
	/// �߂��ɂ��邩�̔���
	/// </summary>
	/// <param name="objPos">����̒��S�ɂȂ���W</param>
	/// <param name="listPos">���X�g���̔��肷����W</param>
	/// <param name="dif"></param>
	/// <returns></returns>
	bool IsNearDistance(F_Vec2 objPos, F_Vec2 listPos, float dif);

	/// <summary>
	/// �e�̎�����̔��ʗp
	/// BaseObject::E_TAG�Ɠ������тɂ���int�^�Ŕ�r�ł���悤�ɂ���
	/// </summary>
	enum BULLET_OWNER
	{
		PLAYER,
		ENEMY,

		OWNER_MAX
	};

	/// <summary>
	// �e�̎��
	/// </summary>
	enum BULLET_KND
	{
		NORMAL,		//�ʏ�e
		BALL,		//�G�̊ۂ��e
		METAL,		//���^���u���[�h

		TYPE_MAX
	};

private:

	/// <summary>
	/// bulletList�ɒe��ǉ�����
	/// </summary>
	template<class T>
	void CreateBullet(int knd)
	{
		//�e���v���[�g�ōD����Bullet�N���X��ǉ��ł���悤�ɂ���
		for (int i = 0; i < MAX_BULLET; i++)
		{
			Bullet* bullet = new T(GetBaseScene(), knd);
			bulletList.emplace_back(bullet);
		}
	}

	/// <summary>
	/// �Ώۂɓ���������
	/// </summary>
	/// <param name="objCol">�Ώۂ̃R���W����</param>
	/// <param name="listCol">���X�g���̃I�u�W�F�N�g�̃R���W����</param>
	/// <returns></returns>
	bool IsHitObject(CollisionData* objCol, CollisionData* listCol);

	/// <summary>
	/// ��ʓ��ɑ��݂��邩
	/// </summary>
	/// <param name="_camDif">�J�����̍��W</param>
	/// <param name="_listObj">���X�g���̔��肷��I�u�W�F�N�g</param>
	/// <returns></returns>
	bool IsInCamera(F_Vec2 _camDif, Bullet* _listObj);

	/// <summary>
	/// �R���W�����̌��݂̍��W���擾
	/// </summary>
	/// <param name="colData">�R���W�����f�[�^</param>
	/// <param name="pos">������̍��W</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

	std::list<Bullet*> bulletList;

	void SetObjectNewScene(BaseScene* _baseScene)override;

};

