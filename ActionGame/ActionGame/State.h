#pragma once
//�z��ɖ��O��t�����邽��unordered_map���g��
#include<unordered_map>
#include<string>

/// <summary>
/// �X�e�[�g�p�^�[���Ŏg�����
/// </summary>
class State
{
public:
	State();
	~State();

	/// <summary>
	/// ���Ɉڍs����X�e�[�g���Z�b�g
	/// </summary>
	/// <param name="stateName">�Z�b�g����X�e�[�g�̖��O</param>
	void SetNextState(std::string stateName);

	/// <summary>
	/// �X�e�[�g��ς���
	/// </summary>
	void ChangeState();

	/// <summary>
	/// ���̃X�e�[�g��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetNowState()const { return nowState; }

	/// <summary>
	/// ���̃X�e�[�g��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetNextState()const { return nextState; }

	/// <summary>
	/// �V�����X�e�[�g�̒ǉ�
	/// </summary>
	/// <param name="stateName">�ǉ�����X�e�[�g�̖��O</param>
	void SetAllStateMember(std::string stateName);

private:

	/// <summary>
	/// ���݂̃X�e�[�g
	/// </summary>
	int nowState;

	/// <summary>
	/// ���̃X�e�[�g
	/// </summary>
	int nextState;

	/// <summary>
	/// �X�e�[�g��ύX�ł��邩
	/// </summary>
	bool isChangeState;

	/// <summary>
	/// �X�e�[�g�̘A�z�z��
	/// </summary>
	std::unordered_map<std::string, int> allState;

	/// <summary>
	/// �z��ɓo�^����ԍ�
	/// </summary>
	int stateValue;

};

