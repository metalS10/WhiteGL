/**
*@file	GameEngine.h
*/
#pragma once
#include "../Constants.h"
#include "../RendTexture/Render.h"
#include "../GamePad.h"


class CCharacter;
class CGameEngine
{
private :
	GLFWwindow* m_Window = NULL;
	bool isInitialized = false;


	int EnemyTexID = START_ENEMY_TEXTURE_NUMBER;


	render::CRenderer* m_renderer;
public:
	float m_hitStop = 0.0f;
	//ゲーム中フラグ(ゲームを終了するときに卸す)
	bool gameNow = true;

public:
	CGameEngine();
	~CGameEngine();
	GLFWwindow* init(int w, int h, const char* file);
	void renderInit();		//描画の初期化
	void changeStageInit();		//ステージ移動用の初期化
	
	void update();
	void update60();
	const GamePad& GetGamePad() const;
	static CGameEngine& Instance();


	void HitStop(float time);
	void GameEnd();

	render::CRenderer* getRenderer();



};