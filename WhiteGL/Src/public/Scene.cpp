#include "Scene.h"

CScene::CScene()
{
}

bool CScene::init()
{
	m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true);
	m_game.allTextureDelete();
	m_bgmBpm = BGM->getBpm();
	this->m_halfNotes = (60 / m_bgmBpm) *60 * 2;
	this->m_quarterNotes = (60 / m_bgmBpm) * 60 ;
	this->m_eighthNotes = (60 / m_bgmBpm) * 60 / 2;
	se1 = new CSound(SOUND_TEST_HALF,4);
	se2 = new CSound(SOUND_TEST_QUARTER,8);
	se3 = new CSound(SOUND_TEST_EIGHTH,16);
	se1->Load();
	se2->Load();
	se3->Load();
	m_startDelay = 0;
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

void CScene::update()
{
	//開始遅延のタイミングになれば
	if (m_delayCount >= m_startDelay)
	{
		this->m_halfCounter++;
		this->m_quarterCounter++;
		this->m_eighthCounter++;
		if (m_halfCounter > m_halfNotes)
		{
			m_halfCounter = 0;
			//2分音符
			this->halfUpdate();
		}
		if (m_quarterCounter > m_quarterNotes)
		{
			m_quarterCounter = 0;
			//4分音符
			this->qauarterUpdate();
		}
		if (m_eighthCounter > m_eighthNotes)
		{
			m_eighthCounter = 0;
			//8分音符
			this->eighthUpdate();
		}
	}
	else
	{
		//Delay
		m_delayCount++;
	}
}

void CScene::halfUpdate()
{
	//std::cerr << 2 << std::endl;
	//se1->Play();
}
void CScene::qauarterUpdate()
{
	std::cerr << 4 << std::endl;
	se2->Play();
}
void CScene::eighthUpdate()
{
	//std::cerr << 8 << std::endl;
	//se3->Play();
}