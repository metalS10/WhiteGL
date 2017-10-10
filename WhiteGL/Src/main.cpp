/**
*	main.cpp
*		2017/09/29	Mats
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Constants.h"
#include "GameMain.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"



GLuint g_texID;
std::vector<CVec2> initializePos;
std::vector<CVec2> endPos;
std::vector<CVec4> rect;

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

enum class COL_TYPE : int
{
	RGB = 0,
	RGBA = 1,
};

enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
};

/*
void render()
{
static const GLfloat vtx[] = {
0, 120,
200, 120,
200, 320,
0, 320,
};
glVertexPointer(2, GL_FLOAT, 0, vtx);

//�e�N�X�`���̗̈�w��
static const GLfloat texuv[] = {
1.0f, 0.0f,
0.0f, 0.0f,
0.0f, 1.0f,
1.0f, 1.0f,
};



/*
//cameraPos
gluLookAt(
0.0f, 0.0f, 0.0f,
0.0f, 0.0f, -10.0f,
0.0f, 1.0f, 0.0f
);
//
glTranslated(0.0f, 0.0f, -579.41f);

glTexCoordPointer(2, GL_FLOAT, 0, texuv);
//�e�N�X�`���̉摜�w��
glBindTexture(GL_TEXTURE_2D, g_texID);

glDrawArrays(GL_QUADS, 0, 4);


glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
*/

void render()
{
	for (int texID = 0;texID < g_texID;texID++)
	{
		//�ꏊ�w��
		const GLfloat vtx2[] = {
			initializePos[texID].x, initializePos[texID].y,
			endPos[texID].x, initializePos[texID].y,
			endPos[texID].x, endPos[texID].y,
			initializePos[texID].x, endPos[texID].y,
		};
		glVertexPointer(2, GL_FLOAT, 0, vtx2);

		//�e�N�X�`���̗̈�w��
		const GLfloat texuv[] = {
			rect[texID].x, rect[texID].z,
			rect[texID].y, rect[texID].z,
			rect[texID].y, rect[texID].w,
			rect[texID].x, rect[texID].w,
		};

		//���_�̐ݒ�
		glTexCoordPointer(2, GL_FLOAT, 0, texuv);

		//�e�N�X�`���̉摜�w��
		glBindTexture(GL_TEXTURE_2D, texID);

		//�l�p�|���S���\��
		glDrawArrays(GL_QUADS, 0, 4);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
}

/*
void setupTexture(GLuint texID, const char *file, const int width, const int height)
{
// �摜�f�[�^�̃��[�h
std::ifstream fstr(file, std::ios::binary);
assert(fstr);

const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
fstr.seekg(0, fstr.beg);
std::vector<char> textureBuffer(fileSize);
fstr.read(&textureBuffer[0], fileSize);

//�摜�f�[�^�ƃe�N�X�`��iD�����т���
glBindTexture(GL_TEXTURE_2D, texID);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &textureBuffer[0]);

//�e�N�X�`���̊e��ݒ�
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

}
*/

/**
*�e�N�X�`���̓ǂݍ��݁AID�̐ݒ�A�摜�͈�
*
*@param	texID	ID
*@param	file	�t�@�C���p�X
*@param	posLeft		�摜�̍��̈ʒu
*@param	posRight	�摜�̉E�̈ʒu
*@param	posBottom	�摜�̉��̈ʒu
*@param	posTop		�摜�̏�̈ʒu
*@param	rect		��`
*/
void setupTexture(GLuint texID, const char *file, const float posLeft, const float posRight, const float posBottom, const float posTop, const CVec4 rect4, const COL_TYPE col_type, const TEX_TYPE tex_type)
{
	CImage* tex = NULL;
	switch (tex_type)
	{
	case TEX_TYPE::BMP:
		tex = new CBmpImage();
		if (tex->load(file) == false)
		{
			std::cerr << "ERROR : �摜�̓ǂݍ��݂Ɏ��s" << std::endl;
		}
		break;

	case TEX_TYPE::PNG:
		tex = new CPngImage();
		if (tex->load(file) == false)
		{
			std::cerr << "ERROR : �摜�̓ǂݍ��݂Ɏ��s" << std::endl;
		}
		break;

	default:
		break;
	}

	//�摜�f�[�^�ƃe�N�X�`��iD�����т���
	glBindTexture(GL_TEXTURE_2D, texID);
	switch (col_type)
	{
	case COL_TYPE::RGB:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->m_width, tex->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->m_bits);
		break;
	case COL_TYPE::RGBA:
		//�e�N�X�`����PNG�t�@�C������ǂݍ��񂾃s�N�Z������������

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->m_width, tex->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->m_bits);
		break;

	default:
		break;
	}

	//�F�X�ݒ�
	initializePos.push_back(CVec2(posLeft, posBottom));
	endPos.push_back(CVec2(posRight, posTop));

	//�摜�̋�`�͈͂�ݒ�
	CVec4 changerect4 = CVec4(rect4.x / tex->m_width, rect4.y / tex->m_width, rect4.z / tex->m_height, rect4.w / tex->m_height);
	rect.push_back(CVec4(changerect4));

	//texID���󂢂Ă���Ƃ����
	glGenTextures(1, &g_texID);

	if (tex == NULL)
	{
		std::cerr << "BMP,PNG,JPEG�Ȃ�ł��Ȃ��ł�" << std::endl;
	}
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


	setupTexture(g_texID, PASS"Sparrow.bmp", 0.0f, 200.0f, 100.0f, 300.0f, CVec4(0.0f, 200.0f, 0.0f, 200.0f), COL_TYPE::RGB, TEX_TYPE::BMP);

	setupTexture(g_texID, PASS"Sparrow.bmp", 200.0f, 400.0f, 100.0f, 300.0f, CVec4(100.0f, 200.0f, 100.0f, 200.0f), COL_TYPE::RGB, TEX_TYPE::BMP);

	setupTexture(g_texID, PASS"player.bmp", 400.0f, 464.0f, 100.0f, 164.0f, CVec4(0.0f, 64.0f, 128.0f, 192.0f), COL_TYPE::RGB, TEX_TYPE::BMP);

	setupTexture(g_texID, PASS"Mel.png", 0.0f, 320.0f, 300.0f, 492.0f, CVec4(0.0f, 320.0f, 0.0f, 192.0f), COL_TYPE::RGBA, TEX_TYPE::PNG);

	//���ߐݒ�
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gameMain = new CGameMain();

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

		render();
		gameMain->update();

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
