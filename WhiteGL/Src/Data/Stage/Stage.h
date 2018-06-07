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
public:
	CStage(){}
	~CStage(){}
	//初期化処理(指定のマップを開く)
	virtual void init() {}
	//次のステージを返す。クリアならNULL。
	virtual CStage* changeStage() { return NULL; }
	//ステージ指定のBGMを返す。
	virtual CSound* getBGM() { return NULL; }

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
};