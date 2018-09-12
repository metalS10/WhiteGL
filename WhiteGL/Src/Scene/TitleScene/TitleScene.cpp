#include "TitleScene.h"

#include "../GameMainScene/GameMainScene.h"

CTitle::CTitle()
{
	this->init();
}

CTitle::~CTitle()
{

}

bool CTitle::init()
{

	//�S�e�N�X�`���폜
	m_game.allTextureDelete();

	//�`����̏�����
	m_game.renderInit();

	gluLookAt(
		-cameraPosX, -cameraPosY, 0.0f,
		-cameraPosX, -cameraPosY, -10.0f,
		0.0f, 1.0f, 0.0f
	);
	//�w�i�̐ݒ�
	//����
	for (int i = 0; i <= 5; i++)
	{
		//��
		for (int j = 0; j <= 10; j++)
		{

			float r = rand() % 100;
			float m_polyRange = 128.0f;		//�Ԋu��
			float range = m_polyRange - 64.0f;	//�傫��

			//m_trianglesLeft.push_back(m_polyRange*j);	//���̃|���S����x�����W����ݒ�
			//m_trianglesRight.push_back((m_polyRange*j) + m_polyRange);	//���̃|���S����x�����W�E��ݒ�
			m_game.setupPoly(CVec4(m_polyRange*j, m_polyRange * i, range, range), CVec4(r, r, 100.0f, 100.0f), i * 2.0f, POLY_TYPE::TRIANGLE, LAYER::MAIN);	//�w�i�ɔ��f


			//m_trianglesLeft.push_back(m_polyRange*j + m_polyRange * 0.5f);		//���̃|���S����x�����W����ݒ�
			//m_trianglesRight.push_back((m_polyRange*j + m_polyRange * 0.5f) + m_polyRange);		//���̃|���S����x�����W�E��ݒ�
			m_game.setupPoly(CVec4(m_polyRange*j + m_polyRange * 0.5f, range * 0.5f + (m_polyRange * i), range, -range), CVec4(r, r, 100.0f, 100.0f), (i + 0.5f) * 2.0f, POLY_TYPE::TRIANGLE,LAYER::MAIN);
		}
	}
	//�^�C�g���̃��S
	m_game.setupTexture(TITLE_TEXT, TEX_TYPE::PNG, TAG_TITLE_TEXT1, CVec2(WINDOW_RIGHT*0.5f, WINDOW_TOP*0.8f), CVec4(0.0f, 0.0f, 300.0f, 80.0f), LAYER::UI);
	//�^�C�g����Start�{�^��
	m_game.setupTexture(TITLE_TEXT, TEX_TYPE::PNG, TAG_TITLE_TEXT2, CVec2(WINDOW_RIGHT*0.3f, WINDOW_TOP*0.4f), CVec4(0.0f, 80.0f, 300.0f, 80.0f), LAYER::UI);
	//�^�C�g����End�{�^��
	m_game.setupTexture(TITLE_TEXT, TEX_TYPE::PNG, TAG_TITLE_TEXT3, CVec2(WINDOW_RIGHT*0.7f, WINDOW_TOP*0.4f), CVec4(0.0f, 160.0f, 300.0f, 80.0f), LAYER::UI);


	BGM = new CSound(SOUND_BGM_TITLE, 180,1,20,true);
	if (CScene::init() == false)
	{
		printf("�V�[���������Ɏ��s");
		return false;
	}
	//�^�C�g���̃o�b�N�O���E���h
	m_game.setupTexture(TITLE_BG, TEX_TYPE::PNG, 0, CVec2(WINDOW_WIDTH * 0.5, WINDOW_HEIGHT*0.5), CVec4(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT),LAYER::BG);
	//m_game.setScale(CVec2(1,1), 0);

	//�{�^���̐F��ς��Ă���
	selectingButton(m_select);


	return true;
}

void CTitle::rendUpdate()
{
	CScene::rendUpdate();
}

void CTitle::update()
{
	if (input->getOnKey(Input::Key::START) == true)
	{
		//gameStart
		if (m_select == 0)
		{
			BGM->fadeOut(1000);
			//�Q�[�����C���V�[���𐶐�
			MS::CMS::getInstance()->setScene(new CGameMain());
		}
		//gameEnd
		else
		{
			BGM->fadeOut(1000);
			m_game.GameEnd();
		}
	}
	//�X�e�[�W�Z���N�g
	if (input->getOnKey(Input::Key::DPAD_RIGHT) == true)
	{
		if (!m_pushButton)
		{
			m_select++;
			if (m_select > 1)
			{
				m_select = 0;
			}
			m_pushButton = true;
			//�{�^���̐F��ς���
			selectingButton(m_select);
		}
	}
	else if (input->getOnKey(Input::Key::DPAD_LEFT) == true)
	{
		if (!m_pushButton)
		{
			m_select--;
			if (m_select < 0)
			{
				m_select = 1;
			}
			m_pushButton = true;
			//�{�^���̐F��ς���
			selectingButton(m_select);
		}
	}
	else
	{
		if (m_pushButton)
		{
			m_pushButton = false;
		}
	}
	
}

void CTitle::qauarterUpdate()
{
	m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT1);
	//printf("a");
	//Start�{�^��
	if (m_select == 0)
	{
		m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT2);
	}
	//End�{�^��
	else if (m_select == 1)
	{
		m_game.setTexScaleAtTag(CVec2(0.9f, 0.9f), TAG_TITLE_TEXT3);
	}
	m_game.notesAction(0);
}

void CTitle::eighthUpdate()
{
}

void CTitle::selectingButton(const int selecting)
{
	switch (selecting)
	{
	case 0:
		m_game.setTexColorAtTag(CVec4(50.0f, 50.0f,100.0f,100.0f), TAG_TITLE_TEXT2);
		m_game.setTexColorAtTag(CVec4(100.0f, 100.0f, 100.0f, 100.0f), TAG_TITLE_TEXT3);
		break;
	case 1:
		m_game.setTexColorAtTag(CVec4(50.0f, 50.0f, 100.0f, 100.0f), TAG_TITLE_TEXT3);
		m_game.setTexColorAtTag(CVec4(100.0f, 100.0f, 100.0f, 100.0f), TAG_TITLE_TEXT2);
		break;
	default:
		printf("�X�e�[�W�I�𒆃{�^��function�ɒǉ�����Ă��܂���\n");
		break;
	}
}
