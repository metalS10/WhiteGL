#pragma once
/**
*RendTexture.h
*
*	2017/10/10	Mat
*		�e�N�X�`���̓ǂݍ��݁A�`��
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"

enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
};
class CRendTexture
{
	

	GLuint g_texID;
	std::vector<CVec2> initializePos;
	std::vector<CVec2> endPos;
	std::vector<CVec4> rect;
	std::vector<TEX_TYPE> texType;

public:

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

	void render();
	

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
	void setupTexture(const char *file, const float posLeft, const float posRight, const float posBottom, const float posTop, const CVec4 rect4, const TEX_TYPE tex_type);
	

};