/**
*	main.cpp
*		2017/09/29	Mats
*/

#include "Constants.h"
#include "GameMain.h"
#include "RendTexture.h"
#include "FPS.h"
#include "Animation.h"


CGameMain* gameMain;

/**
*GLFW����̃G���[�񍐂���������
*
*@param	error	�G���[�ԍ�
*@para,	desc	�G���[���e
*/
void ErrorCallback(int error, const char* desc)
{
	std::cerr << "ERROR : " << desc << std::endl;
}


/**
*	@file main.cpp
*/
//�G���g���[�|�C���g
int main()
{
	glfwSetErrorCallback(ErrorCallback);

	//GL_TRUE/GL_FALSE��OpenGL�̐^�U�l�}�N��
	//OpenGL�����GLFW�̏������A���������GL_TRUE���Ԃ��Ă���
	if (glfwInit() != GL_TRUE)
	{
		return 1;
	}

	/*
	*memo
	*glfwCreateWindow�̓O���t�B�b�N�X�`��p�̃E�B���h�E���쐬����֐�
	*	����:�`��͈͂̏c�A���A�E�B���h�E�̃^�C�g���o�[�ɕ\������镶���A�t���X�N���[�����[�h�p�̃p�����[�^
	*/
	GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE, "WhiteGL", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	//�w�肵���E�B���h�E�ɑΉ�����OpenGL�R���e�L�X�g��`��Ώۂɐݒ肷��֐�
	glfwMakeContextCurrent(window);
	/*
	*memo
	*GLFW�̎���GLEW�̏�����
	*GLEW�ɂ͏I��������֐����Ȃ��A
	*	GLEW�͕��G�ȏI��������K�v�Ƃ���I�u�W�F�N�g���쐬���Ȃ�����
	*	�f�t�H���g�̏I�����@�ŏ\��
	*/
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "ERROR : GLEW�̏������Ɏ��s�B" << std::endl;
		glfwTerminate();
		return 1;
	}

	/*
	// ���j�^�Ƃ̓���
	glfwSwapInterval(1);

	// �`��͈͂̎w��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, g_windowWidth, 0.0f, g_windowHeight, -1.0f, 1.0f);

	//�e�N�X�`���̃��[�h
	glGenTextures(1, &g_texID);
	setupTexture(g_texID, PASS"Sparrow.bmp", 200, 200);
	*/
	// ���j�^�Ƃ̓���
	//glfwSwapInterval(1);

	// �`��͈͂̎w��
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	glOrtho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);

	//================================
	//�e�N�X�`���̕`��
	//================================
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	CRendTexture* rendTex = new CRendTexture();
	
	rendTex->setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 0);
	rendTex->setupTextureSize(CVec4(0.0f, 200.0f, 100.0f, 300.0f), CVec4(0.0f, 200.0f, 0.0f, 200.0f), 0);


	rendTex->setupTexture(PASS"Sparrow.bmp", TEX_TYPE::BMP, 1);
	rendTex->setupTextureSize(CVec4(200.0f, 400.0f, 100.0f, 300.0f), CVec4(100.0f, 200.0f, 100.0f, 200.0f), 1);

	rendTex->setupTexture(PASS"player.bmp", TEX_TYPE::BMP, 2);
	rendTex->setupTextureSize(CVec4(400.0f, 464.0f, 100.0f, 164.0f), CVec4(0.0f, 64.0f, 128.0f, 192.0f), 2);

	rendTex->setupTexture(PASS"kuribo.png", TEX_TYPE::PNG, 3);
	rendTex->setupTextureSize(CVec4(0.0f, 100.0f, 300.0f, 400.0f), CVec4(0.0f, 64.0f, 0.0f, 64.0f), 3);

	rendTex->setupTexture(PASS"player.png", TEX_TYPE::PNG, 4);
	rendTex->setupTextureSize(CVec4(100.0f, 200.0f, 300.0f, 400.0f), CVec4(0.0f, 64.0f, 0.0f, 64.0f), 4);

	


	gameMain = new CGameMain();
	FPS *fps = new FPS(60);//�b��60�t���[��(��sleep)

	int i = 0;
	int j = 0;
	std::vector<CAnimation*>* m_pAnim = new std::vector<CAnimation*>();
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CNotAnimation());
	m_pAnim->push_back(new CListAnimation(60,true));

	(*m_pAnim)[0]->addChipData(new CVec4(0.0f, 200.0f, 0.0f, 200.0f));
	(*m_pAnim)[1]->addChipData(new CVec4(100.0f, 200.0f, 100.0f, 200.0f));
	(*m_pAnim)[2]->addChipData(new CVec4(0.0f, 64.0f, 128.0f, 192.0f));
	(*m_pAnim)[3]->addChipData(new CVec4(0.0f, 64.0f, 0.0f, 64.0f));

	(*m_pAnim)[4]->addChipData(new CVec4(0.0f, 64.0f, 0.0f, 64.0f));
	(*m_pAnim)[4]->addChipData(new CVec4(64.0f, 128.0f, 0.0f, 64.0f));
	(*m_pAnim)[4]->addChipData(new CVec4(128.0f, 192.0f, 0.0f, 64.0f));





	/**
	*memo
	*���C�����[�v
	*���t���[�����s�����
	*glfwWindowShouldClose�̓E�B���h�E�����ׂ����ǂ����𒲂ׂ�֐�
	*	�����œn���ꂽ�E�B���h�E�ɑ΂���OS������I���v�������Ă��Ȃ����0,���Ă����0�ȊO��Ԃ�
	*GLFW�ō쐬�����E�B���h�E��1�����Ȃ�I������͂��̊֐������邾���ŏ\��
	*/
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();

		rendTex->render();

		fps->GetFPS();//FPS�𓾂�
		if (fps->draw) {//�b��60�t���[���̃^�C�~���O�ŕ`��
			rendTex->update(m_pAnim);

			int l = 0;
		}

		glfwSwapBuffers(window);
	}

	/*
	if (glfwWindowShouldClose(window))
	{
	return 0;
	}
	*/
	//�`��g�p���̔j��
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glfwTerminate();

	return 0;
}
