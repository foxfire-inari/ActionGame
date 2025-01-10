#pragma once
#include "BaseObject.h"
#include "Animation.h"

/// <summary>
/// マップ移動をするオブジェクト
/// </summary>
class WarpObject : public BaseObject
{
public:
	WarpObject(BaseScene* baseScene,F_Vec2 pos ,std::string _nextMapName);
	~WarpObject();

private:

	/// <summary>
	/// 次に読み込むCsvファイルの名前
	/// </summary>
	std::string nextMapName;

};

