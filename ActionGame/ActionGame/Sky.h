#pragma once
#include "BaseObject.h"
class Sky : public BaseObject
{
public:
	Sky(BaseScene* baseScene,
		std::vector<std::vector<std::string>> _info);
	~Sky();
	void Update()override;
	void Draw(F_Vec2 _camDif)override;
private:
	int imageH;
};

