#include "BlockManager.h"
#include "Image.h"
#include "Block.h"


BlockManager::BlockManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::BLOCK }
{
	//�u���b�N�p�̔z��ɂ��ꂪ�����Ȃ��悤�ɒ萔�Ō��炷
	//�摜��0����n�߂邽�߂�CSV_BLOCK
	static const int IMAGE_DIF = BaseManager::E_CSV_KND::CSV_BLOCK;

	F_Vec2 pos = {};

	int imageH = -1;

	//�ǂݍ��񂾃f�[�^�Ńu���b�N�𐶐�����
	int knd = 0;
	for (int y = 0; y < _info.size(); y++)
	{
		for (int x = 0; x < _info.at(y).size(); x++)
		{
			knd = std::stoi(_info.at(y).at(x));

			switch (knd)
			{
			case E_CSV_KND::CSV_BLOCK:
			case E_CSV_KND::CSV_GRASS:
				pos = { static_cast<float>(x),static_cast<float>(y) };
				SetObject(pos, _info.at(y));

				imageH = Image::GetInstance()->GetBlockH(knd - IMAGE_DIF);
				Block* block = new Block{ GetBaseScene(), pos ,imageH };
				blockList.emplace_back(block);
				continue;
				break;
			}
		}
	}

}

BlockManager::~BlockManager()
{
	for (auto it = blockList.begin(); it != blockList.end();)
	{
		//nullptr����Ȃ���Ώ���
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			//�����ŗv�f�������Ă邩��O�l�߂����
			it = blockList.erase(it);
		}
		else it++;//�v�f���Ȃ���΃C���N�������g��end�ɂ���
	}
}

void BlockManager::Start()
{
	Init();

}

void BlockManager::Update()
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		(*it)->Update();
	}
}

void BlockManager::Draw(F_Vec2 _camDif)
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		(*it)->Draw(_camDif);
	}
}

const std::list<CollisionObject*> BlockManager::GetCollisionObjList() const
{
	std::list<CollisionObject*> collObjList;

	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		collObjList.emplace_back(*it);
	}

	return collObjList;
}

void BlockManager::SetObjectNewScene(BaseScene* _baseScene)
{
	for (auto it = blockList.begin(); it != blockList.end(); it++)
	{
		(*it)->SetNewScene(_baseScene);
	}
}
