#pragma once
#include "Common.h"
#include"SceneChange.h"
class GameScene;

//ーーーーーーテスト用
#include "Player.h"
class Player;
//ーーーーーーテスト用

class GameMaster : public SceneChange
{
	Player* player;
public:
	GameMaster();
	~GameMaster();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// シーンとマップの切り替えを行う
	/// </summary>
	/// <param name="nextscenenum">次のシーンの番号</param>
	/// <param name="nextmapname">次のマップの名前</param>
	/// <param name="oldmapname">元々いたマップの名前</param>
	/// <returns>切り替えに成功したらtrue</returns>
	bool Change(int nextscenenum, std::string nextmapname, std::string oldmapname)override;

private:
	std::list<BaseScene*> scene;

};

