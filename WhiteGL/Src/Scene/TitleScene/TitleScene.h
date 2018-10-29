#pragma once
#include "../Scene.h"

class CTitle : public CScene
{
private:
	int m_select = 0;
	bool m_pushButton = false;
	bool m_pushStart = false;
	bool m_start = false;

	rendInfo::CTexRendInfo* m_titleText	;
	rendInfo::CTexRendInfo* m_startButton;
	rendInfo::CTexRendInfo* m_endButton	;
	rendInfo::CTexRendInfo* m_titleBG	;

	std::vector<rendInfo::CTriPolygonRendInfo*> m_bgPoly;
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
	void selectEnter(bool start);
};