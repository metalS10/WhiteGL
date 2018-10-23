#include "Render.h"
#include "../Search/BinarySearch.h"
#include <algorithm>

using namespace render;

//初期化
void CRenderer::init()
{
	//==================================
	//テクスチャ
	//==================================
	//まず全削除
	_texRectPos.clear();
	_texRect.clear();
	_texType.clear();
	_texColorRGBA.clear();
	_texID.clear();
	m_texLayer.clear();	

	//vector型の初期化
	_texRectPos			= std::vector<CVec4*>();
	_texRect			= std::vector<CVec4*>();
	_texType			= std::vector<TEX_TYPE*>();
	_texColorRGBA		= std::vector<CVec4*>();
	_texID				= std::vector<GLuint*>();
	m_texLayer			= std::vector<LAYER*>();

	//==================================
	//ポリゴン
	//==================================
	_polyVert.clear();
	_polyColor.clear();
	_polyAngle.clear();
	m_polyLayer.clear();

	//初期化
	_polyVert		= std::vector<CVec4*>();
	_polyColor		= std::vector<CVec4*>();
	_polyAngle		= std::vector<float*>();
	m_polyLayer		= std::vector<LAYER*>();


	//==================================
	//背景ポリゴン
	//==================================
	_bgPolyVert.clear();
	_bgPolyColor.clear();
	_bgPolyAngle.clear();
	m_bgPolyLayer.clear();

	_bgPolyVert		= std::vector<CVec4*>();
	_bgPolyColor	= std::vector<CVec4*>();
	_bgPolyAngle	= std::vector<float*>();
	 m_bgPolyLayer	= std::vector<LAYER*>();	//背景用三角ポリゴンのレイヤ情報

}
//ステージ移動の初期化
void CRenderer::changeStageInit()
{
	//==================================
	//テクスチャ
	//==================================
	//まず全削除
	_texRectPos.clear();
	_texRect.clear();
	_texType.clear();
	_texColorRGBA.clear();
	_texID.clear();
	m_texLayer.clear();

	//vector型の初期化
	_texRectPos = std::vector<CVec4*>();
	_texRect = std::vector<CVec4*>();
	_texType = std::vector<TEX_TYPE*>();
	_texColorRGBA = std::vector<CVec4*>();
	_texID = std::vector<GLuint*>();
	m_texLayer = std::vector<LAYER*>();

	//==================================
	//背景ポリゴン
	//==================================
	_bgPolyVert.clear();
	_bgPolyColor.clear();
	_bgPolyAngle.clear();
	m_bgPolyLayer.clear();

	_bgPolyVert = std::vector<CVec4*>();
	_bgPolyColor = std::vector<CVec4*>();
	_bgPolyAngle = std::vector<float*>();
	m_bgPolyLayer = std::vector<LAYER*>();	//背景用三角ポリゴンのレイヤ情報
}




