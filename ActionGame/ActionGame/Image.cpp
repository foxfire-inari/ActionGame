#include "Image.h"

Image* Image::Singleton::instance = nullptr;

Image::Image()
{

	//プレイヤー

	playerIdleH.at(0) = LoadGraph("Data/Image/Chara/Player/Idle/left.png");
	playerIdleH.at(1) = LoadGraph("Data/Image/Chara/Player/Idle/right.png");
	for (int i = 0; i < playerIdleH.size(); i++)
	{
		assert(playerIdleH.at(i) > 0);
	}

	playerWalkH.at(0) = LoadGraph("Data/Image/Chara/Player/Walk/left_1.png");
	playerWalkH.at(1) = LoadGraph("Data/Image/Chara/Player/Walk/left_2.png");
	playerWalkH.at(2) = LoadGraph("Data/Image/Chara/Player/Walk/left_3.png");
	playerWalkH.at(3) = LoadGraph("Data/Image/Chara/Player/Walk/left_2.png");
	playerWalkH.at(4) = LoadGraph("Data/Image/Chara/Player/Walk/right_1.png");
	playerWalkH.at(5) = LoadGraph("Data/Image/Chara/Player/Walk/right_2.png");
	playerWalkH.at(6) = LoadGraph("Data/Image/Chara/Player/Walk/right_3.png");
	playerWalkH.at(7) = LoadGraph("Data/Image/Chara/Player/Walk/right_2.png");
	for (int i = 0; i < playerWalkH.size(); i++)
	{
		assert(playerWalkH.at(i) > 0);
	}

	playerFallH.at(0) = LoadGraph("Data/Image/Chara/Player/Fall/left.png");
	playerFallH.at(1) = LoadGraph("Data/Image/Chara/Player/Fall/right.png");
	for (int i = 0; i < playerFallH.size(); i++)
	{
		assert(playerFallH.at(i) > 0);
	}

	playerDamageH.at(0) = LoadGraph("Data/Image/Chara/Player/Damage/left.png");
	playerDamageH.at(1) = LoadGraph("Data/Image/Chara/Player/Damage/right.png");
	for (int i = 0; i < playerDamageH.size(); i++)
	{
		assert(playerDamageH.at(i) > 0);
	}

	//テリー

	terryH.at(0) = LoadGraph("Data/Image/Chara/Enemy/Terry/top.png");
	terryH.at(1) = LoadGraph("Data/Image/Chara/Enemy/Terry/right.png");
	terryH.at(2) = LoadGraph("Data/Image/Chara/Enemy/Terry/under.png");
	terryH.at(3) = LoadGraph("Data/Image/Chara/Enemy/Terry/left.png");
	for (int i = 0; i < terryH.size(); i++)
	{
		assert(terryH.at(i) > 0);
	}

	//メットール

	metallIdleH.at(0) = LoadGraph("Data/Image/Chara/Enemy/Metall/Idle/left.png");
	metallIdleH.at(1) = LoadGraph("Data/Image/Chara/Enemy/Metall/Idle/right.png");
	for (int i = 0; i < metallIdleH.size(); i++)
	{
		assert(metallIdleH.at(i) > 0);
	}

	metallRunH.at(0) = LoadGraph("Data/Image/Chara/Enemy/Metall/Run/left_1.png");
	metallRunH.at(1) = LoadGraph("Data/Image/Chara/Enemy/Metall/Run/left_2.png");
	metallRunH.at(2) = LoadGraph("Data/Image/Chara/Enemy/Metall/Run/right_1.png");
	metallRunH.at(3) = LoadGraph("Data/Image/Chara/Enemy/Metall/Run/right_2.png");
	for (int i = 0; i < metallRunH.size(); i++)
	{
		assert(metallRunH.at(i) > 0);
	}

	metallUpH.at(0) = LoadGraph("Data/Image/Chara/Enemy/Metall/Up/left_1.png");
	metallUpH.at(1) = LoadGraph("Data/Image/Chara/Enemy/Metall/Up/left_2.png");
	metallUpH.at(2) = LoadGraph("Data/Image/Chara/Enemy/Metall/Up/right_1.png");
	metallUpH.at(3) = LoadGraph("Data/Image/Chara/Enemy/Metall/Up/right_2.png");
	for (int i = 0; i < metallUpH.size(); i++)
	{
		assert(metallUpH.at(i) > 0);
	}

	//メタルマン

	metalManIdleH.at(0) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/left_1.png");
	metalManIdleH.at(1) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/left_2.png");
	metalManIdleH.at(2) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/left_3.png");
	metalManIdleH.at(3) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/left_2.png");
	metalManIdleH.at(4) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/right_1.png");
	metalManIdleH.at(5) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/right_2.png");
	metalManIdleH.at(6) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/right_3.png");
	metalManIdleH.at(7) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Idle/right_2.png");
	for (int i = 0; i < metalManIdleH.size(); i++)
	{
		assert(metalManIdleH.at(i) > 0);
	}

	metalManJumpH.at(0) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Jump/left.png");
	metalManJumpH.at(1) = LoadGraph("Data/Image/Chara/Enemy/MetalMan/Jump/right.png");
	for (int i = 0; i < metalManJumpH.size(); i++)
	{
		assert(metalManJumpH.at(i) > 0);
	}


	//弾

	bulletH.at(0) = LoadGraph("Data/Image/Bullet/normal.png");
	bulletH.at(1) = LoadGraph("Data/Image/Bullet/ball.png");
	bulletH.at(2) = LoadGraph("Data/Image/Bullet/metal.png");
	for (int i = 0; i < bulletH.size(); i++)
	{
		assert(bulletH.at(i) > 0);
	}

	//ブロック
	blockH.at(0) = LoadGraph("Data/Image/Blocks/ground.png");
	blockH.at(1) = LoadGraph("Data/Image/Blocks/grass.png");
	for (int i = 0; i < blockH.size(); i++)
	{
		assert(blockH.at(i) > 0);
	}

	//ワープ
	warpH.at(0) = LoadGraph("Data/Image/Blocks/Warp/warp_1.png");
	warpH.at(1) = LoadGraph("Data/Image/Blocks/Warp/warp_2.png");
	warpH.at(2) = LoadGraph("Data/Image/Blocks/Warp/warp_3.png");
	warpH.at(3) = LoadGraph("Data/Image/Blocks/Warp/warp_4.png");
	for (int i = 0; i < warpH.size(); i++)
	{
		assert(warpH.at(i) > 0);
	}

	//ワープ中
	waveH.at(0) = LoadGraph("Data/Image/Wave/wave_1.png");
	waveH.at(1) = LoadGraph("Data/Image/Wave/wave_2.png");
	waveH.at(2) = LoadGraph("Data/Image/Wave/wave_3.png");
	waveH.at(3) = LoadGraph("Data/Image/Wave/wave_4.png");
	for (int i = 0; i < waveH.size(); i++)
	{
		assert(waveH.at(i) > 0);
	}

	//エフェクト
	effectH.at(0) = LoadGraph("Data/Image/Effect/effect_1.png");
	effectH.at(1) = LoadGraph("Data/Image/Effect/effect_2.png");
	effectH.at(2) = LoadGraph("Data/Image/Effect/effect_3.png");
	effectH.at(3) = LoadGraph("Data/Image/Effect/effect_4.png");
	for (int i = 0; i < effectH.size(); i++)
	{
		assert(effectH.at(i) > 0);
	}
	
	//空
	skyH.at(0) = LoadGraph("Data/Image/Sky/グレイシア.png");


	//タイトル
	titleH = LoadGraph("Data/Image/Title/title.png");
	assert(titleH > 0);

	titleGroundH = LoadGraph("Data/Image/Title/ground.png");
	assert(titleGroundH > 0);

	//ゲームオーバー
	gameOverH = LoadGraph("Data/Image/GameOver/gameover.png");
	assert(gameOverH > 0);
}

