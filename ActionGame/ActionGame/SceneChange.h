#pragma once
#include<string>
#include<vector>

enum SCENETAG
{
	TITLE,
	STAGE_SELECT,
	METAL_STAGE,

	SCENETAG_MAX

};


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
	virtual bool Change(int nextscenenum, std::string nextmapname, std::string oldmapname) =0;
};

