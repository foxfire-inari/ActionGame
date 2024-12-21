#include "CommonObjectAndManager.h"

#include "BlockManager.h"

#include "Player.h"
#include "Camera.h"

#include "CollisionManager.h"


//�w�b�_�[�őO���錾�����N���X�͂����ŃC���N���[�h����

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	collisionManager = new CollisionManager{ nowScene };
	blockManager = new BlockManager{ nowScene };

	camera = new Camera{ nowScene };
	player = new Player{ nowScene };



	collisionManager->Start();
	blockManager->Start();

	player->Start();

}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
