#include "BlockManager.h"
#include "Image.h"
#include "Block.h"


BlockManager::BlockManager(BaseScene* baseScene, std::vector<std::vector<std::string>> _info)
	:BaseManager{ baseScene,BaseManager::E_MANAGER_TAG::BLOCK }
{
	//ブロック用の配列にずれが生じないように定数で減らす
	//画像を0から始めるためにCSV_BLOCK
	static const int IMAGE_DIF = BaseManager::E_CSV_KND::CSV_BLOCK_WALL;

	F_Vec2 pos = {};

	int imageH = -1;

	//読み込んだデータでブロックを生成する
	int knd = 0;
	for (int i = 0; i < _info.size(); i++)
	{
		knd = std::stoi(_info.at(i).at(0));

		switch (knd)
		{
		case E_CSV_KND::CSV_BLOCK_WALL:
		case E_CSV_KND::CSV_BLOCK_GRASS:
			SetObject(pos, _info.at(i));
			//1つの画像しか使わないから先に画像を取得しておく
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
		//nullptrじゃなければ消す
		if (*it != nullptr)
		{
			delete* it;
			*it = nullptr;
			//ここで要素を消してるから前詰めされる
			it = blockList.erase(it);
		}
		else it++;//要素がなければインクリメントでendにする
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
