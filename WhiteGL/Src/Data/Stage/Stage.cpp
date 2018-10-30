#include "Stage.h"



//===========================================================
//�e
//===========================================================
//�w�i�X�N���[���p�̊֐�
//���փX�N���[����
void CStage::scrollBackGroundTrianglesLeft(float posX)
{
	for (int i = 0; i < m_trianglesLeft.size(); i++)
	{
		//�|���S���̍�����ʉE�[�ɗ�����
		if (m_trianglesLeft[i] >= posX)
		{
			float pos = m_trianglesLeft[i];

			//������ʍ��[+�|���S���Ԋu�ɍĐݒu
			m_trianglesLeft[i] = pos - WINDOW_RIGHT - m_polyRange;
			//�E����ʍ��[��
			m_trianglesRight[i] = pos - WINDOW_RIGHT;
			//�F���Đݒ�
			int r = rand() % 100;
			int l = i;
			while (l >= 0)
			{
				l -= 2;
				if (l <= -1)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(false));	//�w�i�ɔ��f
					break;
				}
				else if (l <= 0)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(true));	//�w�i�ɔ��f
					break;
				}
			}
		}
	}
}
//�E�փX�N���[����
void CStage::scrollBackGroundTrianglesRight(float posX)
{
	for (int i = 0; i < m_trianglesRight.size(); i++)
	{
		float pos = m_trianglesRight[i];

		//�|���S���̉E����ʍ��[�ɗ�����
		if (m_trianglesRight[i] <= posX)
		{
			//������ʉE�[��
			m_trianglesLeft[i] = pos + WINDOW_RIGHT;
			//�E����ʉE�[+�|���S���Ԋu��
			m_trianglesRight[i] = pos + WINDOW_RIGHT + m_polyRange;
			//�F���Đݒ�
			int r = rand() % 100;
			int l = i;
			while (l >= 0)
			{
				l -= 2;
				if (l <= -1)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(false));	//�w�i�ɔ��f
					break;
				}
				else if (l <= 0)
				{
					m_bgPoly[i]->setTrianglesPolyPos(m_trianglesLeft[i], getChangePositionColor(true));	//�w�i�ɔ��f
					break;
				}
			}
		}
	}
}

//�w�i�|���S���̃A�N�V����
/**
*	mode
*0.Random
*1.Up
*2.doubleUp
*/
void CStage::actionBackground(int mode)
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		switch (mode)
		{
		case 0:
			bgPoly->notesRandomFadeInit();
			break;
		case 1:
			bgPoly->notesUpFadeInit(mode - 1);
			break;
		case 2:
			bgPoly->notesUpFadeInit(mode - 1);
			break;
		default:
			break;

			//renderer->setRotate(CVec3(1.0f, 0.0f, 0.0f), 1.0f);
		}
	}
}




//===========================================================
//1-1
//===========================================================
//����������
void CStage1_1::init()
{

	//�X�e�[�W�ɒ�߂�ꂽ�}�b�v���J��
	CMapManager::getInstance()->setMap(MAP_DATA_1);
	//�w�i�A�N�V�����^�C�v�ݒ�
	backgroundType = 0;


	//�w�i�|���S���R�̏�����
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

	m_bgPoly.clear();

	//�w�i�̐ݒ�
	//����
	for (int i = 0; i <= 5; i++)
	{
		//��
		for (int j = 0; j <= 10; j++)
		{

			float r = rand() % 100;
			m_polyRange = 128.0f;		//�Ԋu��
			float range = m_polyRange - 64.0f;	//�傫��

			m_trianglesLeft.push_back(m_polyRange*j);	//���̃|���S����x�����W����ݒ�
			m_trianglesRight.push_back((m_polyRange*j) + m_polyRange);	//���̃|���S����x�����W�E��ݒ�
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly.back()->setupTrianglesPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(100.0f, r, r, 100.0f), i * 2.0f,rendInfo::LAYER::BG);	//�w�i�ɔ��f


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//���̃|���S����x�����W����ݒ�
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//���̃|���S����x�����W�E��ݒ�
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, rendInfo::LAYER::BG);
		}
	}
}

//�X�N���[���X�V�̍ۂ̔w�i�F���
CVec4 CStage1_1::getChangePositionColor(bool Top)
{
	float r = rand() % 100;
	if (Top)
		return CVec4(100.0f, r, r, 100.0f);
	else
		return CVec4(r, r, 100.0f, 100.0f);
}

//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
CStage* CStage1_1::changeStage()
{
	CMapManager::removeInstance();
	for(rendInfo::CTriPolygonRendInfo* triPoly:m_bgPoly)
	{
		SAFE_DELETE(triPoly);
	}
	//���̃X�e�[�W��Ԃ�
	return new CStage1_2();
}

//�X�e�[�W�w���BGM��Ԃ��B
CSound* CStage1_1::getBGM()
{
	//���̃X�e�[�W��BGM��ݒ�
	bgm = new CSound(SOUND_BGM, 140,1, 20, true);
	//�ݒ肵�����̂�n��
	return bgm;
}
void CStage1_1::update()
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		bgPoly->notesFadeBackground();
	}
}


//===========================================================
//1-2
//===========================================================
//����������
void CStage1_2::init()
{
	//�X�e�[�W�ɒ�߂�ꂽ�}�b�v���J��
	CMapManager::getInstance()->setMap(MAP_DATA_2);
	
	//�w�i�A�N�V�����^�C�v�ݒ�
	backgroundType = 1;

	//�w�i�|���S���R�̏�����
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

	m_bgPoly.clear();

	//�w�i�̐ݒ�
	//����
	for (int i = 0; i <= 5; i++)
	{
		//��
		for (int j = 0; j <= 10; j++)
		{

			float r = rand() % 100;
			m_polyRange = 128.0f;		//�Ԋu��
			float range = m_polyRange - 64.0f;	//�傫��

			m_trianglesLeft.push_back(m_polyRange*j);	//���̃|���S����x�����W����ݒ�
			m_trianglesRight.push_back((m_polyRange*j) + m_polyRange);	//���̃|���S����x�����W�E��ݒ�
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, r, 100.0f), i * 2.0f, rendInfo::LAYER::BG);	//�w�i�ɔ��f


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//���̃|���S����x�����W����ݒ�
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//���̃|���S����x�����W�E��ݒ�
			m_bgPoly.push_back(new rendInfo::CTriPolygonRendInfo());
			m_bgPoly[m_bgPoly.size() - 1]->setupTrianglesPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, r, 100.0f), (i + 0.5f) * 2.0f, rendInfo::LAYER::BG);
		}
	}
}

//�X�N���[���X�V�̍ۂ̔w�i�F���
CVec4 CStage1_2::getChangePositionColor(bool Top)
{
	float r = rand() % 100;
	return CVec4(r, r, r, 100.0f);
}

//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
CStage* CStage1_2::changeStage()
{
	CMapManager::removeInstance();
	for (rendInfo::CTriPolygonRendInfo* triPoly : m_bgPoly)
	{
		SAFE_DELETE(triPoly);
	}
	//���̃X�e�[�W��Ԃ�
	return NULL;
}

//�X�e�[�W�w���BGM��Ԃ��B
CSound* CStage1_2::getBGM()
{
	//���̃X�e�[�W��BGM��ݒ�
	bgm = new CSound(SOUND_BGM2, 180,1, 15, true);
	//�ݒ肵�����̂�n��
	return bgm;
}
void CStage1_2::update()
{
	for (rendInfo::CTriPolygonRendInfo* bgPoly : m_bgPoly)
	{
		bgPoly->notesFadeBackground();
	}
}