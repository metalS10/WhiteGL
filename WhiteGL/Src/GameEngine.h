/**
*@file	GameEngine.h
*/
#pragma once
#include "Constants.h"
#include "GameMain.h"
#include "RendTexture.h"
#include "Animation.h"
#include "GamePad.h"
#include "GLFWEW.h"

class CGameEngine
{
private :
	CRendTexture* rendTex = NULL;
	std::vector<CAnimation*>* m_pAnim = NULL;
	GLFWwindow* m_Window = NULL;
	bool isInitialized = false;
public:
	CGameEngine() {}
	~CGameEngine(){}
	GLFWwindow* init(int w, int h, const char* file);
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec4 texSize, CVec4 texRect);
	void setChipAnim(CAnimation *&&_val);
	void setChipData(GLuint texID, CVec4 rectData);
	void update();
	void update60();
	const GamePad& GetGamePad() const;
	static CGameEngine& Instance();
	void Run();
};