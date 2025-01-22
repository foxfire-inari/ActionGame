#pragma once
#include"BaseObject.h"

#include"Fall.h"
#include"State.h"
#include"Life.h"
#include"PositionSetter.h"
#include"CollisionData.h"
#include"Gravity.h"
#include"Animation.h"
#include"CollisionManager.h"

/// <summary>
/// �S�ẴL�����̌p����
/// </summary>
class Chara : public BaseObject
{
public:
	Chara(BaseScene* baseScene, int hp,
		float top, float under, float left, float right,
		int tag);
	~Chara();
	virtual void Update()override {}
	virtual void Draw(F_Vec2 _camDif)override {}

protected:

	/// <summary>
	/// �����蔻��̏��
	/// </summary>
	CollisionData* collisionData;

	/// <summary>
	/// �n�ʂɏ���Ă邩
	/// </summary>
	Fall* fall;

	/// <summary>
	/// HP�Ǝ�
	/// </summary>
	Life* life;

	/// <summary>
	/// �d��
	/// </summary>
	Gravity* gravity;

	/// <summary>
	/// �L�����ړ��Ɋւ���N���X
	/// </summary>
	PositionSetter* positionSetter;

	/// <summary>
	/// �X�e�[�g
	/// </summary>
	State* state;

	/// <summary>
	/// �����蔻��̃}�l�[�W���[
	/// </summary>
	CollisionManager* collisionManager;

	/// <summary>
	/// �A�j���[�V�����̃}�l�[�W���[
	/// </summary>
	Animation* animation;

	int imageH;		//�摜

};