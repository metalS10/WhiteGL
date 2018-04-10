#include "Scene.h"

CScene::CScene()
{
	init();
}

bool CScene::init()
{
	m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true);
	m_game.allTextureDelete();
	return true;
}

//カメラシェイクのセット
void CScene::SetCameraShake(float range, int count, int frame) 
{
	m_shake = true;
	m_shakeRange = range;
	m_shakeCount = count;
	m_shakeFrame = frame;
};

//カメラシェイク
void CScene::cameraShake()
{
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
}