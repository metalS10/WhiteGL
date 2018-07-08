#include "Stage.h"

//����������
void CStage1_1::init(CGameEngine& game)
{

	//�X�e�[�W�ɒ�߂�ꂽ�}�b�v���J��
	CMapManager::getInstance()->setMap(MAP_DATA_1);
	//�w�i�A�N�V�����^�C�v�ݒ�
	backgroundType = 0;


	//�w�i�|���S���R�̏�����
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

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
			game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(100.0f, r, r, 100.0f), i * 2.0f,POLY_TYPE::TRIANGLE);	//�w�i�ɔ��f


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//���̃|���S����x�����W����ݒ�
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//���̃|���S����x�����W�E��ݒ�
			game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE);
		}
	}
}

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
	SAFE_DELETE(bgm);
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

//����������
void CStage1_2::init(CGameEngine& game)
{
	//�X�e�[�W�ɒ�߂�ꂽ�}�b�v���J��
	CMapManager::getInstance()->setMap(MAP_DATA_2);
	
	//�w�i�A�N�V�����^�C�v�ݒ�
	backgroundType = 1;

	//�w�i�|���S���R�̏�����
	m_trianglesLeft = std::vector<float>();
	m_trianglesRight = std::vector<float>();

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
			game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, r, 100.0f), i * 2.0f, POLY_TYPE::TRIANGLE);	//�w�i�ɔ��f


			m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//���̃|���S����x�����W����ݒ�
			m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//���̃|���S����x�����W�E��ݒ�
			game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, r, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE);
		}
	}
}

CVec4 CStage1_2::getChangePositionColor(bool Top)
{
	float r = rand() % 100;
	return CVec4(r, r, r, 100.0f);
}

//���̃X�e�[�W��Ԃ��B�N���A�Ȃ�NULL�B
CStage* CStage1_2::changeStage()
{
	//���̃X�e�[�W��Ԃ�
	return NULL;
}

//�X�e�[�W�w���BGM��Ԃ��B
CSound* CStage1_2::getBGM()
{
	//���̃X�e�[�W��BGM��ݒ�
	bgm = new CSound(SOUND_BGM2, 212,1, 15, true);
	//�ݒ肵�����̂�n��
	return bgm;
}