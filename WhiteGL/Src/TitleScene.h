#pragma once
#include "public/Scene.h"
#include "GameMainScene.h"

class CTitle : public CScene
{
private:

public:
	CTitle(bool end);
	~CTitle();
	bool init()override;
	void update()override;
	
};