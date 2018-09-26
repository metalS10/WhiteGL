#include "GameEngine.h"



//�`�揉����(�X�e�[�W�ړ�����)
void CGameEngine::renderInit()
{
	renderer->init();
}

void CGameEngine::setupTexture(const char* file,TEX_TYPE texType,GLuint texID,CVec2 texPos,CVec4 texRect,CVec4 color)
{
	//================================
	//�e�N�X�`���̕`��
	//================================
	renderer->setupTexture(file, texType, texID, LAYER::MAIN);
	renderer->setupTextureTransform(texPos, texRect);
	renderer->setupTextureColor(color);
}
void CGameEngine::setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect)
{
	//================================
	//�e�N�X�`���̕`��
	//================================
	renderer->setupTexture(file, texType, texID, LAYER::MAIN);
	renderer->setupTextureTransform(texPos, texRect);
	renderer->setupTextureColor(CVec4(100.0f,100.0f,100.0f,100.0f));
}
void CGameEngine::setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer)
{
	//================================
	//�e�N�X�`���̕`��
	//================================
	renderer->setupTexture(file, texType, texID, layer);
	renderer->setupTextureTransform(texPos, texRect);
	renderer->setupTextureColor(color);
}
void CGameEngine::setupTexture(const char* file, TEX_TYPE texType, GLuint texID, CVec2 texPos, CVec4 texRect, LAYER layer)
{
	//================================
	//�e�N�X�`���̕`��
	//================================
	renderer->setupTexture(file, texType, texID, layer);
	renderer->setupTextureTransform(texPos, texRect);
	renderer->setupTextureColor(CVec4(100.0f, 100.0f, 100.0f, 100.0f));
}

void CGameEngine::setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype)
{
	if (polytype == POLY_TYPE::TRIANGLE)
		renderer->setupTrianglesPoly(vertex, color, line, LAYER::MAIN);
	else if (polytype == POLY_TYPE::QUAD)
		renderer->setupPoly(vertex, color, LAYER::MAIN,0);
}
void CGameEngine::setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype, const GLuint tag)
{
	if (polytype == POLY_TYPE::TRIANGLE)
		renderer->setupTrianglesPoly(vertex, color, line, LAYER::MAIN);
	else if (polytype == POLY_TYPE::QUAD)
		renderer->setupPoly(vertex, color, LAYER::MAIN,tag);
}
void CGameEngine::setupPoly(const CVec4 vertex, const CVec4 color,const GLuint line, const POLY_TYPE polytype, const LAYER layer)
{
	if (polytype == POLY_TYPE::TRIANGLE)
		renderer->setupTrianglesPoly(vertex, color, line, layer);
	else if (polytype == POLY_TYPE::QUAD)
		renderer->setupPoly(vertex, color,layer,0);
}
void CGameEngine::setupPoly(const CVec4 vertex, const CVec4 color, const GLuint line, const POLY_TYPE polytype,const LAYER layer, const GLuint tag)
{
	if (polytype == POLY_TYPE::TRIANGLE)
		renderer->setupTrianglesPoly(vertex, color, line, layer);
	else if (polytype == POLY_TYPE::QUAD)
		renderer->setupPoly(vertex, color, layer,tag);
}

void CGameEngine::setTrianglesPolyPos(const float vertexX, const CVec4 color, const GLuint number)
{
	renderer->setTrianglesPolyPos(vertexX, color, number);
}

void CGameEngine::setPolyPos(const CVec2 vertex,const GLuint tag)
{
	renderer->setPolyPos(vertex,tag);
}
void CGameEngine::setPolyScale(const CVec2 scale,const GLuint tag)
{
	renderer->setPolyScale(scale,tag);
}
void CGameEngine::setPolyPosX(const float vertex,const GLuint tag)
{
	renderer->setPolyPosX(vertex,tag);
}
void CGameEngine::setPolyAngle(const float angle, const GLuint tag)
{
	renderer->setPolyAngle(angle, tag);
}
void CGameEngine::setPolyColor(const CVec4 color, const GLuint tag)	//�|���S���̐F�ݒ�
{
	renderer->setPolyColor(color, tag);
}
void CGameEngine::addPolyAngle(const float angle, const GLuint tag)
{
	renderer->addPolyAngle(angle, tag);
}
float CGameEngine::getPolyAngle(const GLuint tag)
{
	return renderer->getPolyAngle(tag);
}
CVec2 CGameEngine::getPolyScale(const GLuint tag)
{
	return renderer->getPolyScale(tag);
}
CVec4 CGameEngine::getPolyColor(const GLuint tag)
{
	return renderer->getPolyColor(tag);
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

	renderer = new CRenderer();

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
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();

	renderer->update(m_pAnim);
	renderer->render();

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
	renderer->notesFadeBackground();
	renderer->polygonNotesAction();
	renderer->textureNotesAction();
	m_hitStop--;
	if (m_hitStop <= 0)
		m_hitStop = 0;
}


