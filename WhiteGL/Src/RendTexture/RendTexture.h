#pragma once
/**
*RendTexture.h
*
*	2017/10/10	Mat
*		テクスチャの読み込み、描画
*/

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Image/image.h"
#include "../Vec2.h"
#include "../Vec3.h"
#include "../Vec4.h"
#include "../Constants.h"
#include "../Data/Animation/Animation.h"
#include <vector>
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
public:
	CVec4 _rectPos[MAX_TEXTURE_NUMBER] = {};
	CVec2 _position[MAX_TEXTURE_NUMBER] = {};

	CVec4 rect[MAX_TEXTURE_NUMBER] = {};
	CVec2 texWH[MAX_TEXTURE_NUMBER] = {};
	CVec2 texScale[MAX_TEXTURE_NUMBER] = {};

	TEX_TYPE texType[MAX_TEXTURE_NUMBER] = {};
	CVec4 colorRGBA[MAX_TEXTURE_NUMBER] = {};
	//テクスチャ情報
	GLuint g_texID[MAX_TEXTURE_NUMBER] = {};
	CImage* tex[MAX_TEXTURE_NUMBER] = {};
	bool actionFade[MAX_TEXTURE_NUMBER] = {};
	float actionFadeInterval[MAX_TEXTURE_NUMBER] = {};
	bool fadeOut[MAX_TEXTURE_NUMBER] = {};

	//板の三角ポリゴン用
	CVec4 _polyVert[MAX_BACKGROUND_NUMBER] = {};
	CVec4 _polyColor[MAX_BACKGROUND_NUMBER] = {};

	CRendTexture()
	{

	}

	~CRendTexture()
	{
		for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
		{
			deleteTexture(i);
			SAFE_DELETE(tex[i]);
		}
	}

public:

	void update(std::vector<CAnimation*>* anim);

	void render();

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

	//三角ポリゴン設定
	void setupTrianglesPoly(const CVec4 vertex,const CVec4 color);

	void setupTextureSize(const CVec2 texPos, const CVec4 texRect, GLuint texID);

	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	void setupTextureColor(const CVec4 cloar,const GLuint texID);

	void TextureFade(const GLuint texID,const bool out,const float fadeInterval);

	void deleteTexture(const GLuint texID);

	void setScale(const CVec2 Size, const GLuint texID);

	void setPosition(const CVec2 position, const GLuint texID);

	void setMapPosition(const CVec2 position, const GLuint texID);

	void setRotate(const CVec3 rotate, const GLuint texID);

	void setTextureRect(const CVec4 Rect, const GLuint texID);

	void fadeSearch();

	void allTextureDelete();			//ゲームの中のテクスチャをすべて削除
	void allTextureDeletenotPlayer();	//ゲームに必要不可欠なテクスチャ以外のテクスチャを削除(ステージ移動)

	void SetProgressBarWH(const GLuint texID, const CVec4 Rect,const CVec2 position);

	void notesFadeBackground();	//背景用の更新処理

	void notesFadeInit();		//背景用の初期化
};