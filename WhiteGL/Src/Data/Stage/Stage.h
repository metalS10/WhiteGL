#pragma once
#include "../Sound/Sound.h"
#include "../../Constants.h"
#include "../Map/Map.h"

class CGameEngine;
//ステージ毎の動きを動かす

//各ステージのもととなるクラス
class CStage
{
protected:
	bool Boss = false;

	CSound* bgm;
public:
	CStage(){}
	~CStage(){}
	//初期化処理(指定のマップを開く)
	virtual void init(CGameEngine& game) {}
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() { return NULL; }
	//ステージ指定のBGMを返す。
	virtual CSound* getBGM() { return NULL; }
	//ステージの指定の色を返す(スクロール中)
	virtual CVec4 getChangePositionColor(bool Top) { return NULL; }


	//背景ポリゴン軍
	std::vector<float> m_trianglesLeft = {};
	std::vector<float> m_trianglesRight ={};

	float m_polyRange = 0.0f;

	int backgroundType = 0;
	CVec4 backgroundVertex[2] = {};
	CVec4 backgroundColor[2] = {};
};

//ステージ1-1
class CStage1_1 : public CStage
{
public:
	CStage1_1() {}
	~CStage1_1() {}
	//初期化処理(指定のマップを開く)
	virtual void init(CGameEngine& game) override;
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() override;
	//ステージ指定のBGMを返す。
	virtual CSound* getBGM() override;
	//ステージの指定の色を返す(スクロール中)
	virtual CVec4 getChangePositionColor(bool Top) override;
};
//ステージ1-2
class CStage1_2 : public CStage
{
public:
	CStage1_2() {}
	~CStage1_2() {}
	//初期化処理(指定のマップを開く
	virtual void init(CGameEngine& game) override;
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() override;
	//ステージ指定のBGMを返す
	virtual CSound* getBGM() override;
	//ステージの指定の色を返す(スクロール中)
	virtual CVec4 getChangePositionColor(bool Top) override;
};