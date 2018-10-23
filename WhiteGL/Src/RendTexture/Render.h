#pragma once
/**
*Render.h
*
*	2017/10/10	Mat
*		テクスチャの読み込み、描画
*/

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Vec2.h"
#include "../Vec4.h"
#include "../Constants.h"
#include "../Data/Animation/Animation.h"
#include <vector>


namespace render
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
		//テクスチャ情報
		std::vector<GLuint*>	_texID = {};		//テクスチャのID
		std::vector<CVec4*>		_texRectPos = {};	//テクスチャの切り取り矩形
		std::vector<CVec4*>		_texRect = {};		//テクスチャの矩形
		std::vector<TEX_TYPE*>	_texType = {};		//テクスチャのタイプ
		std::vector<CVec4*>		_texColorRGBA = {};	//テクスチャの色情報


		//板の三角ポリゴン用
		std::vector<CVec4*> _bgPolyVert = {};		//背景用三角ポリゴンの頂点座標情報
		std::vector<CVec4*> _bgPolyColor = {};		//背景用三角ポリゴンの色情報
		std::vector<float*> _bgPolyAngle = {};		//背景用三角ポリゴンの回転情報


		//板のポリゴン用
		std::vector<CVec4*> _polyVert = {};		//ポリゴンの頂点座標情報
		std::vector<CVec4*> _polyColor = {};		//ポリゴンの色情報
		std::vector<float*> _polyAngle = {};		//ポリゴンの回転情報

		

		//レイヤ設定用
		std::vector<LAYER*> m_texLayer = {};		//テクスチャのレイヤ情報
		std::vector<LAYER*> m_bgPolyLayer = {};	//背景用三角ポリゴンのレイヤ情報
		std::vector<LAYER*> m_polyLayer = {};		//ポリゴンのレイヤ情報


		CRenderer()
		{
			//init();
		}

		~CRenderer()
		{
			for (int i = 0; i < _texID.size(); i++)
			{
				SAFE_DELETE(_texID[i]);
				SAFE_DELETE(_texRectPos[i]);
				SAFE_DELETE(_texRect[i]);
				SAFE_DELETE(_texType[i]);
				SAFE_DELETE(_texColorRGBA[i]);
				SAFE_DELETE(m_texLayer[i]);
			}
			for (int i = 0; i < _polyVert.size(); i++)
			{
				SAFE_DELETE(_polyVert[i]);
				SAFE_DELETE(_polyColor[i]);
				SAFE_DELETE(_polyAngle[i]);
				SAFE_DELETE(m_polyLayer[i]);
			}
			for (int i = 0; i < _bgPolyVert.size(); i++)
			{
				SAFE_DELETE(_bgPolyVert[i]);
				SAFE_DELETE(_bgPolyColor[i]);
				SAFE_DELETE(_bgPolyAngle[i]);
				SAFE_DELETE(m_bgPolyLayer[i]);
			}
		}

	public:

		//初期化
		void init();
		void changeStageInit();

		//テクスチャ情報登録
		void pushTexture(GLuint* texID, CVec4* texRectPos, CVec4* texRect, int* texType, CVec4* texColor,int* layer);
		//ポリゴン情報登録
		void pushPoly(CVec4* vertex, CVec4* color, float* angle,int* layer);
		//背景用三角ポリゴン情報登録
		void pushTriPoly(CVec4* vertex, CVec4* color, float* angle, int* layer);



		//登録情報全ての描画更新処理
		void render();











		
	};
}