#pragma once
#include "../Vec2.h"
#include "../Vec4.h"
#include "../Image/image.h"
#include "../RendTexture/Render.h"

namespace rendInfo
{
	//テクスチャのタイプ
	enum class TEX_TYPE : int
	{
		BMP = 0,
		PNG = 1,
		JPEG = 2,
		QUAD = 3,
	};
	//レイヤーのタイプ
	enum class LAYER : int
	{
		BG = 0,
		MAIN = 1,
		UI = 2,
		BB = 3,
		MAX = BB,
	};

	//==========================================
	//テクスチャ
	//==========================================
	class CTexRendInfo
	{
	private:
		GLuint	_texID = 0;			//テクスチャのID情報
		CImage* _texImage = {};		//テクスチャの画像情報
		CVec4	_texRectPos = {};	//テクスチャの切り取り矩形
		CVec2	_texPosition = {};	//テクスチャのポジション
		int		_texTag = {};		//テクスチャのタグ
		CVec2	_texWH = {};		//テクスチャの縦横
		CVec2	_texScale = {};		//テクスチャのスケール
		CVec4	_texRect = {};		//テクスチャの矩形
		float	_texDefaultScale = {};	//テクスチャの初期スケール
		TEX_TYPE _texType = {};		//テクスチャのタイプ
		CVec4	_texColorRGBA = {};	//テクスチャの色情報
		render::CRenderer* m_renderer = {};	//描画者
		LAYER _texLayer = {};		//テクスチャのレイヤ設定

		int _texActionFadeCounter = 0;	//フェードイン・アウトの速度
		bool _texFadeOut = false;		//フェードアウトか否か(trueならフェードイン)
		bool _texActionFade = false;	//フェードイン・アウト中かどうか
		bool _texActionBeats = false;	//テクスチャを拍子に合わせるか否か

	public:
		//コンストラクタ
		CTexRendInfo();
		//デストラクタ
		~CTexRendInfo();
		//初期化用
		void init();

	private:
		//描画設定用
		/**
		*テクスチャ情報登録
		*@param	file	ファイルパス
		*@param	tex_type	テクスチャの拡張子
		*param	texPos	テクスチャの位置
		*@param	texRect	テクスチャの矩形
		*@param	color	テクスチャ色
		*@param	layer	レイヤ設定
		*/
		void setupTexture(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color,LAYER layer);
	public:
		//テクスチャ情報の設定
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color,LAYER layer);
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color);
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect,LAYER layer);
		void setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect);
		//テクスチャの座標設定(初期化)
		void setupTextureTransform(const CVec2 texPos, const CVec4 texRect);
		//テクスチャの色設定(初期化)
		void setupTextureColor(const CVec4 color);
		//テクスチャのスケール設定
		void setTextureScale(const CVec2 Size);
		//テクスチャの座標設定
		void setTexPosition(const CVec2 position);
		//テクスチャの矩形設定
		void setTextureRect(const CVec4 Rect);
		//HPやBPのバーのための矩形設定
		void SetProgressBarWH(const CVec4 Rect, const CVec2 position);
		//Map用
		void setMapPosition(const CVec2 position, const int tag);


		//テクスチャのフェードアクション
		void setActionFade(const bool out, const float fadeInterval);
		//フェードイン・アウト中のテクスチャの色変更処理
		void textureActionFade();
		//テクスチャフェード終了しているかどうかを返す
		bool endTextureFade();
		//テクスチャを拍子に合わせるか否かのセット
		void setTexActionBeats(bool action);
		//テクスチャの拍子に合わせるアクションの更新処理
		void textureNotesAction();

		//テクスチャの削除
		void deleteTexture();
	};

	//===================================================
	//ポリゴン
	//===================================================
	class CPolygonRendInfo
	{
	private:
		//板のポリゴン用
		CVec4 _polyVert = {};			//頂点座標
		CVec4 _polyColor = {};			//ポリゴン色情報
		CVec2 _polyDefaultVert = {};	//初期頂点座標
		float _polyAngle = {};			//回転角度
		LAYER m_polyLayer;				//レイヤ情報
		bool _polyActionBeats = false;	//テクスチャを拍子に合わせるか否か
		render::CRenderer* m_renderer = {};	//描画者

	public:
		//コンストラクタ
		CPolygonRendInfo();
		//デストラクタ
		~CPolygonRendInfo();
		//初期化用
		void init();

		//板ポリゴン設定
		/**
		*ポリゴン情報登録
		*@param	vertex	頂点座標
		*@param	color	ポリゴン色
		*@param	layer	レイヤ設定
		*/
		void setupPoly(const CVec4 vertex, const CVec4 color, LAYER layer);
		void setPolyPos(const CVec2 vertex);	//ポリゴンの座標再設定
		void setPolyScale(const CVec2 scale);	//ポリゴンのスケール再設定
		void setPolyPosX(const float vertex);	//ポリゴンの座標再設定
		void setPolyAngle(const float angle);	//ポリゴンの回転設定
		void setPolyColor(const CVec4 color);	//ポリゴンの色設定
		void addPolyAngle(const float angle);	//ポリゴンの回転増
		float getPolyAngle();					//ポリゴンの回転取得
		CVec2 getPolyScale();					//ポリゴンのスケール取得
		CVec4 getPolyColor();					//ポリゴンの色取得
		void deletePoly();		//ポリゴンの削除


		void polygonBeatsAction();		//beatsに合わせるアクションの更新処理
		void polygonBeatsActionInit(const int mode);		//beatsに合わせるアクション(mode(0:サイズ,1色))


	};

	//===================================================
	//背景用三角ポリゴン
	//===================================================
	class CTriPolygonRendInfo
	{
	private:
		//板の三角ポリゴン用
		CVec4 _bgPolyVert = {};			//頂点座標
		CVec4 _bgPolyColor = {};		//色
		int _bgPolyLine = {};		//列
		int _bgPolyMaxLine = 0;		//最大列数
		int _bgPolyDefaultVert = 0;	//初期頂点座標
		LAYER m_bgPolyLayer = {};		//レイヤ
		float _bgPolyAngle = 0;			//回転角度

		//ポリゴン達のアニメーション用
		int upfadeCount = 0;
		int _beatUpSize = BEAT_BIGSIZE;

		render::CRenderer* m_renderer = {};	//描画者

	public:
		//コンストラクタ
		CTriPolygonRendInfo();
		//デストラクタ
		~CTriPolygonRendInfo();
		//初期化用
		void init();


		//三角ポリゴン設定
		void setupTrianglesPoly(CVec4 vertex, CVec4 color, int line, LAYER layer);
		//背景ポリゴンのX座標変更
		void setTrianglesPolyPos(float vertexX, CVec4 color);
		//三角ポリゴンの回転増
		void addTrianglesPolyAngle(float angle);

		void notesFadeBackground();	//背景用の更新処理

		void notesRandomFadeInit();		//背景用のランダム初期化
		void notesUpFadeInit(int mode);			//背景用の上に上がっていく初期化(mode)

	};

}