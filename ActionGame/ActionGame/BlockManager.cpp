#include "BlockManager.h"
#include "Image.h"
#include "Block.h"


BlockManager::BlockManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::BLOCK }
{
	//�u���b�N�p�̔z��ɂ��ꂪ�����Ȃ��悤�ɒ萔�Ō��炷
	//�摜��0����n�߂邽�߂�CSV_BLOCK
	static const int IMAGE_DIF = BaseManager::E_CSV_KND::CSV_BLOCK_WALL;

	F_Vec2 pos = {};

	int imageH = -1;

	//�ǂݍ��񂾃f�[�^�Ńu���b�N�𐶐�����
	int knd = 0;
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));

		switch (knd)
		{
		case E_CSV_KND::CSV_BLOCK_WALL:
		case E_CSV_KND::CSV_BLOCK_GRASS:
			SetObject(pos, _info.at(i));
			//1�̉摜�����g��Ȃ������ɉ摜���擾���Ă���
			imageH = Image::GetInstance()->GetBlockH(knd - IMAGE_DIF);
			Block* block = new Block{ GetBaseScene(), pos ,imageH };
			blockList.emplace_back(block);
			continue;
			break;
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
