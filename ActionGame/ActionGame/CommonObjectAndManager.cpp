#include "CommonObjectAndManager.h"
#include "Player.h"

#include "CollisionManager.h"

//�w�b�_�[�őO���錾�����N���X�͂����ŃC���N���[�h����

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	player = new Player{ nowScene };

	collisionManager = new CollisionManager{ nowScene };


	player->Start();
	collisionManager->Start();
}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
