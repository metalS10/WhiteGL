#pragma once
/**
*	GameMain.h
*		2017/9/30	Mats
*		ゲームの中身
*/

#include "Constants.h";

class CGameMain
{
public:
	CGameMain();
	~CGameMain();

	void init();
	void update();

	int i = 0;
};