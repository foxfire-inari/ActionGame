#pragma once
#include<string>
#include<vector>

/// <summary>
/// 全てのシーン判別タグ
/// </summary>
enum E_SCENE
{
	TITLE,
	GAME,
	STAGE_SELECT,

	SCENETAG_MAX

};

/// <summary>
/// Change関数を全てのシーンで使えるように分けた
/// </summary>
class SceneChange
{
public:
	SceneChange() {}
	~SceneChange() = default;

	/// <summary>
	/// シーンとマップの切り替えを行う
	/// </summary>
	/// <param name="nextscenenum">次のシーンの番号</param>
	/// <param name="nextmapname">次のマップの名前</param>
	/// <param name="oldmapname">元々いたマップの名前</param>
	/// <returns>切り替えに成功したらtrue</returns>
	virtual bool Change(int nextscenenum, std::string nextmapname ="", std::string oldmapname="") = 0;
};

