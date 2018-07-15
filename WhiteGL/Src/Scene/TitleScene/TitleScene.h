#pragma once
#include "../Scene.h"
#include "../GameMainScene/GameMainScene.h"

class CTitle : public CScene
{
private:
	int m_select = 0;
	bool m_pushButton = false;
public:
	CTitle();
	~CTitle();
	bool init()override;
	void update()override;
	void rendUpdate()override ;
	void sceneUpdate()override {};
	void qauarterUpdate()override;
	void eighthUpdate()override;

	void selectingButton(const int selecting);

};