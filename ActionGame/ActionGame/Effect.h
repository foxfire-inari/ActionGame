#pragma once
#include "BaseObject.h"
class Animation;
class EffectManager;

/// <summary>
/// �G�t�F�N�g�N���X
/// </summary>
class Effect : public BaseObject
{
public:
	Effect(BaseScene* baseScene, EffectManager* _effectManager);
	~Effect();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;


	/// <summary>
	/// �G�t�F�N�g�̔���
	/// </summary>
	/// <param name="pos">����������ʒn</param>
	/// <param name="vel">�ړ����x</param>
	void SetState(F_Vec2 pos, F_Vec2 vel);

	/// <summary>
	/// �t���O��Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetFlag()const { return flag; }

	/// <summary>
	/// �t���O���Z�b�g
	/// </summary>
	/// <param name="_flag"></param>
	void SetFlag(bool _flag) { flag = _flag; }

private:
	Animation* animation;

	EffectManager* effectManager;//���g���Ǘ�����}�l�[�W���[�̃|�C���^

	int maxFrame;		//�`��̍ő�t���[��
	int oneImageFrame;	//�摜�ꖇ�̃t���[����
	int deffusionFlame; //��юU���Ă��鎞��
	bool flag;			//�����Ă��邩
};

