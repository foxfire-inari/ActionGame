#include "CommonObjectAndManager.h"
#include "CollisionManager.h"

#include "Player.h"


//�w�b�_�[�őO���錾�����N���X�͂����ŃC���N���[�h����

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	collisionManager = new CollisionManager{ nowScene };

	player = new Player{ nowScene };



	collisionManager->Start();
	player->Start();

}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
