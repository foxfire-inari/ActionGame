#pragma once
#include"Common.h"
#include"Vector"

class KeyControlle
{
public:

	/// <summary>
	/// KeyLog�ɑΏۂ̃L�[�����邩�̊m�F
	/// </summary>
	/// <param name="KEY_INPUT">�ΏۂƂ���L�[</param>
	/// <returns>����Ȃ�True</returns>
	bool FindKeyLog(int KEY_INPUT);

	/// <summary>
	/// KeyLog�ɂ���Ώۂ̃L�[���O������΍폜
	/// </summary>
	/// <param name="KEY_INPUT">�ΏۂƂ���L�[</param>
	void DeletKeyLog(int KEY_INPUT);

	/// <summary>
	/// �Ώۂ̃L�[�������ꂽ�u��
	/// </summary>
	/// <param name="KEY_INPUT">�ΏۂƂ���L�[</param>
	/// <returns>�����ꂽ�u�ԂȂ�True</returns>
	bool GetKeyDown(int KEY_INPUT);

	/// <summary>
	/// �Ώۂ̃L�[�������ꑱ���Ă��邩
	/// </summary>
	/// <param name="KEY_INPUT">�ΏۂƂ���L�[</param>
	/// <returns>�����ꑱ���Ă���Ȃ�True</returns>
	bool GetKeyPressed(int KEY_INPUT);

	//�S�Ẵt�@�C���œ������̂��擾������
	static  KeyControlle* GetInstance()
	{
		return instance;
	}

	/// <summary>
	/// �����iinstance�ɒ��g�����ē����悤�ɂ���j
	/// </summary>
	static void Create();

	/// <summary>
	/// �폜�iinstance�̒��g��nullptr�ɂ��ē����Ȃ��悤�ɂ���j
	/// </summary>
	static void Destroy();
private:
	//KeyCOntrolle�̃C���X�^���X
	static KeyControlle* instance;

	//�L�[�̓��I�z��
	std::vector<int> KeyLog;
};
