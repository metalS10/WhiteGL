#pragma once
#include "../Sound/Sound.h"
#include "../../Constants.h"
#include "../Map/Map.h"

//ステージ毎の動きを動かす

//各ステージのもととなるクラス
class CStage
{
protected:
	bool Boss = false;

	CSound* bgm;

	std::vector<rendInfo::CTriPolygonRendInfo*> m_bgPoly;
public:
	CStage(){}
	~CStage()
	{
		for (rendInfo::CTriPolygonRendInfo* triPoly : m_bgPoly)
		{
			SAFE_DELETE(triPoly);
		}
	}
	//初期化処理(指定のマップを開く)
	virtual void init() {}
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() { return NULL; }
	//ステージ指定のBGMを返す。
	virtual CSound* getBGM() { return NULL; }
	//ステージの指定の色を返す(スクロール中)
	virtual CVec4 getChangePositionColor(bool Top) { return NULL; }
	//ステージの更新
	virtual	void update() {};

	//背景ポリゴンCulling
	void scrollBackGroundTrianglesLeft(float posX);
	void scrollBackGroundTrianglesRight(float posX);

	//背景ポリゴンのアクション
	void actionBackground(int mode);



protected:
	//背景ポリゴン軍
	std::vector<float> m_trianglesLeft = {};
	std::vector<float> m_trianglesRight ={};

	float m_polyRange = 0.0f;

	CVec4 backgroundVertex[2] = {};
	CVec4 backgroundColor[2] = {};
public:

	int backgroundType = 0;
};

//ステージ1-1
class CStage1_1 : public CStage
{
public:
	CStage1_1() {}
	~CStage1_1() {}
	//初期化処理(指定のマップを開く)
	virtual void init() override;
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() override;
	//ステージ指定のBGMを返す。
	virtual CSound* getBGM() override;
	//ステージの指定の色を返す(スクロール中)
	virtual CVec4 getChangePositionColor(bool Top) override;
	//ステージの更新
	virtual	void update() override;
};
//ステージ1-2
class CStage1_2 : public CStage
{
public:
	CStage1_2() {}
	~CStage1_2() {}
	//初期化処理(指定のマップを開く
	virtual void init() override;
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() override;
	//ステージ指定のBGMを返す
	virtual CSound* getBGM() override;
	//ステージの指定の色を返す(スクロール中)
	virtual CVec4 getChangePositionColor(bool Top) override;
	//ステージの更新
	virtual	void update() override;
};