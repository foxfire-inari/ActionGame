#pragma once
#include "Chara.h"
class BulletManager;
class EffectManager;

/// <summary>
/// �G�̌p����
/// </summary>
class Enemy : public Chara
{
public:
	Enemy(BaseScene* baseScene,
		BulletManager* _bulletManager, EffectManager* _effectManager, BaseObject* _plBase,
		F_Vec2 pos, int _knd, int hp, float top, float under, float left, float right);
	~Enemy();
	virtual void Update()override {};
	virtual void Draw(F_Vec2 _camDif)override {};

	/// <summary>
	/// �G�̎��
	/// </summary>
	enum E_ENEMY_KND
	{
		TERRY = 0,
		METALL,

	};

	/// <summary>
	/// �{�X�̎��
	/// </summary>
	enum E_BOSS_KND
	{
		METAL_MAN = 10000,
	};

	/// <summary>
	/// Life�̃|�C���^��Ԃ�
	/// const���ƊO������l��ύX����Ȃ�
	/// </summary>
	/// <returns></returns>
	const Life* GetLifePtr()const { return life; }

	/// <summary>
	/// �R���W������Ԃ�
	/// </summary>
	/// <returns></returns>
	CollisionData* GetCollisionData()const { return collisionData; }

	/// <summary>
	/// �p���[��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetBodyPower()const { return bodyPower; }

	/// <summary>
	/// ���g�̎�ނ�Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetKnd()const { return knd; }

	/// <summary>
	/// �t���O�������Ă��邩�Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// �t���O���Z�b�g
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }


protected:

	/// <summary>
	/// �e�Ƃ̓����蔻��
	/// </summary>
	BulletManager* bulletManager;

	/// <summary>
	/// �G�t�F�N�g�𔭐�������
	/// </summary>
	EffectManager* effectManager;

	/// <summary>
	/// �v���C���[��BaseObject�^�̃|�C���^
	/// </summary>
	BaseObject* plBase;

	/// <summary>
	/// ���ڐG�ꂽ�Ƃ��̃p���[
	/// </summary>
	int bodyPower;

	/// <summary>
	/// ���g�̎��
	/// </summary>
	int knd;

	/// <summary>
	/// ���ł܂ł̃J�E���g
	/// </summary>
	int deathCount;

	/// <summary>
	/// ��ʓ��ɂ��邩�ǂ���
	/// </summary>
	bool flag;

};

