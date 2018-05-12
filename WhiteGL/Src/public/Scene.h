#pragma once
#include "../MSlib.h"
#include "../Data/Sound/Sound.h"

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
	int m_halfNotes = 0;		int m_halfCounter = 100;
	//4
	int m_quarterNotes = 0;		int m_quarterCounter = 100;
	//8
	int m_eighthNotes = 0;		int m_eighthCounter = 100;
	//BGM開始遅延
	int m_startDelay = 0;
	int m_delayCount = 0;

	CSound* se1 = NULL;
	CSound* se2 = NULL;
	CSound* se3 = NULL;

	int Delay = 0;

	bool m_BGMStart = false;
public:

	//コンストラクタ
	CScene();

	//デストラクタ
	virtual ~CScene() {};
	//初期化処理
	virtual bool init();

	//更新処理
	virtual void update();
	//ゲーム本体更新
	virtual void sceneUpdate() {};

	//描画用Update
	virtual void rendUpdate() {};

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
