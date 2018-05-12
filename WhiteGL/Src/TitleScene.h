#pragma once
#include "public/Scene.h"
#include "GameMainScene.h"

class CTitle : public CScene
{
private:
	bool flipfrop = false;
	int counter = 0;
public:
	CTitle();
	~CTitle();
	bool init()override;
	void update()override;
	void rendUpdate()override {};
	void sceneUpdate()override {};
	void qauarterUpdate()override;

};