Image::~Image()
{
}

int Image::GetPlayerIdleH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= playerIdleH.size())return -1;
	return playerIdleH.at(index);

}

int Image::GetPlayerWalkH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= playerWalkH.size())return -1;
	return playerWalkH.at(index);
}

int Image::GetPlayerFallH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= playerFallH.size())return -1;
	return playerFallH.at(index);
}

int Image::GetPlayerDamageH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= playerDamageH.size())return -1;
	return playerDamageH.at(index);
}

int Image::GetTerryH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= terryH.size())return -1;
	return terryH.at(index);
}

int Image::GetMetallIdleH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= metallIdleH.size())return -1;
	return metallIdleH.at(index);
}

int Image::GetMetallRunH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= metallRunH.size())return -1;
	return metallRunH.at(index);
}

int Image::GetMetallUpH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= metallUpH.size())return -1;
	return metallUpH.at(index);
}

int Image::GetMetalManIdleH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= metalManIdleH.size())return -1;
	return metalManIdleH.at(index);
}

int Image::GetMetalManJumpH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= metalManJumpH.size())return -1;
	return metalManJumpH.at(index);
}

int Image::GetBulletH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= bulletH.size())return -1;
	return bulletH.at(index);
}

int Image::GetBlockH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= blockH.size())return -1;
	return blockH.at(index);
}

int Image::GetWarpH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= warpH.size())return -1;
	return warpH.at(index);
}

int Image::GetWaveH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= warpH.size())return -1;
	return waveH.at(index);
}

int Image::GetEffectH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= warpH.size())return -1;
	return effectH.at(index);
}

int Image::GetSkyH(int index) const
{
	//不明な値やハンドルのサイズより大きい値が入力されたら-1（エラーさせる値）を返す
	if (index < 0 || index >= skyH.size())return -1;
	return skyH.at(index);
}
