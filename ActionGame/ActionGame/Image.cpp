#include "Image.h"

Image* Image::Singleton::instance = nullptr;

Image::Image()
{
	playerIdleH.at(0) = LoadGraph("Data/Image/Player/Idle/right.png");
	playerIdleH.at(1) = LoadGraph("Data/Image/Player/Idle/left.png");
}

Image::~Image()
{
}

int Image::GetPlayerIdleH(int index) const
{
	//�s���Ȓl��n���h���̃T�C�Y���傫���l�����͂��ꂽ��-1�i�G���[������l�j��Ԃ�
	if (index < 0 || index >= playerIdleH.size())return -1;
	return playerIdleH.at(index);

}

int Image::GetPlayerWalkH(int index) const
{
	//�s���Ȓl��n���h���̃T�C�Y���傫���l�����͂��ꂽ��-1�i�G���[������l�j��Ԃ�
	if (index < 0 || index >= playerWalkH.size())return -1;
	return playerWalkH.at(index);
}

int Image::GetPlayerAttackH(int index) const
{
	//�s���Ȓl��n���h���̃T�C�Y���傫���l�����͂��ꂽ��-1�i�G���[������l�j��Ԃ�
	if (index < 0 || index >= playerAttackH.size())return -1;
	return playerAttackH.at(index);
}

int Image::GetplayerFallH(int index) const
{
	//�s���Ȓl��n���h���̃T�C�Y���傫���l�����͂��ꂽ��-1�i�G���[������l�j��Ԃ�
	if (index < 0 || index >= playerFallH.size())return -1;
	return playerFallH.at(index);
}

int Image::GetTerryH(int index) const
{
	//�s���Ȓl��n���h���̃T�C�Y���傫���l�����͂��ꂽ��-1�i�G���[������l�j��Ԃ�
	if (index < 0 || index >= terryH.size())return -1;
	return terryH.at(index);
}

int Image::GetBlockH(int index) const
{
	//�s���Ȓl��n���h���̃T�C�Y���傫���l�����͂��ꂽ��-1�i�G���[������l�j��Ԃ�
	if (index < 0 || index >= BlockH.size())return -1;
	return BlockH.at(index);
}
