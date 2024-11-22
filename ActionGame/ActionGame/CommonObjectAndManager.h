#pragma once
#include<vector>
#include<string>
class Player;

class BaseScene;

class CommonObjectAndManager
{
public:
	CommonObjectAndManager(BaseScene* nowScene);
	~CommonObjectAndManager();

	/// <summary>
	/// ƒvƒŒƒCƒ„[‚ğ•Ô‚·
	/// </summary>
	/// <returns></returns>
	Player* GetPlayer()& { return player; }

private:
	Player* player;

};

