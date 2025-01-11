#pragma once
#include<string>
#include<vector>

/// <summary>
/// �S�ẴV�[�����ʃ^�O
/// </summary>
enum E_SCENE
{
	TITLE,
	GAME,
	STAGE_SELECT,

	SCENETAG_MAX

};


class SceneChange
{
public:
	SceneChange() {}
	~SceneChange() = default;

	/// <summary>
	/// �V�[���ƃ}�b�v�̐؂�ւ����s��
	/// </summary>
	/// <param name="nextscenenum">���̃V�[���̔ԍ�</param>
	/// <param name="nextmapname">���̃}�b�v�̖��O</param>
	/// <param name="oldmapname">���X�����}�b�v�̖��O</param>
	/// <returns>�؂�ւ��ɐ���������true</returns>
	virtual bool Change(int nextscenenum, std::string nextmapname, std::string oldmapname) =0;
};

