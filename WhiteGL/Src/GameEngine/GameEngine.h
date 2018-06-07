/**
*@file	GameEngine.h
*/
#pragma once
#include "../Constants.h"
#include "../RendTexture/RendTexture.h"
#include "../Data/Animation/Animation.h"
#include "../GamePad.h"
#include "../GLFWEW/GLFWEW.h"
#include "../interpreter/interpreter.h"

class CCharacter;
class CGameEngine
{
private :
	CRendTexture* rendTex = NULL;
	std::vector<CAnimation*>* m_pAnim = NULL;
	GLFWwindow* m_Window = NULL;
	bool isInitialized = false;

	int countMap = 0;

	int EnemyTexID = START_ENEMY_TEXTURE_NUMBER;

	bool actionone1 = false;
public:
	float m_hitStop = 0.0f;

public:
	CGameEngine() {}
	~CGameEngine(){}
	GLFWwindow* init(int w, int h, const char* file);
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color);	//テクスチャ設定
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect);				//色変更なしoverload
	void setChipAnim(CAnimation *&&_val);		//Chipアニメーション設定
	void setChipData(GLuint texID, CVec4 rectData);	
	void update();
	void update60();
	void render();		//　描画処理
	const GamePad& GetGamePad() const;
	static CGameEngine& Instance();
	void setTextureRect(const CVec4 mrect,const GLuint texID);
	void setPosition(CVec2 pos, GLuint texID);
	void setScale(CVec2 scale,GLuint texID);
	void deleteTexture(const GLuint texID);
	void allTextureDelete();
	void allTextureDeletenotPlayer();
	void SetProgressBarWH(const GLuint texID, const CVec4 Rect, const CVec2 position);
	//アクション
	bool ActionStage(const GLuint texID, const float fadeInterval, const bool fade);
	void* TextureFade(const GLuint texID, const bool out ,const float fadeInterval);
	bool getFadeEnd(const GLuint texID);

	CRendTexture* getRendTexture();


	void loadTMXMap(CLayerData layerData[MAX_LAYER_NUMBER],int width,int height);
	void TMXMapSetPos(float x,float y);
	void layerSetPos(float x, float y,GLuint texID);

	void HitStop(float time);

	




};