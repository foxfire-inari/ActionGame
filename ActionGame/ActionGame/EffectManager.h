#pragma once
#include "BaseManager.h"
class Effect;

class EffectManager : public BaseManager
{
public:
	EffectManager(BaseScene* baseScene);
	~EffectManager();
	void Start()override;
	void Update()override;
	void Draw(F_Vec2 _camDif)override;

	/// <summary>
	/// �G�t�F�N�g�̔���
	/// </summary>
	/// <param name="pos">����������ʒn</param>
	/// <param name="vel">�ړ����x</param>
	void SetState(F_Vec2 pos, F_Vec2 vel);

	/// <summary>
	/// ��юU��G�t�F�N�g�̔���
	/// �v���C���[��{�X�����ꂽ�Ƃ��̉��o
	/// </summary>
	/// <param name="pos">����������ʒu</param>
	void SetDeffusion(F_Vec2 pos);

	/// <summary>
	/// �����I�ɃG�t�F�N�g������
	/// </summary>
	/// <param name="_knd">�����G�t�F�N�g�̎��</param>
	void SetFlagFalse(int _knd);

private:
	std::list<Effect*> effectList;

	/// <summary>
	/// ���̃}�l�[�W���[�ɏ������Ă���I�u�W�F�N�g�B��
	/// �������Ă���V�[�����ݒ肵�Ȃ���
	/// </summary>
	/// <param name="_baseScene">�V������������V�[��</param>
	void SetObjectNewScene(BaseScene* _baseScene)override;

	/// <summary>
	/// �e�̕������߂�֐�
	/// </summary>
	/// <param name="genVec">�e�̐������x�i�Q�Ɠn���j</param>
	/// <param name="rad">���ˊp�x</param>
	/// <param name="speed">�������x</param>
	void SetGenVel(F_Vec2& genVec, float rad,float speed);


};

