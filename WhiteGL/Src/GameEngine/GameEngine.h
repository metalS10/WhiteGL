/**
*@file	GameEngine.h
*/
#pragma once
#include "../Constants.h"
#include "../RendTexture/Render.h"
#include "../Data/Animation/Animation.h"
#include "../GamePad.h"
#include "../GLFWEW/GLFWEW.h"
#include "../interpreter/interpreter.h"

//ポリゴン設定に使うポリゴン判別
enum POLY_TYPE :GLuint
{
	TRIANGLE	= 0,
	QUAD		= 1,
};

class CCharacter;
class CGameEngine
{
private :
	CRenderer* renderer = NULL;
	std::vector<CAnimation*>* m_pAnim = NULL;
	GLFWwindow* m_Window = NULL;
	bool isInitialized = false;

	int countMap = 0;

	int EnemyTexID = START_ENEMY_TEXTURE_NUMBER;

	bool actionone1 = false;
public:
	float m_hitStop = 0.0f;
	//ゲーム中フラグ(ゲームを終了するときに卸す)
	bool gameNow = true;

public:
	CGameEngine() {}
	~CGameEngine(){}
	GLFWwindow* init(int w, int h, const char* file);
	void renderInit();		//描画の初期化
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color);	//テクスチャ設定
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect);				//色変更なしoverload
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer);	//テクスチャ設定(レイヤー設定あり)
	void setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, LAYER layer);				//色変更なしoverload(レイヤー設定あり)
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype);		//背景三角ポリゴンの設定(vertex(中央X,中央Y,Width,Height))
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype,const LAYER layer);		//layer設定あり背景三角ポリゴンの設定(vertex(中央X,中央Y,Width,Height))
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype,const GLuint tag);		//layer設定あり背景三角ポリゴンの設定(vertex(中央X,中央Y,Width,Height))後に編集する場合のためのtag指定
	void setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype,const LAYER layer, const GLuint tag);		//layer設定あり背景三角ポリゴンの設定(vertex(中央X,中央Y,Width,Height))後に編集する場合のためのtag指定
	void setTrianglesPolyPos(const float vertexX, const CVec4 color, const GLuint number);	//背景三角ポリゴンの位置再設定(X座標のみ)
	void setPolyPos(const CVec2 vertex, const GLuint tag);	//ポリゴンの位置再設定
	void setPolyScale(const CVec2 scale , const GLuint tag);	//ポリゴンのスケール再設定
	void setPolyPosX(const float vertex, const GLuint tag);	//ポリゴンのX位置再設定
	void setPolyAngle(const float angle, const GLuint tag);	//ポリゴンの回転設定
	void setPolyColor(const CVec4 color, const GLuint tag);	//ポリゴンの色設定
	void addPolyAngle(const float angle, const GLuint tag);	//ポリゴンの回転設定
	float getPolyAngle(const GLuint tag);	//ポリゴンの回転ゲット
	CVec2 getPolyScale(const GLuint tag);	//ポリゴンのスケール取得
	CVec4 getPolyColor(const GLuint tag);	//ポリゴンの色取得
	void setChipAnim(CAnimation *&&_val);		//Chipアニメーション設定
	void setChipData(GLuint texID, CVec4 rectData);	
	void update();
	void update60();
	void render();		//　描画処理
	const GamePad& GetGamePad() const;
	static CGameEngine& Instance();
	void setTextureRect(const CVec4 mrect,const GLuint texID);
	void setTexPosition(CVec2 pos, GLuint texID);
	void setTexScale(CVec2 scale,GLuint texID);
	void setTexScaleAtTag(const CVec2 scale,const GLuint tag);
	void setTexColorAtTag(const CVec4 color,const GLuint tag);
	void deleteTexture(const GLuint texID);
	void deletePoly(const GLuint tag);
	void allTextureDelete();
	void allTextureDeletenotPlayer();
	void SetProgressBarWH(const GLuint texID, const CVec4 Rect, const CVec2 position);

	void loadTMXMap(CLayerData layerData[MAX_LAYER_NUMBER], int width, int height);
	void TMXMapSetPos(float x, float y);
	void layerSetPos(float x, float y, GLuint texID);

	//アクション
	bool ActionStage(const GLuint texID, const float fadeInterval, const bool fade);
	void* TextureFade(const GLuint texID, const bool out ,const float fadeInterval);
	bool getFadeEnd(const GLuint tag);

	CRenderer* getRenderer();

	void HitStop(float time);
	void GameEnd();

	/**
	*	mode
	*0.Random
	*1.Up
	*2.doubleUp
	*/
	void notesAction(int mode);
	//beatsに合わせるアクション(0:Vert,1:Color)
	void polygonAction(const GLuint tag,const GLuint mode);




};