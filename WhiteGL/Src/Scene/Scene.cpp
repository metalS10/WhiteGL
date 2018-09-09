#include "Scene.h"

CScene::CScene()
{
}
CScene::~CScene()
{
}

bool CScene::init()
{

	m_game.ActionStage(MAX_TEXTURE_NUMBER - 1, 1.0f, true);



	//BGM開始初期化
	m_BGMStart = false;
	//BGMをロード
	BGM->Load();
	//BGMにセットされているBPMを取得
	m_bgmBpm = BGM->getBpm();
	//BPMから秒を計算(ms)
	this->m_halfNotes = (60 / m_bgmBpm)  * 2 * 1000;
	this->m_quarterNotes = (60 / m_bgmBpm)  * 1000;
	this->m_eighthNotes = (60 / m_bgmBpm) * 0.5 * 1000;




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

void CScene::rendUpdate()
{

	//BGM開始
	if (!m_BGMStart)
	{
		m_BGMStart = true;
		BGM->Play();

		//ステージ切り替わり用の初期化
		if (this->stageChangeInit() == false)
			printf("ステージ遷移用初期化に失敗");

		//LARGE_INDEGER変数の初期化
		memset(&m_nFreq, 0x00, sizeof m_nFreq);
		memset(&m_nInit, 0x00, sizeof m_nInit);
		memset(&m_nAfter, 0x00, sizeof m_nAfter);

		m_nInit.QuadPart = 0;
		m_nAfter.QuadPart = 0;
		HalfTime = 0;
		QuarterTime = 0;
		EighthTime = 0;


		//高解像度カウンタ対応判別 & PCの周波数get
		if (QueryPerformanceFrequency(&m_nFreq))
		{
			//高解像度カウンタに対応しています！
			m_queryPC = true;
			//ゲーム開始ms取得
			QueryPerformanceCounter(&m_nInit);
		}
		else
		{
			//対応していなければ1ms感覚のtimeGetTime()を使用(少しずれます)
			m_nInit.QuadPart = timeGetTime();
		}
	}

	//時間を受け取る
	if (m_queryPC)
	{
		//高解像度カウンタ
		QueryPerformanceCounter(&m_nAfter);
	}
	else
	{
		//Windows起動からのカウンタ
		m_nAfter.QuadPart = timeGetTime();
	}

	Time = ((double)(m_nAfter.QuadPart - m_nInit.QuadPart) * 1000 / (double)m_nFreq.QuadPart);	//周波数で割る
	//printf("%f ミリ秒\n", Time);

	//二分のタイミング(ms)
	if (Time - HalfTime >= m_halfNotes)
	{
		HalfTime += m_halfNotes;
		halfUpdate();
	}

	//四分のタイミング
	if (Time - QuarterTime >= m_quarterNotes)
	{
		QuarterTime += m_quarterNotes;
		qauarterUpdate();
		
	}

	//八分のタイミング
	if (Time - EighthTime >= m_eighthNotes)
	{
		EighthTime += m_eighthNotes;
		eighthUpdate();
	}
	
}

void CScene::halfUpdate()
{
	//std::cerr << 2 << std::endl;
	//se1->Play();
}
void CScene::qauarterUpdate()
{
	//std::cerr << 4 << std::endl;
	//se2->Play();
}
void CScene::eighthUpdate()
{
	//std::cerr << 8 << std::endl;
	//se3->Play();
}