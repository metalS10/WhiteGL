#pragma once
#include "../MSlib.h"

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
public:

	//コンストラクタ
	CScene();

	//デストラクタ
	virtual ~CScene() {};
	//初期化処理
	virtual bool init();

	//更新処理
	virtual void update() {};
	//ゲーム本体更新
	virtual void sceneUpdate() {};

	//描画用Update
	virtual void rendUpdate() {};

	//カメラシェイクのセット
	void SetCameraShake(float range, int count, int frame);

	//カメラシェイク
	void cameraShake();


	void moveScene(CScene* scene);
};
