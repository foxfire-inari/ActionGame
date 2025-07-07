#include "Sky.h"
#include "Image.h"

namespace
{
	//�u���b�N�̏�񂪂���C���f�b�N�X
	static const int SKY_INDEX = 3;

	static const int SKY_LEFT = 0;
	static const int SKY_TOP = 0;
}

Sky::Sky(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseObject{ baseScene, BaseObject::E_TAG::SKY }
	, imageH{ -1 }
{
	//�ǂݍ��񂾃f�[�^�Ńu���b�N�𐶐�����
	int knd = 0;
	GetBaseScene()->SetOneObjectList(this);
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));
		//��̉摜���Z�b�g
		if (knd == BaseManager::E_CSV_KND::CSV_SKY)
		{
			int num = std::stoi(_info.at(i).at(SKY_INDEX));
			imageH = Image::GetInstance()->GetSkyH(num);
		}
	}
}

Sky::~Sky()
{
}

void Sky::Update()
{
}

void Sky::Draw(F_Vec2 _camDif)
{
	DrawGraph
	(
		SKY_LEFT,
		SKY_TOP,
		imageH,
		true
	);
}
