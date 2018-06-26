#pragma once
#include "../AllController/AllController.h"
#include "../Data/Sound/Sound.h"
#include <Windows.h>
#include <vector>

//シーンの親となるクラス
class CScene
{
protected:

	//カメラの動いた値を設定する変数
	float cameraMoveX = 0.0f;
	float cameraPosX = 0.0f;
	float cameraMoveY = 0.0f;
	float cameraPosY = 0.0f;

	//カメラシェイクスイッチ
	bool m_shake = false;

	//揺らす大きさ
	float m_shakeRange = 0.0f;

	//揺らした回数
	int m_shakeCount = 0;

	//何フレーム毎に動かす
	int m_shakeFrame = 0;
	int m_shakeFrameCount = 0;
	bool m_shakeFripFrop = false;

	//ゲームエンジン
	CGameEngine& m_game = MS::CMS::getInstance()->getGame();
	//入力
	Input::CGameInput* input = MS::CMS::getInstance()->getInput();

	//BGM
	CSound* BGM = NULL;

	//BGMのBPM
	float m_bgmBpm = 0;
	//BPMに合わせて動かすためのカウンター
	int m_bpmCounter = 0;
	//2分音符
	double m_halfNotes = 0;		
	//4
	double m_quarterNotes = 0;
	//8
	double m_eighthNotes = 0;

	
	//周波数,最初のms,updateのms
	LARGE_INTEGER m_nFreq, m_nInit, m_nAfter;

	//二分音符、四分音符、八分音符(ms)
	double Time = 0, HalfTime = 0, QuarterTime = 0, EighthTime = 0;

	CSound* m_attackSE = NULL;
	CSound* m_avoidanceSE = NULL;
	CSound* m_enemyDestroySE = NULL;

	//高解像度カウンタ対応判別(Windows NT(/2000) 3.1 以降,Windows95(/98)以降)
	bool m_queryPC = false;

	int Delay = 0;

	bool m_BGMStart = false;
public:

	//コンストラクタ
	CScene();

	//デストラクタ
	virtual ~CScene() ;
	//初期化処理
	virtual bool init();

	//更新処理
	virtual void update() {};
	//ゲーム本体更新
	virtual void sceneUpdate() {};

	//描画用Update
	virtual void rendUpdate() ;

	//bpm等の少し細かい更新処理
	//virtual void bpmUpdate();

	//カメラシェイクのセット
	void SetCameraShake(float range, int count, int frame);

	//カメラシェイク
	void cameraShake();


	void moveScene(CScene* scene);

	//分音符に合わせて呼ばれる関数
	virtual void halfUpdate();
	virtual void qauarterUpdate();
	virtual void eighthUpdate();

};
