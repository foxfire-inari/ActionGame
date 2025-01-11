#include "Image.h"

Image* Image::Singleton::instance = nullptr;

Image::Image()
{

	//プレイヤー

	playerIdleH.at(0) = LoadGraph("Data/Image/Player/Idle/right.png"); 
	playerIdleH.at(1) = LoadGraph("Data/Image/Player/Idle/left.png");

	playerWalkH.at(0) = LoadGraph("Data/Image/Player/Walk/right_1.png");
	playerWalkH.at(1) = LoadGraph("Data/Image/Player/Walk/right_2.png");
	playerWalkH.at(2) = LoadGraph("Data/Image/Player/Walk/right_3.png");
	playerWalkH.at(3) = LoadGraph("Data/Image/Player/Walk/right_2.png");
	playerWalkH.at(4) = LoadGraph("Data/Image/Player/Walk/left_1.png");
	playerWalkH.at(5) = LoadGraph("Data/Image/Player/Walk/left_2.png");
	playerWalkH.at(6) = LoadGraph("Data/Image/Player/Walk/left_3.png");
	playerWalkH.at(7) = LoadGraph("Data/Image/Player/Walk/left_2.png");

	playerFallH.at(0) = LoadGraph("Data/Image/Player/Fall/right.png");
	playerFallH.at(1) = LoadGraph("Data/Image/Player/Fall/left.png");

	playerDamageH.at(0) = LoadGraph("Data/Image/Player/Damage/right.png");
	playerDamageH.at(1) = LoadGraph("Data/Image/Player/Damage/left.png");


	//ブロック
	blockH.at(0) = LoadGraph("Data/Image/Blocks/ground.png");
	blockH.at(1) = LoadGraph("Data/Image/Blocks/grass.png");

	//ワープ
	warpH.at(0) = LoadGraph("Data/Image/Blocks/Warp/warp_1.png");
	warpH.at(1) = LoadGraph("Data/Image/Blocks/Warp/warp_2.png");
	warpH.at(2) = LoadGraph("Data/Image/Blocks/Warp/warp_3.png");
	warpH.at(3) = LoadGraph("Data/Image/Blocks/Warp/warp_4.png");
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
