#pragma once
#include "public/Scene.h"
#include "GameMainScene.h"

class CTitle : public CScene
{
private:
public:
	CTitle();
	~CTitle();
	bool init()override;
	void update()override;
	void rendUpdate()override {};
	void sceneUpdate()override {};
	void qauarterUpdate()override;

};