#pragma once
#include "../Data/Notes/Notes.h"
#include "../Data/Animation/Animation.h"

class CNotesUI
{
private :

public:
	//コンストラクタ
	CNotesUI();
	//デストラクタ
	~CNotesUI();

	int m_state = 0;
	const char* texPas;

	CNotesAnimation2* m_pNotes = {};

	std::vector<CAnimation*>* m_pAnimations;

	bool init();

	void update();

	void half();
	void quarter();
	void eighth();


};