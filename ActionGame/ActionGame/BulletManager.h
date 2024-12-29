#pragma once
#include"BaseManager.h"
class Bullet;
class CollisionData;

class BulletManager : public BaseManager
{
public:
	BulletManager(BaseScene* baseScene);
	~BulletManager();

	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// �e�𐶐�
	/// </summary>
	/// <param name="pos">���˒n�_</param>
	/// <param name="vec">���˕���</param>
	/// <param name="_power">�_���[�W��</param>
	void SetState(F_Vec2 pos, F_Vec2 vec);
private:
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

