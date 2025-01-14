#pragma once
#include "BaseScene.h"
#include "Animation.h"
class TitleScene : public BaseScene
{
public:
	TitleScene(SceneChange* sceneChange);
	~TitleScene();
	bool Update()override;
	void Draw()override;
private:	

	Animation* animation;
	int animNum;//�S�ẴA�j���[�V�������Ǘ�����

	//�C���[�W
	int titleH;
	int playerH;
	int groundH;

	bool isStart;//�X�^�[�g������
	int startCount;//�X�^�[�g���Ă���̃J�E���g

	void SetImageH();	//�`�悷�镨���Z�b�g����

};

