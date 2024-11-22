#include "CommonObjectAndManager.h"
#include "Player.h"

CommonObjectAndManager::CommonObjectAndManager(BaseScene* nowScene)
{
	player = new Player{ nowScene };


	player->Start();
}

CommonObjectAndManager::~CommonObjectAndManager()
{

}