void CGameEngine::setTexScale(const CVec2 scale, const GLuint texID)
{
	renderer->setTextureScaleAtTag(scale, texID);
}
void CGameEngine::setTexScaleAtTag(const CVec2 scale, const GLuint tag)
{
	renderer->setTextureScaleAtTag(scale, tag);
}
void CGameEngine::setTexColorAtTag(const CVec4 color, const GLuint tag)
{
	renderer->setupTextureColorAtTag(color, tag);
}


void CGameEngine::setTextureRect(const CVec4 mrect,const GLuint texID)
{	
	renderer->setTextureRectAtTag(mrect,texID);
}

void CGameEngine::SetProgressBarWH(const GLuint tag, const CVec4 Rect, const CVec2 position)
{
	renderer->SetProgressBarWH(tag, Rect,position);
}

void CGameEngine::setTexPosition(CVec2 pos, GLuint texID)
{
	renderer->setTexPositionAtTag(pos, texID);
}

void CGameEngine::deleteTexture(const GLuint texID)
{
	renderer->deleteTexture(texID);
}

void CGameEngine::loadTMXMap(CLayerData layerData[MAX_LAYER_NUMBER],int width,int height)
{
	int countW = 0;
	int countH = height-1;
	int tileID = 0;
	for (int j = 0;j < MAX_LAYER_NUMBER; j++)
	{
		for (int i = 0;i < layerData[j].m_gid.size();i++)
		{
			if (layerData[j].m_gid[i] != 0)
			{
				int gidten = (int)((layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) / layerData[j].m_columns < 0.0 ? (layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) / layerData[j].m_columns - 0.9 : (layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) / layerData[j].m_columns);
				int gidone = (layerData[j].m_gid[i] - layerData[j].m_firstgid + 1) % (layerData[j].m_columns);
				float rectL = layerData[j].m_tileWidth * gidone - layerData[j].m_tileWidth;
				float rectB = layerData[j].m_tileHeight * gidten;
				setupTexture(layerData[j].m_imageSource.c_str(), TEX_TYPE::PNG, START_MAP_TEXTURE_NUMBER + tileID + countMap, CVec2(layerData[j].m_tileWidth * 0.5 + (layerData[j].m_tileWidth * countW), layerData[j].m_tileHeight * 0.5 + (layerData[j].m_tileHeight * countH)), CVec4(rectL, rectB, layerData[j].m_tileWidth, layerData[j].m_tileHeight),LAYER::MAIN);
				tileID++;
			}
			if (countW >= width - 1)
			{
				countW = 0;
				countH--;
			}
			else
			{
				countW++;
			}
		}
		countMap += layerData[j].m_gid.size();
	}
	//���C���[�܂ŏI������珉����
	countMap = 0;

}
void CGameEngine::TMXMapSetPos(float x, float y)
{
	for (int i = 0;i < countMap;i++)
	{
		renderer->setMapPosition(CVec2(x, y), START_MAP_TEXTURE_NUMBER + i);
	}
}
void CGameEngine::layerSetPos(float x, float y,GLuint texID)
{
	renderer->setMapPosition(CVec2(x, y), texID);
}

void CGameEngine::GameEnd()
{
	gameNow = false;
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

//�A�N�V�����n
bool CGameEngine::ActionStage(GLuint tag, const float fadeInterval, const bool fade)
{
	if (!actionone1)
	{
		renderer->TextureFade(tag, fade, fadeInterval);
		actionone1 = true;
	}
	if (getFadeEnd(tag))
	{
		actionone1 = false;
		return true;
	}
	return false;
}
void* CGameEngine::TextureFade(const GLuint texID, const bool out, const float fadeInterval)
{

	renderer->TextureFade(texID, out, fadeInterval);
	return this;
}
bool CGameEngine::getFadeEnd(const GLuint tag)
{
	return !renderer->endTextureFade(tag);
}

CRenderer* CGameEngine::getRenderer()
{
	return renderer;
}

void CGameEngine::deletePoly(const GLuint tag)
{
	renderer->deletePoly(tag);
}

//BB�ȊO��������
void CGameEngine::allTextureDelete()
{
	renderer->allTextureDelete();
	//renderer->g_texID;
}

void CGameEngine::allTextureDeletenotPlayer()
{
	renderer->allTextureDeletenotPlayer();
}


void CGameEngine::HitStop(float time)
{
	m_hitStop = time;
}

/**
*	mode
*0.Random
*1.Up
*2.doubleUp
*/
void CGameEngine::notesAction(int mode)
{
	switch (mode)
	{
	case 0:
		renderer->notesRandomFadeInit();
		break;
	case 1:
		renderer->notesUpFadeInit(mode - 1);
		break;
	case 2:
		renderer->notesUpFadeInit(mode - 1);
		break;
	default:
		break;
	}
	//renderer->setRotate(CVec3(1.0f, 0.0f, 0.0f), 1.0f);
}
//beats�ɍ��킹��A�N�V����
void CGameEngine::polygonAction(const GLuint tag,const GLuint mode)
{
	renderer->polygonNotesActionInit(tag,mode);
}