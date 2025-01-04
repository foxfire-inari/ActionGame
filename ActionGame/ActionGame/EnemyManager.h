#pragma once
#include "BaseManager.h"
class Enemy;
class Life;
class CollisionData;

class EnemyManager : public BaseManager
{
public:
	EnemyManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info);
	~EnemyManager();
	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// �v���C���[�ƓG���������Ă�����_���[�W��Ԃ�
	/// �������Ă��Ȃ�������|1
	/// </summary>
	/// <param name="collInfo">�v���C���[�̓����蔻����</param>
	/// <param name="damageVel">�_���[�W�Ŕ�ԕ���</param>
	/// <returns></returns>
	int CheckPlayerHit(CollisionData* colData, int& damageVel);

private:
	std::list<Enemy*> enemyList;
	std::vector<std::vector<std::string>> information;//���������i�[

	/// <summary>
	/// �v���C���[�ɓ���������
	/// </summary>
	/// <param name="objcol">���肷��I�u�W�F�N�g�̃R���W�����f�[�^</param>
	/// <param name="listcol">���X�g���̃R���W�����f�[�^</param>
	/// <returns></returns>
	bool IsHitPlayer(CollisionData* objCol, CollisionData* listCol);


	/// <summary>
	/// ��ʓ��ɑ��݂��邩
	/// </summary>
	/// <param name="_camDif">�J�����̍��W</param>
	/// <param name="_listObj">���X�g���̔��肷��I�u�W�F�N�g</param>
	/// <returns></returns>
	bool IsInCamera(F_Vec2 _camDif, Enemy* _listObj);

	/// <summary>
	/// �R���W�����̌��݂̍��W���擾
	/// </summary>
	/// <param name="colData">�R���W�����f�[�^</param>
	/// <param name="pos">������̍��W</param>
	/// <returns></returns>
	CollisionData* GetNowPositionCol(CollisionData* colData, F_Vec2 pos);

	/// <summary>
	/// ���̃}�l�[�W���[�ɏ������Ă���I�u�W�F�N�g�B��
	/// �������Ă���V�[�����ݒ肵�Ȃ���
	/// </summary>
	/// <param name="_baseScene">�V������������V�[��</param>
	void SetObjectNewScene(BaseScene* _baseScene)override;



};

