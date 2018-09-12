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
#include "../Vec4.h"
#include "../Constants.h"
#include "../Data/Animation/Animation.h"
#include <vector>

#pragma warning(disable:4996)

//テクスチャのタイプ
enum class TEX_TYPE : int
{
	BMP = 0,
	PNG = 1,
	JPEG = 2,
	QUAD = 3,
};
//レイヤーのタイプ
enum class LAYER : GLuint
{
	BG = 0,
	MAIN = 1,
	UI = 2,
	BB = 3,
	MAX = BB,
};

//全ての描画を担うクラス
class CRenderer
{
public:
	std::vector<CVec4>	_texRectPos		= {};	//テクスチャの切り取り矩形
	std::vector<CVec2>	_texPosition	= {};	//テクスチャのポジション
	std::vector<GLuint> _texTag			= {};	//テクスチャのタグ
	std::vector<CVec4>	_texRect		= {};	//テクスチャの矩形
	std::vector<CVec2>	_texWH			= {};	//テクスチャの縦横
	std::vector<CVec2>	_texScale		= {};	//テクスチャのスケール
	std::vector<float>	_texDefaultScale= {};	//テクスチャの初期スケール
	std::vector<TEX_TYPE> _texType		= {};	//テクスチャのタイプ
	std::vector<CVec4>	_texColorRGBA	= {};	//テクスチャの色情報

	//テクスチャ情報
	std::vector<GLuint> _texID = {};
	std::vector<CImage*> _texImage = {};
	std::vector<bool> _texActionFade = {};
	std::vector<float> _texActionFadeInterval = {};
	std::vector<bool> _texFadeOut = {};

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
	std::vector<GLuint> _polyTag = {};

	//ポリゴン達のアニメーション用
	GLuint upfadeCount = 0;
	GLuint _beatUpSize = BEAT_BIGSIZE;
	 
	//レイヤ設定用
	std::vector<LAYER> m_texLayer = {};
	LAYER m_bgPolyLayer[MAX_BACKGROUND_NUMBER] = {};
	LAYER m_polyLayer[MAX_POLYGON_NUMBER] = {};



	CRenderer()
	{
		init();
	}

	~CRenderer()
	{
		for (int i = 0;i < MAX_TEXTURE_NUMBER;i++)
		{
			deleteTexture(i);
			SAFE_DELETE(_texImage[i]);
		}
	}

public:

	//初期化
	void init();

	//アニメーション更新
	void update(std::vector<CAnimation*>* anim);

	//全ての描画更新処理
	void render();

	/**
	*テクスチャ情報登録
	*@param	file	ファイルパス
	*@param	tex_type	テクスチャの拡張子
	*@param	tag		テクスチャID,texTag
	*@param	layer	レイヤ設定
	*/
	void setupTexture(const char *file, const TEX_TYPE tex_type, GLuint tag,const LAYER layer);

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

	//テクスチャのトランスフォーム設定(初期化)
	void setupTextureTransform(const CVec2 texPos, const CVec4 texRect);
	//テクスチャのトランスフォーム設定
	void setupTextureTransformAtTag(const CVec2 texPos, const CVec4 texRect,const GLuint tag);

	//PngImageのロード関数(これだけめちゃくちゃ長いので分けました)
	bool loadPngImage(const char *name, int &outWidth, int &outHeight, bool &outHasAlpha, GLubyte **outData);

	//テクスチャの色設定(初期化)
	void setupTextureColor(const CVec4 cloar);
	//テクスチャ色変更設定
	void setupTextureColorAtTag(const CVec4 cloar,const GLuint tag);
	
	//テクスチャのフェード設定
	void TextureFade(const GLuint tag,const bool out,const float fadeInterval);
	//テクスチャフェード終了しているか
	bool endTextureFade(GLuint tag);

	//テクスチャの削除
	void deleteTexture(const GLuint tag);
	//ポリゴンの削除
	void deletePoly(const GLuint tag);

	//テクスチャのスケール設定
	void setTextureScale(const CVec2 Size, const GLuint texID);
	void setTextureScaleAtTag(const CVec2 Size, const GLuint tag);

	//テクスチャの座標設定
	void setTexPosition(const CVec2 position, const GLuint texID);
	void setTexPositionAtTag(const CVec2 position, const GLuint tag);

	//マップデータの座標設定
	void setMapPosition(const CVec2 position, const GLuint tag);

	//テクスチャの矩形設定
	void setTextureRect(const CVec4 Rect, const GLuint texID);
	void setTextureRectAtTag(const CVec4 Rect, const GLuint tag);

	//フェードイン・アウト中のテクスチャの色変更処理
	void fadeSearch();

	void allTextureDelete();			//ゲームの中のテクスチャをすべて削除
	void allTextureDeletenotPlayer();	//ゲームに必要不可欠なテクスチャ以外のテクスチャを削除(ステージ移動)

	//HPやBPのバーのための矩形設定
	void SetProgressBarWH(const GLuint texID, const CVec4 Rect,const CVec2 position);

	void notesFadeBackground();	//背景用の更新処理
	void polygonNotesAction();		//beatsに合わせるアクションの更新処理
	void textureNotesAction();		//テクスチャのbeatsに合わせるアクションの更新処理

	void notesRandomFadeInit();		//背景用のランダム初期化
	void notesUpFadeInit(const GLuint mode);			//背景用の上に上がっていく初期化(mode)
	void polygonNotesActionInit(const GLuint tag,const GLuint mode );		//beatsに合わせるアクション(mode(0:サイズ,1色))
};