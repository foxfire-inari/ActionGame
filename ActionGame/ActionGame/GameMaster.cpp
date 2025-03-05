#include "GameMaster.h"

//�V���O���g���N���X
#include "KeyControlle.h"
#include "Image.h"
#include "BackGroundMusic.h"

//�S�ẴV�[�����C���N���[�h
#include "TitleScene.h"
#include "GameScene.h"

GameMaster::GameMaster()
{
	//�V���O���g���N���X���쐬
	KeyControlle::Create();
	Image::Create();
	BackGroundMusic::Create();

	//�ŏ��̃V�[����ǉ�
	TitleScene* title = new TitleScene{ this};
	scene.emplace_back(title);
}

GameMaster::~GameMaster()
{
	if (scene.empty())return;
	//�V�[����S�ăf���[�g
	for (auto it = scene.begin(); it != scene.end(); )
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = scene.erase(it);
		}
		else it++;
	}

	//�V���O���g���N���X���f���[�g
	KeyControlle::Destroy();
	Image::Destroy();
	BackGroundMusic::Destroy();
}


void GameMaster::Update()
{
	//�L�[���͂��X�V
	KeyControlle::GetInstance()->Update();

	//�V�[���ɒ��g������΍X�V���`��
	if (scene.empty())return;
	if ((*scene.begin())->Update())return;
	(*scene.begin())->Draw();
}

bool GameMaster::Change(int nextSceneNum, std::string nextMapName, std::string oldMapName)
{
	//���܂ł̃V�[���S�Ă����X�g�������
	for (auto it = scene.begin(); it != scene.end();)
	{
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			it = scene.erase(it);
		}
		else it++;
	}

	//���̃V�[����o�^����
	switch (nextSceneNum)
	{
	case E_SCENE::TITLE:
	{
		TitleScene* title = new TitleScene{ this };
		scene.emplace_front(title);
		(*scene.begin())->Start();
	}
	return true;

	case E_SCENE::GAME:
	{
		GameScene* game = new GameScene{ this,nextMapName ,oldMapName };
		scene.emplace_front(game);
		(*scene.begin())->Start();
	}
	return true;

	default:
		assert(false);
		break;
	}

	return false;
}


