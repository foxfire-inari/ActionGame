#pragma once
#include "Animation.h"


/// <summary>
/// ワープ等のシーンの切替の演出をするクラス
/// </summary>
class Waveout
{
public:
	Waveout(float _waitSecond, float _addVal);
	~Waveout();

	void Update();
	void Draw();

	/// <summary>
	/// 暗転後、待ち時間を終えたか
	/// </summary>
	/// <returns></returns>
	bool GetIsWaveFinish()const { return isWaveFinish; }

	/// <summary>
	/// 波を小さくするかをセット
	/// </summary>
	/// <param name="_isReversal"></param>
	void SetIsReversal(bool _isReversal);

	/// <summary>
	/// 波が消え、元に戻ったか
	/// </summary>
	/// <returns></returns>
	bool GetIsReturnFinish()const { return isReturnFinish; }

	/// <summary>
	/// 最初にalphaが255になった時だけtrueを返す
	/// </summary>
	/// <returns></returns>
	bool GetNowMaxAlpha()const;

private:
	int imageH;				//画像
	
	int count;				//波の秒数
	
	float waveCount;		//波のカウント

	float alpha;			//画像の濃さ
	float oldAlpha;			//1フレーム前の画像の濃さ
	float addVal;			//濃さの追加量
	float waitSecond;		//演出の秒数
	
	bool isWaveFinish;		//波の発生から演出の秒数分動いたか
	bool isReturnFinish;	//波の演出から元に戻ったか
	bool isReversal;		//元に戻り始めているか

	Animation* animation;	//ワープの揺らいでる感を出すため

};

