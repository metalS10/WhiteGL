#pragma once
#include "../MSlib.h"

//シーンの親となるクラス
class CScene
{
protected:

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
	//多分全部に必要
	CGameEngine& m_game = MS::CMS::getInstance()->getGame();
	Input::CGameInput* input = MS::CMS::getInstance()->getInput();
public:
	CScene() { init(); };
	

	//デストラクタ
	virtual ~CScene() {};
	//初期化処理
	virtual bool init() {

		m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true);
		m_game.allTextureDelete();
		return true; };
	//更新処理
	virtual void update() {};
	//ゲーム本体更新
	virtual void sceneUpdate() {};

	//描画用Update
	virtual void rendUpdate() {};

	//カメラシェイクのセット
	void SetCameraShake(float range, int count ,int frame) {
		m_shake = true;
		m_shakeRange = range;
		m_shakeCount = count;
		m_shakeFrame = frame;
	};

	//カメラシェイク
	void cameraShake()
	{
		if (this->m_shake)
		{
			this->m_shakeFrameCount++;
			if (this->m_shakeFrame <= this->m_shakeFrameCount)
			{
				if (m_shakeFripFrop)
				{
					this->m_shakeFrameCount = 0;

					this->cameraMoveY = this->m_shakeRange;

					this->m_shakeRange *= -0.5f;
					this->m_shakeFripFrop = true;
				}
				else
				{
					this->m_shakeFrameCount = 0;
					this->m_shakeCount--;

					this->cameraMoveY = this->m_shakeRange;

					this->m_shakeRange *= -1.0f;
					this->m_shakeFripFrop = false;
				}

				if (this->m_shakeCount <= 0)
				{
					this->cameraMoveY = 0.0f;
					this->m_shakeCount = 0;
					this->m_shake = false;
				}
			}
		}
	}


	void moveScene(CScene* scene)
	{

	}
};