//全ての描画更新処理
void CRenderer::render()
{
	// The following two lines enable semi transparent
	glEnable(GL_BLEND);
	glEnable(GL_COLOR_ARRAY);
	//色データをメモリに登録するための許可
	glEnableClientState(GL_COLOR_ARRAY);
	//テクスチャ情報も同様
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//レイヤー情報Findできた順番
	for (GLuint i = 0; i <= (GLuint)LAYER::MAX; i++)
	{
		//背景用ポリゴン描画
		for (int j = 0; j < _bgPolyVert.size(); j++)
		{
			if (_bgPolyVert.size() != 0)		//中身があるか確認
			{
				if ((GLuint)*(m_bgPolyLayer)[j] == i)
				{

					//空であれば飛ばす
					if (!_bgPolyVert[j]->x && !_bgPolyVert[j]->y && !_bgPolyVert[j]->z)
						continue;

					glPushMatrix();
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glEnableClientState(GL_VERTEX_ARRAY);


					//場所指定
					const GLfloat vtx2[] = {	//x左下となる点の位置,底辺となる点の位置y,z上の点の位置,w三角形の大きさ
						_bgPolyVert[j]->x - _bgPolyVert[j]->z * 0.5f 		,	_bgPolyVert[j]->y - _bgPolyVert[j]->w * 0.5f,1.0f,	//左
						_bgPolyVert[j]->x + _bgPolyVert[j]->z * 0.5f		,	_bgPolyVert[j]->y - _bgPolyVert[j]->w * 0.5f,1.0f,	//右
						_bgPolyVert[j]->x									,	_bgPolyVert[j]->y + _bgPolyVert[j]->w * 0.5f,1.0f,	//上
					};
					//3次元
					glVertexPointer(3, GL_FLOAT, 0, vtx2);

					//色設定
					const GLfloat color[] = {
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
						_bgPolyColor[j]->x*0.01f,_bgPolyColor[j]->y*0.01f,_bgPolyColor[j]->z*0.01f,_bgPolyColor[j]->w*0.01f,
					};
					//色反映
					glColorPointer(4, GL_FLOAT, 0, color);
					//テクスチャの領域指定
					const GLfloat texuv[] = {
						0.0f, 0.0f,
						0.0f, 0.0f,
						0.0f, 0.0f,
						0.0f, 0.0f,
					};
					//頂点の設定
					glTexCoordPointer(2, GL_FLOAT, 0, texuv);
					//板ポリゴン表示
					glDrawArrays(GL_TRIANGLES, 0, 4);

					//色設定
					const GLfloat colorLine[] = {
						0,0,0,100,
						0,0,0,100,
						0,0,0,100,
						0,0,0,100,
					};


					glColorPointer(4, GL_FLOAT, 0, colorLine);
					//3次元
					glVertexPointer(3, GL_FLOAT, 0, vtx2);
					glDrawArrays(GL_LINE_LOOP, 0, 3);

					glDisableClientState(GL_VERTEX_ARRAY);

					glPopMatrix();
				}
			}
		}
		//ポリゴン描画
		for (int j = 0; j < _polyVert.size(); j++)
		{
			if (_polyVert.size() != 0)		//中身があるか確認
			{
				if ((GLuint)*(m_polyLayer)[j] == i)
				{
					//空であれば飛ばす
					if (_polyVert[j]->x && !_polyVert[j]->y && !_polyVert[j]->z && !_polyVert[j]->w)
						continue;

					glPushMatrix();
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					glEnableClientState(GL_VERTEX_ARRAY);

					//場所指定
					const GLfloat vtx2[] = {	//x:X座標中央,y:Y座標中央,z:X座標Scale,w:y座標Scale
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//左下
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y - _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//右下
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x + _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//右上
						_polyVert[j]->x + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) - sin(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) 	, _polyVert[j]->y + sin(*_polyAngle[j] / 180.0f) * ((_polyVert[j]->x - _polyVert[j]->z * 0.5f) - _polyVert[j]->x) + cos(*_polyAngle[j] / 180.0f)*((_polyVert[j]->y + _polyVert[j]->w * 0.5f) - _polyVert[j]->y) ,1.0f,	//左上
					};
					//3次元
					glVertexPointer(3, GL_FLOAT, 0, vtx2);

					//色設定
					const GLfloat color[] = {
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
						_polyColor[j]->x*0.01f,_polyColor[j]->y*0.01f,_polyColor[j]->z*0.01f,_polyColor[j]->w*0.01f,
					};
					//色反映
					glColorPointer(4, GL_FLOAT, 0, color);

					//板ポリゴン表示
					glDrawArrays(GL_QUADS, 0, 4);

					//色設定
					const GLfloat colorLine[] = {
						0,0,0,_polyColor[j]->w*0.01f,
						0,0,0,_polyColor[j]->w*0.01f,
						0,0,0,_polyColor[j]->w*0.01f,
						0,0,0,_polyColor[j]->w*0.01f,
					};


					glColorPointer(4, GL_FLOAT, 0, colorLine);
					//3次元
					glVertexPointer(3, GL_FLOAT, 0, vtx2);
					glDrawArrays(GL_LINE_LOOP, 0, 4);

					glDisableClientState(GL_VERTEX_ARRAY);

					glPopMatrix();
				}
			}
		}
		for (int j = 0; j < _texID.size(); j++)
		{
			if (_texID.size() != 0)		//中身があるか確認
			{
				if ((GLuint)*m_texLayer[j] == i)
				{
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

					//使用許可
					glEnable(GL_TEXTURE_2D);

					if (*_texType[j] == TEX_TYPE::BMP)
					{
						//場所指定
						const GLfloat vtx2[] = {
							_texRectPos[j]->x,_texRectPos[j]->z,0,
							_texRectPos[j]->y,_texRectPos[j]->z,0,
							_texRectPos[j]->y,_texRectPos[j]->w,0,
							_texRectPos[j]->x,_texRectPos[j]->w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//テクスチャの領域指定
						const GLfloat texuv[] = {
							_texRect[j]->x, _texRect[j]->z,
							_texRect[j]->y, _texRect[j]->z,
							_texRect[j]->y, _texRect[j]->w,
							_texRect[j]->x, _texRect[j]->w,
						};
						//頂点の設定
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);

					}
					else if (*_texType[j] == TEX_TYPE::PNG)
					{
						//場所指定
						const GLfloat vtx2[] = {
							_texRectPos[j]->x, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->w,0,
							_texRectPos[j]->x, _texRectPos[j]->w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,

						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//テクスチャの領域指定
						const GLfloat texuv[] = {
							_texRect[j]->x, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->z,
							_texRect[j]->x, _texRect[j]->z,
						};
						//頂点の設定
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);

					}
					else if (*_texType[j] == TEX_TYPE::QUAD)
					{
						//場所指定
						const GLfloat vtx2[] = {
							_texRectPos[j]->x, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->z,0,
							_texRectPos[j]->y, _texRectPos[j]->w,0,
							_texRectPos[j]->x, _texRectPos[j]->w,0,
						};
						glVertexPointer(3, GL_FLOAT, 0, vtx2);

						const GLfloat color[] = {
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
							_texColorRGBA[j]->x*0.01f,_texColorRGBA[j]->y*0.01f,_texColorRGBA[j]->z*0.01f,_texColorRGBA[j]->w*0.01f,
						};
						glColorPointer(4, GL_FLOAT, 0, color);

						//テクスチャの領域指定
						const GLfloat texuv[] = {
							_texRect[j]->x, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->w,
							_texRect[j]->y, _texRect[j]->z,
							_texRect[j]->x, _texRect[j]->z,
						};
						//頂点の設定
						glTexCoordPointer(2, GL_FLOAT, 0, texuv);
					}

					glEnableClientState(GL_VERTEX_ARRAY);
					//テクスチャの画像指定
					glBindTexture(GL_TEXTURE_2D, *(_texID)[j]);
					//板ポリゴン表示
					glDrawArrays(GL_QUADS, 0, 4);

					glDisableClientState(GL_VERTEX_ARRAY);

					//使用許可
					glDisable(GL_TEXTURE_2D);

				}
			}
		}
	}

	//許可を外す
	glDisable(GL_BLEND);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//テクスチャ情報登録関数
void CRenderer::pushTexture(GLuint* texID, CVec4* texRectPos, CVec4* texRect, int* texType, CVec4* texColor,int* layer)
{
	_texID			.push_back(texID);
	_texRectPos		.push_back(texRectPos);
	_texRect		.push_back(texRect);
	_texType		.push_back((TEX_TYPE*)texType);
	_texColorRGBA	.push_back(texColor);
	m_texLayer		.push_back((LAYER*)layer);
}
//ポリゴン情報登録関数
void CRenderer::pushPoly(CVec4* vertex, CVec4* color, float* angle, int* layer)
{
	_polyVert	.push_back(vertex);
	_polyColor	.push_back(color);
	_polyAngle	.push_back(angle);
	m_polyLayer	.push_back((LAYER*)layer);
}
//ポリゴン情報登録関数
void CRenderer::pushTriPoly(CVec4* vertex, CVec4* color, float* angle, int* layer)
{
	_bgPolyVert		.push_back(vertex);
	_bgPolyColor	.push_back(color);
	_bgPolyAngle	.push_back(angle);
	m_bgPolyLayer	.push_back((LAYER*)layer);
}




















