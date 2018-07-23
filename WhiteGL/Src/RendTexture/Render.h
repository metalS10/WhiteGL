#pragma once
/**
*Render.h
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
enum class LAYER : GLuint
{
	BG = 0,
	MAIN = 1,
	UI = 2,
	MAX = 2,
};

class CRenderer
{
public:
	CVec4 _rectPos[MAX_TEXTURE_NUMBER] = {};	//テクスチャの切り取り矩形
	CVec2 _position[MAX_TEXTURE_NUMBER] = {};	//テクスチャのポジション
	GLuint _texTag[MAX_TEXTURE_NUMBER] = {};

	CVec4 rect[MAX_TEXTURE_NUMBER] = {};
	CVec2 texWH[MAX_TEXTURE_NUMBER] = {};
	CVec2 texScale[MAX_TEXTURE_NUMBER] = {};
	float texDefaultScale[MAX_TEXTURE_NUMBER] = {};

	TEX_TYPE texType[MAX_TEXTURE_NUMBER] = {};
	CVec4 colorRGBA[MAX_TEXTURE_NUMBER] = {};
	//テクスチャ情報
	GLuint g_texID[MAX_TEXTURE_NUMBER] = {};
	CImage* tex[MAX_TEXTURE_NUMBER] = {};
	bool actionFade[MAX_TEXTURE_NUMBER] = {};
	float actionFadeInterval[MAX_TEXTURE_NUMBER] = {};
	bool fadeOut[MAX_TEXTURE_NUMBER] = {};

	//板の三角ポリゴン用
	CVec4 _bgPolyVert[MAX_BACKGROUND_NUMBER] = {};
	CVec4 _bgPolyColor[MAX_BACKGROUND_NUMBER] = {};
	GLuint _bgPolyLine[MAX_BACKGROUND_NUMBER] = {};
	GLuint _bgPolyMaxLine = 0;
	GLuint _bgPolyDefaultVert = 0;

	//板のポリゴン用
	CVec4 _polyVert[MAX_POLYGON_NUMBER] = {};
	CVec4 _polyColor[MAX_POLYGON_NUMBER] = {};
	CVec2 _polyDefaultVert[MAX_POLYGON_NUMBER] = {};
	float _polyAngle[MAX_POLYGON_NUMBER] = {};
	GLuint _polyTag[MAX_POLYGON_NUMBER] = {};

	//ポリゴン達のアニメーション用
	GLuint upfadeCount = 0;
	GLuint _beatUpSize = BEAT_BIGSIZE;
	 
	//レイヤ設定用
	LAYER m_texLayer[MAX_TEXTURE_NUMBER] = {};
	LAYER m_bgPolyLayer[MAX_BACKGROUND_NUMBER] = {};
	LAYER m_polyLayer[MAX_POLYGON_NUMBER] = {};



	CRenderer()
	{

	}

	~CRenderer()
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
	void setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID,const LAYER layer,const GLuint tag);

	//三角ポリゴン設定
	void setupTrianglesPoly(const CVec4 vertex, const CVec4 color, const GLuint line,const LAYER layer);
	void setTrianglesPolyPos(const float vertexX, const CVec4 color, const GLuint number);
	//板ポリゴン設定
	void setupPoly(const CVec4 vertex, const CVec4 color, const LAYER layer, const GLuint tag);
	void setPolyPos(const CVec2 vertex, const GLuint tag);	//ポリゴンの座標再設定
	void setPolyScale(const CVec2 scale, const GLuint tag);	//ポリゴンのスケール再設定
	void setPolyPosX(const float vertex, const GLuint tag);	//ポリゴンの座標再設定
	void setPolyAngle(const float angle,const GLuint tag);	//ポリゴンの回転設定
	void setPolyColor(const CVec4 color, const GLuint tag);	//ポリゴンの色設定
	void addPolyAngle(const float angle,const GLuint tag);	//ポリゴンの回転増
	float getPolyAngle(const GLuint tag);	//ポリゴンの回転取得
	CVec2 getPolyScale(const GLuint tag);	//ポリゴンのスケール取得
	CVec4 getPolyColor(const GLuint tag);	//ポリゴンの色取得

	void setupTextureSize(const CVec2 texPos, const CVec4 texRect,const GLuint texID);
	void setupTextureSizeAtTag(const CVec2 texPos, const CVec4 texRect,const GLuint tag);

	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	void setupTextureColor(const CVec4 cloar,const GLuint texID);
	void setupTextureColorAtTag(const CVec4 cloar,const GLuint tag);

	void TextureFade(const GLuint texID,const bool out,const float fadeInterval);

	void deleteTexture(const GLuint texID);
	void deletePoly(const GLuint tag);

	void setTextureScale(const CVec2 Size, const GLuint texID);
	void setTextureScaleAtTag(const CVec2 Size, const GLuint texID);

	void setPosition(const CVec2 position, const GLuint texID);
	void setPositionAtTag(const CVec2 position, const GLuint tag);

	void setMapPosition(const CVec2 position, const GLuint texID);

	void setTextureRect(const CVec4 Rect, const GLuint texID);

	void fadeSearch();

	void allTextureDelete();			//ゲームの中のテクスチャをすべて削除
	void allTextureDeletenotPlayer();	//ゲームに必要不可欠なテクスチャ以外のテクスチャを削除(ステージ移動)

	void SetProgressBarWH(const GLuint texID, const CVec4 Rect,const CVec2 position);

	void notesFadeBackground();	//背景用の更新処理
	void polygonNotesAction();		//beatsに合わせるアクションの更新処理
	void textureNotesAction();		//テクスチャのbeatsに合わせるアクションの更新処理

	void notesRandomFadeInit();		//背景用のランダム初期化
	void notesUpFadeInit(const GLuint mode);			//背景用の上に上がっていく初期化(mode)
	void polygonNotesActionInit(const GLuint tag,const GLuint mode );		//beatsに合わせるアクション(mode(0:サイズ,1色))
};