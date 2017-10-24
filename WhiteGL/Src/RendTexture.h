#pragma once
/**
*RendTexture.h
*
*	2017/10/10	Mat
*		テクスチャの読み込み、描画
*/

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "image.h"
#include "Vec2.h"
#include "Vec4.h"
#include "Constants.h"
#include "Animation.h"
#pragma warning(disable:4996)


enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
	QUAD = 3,
};
class CRendTexture
{
private:
	CVec2 initializePos[MAX_TEXTURE_NUMBER] = {};
	CVec2 endPos[MAX_TEXTURE_NUMBER] = {};
	CVec4 rect[MAX_TEXTURE_NUMBER] = {};
	TEX_TYPE texType[MAX_TEXTURE_NUMBER] = {};
	CVec4 colorRGBA[MAX_TEXTURE_NUMBER] = {};
	//テクスチャ情報
	GLuint g_texID[MAX_TEXTURE_NUMBER] = {};
	CImage* tex[MAX_TEXTURE_NUMBER] = {};
	bool actionFade[MAX_TEXTURE_NUMBER] = {};
	bool fadeOut[MAX_TEXTURE_NUMBER] = {};


	~CRendTexture()
	{
		for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
			SAFE_DELETE(tex[i]);
	}

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

	//テクスチャの領域指定
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
	//テクスチャの画像指定
	glBindTexture(GL_TEXTURE_2D, g_texID);

	glDrawArrays(GL_QUADS, 0, 4);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	*/

	void update(std::vector<CAnimation*>* anim);

	void render();


	/*
	void setupTexture(GLuint texID, const char *file, const int width, const int height)
	{
	// 画像データのロード
	std::ifstream fstr(file, std::ios::binary);
	assert(fstr);

	const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
	fstr.seekg(0, fstr.beg);
	std::vector<char> textureBuffer(fileSize);
	fstr.read(&textureBuffer[0], fileSize);

	//画像データとテクスチャiDを結びつける
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &textureBuffer[0]);

	//テクスチャの各種設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	}
	*/

	/**
	*テクスチャの読み込み、IDの設定、画像範囲
	*
	*@param	texID	ID
	*@param	file	ファイルパス
	*@param	posLeft		画像の左の位置
	*@param	posRight	画像の右の位置
	*@param	posBottom	画像の下の位置
	*@param	posTop		画像の上の位置
	*@param	rect		矩形
	*/
	void setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID);

	void setupTextureSize(const CVec4 texSize, const CVec4 texRect, GLuint texID);

	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	void setupTextureColor(const CVec4 cloar,const GLuint texID);

	void TextureFade(const GLuint texID,const bool out);

	void deleteTexture(const GLsizei texID);
};