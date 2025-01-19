#pragma once
#include "Animation.h"


/// <summary>
/// ���[�v���̃V�[���̐ؑւ̉��o������N���X
/// </summary>
class Waveout
{
public:
	Waveout(float _waitSecond, float _addVal);
	~Waveout();

	void Update();
	void Draw();

	/// <summary>
	/// �Ó]��A�҂����Ԃ��I������
	/// </summary>
	/// <returns></returns>
	bool GetIsWaveFinish()const { return isWaveFinish; }

	/// <summary>
	/// �g�����������邩���Z�b�g
	/// </summary>
	/// <param name="_isReversal"></param>
	void SetIsReversal(bool _isReversal);

	/// <summary>
	/// �g�������A���ɖ߂�����
	/// </summary>
	/// <returns></returns>
	bool GetIsReturnFinish()const { return isReturnFinish; }

	/// <summary>
	/// �ŏ���alpha��255�ɂȂ���������true��Ԃ�
	/// </summary>
	/// <returns></returns>
	bool GetNowMaxAlpha()const;

private:
	int imageH;				//�摜
	
	int count;				//�g�̕b��
	
	float waveCount;		//�g�̃J�E���g

	float alpha;			//�摜�̔Z��
	float oldAlpha;			//1�t���[���O�̉摜�̔Z��
	float addVal;			//�Z���̒ǉ���
	float waitSecond;		//���o�̕b��
	
	bool isWaveFinish;		//�g�̔������牉�o�̕b������������
	bool isReturnFinish;	//�g�̉��o���猳�ɖ߂�����
	bool isReversal;		//���ɖ߂�n�߂Ă��邩

	Animation* animation;	//���[�v�̗h�炢�ł銴���o������

};

