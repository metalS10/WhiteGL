#pragma once
#include "../Scene.h"
#include "../GameMainScene/GameMainScene.h"

class CTitle : public CScene
{
private:
	int select = 0;
	bool pushButton = false;
public:
	CTitle();
	~CTitle();
	bool init()override;
	void update()override;
	void rendUpdate()override ;
	void sceneUpdate()override {};
	void qauarterUpdate()override;
	void eighthUpdate()override;

};