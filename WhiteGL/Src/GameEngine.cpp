#include "GameEngine.h"




void CGameEngine::setupTexture(const char* file,TEX_TYPE texType,GLuint texID,CVec2 texPos,CVec4 texRect,CVec4 color)
{
	//================================
	//�e�N�X�`���̕`��
	//================================
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//�F�f�[�^���������ɓo�^���邽�߂̋��𓾂�
	glEnableClientState(GL_COLOR_ARRAY);

	if (rendTex == NULL)
		rendTex = new CRendTexture();

	rendTex->setupTexture(file, texType, texID);
	rendTex->setupTextureSize(texPos, texRect , texID);
	rendTex->setupTextureColor(color, texID);
}

void CGameEngine::setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect)
{
	//================================
	//�e�N�X�`���̕`��
	//================================
	//�g�p����
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//�F�f�[�^���������ɓo�^���邽�߂̋��𓾂�
	glEnableClientState(GL_COLOR_ARRAY);

	if (rendTex == NULL)
		rendTex = new CRendTexture();

	rendTex->setupTexture(file, texType, texID);
	rendTex->setupTextureSize(texPos, texRect, texID);
	rendTex->setupTextureColor(CVec4(100.0f,100.0f,100.0f,100.0f), texID);
}

void CGameEngine::setChipAnim(CAnimation *&&_val)
{
	m_pAnim->push_back(_val);
}

void CGameEngine::setChipData(GLuint texID,CVec4 rectData)
{
	(*m_pAnim)[texID]->addChipData(new CVec4(rectData));
}


GLFWwindow* CGameEngine::init(int w,int h,const char* file)
{
	if (isInitialized)
	{
		return m_Window;
	}
	m_Window = GLFWEW::Window::Instance().Init(w, h, file);
	if (m_Window == NULL)
	{
		return NULL;
	}
	m_pAnim = new std::vector<CAnimation*>();

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
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();

	rendTex->render();

	//rendTex->update(m_pAnim);
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
	rendTex->update(m_pAnim);
}
void CGameEngine::setScale(CVec2 scale, GLuint texID)
{
	rendTex->setScale(scale, texID);
}

void CGameEngine::inputKeyA()
{
	rendTex->TextureFade(6, true);
	//rendTex->deleteTexture(2);
}
void CGameEngine::inputKeyS()
{
	rendTex->TextureFade(6, false);
}
void CGameEngine::inputKeyZ()
{
	rendTex->setScale(CVec2(1, 1), 4);
}
void CGameEngine::inputKeyX()
{
	rendTex->setScale(CVec2(2, 2), 4);
}

void CGameEngine::setTextureRect(const CVec4 mrect,const GLuint texID)
{	
	rendTex->setTextureRect(mrect,texID);
}

void CGameEngine::setPosition(CVec2 pos, GLuint texID)
{
	rendTex->setPosition(pos, texID);
}

void CGameEngine::deleteTexture(const GLuint texID)
{
	rendTex->deleteTexture(texID);
}

/**
*	�Q�[�������s����
*/
/*
void CGameEngine::Run()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	double prevTime = glfwGetTime();
	while (!window.ShowldClose())
	{
		const double curTime = glfwGetTime();
		const double delta = curTime - prevTime;
		prevTime = curTime;
		window.UpdateGamePad();
		window.SwapBuffers();
	}
}
*/


CRendTexture* CGameEngine::getRendTexture()
{
	return rendTex;
}
