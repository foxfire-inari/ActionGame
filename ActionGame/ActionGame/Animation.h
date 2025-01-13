#pragma once

class Animation
{
public:
	Animation();
	~Animation();

	/// <summary>
	/// �A�j���[�V�������n�߂�ʒu�������ɂ���Č��߂�֐�
	/// </summary>
	/// <param name="right">�E�����̎��̊J�n�ʒu</param>
	/// <param name="left">�������̎��̊J�n�ʒu</param>
	/// <param name="moveAngle">�����Ă������</param>
	/// <returns></returns>
	int GetAngleImage(int right, int left, int moveAngle);

	/// <summary>
	/// �A�j���[�V�����̌��݂̃t���[������Ԃ�
	/// </summary>
	/// <param name="animFrame">�A�j���[�V�����̍��v�̃t���[����</param>
	/// <param name="oneFrame">�ꖇ���Ƃ̃t���[����</param>
	/// <returns></returns>
	int GetAnimation(int allFrame, int oneFrame);

	/// <summary>
	/// �A�j���[�V�����̃J�E���g�𑫂�
	/// </summary>
	/// <param name="addCount">�����J�E���g��</param>
	void AddAnimCount(float addCount);

	/// <summary>
	/// �A�j���[�V�����̃J�E���g���Œ肷��
	/// �iAttack�Ȃǂŏ���������p�j
	/// </summary>
	/// <param name="setCount">�Œ肷��l</param>
	void SetAnimCount(float setCount);

	/// <summary>
	/// animCount��Ԃ�
	/// </summary>
	/// <returns></returns>
	float GetAnimCount()const { return animCount; }

	/// <summary>
	/// animNum��setNum�ɂ���
	/// </summary>
	/// <param name="setNum">�Z�b�g����l</param>
	void SetAnimNum(int setNum);

	/// <summary>
	/// animNum��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetAnimNum()const { return animNum; }

private:

	/// <summary>
	/// �A�j���[�V�����̃J�E���^�[
	/// </summary>
	float animCount;

	/// <summary>
	/// �A�j���[�V�����̌��݂̔ԍ���ۑ�
	/// </summary>
	float animNum;

};

