#include "GameEngine.h"
#include "../GLFWEW/GLFWEW.h"


CGameEngine::CGameEngine()
{

}
CGameEngine::~CGameEngine()
{

}
//�`�揉����(�X�e�[�W�ړ�����)
void CGameEngine::renderInit()
{
	m_renderer->init();
}
void CGameEngine::changeStageInit()
{
	m_renderer->changeStageInit();
}

GLFWwindow* CGameEngine::init(int w,int h,const char* file)
{

	m_renderer = new render::CRenderer();

	if (isInitialized)
	{
		return m_Window;
	}
	m_Window = GLFWEW::Window::Instance().Init(w, h, file);
	if (m_Window == NULL)
	{
		return NULL;
	}

	//GL_TRUE/GL_FALSE��OpenGL�̐^�U�l�}�N��
	//OpenGL�����GLFW�̏������A���������GL_TRUE���Ԃ��Ă���
	if (glfwInit() != GL_TRUE)
	{
		return NULL;
	}

	/*
	*memo
	*glfwCreateWindow�̓O���t�B�b�N�X�`��p�̃E�B���h�E���쐬����֐�
	*	����:�`��͈͂̏c�A���A�E�B���h�E�̃^�C�g���o�[�ɕ\������镶���A�t���X�N���[�����[�h�p�̃p�����[�^
	*/
	if (!m_Window)
	{
		glfwTerminate();
		return NULL;
	}

	//�w�肵���E�B���h�E�ɑΉ�����OpenGL�R���e�L�X�g��`��Ώۂɐݒ肷��֐�
	glfwMakeContextCurrent(m_Window);
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
		return NULL;
	}
	glOrtho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -1.0f, 1.0f);

	isInitialized = true;

	return m_Window;
}

/**
*�Q�[���G���W���̃C���X�^���X���擾����
*
*@return �Q�[���G���W���̃C���X�^���X
*/
CGameEngine& CGameEngine::Instance()
{
	static CGameEngine instance;
	return instance;
}

/**
*	�Q�[���p�b�h�̏�Ԃ��擾����
*/
const GamePad& CGameEngine::GetGamePad() const
{
	return GLFWEW::Window::Instance().GetGamePad();
}


void CGameEngine::update()
{
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();

	m_renderer->render();

	//renderer->update(m_pAnim);
	/*
	GameEngine& game = GameEngine::Instance();
	const GamePad gamepad = game.GetGamePad();
	if (gamepad.buttons !=0 )
	{
	//GamePad::DPAD_LEFT

	}
	*/
}

void CGameEngine::update60()
{
	

	if (m_hitStop > 0)
	{
		m_hitStop--;
	}
	else if (m_hitStop < 0)
	{
		m_hitStop = 0;
	}
}




void CGameEngine::GameEnd()
{
	gameNow = false;
}




void CGameEngine::HitStop(float time)
{
	m_hitStop = time;
}

render::CRenderer* CGameEngine::getRenderer()
{
	return m_renderer;
}

