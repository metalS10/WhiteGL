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



	//BGM�J�n������
	m_BGMStart = false;
	//BGM�����[�h
	BGM->Load();
	//BGM�ɃZ�b�g����Ă���BPM���擾
	m_bgmBpm = BGM->getBpm();
	//BPM����b���v�Z(ms)
	this->m_halfNotes = (60 / m_bgmBpm)  * 2 * 1000;
	this->m_quarterNotes = (60 / m_bgmBpm)  * 1000;
	this->m_eighthNotes = (60 / m_bgmBpm) * 0.5 * 1000;




	return true;
}

//�J�����V�F�C�N�̃Z�b�g
void CScene::SetCameraShake(float range, int count, int frame) 
{
	m_shake = true;
	m_shakeRange = range;
	m_shakeCount = count;
	m_shakeFrame = frame;
};

//�J�����V�F�C�N
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

	//BGM�J�n
	if (!m_BGMStart)
	{
		m_BGMStart = true;
		BGM->Play();

		//�X�e�[�W�؂�ւ��p�̏�����
		if (this->stageChangeInit() == false)
			printf("�X�e�[�W�J�ڗp�������Ɏ��s");

		//LARGE_INDEGER�ϐ��̏�����
		memset(&m_nFreq, 0x00, sizeof m_nFreq);
		memset(&m_nInit, 0x00, sizeof m_nInit);
		memset(&m_nAfter, 0x00, sizeof m_nAfter);

		m_nInit.QuadPart = 0;
		m_nAfter.QuadPart = 0;
		HalfTime = 0;
		QuarterTime = 0;
		EighthTime = 0;


		//���𑜓x�J�E���^�Ή����� & PC�̎��g��get
		if (QueryPerformanceFrequency(&m_nFreq))
		{
			//���𑜓x�J�E���^�ɑΉ����Ă��܂��I
			m_queryPC = true;
			//�Q�[���J�nms�擾
			QueryPerformanceCounter(&m_nInit);
		}
		else
		{
			//�Ή����Ă��Ȃ����1ms���o��timeGetTime()���g�p(��������܂�)
			m_nInit.QuadPart = timeGetTime();
		}
	}

	//���Ԃ��󂯎��
	if (m_queryPC)
	{
		//���𑜓x�J�E���^
		QueryPerformanceCounter(&m_nAfter);
	}
	else
	{
		//Windows�N������̃J�E���^
		m_nAfter.QuadPart = timeGetTime();
	}

	Time = ((double)(m_nAfter.QuadPart - m_nInit.QuadPart) * 1000 / (double)m_nFreq.QuadPart);	//���g���Ŋ���
	//printf("%f �~���b\n", Time);

	//�񕪂̃^�C�~���O(ms)
	if (Time - HalfTime >= m_halfNotes)
	{
		HalfTime += m_halfNotes;
		halfUpdate();
	}

	//�l���̃^�C�~���O
	if (Time - QuarterTime >= m_quarterNotes)
	{
		QuarterTime += m_quarterNotes;
		qauarterUpdate();
		
	}

	//�����̃^�C�~���O
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