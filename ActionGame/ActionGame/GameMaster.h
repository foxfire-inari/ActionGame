#pragma once
<<<<<<< Updated upstream
=======
#include"Common.h"
>>>>>>> Stashed changes
#include"SceneChange.h"
#include<list>
class BaseScene;

class GameMaster : public SceneChange
{

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
	bool Change(int nextSceneNum, std::string nextMapName, std::string oldMapName)override;

private:
	std::list<BaseScene*> scene;

};

