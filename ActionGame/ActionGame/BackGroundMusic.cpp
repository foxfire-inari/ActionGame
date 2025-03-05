#include "BackGroundMusic.h"

BackGroundMusic::BackGroundMusic()
{
	LoadSound("Data/BGM/.mp3",E_BGM_KND::TITLE);
	LoadSound("Data/BGM/.mp3",E_BGM_KND::MAP_01);
	LoadSound("Data/BGM/.mp3",E_BGM_KND::BOSS);
}

BackGroundMusic::~BackGroundMusic()
{
	for (auto& i : bgmVec)
	{
		//��ڂ̗v�f�i�T�E���h�������j���폜
		DeleteSoundMem(i.second);
	}
}

void BackGroundMusic::PlayBGM(E_BGM_KND _bgmKnd)
{
	for (int i = 0; i < bgmVec.size(); i++)
	{
		//��ڂ̗v�f�iBGM�̎�ށj�Ō���
		if (bgmVec.at(i).first != _bgmKnd)continue;
		//�q�b�g�����烋�[�v�ŗ���
		PlaySoundMem(bgmVec.at(i).second, DX_PLAYTYPE_LOOP);
		break;
	}
}

void BackGroundMusic::StopBGM(E_BGM_KND _bgmKnd)
{
	for (int i = 0; i < bgmVec.size(); i++)
	{
		//��ڂ̗v�f�iBGM�̎�ށj�Ō���
		if (bgmVec.at(i).first != _bgmKnd)continue;

		//�����Ŏ~�܂����Ȃ痬��Ă��Ȃ�BGM���~�߂悤�Ƃ��Ă���
		//�̂ŃR�[�h���������ׂ�
		assert(!CheckSoundMem(_bgmKnd));
		
		//�q�b�g�������~����
		StopSoundMem(bgmVec.at(i).second);
		break;
	}
}

void BackGroundMusic::LoadSound(const char* fileName, E_BGM_KND _knd)
{
	//�T�E���h�������ɓo�^���ꎞ�I�ɕϐ��ɕۑ�
	int handle = LoadSoundMem(fileName);
	assert(handle > 0);
	//�S�Ă̏���pair�^�ŕۑ�
	std::pair<E_BGM_KND, int> pair = { _knd,handle };
	//bgmVec�ɓo�^
	bgmVec.emplace_back(pair);
}
