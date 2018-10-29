#include "RendInfo.h"
#include "../AllController/AllController.h"
#include "../Image/LoadImage/LoadImage.h"

using namespace rendInfo;

//===============================================================
//	テクスチャ
//===============================================================

//コンストラクタ
CTexRendInfo::CTexRendInfo()
{
	init();
}
//デストラクタ
CTexRendInfo::~CTexRendInfo()
{
	deleteTexture();
	SAFE_DELETE(_texImage);
}
//初期化
void CTexRendInfo::init()
{
	//全体描画のm_rendererをゲット
	m_renderer = MS::CMS::getInstance()->getRenderer();

	//rendererに自分の描画用の全てを設定する
	m_renderer->pushTexture(&_texID, &_texRectPos, &_texRect, (int*)&_texType, &_texColorRGBA, (int*)&_texLayer);
}


//==============================================================
//情報設定系
//==============================================================

//テクスチャの情報設定(初期化)
/**
*テクスチャ情報登録
*@param	file	ファイルパス
*@param	tex_type	テクスチャの拡張子
*param	texPos	テクスチャの位置
*@param	texRect	テクスチャの矩形
*@param	color	テクスチャ色
*@param	layer	レイヤ設定
*/
void CTexRendInfo::setupTexture(const char *file, const TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer)
{

	//使用許可
	glEnable(GL_TEXTURE_2D);

	//texIDを空いているところへ
	_texID = texID;
	//glGenTextures(1, &_texID);
	//初期化
	glBindTexture(GL_TEXTURE_2D, _texID);

	switch (tex_type)
	{
	case TEX_TYPE::BMP:
		_texImage = new CBmpImage();
		//画像情報読み込み
		if (_texImage->load(file) == false)
		{
			std::cerr << "ERROR : 画像の読み込みに失敗" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texImage->m_width, _texImage->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texImage->m_bits);

		//テクスチャの拡大・縮小方法の設定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//テクスチャの繰り返しの指定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		break;

	case TEX_TYPE::PNG:
		_texImage = new CPngImage();
		if (_texImage->load(file) == false)
		{
			std::cerr << "ERROR : 画像の読み込みに失敗" << std::endl;
		}
		if (_texImage->m_format == PNG_COLOR_TYPE_RGBA)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _texImage->m_width, _texImage->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _texImage->m_bits);

			//テクスチャの拡大・縮小方法の設定
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//テクスチャの繰り返しの指定
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}
		else if (_texImage->m_format == PNG_COLOR_TYPE_RGB)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texImage->m_width, _texImage->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, _texImage->m_bits);

			//テクスチャの拡大・縮小方法の設定
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//テクスチャの繰り返しの指定
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		}
		else if (_texImage->m_format == PNG_COLOR_TYPE_PALETTE)
		{
			GLubyte* textureImage;

			int width, height;
			bool hasAlpha = true;	//とりあえずPngはAlphaあるでしょ
			const char* filename = file;
			bool success = loadImage::CLoadImage::loadPngImage(filename, width, height, hasAlpha, &textureImage);
			if (!success) {
				//std::cout << "Unable to load png file" << std::endl;
				return;
			}
			//std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width,
				height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE,
				textureImage);

			//テクスチャの拡大・縮小方法の設定
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			//テクスチャの繰り返しの指定
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			SAFE_DELETE(textureImage);
		}
		else if (_texImage->m_format == PNG_COLOR_TYPE_GRAY)
		{
			//テクスチャにPNGファイルから読み込んだピクセルを書き込む
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, _texImage->m_width, _texImage->m_height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, _texImage->m_bits);
			//grayってどう描画するんだろう
			std::cout << "PNG_COLOR_TYPE_GRAY用描画システム未完成" << std::endl;
		}

		break;

	case TEX_TYPE::QUAD:
		_texImage = new CPngImage();

		_texImage->m_width = 1; _texImage->m_height = 1;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ONE, 1, 1, 0, GL_ONE, GL_UNSIGNED_BYTE, 0);

		//テクスチャの拡大・縮小方法の設定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//テクスチャの繰り返しの指定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		break;


	default:
		break;
	}
	
	//スケールの初期化
	_texScale = CVec2(1, 1);
	//スケールの初期値
	_texDefaultScale = 1.0f;


	//レイヤ設定
	_texLayer = layer;
	//テクスチャ色設定(初期化)
	setupTextureColor(color);
	//テクスチャ拡張子の設定
	_texType = tex_type;

	//座標設定
	setupTextureTransform(texPos,texRect);


	//使用許可
	glDisable(GL_TEXTURE_2D);

}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type,GLuint texID,CVec2 texPos, CVec4 texRect, CVec4 color, LAYER layer)
{
	setupTexture(file, tex_type, texID, texPos, texRect, color, layer);
}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type,GLuint texID,CVec2 texPos, CVec4 texRect, CVec4 color)
{
	setupTexture(file, tex_type, texID, texPos, texRect, color, LAYER::MAIN);
}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect, LAYER layer)
{
	setupTexture(file, tex_type, texID, texPos, texRect, CVec4(100.0f,100.0f,100.0f,100.0f), layer);
}
void CTexRendInfo::setImage(const char *file, TEX_TYPE tex_type, GLuint texID, CVec2 texPos, CVec4 texRect)
{
	setupTexture(file, tex_type, texID, texPos, texRect, CVec4(100.0f,100.0f,100.0f,100.0f), LAYER::MAIN);
}

//テクスチャのトランスフォーム設定(初期化)
void CTexRendInfo::setupTextureTransform(const CVec2 texPos, const CVec4 texRect)
{

	//横幅縦幅をセット
	_texWH = CVec2(((texRect.x + texRect.z) - texRect.x) * 0.5f, ((texRect.y + texRect.w) - texRect.y) * 0.5f);
	_texRectPos = CVec4(texPos.x - _texWH.x, texPos.x + _texWH.x, texPos.y - _texWH.y, texPos.y + _texWH.y);
	_texPosition = texPos;
	//画像の矩形範囲を設定
	CVec4 changerect4 = CVec4(texRect.x / _texImage->m_width, (texRect.x + texRect.z) / _texImage->m_width, texRect.y / _texImage->m_height, (texRect.y + texRect.w) / _texImage->m_height);
	_texRect = CVec4(changerect4);

	if (_texImage == NULL)
	{
		std::cerr << "BMP,PNG,JPEGなんでもないです" << std::endl;
	}
}

//テクスチャの色設定(初期化)
void CTexRendInfo::setupTextureColor(const CVec4 color)
{
	_texColorRGBA = color;
}
//テクスチャのスケール設定
void CTexRendInfo::setTextureScale(const CVec2 Size)
{
	_texScale= Size;
	_texRectPos = CVec4(_texPosition.x - _texWH.x * Size.x, _texPosition.x + _texWH.x * Size.x, _texPosition.y - _texWH.y * Size.y, _texPosition.y + _texWH.y * Size.y);
}
//テクスチャの座標設定
void CTexRendInfo::setTexPosition(const CVec2 position)
{
	_texPosition = position;
	_texRectPos = CVec4(
		_texPosition.x - _texWH.x * _texScale.x,
		_texPosition.x + _texWH.x * _texScale.x,
		_texPosition.y - _texWH.y * _texScale.y,
		_texPosition.y + _texWH.y * _texScale.y);
}
//テクスチャの矩形設定
void CTexRendInfo::setTextureRect(const CVec4 rect)
{
	//画像の矩形範囲を設定
	CVec4 changerect4 = CVec4(rect.x / _texImage->m_width, (rect.x + rect.z) / _texImage->m_width, rect.y / _texImage->m_height, (rect.y + rect.w) / _texImage->m_height);

	_texRect = CVec4(changerect4);
}
//HPやBPのバーのための矩形設定
void CTexRendInfo::SetProgressBarWH(const CVec4 _texRect, const CVec2 position)
{
	CVec2 vec2;
	if (_texRect.z >= 0)
	{
		_texWH = CVec2(_texRect.z, 5.0f);
		vec2 = CVec2(position.x + _texRect.z, position.y);
	}
	else
	{
		_texWH = CVec2(0.0f, 5.0f);
		vec2 = CVec2(position.x + 0.0f, position.y);
	}
	_texPosition = vec2;
	_texRectPos = CVec4(
		_texPosition.x - _texWH.x * _texScale.x,
		_texPosition.x + _texWH.x * _texScale.x,
		_texPosition.y - _texWH.y * _texScale.y,
		_texPosition.y + _texWH.y * _texScale.y);

	return;
}


//==============================================================
//Map用
//==============================================================
//マップデータの座標設定
void CTexRendInfo::setMapPosition(const CVec2 position, const int tag)
{
	_texPosition = position;
	CVec4 defrect = _texRectPos;
	_texRectPos = CVec4(_texPosition.x + defrect.x, _texPosition.x + defrect.y, _texPosition.y + defrect.z, _texPosition.y + defrect.w);
	return;
}


//==============================================================
//アクション系
//==============================================================

//テクスチャのフェードアクション設定
void CTexRendInfo::setActionFade(const bool out, const float fadeCounter)
{
	//フェードイン・アウト中である
	_texActionFade = true;
	//フェードの速度
	_texActionFadeCounter = fadeCounter;
	//フェードインorアウトのセット
	_texFadeOut = out;

	return;
}

//フェードイン・アウト中の動き(色情報)
void CTexRendInfo::textureActionFade()
{
	//フェードインアウト
	if (_texActionFade)
	{
		//フェードアウト
		if (_texFadeOut)
		{
			_texColorRGBA.w -= _texActionFadeCounter;
			if (_texColorRGBA.w < 0.0f)
			{
				_texColorRGBA.w = 0.0f;
				_texActionFade = false;
			}
		}
		//フェードイン
		else
		{
			_texColorRGBA.w += _texActionFadeCounter;
			if (_texColorRGBA.w > 100.0f)
			{
				_texColorRGBA.w = 100.0f;
				_texActionFade = false;
			}
		}

	}

}

//テクスチャフェード終了しているかどうかを返す
bool CTexRendInfo::endTextureFade()
{
	return !_texActionFade;
}
//テクスチャを拍子に合わせるか否かのセット
void CTexRendInfo::setTexActionBeats(bool action)
{
	_texActionBeats = action;
}
//テクスチャのサイズが戻る動き
void CTexRendInfo::textureNotesAction()
{
	if (_texActionBeats)
	{
		if (_texScale.x < _texDefaultScale)
		{
			setTextureScale(CVec2(_texScale.x + 0.01f, _texScale.y + 0.01f));
		}
	}
}

//==============================================================
//削除系
//==============================================================


//テクスチャの削除
void CTexRendInfo::deleteTexture()
{
	//使用許可
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glDeleteTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_2D, 0);
	//_texID = 0;
	_texRect = {};
	_texRectPos = {};

	//使用許可
	glDisable(GL_TEXTURE_2D);
}


//===============================================================
//ポリゴン
//===============================================================
//コンストラクタ
CPolygonRendInfo::CPolygonRendInfo()
{
	init();
}
//デストラクタ
CPolygonRendInfo::~CPolygonRendInfo()
{
	deletePoly();
}
//初期化
void CPolygonRendInfo::init()
{
	//全体描画のm_rendererをゲット
	m_renderer = MS::CMS::getInstance()->getRenderer();

	//rendererに自分の描画用の全てを設定する
	m_renderer->pushPoly(&_polyVert, &_polyColor, &_polyAngle, (int*)&m_polyLayer);
}


//ポリゴンのセットアップ
void CPolygonRendInfo::setupPoly(const CVec4 vertex, const CVec4 color, const LAYER layer)
{
	//ポリゴン設定を追加
	_polyVert = vertex;
	_polyColor = color;
	_polyDefaultVert = CVec2(vertex.z, vertex.w);
	m_polyLayer = layer;
}
void CPolygonRendInfo::setPolyPos(const CVec2 vertex)
{
	_polyVert.x = vertex.x;
	_polyVert.y = vertex.y;
}
void CPolygonRendInfo::setPolyScale(const CVec2 scale)
{
	_polyVert.z = scale.x;
	_polyVert.w = scale.y;
}

void CPolygonRendInfo::setPolyPosX(const float vertex)
{
	_polyVert.x = vertex;
}
void CPolygonRendInfo::setPolyAngle(const float angle)
{
	_polyAngle = angle;
}
void CPolygonRendInfo::setPolyColor(const CVec4 color)
{
	_polyColor = color;
}
void CPolygonRendInfo::addPolyAngle(const float angle)
{
	_polyAngle += angle;
}
float CPolygonRendInfo::getPolyAngle()
{
	return _polyAngle;
}
CVec2 CPolygonRendInfo::getPolyScale()
{
	return CVec2(_polyVert.z, _polyVert.w);
}
CVec4 CPolygonRendInfo::getPolyColor()
{
	return _polyColor;
}

//ポリゴンの削除
void CPolygonRendInfo::deletePoly()
{
	setPolyPos(CVec2(0.0f, 0.0f));
	setPolyScale(CVec2(0.0f, 0.0f));
	setPolyAngle(0.0f);
}

//=====================================================
//アクション
//=====================================================
//beatsに合わせるアクションの更新処理
void CPolygonRendInfo::polygonBeatsAction()
{
	//初期より小さければ
	if (_polyVert.z < _polyDefaultVert.x)
	{
		//Scaleを徐々に戻す
		_polyVert.z += _polyDefaultVert.x*0.02f;
		_polyVert.w += _polyDefaultVert.y*0.02f;
	}
	//10より大きければ
	if (_polyColor.w > 10.0f)
	{
		if (_polyActionBeats)
			_polyColor.w -= 10.0f;	//小さくしていく
	}
	/*
	if (_polyTag == TAG_PLAYER_1)
	{
		if (_polyColor.z < 100.0f)
			_polyColor.z += 10.0f;
	}
	*/

}

//beatsに合わせるアクション(mode(0:サイズ,1色))
void CPolygonRendInfo::polygonBeatsActionInit(const int mode)
{
	_polyActionBeats = true;
	switch (mode)
	{
	case 0:
		_polyVert.z = _polyDefaultVert.x * 0.6f;
		_polyVert.w = _polyDefaultVert.y * 0.6f;
		break;
	case 1:
		_polyColor.w = 100.0f;
		break;
	default:
		break;
	}
}

//===============================================================
//背景用三角ポリゴン
//===============================================================
CTriPolygonRendInfo::CTriPolygonRendInfo()
{
	init();
}

CTriPolygonRendInfo::~CTriPolygonRendInfo()
{
	
}

void CTriPolygonRendInfo::init()
{
	//全体描画のm_rendererをゲット
	m_renderer = MS::CMS::getInstance()->getRenderer();

	//rendererに自分の描画用の全てを設定する
	m_renderer->pushTriPoly(&_bgPolyVert, &_bgPolyColor, &_bgPolyAngle, (int*)&m_bgPolyLayer);
}

//三角ポリゴンのセットアップ
void CTriPolygonRendInfo::setupTrianglesPoly(CVec4 vertex, CVec4 color, int line, LAYER layer)
{
	if (!_bgPolyVert.x && !_bgPolyVert.y && !_bgPolyVert.z && !_bgPolyVert.w)
	{
		//ポリゴン設定を追加
		_bgPolyVert = vertex;
		_bgPolyColor = color;
		_bgPolyLine = line;
		_bgPolyMaxLine = line;
		_bgPolyDefaultVert = vertex.z;
		m_bgPolyLayer = layer;
	}
}


void CTriPolygonRendInfo::setTrianglesPolyPos(float vertexX, CVec4 color)
{
	_bgPolyVert.x = vertexX;
	_bgPolyColor = color;
}
void CTriPolygonRendInfo::addTrianglesPolyAngle(float angle)
{
	_bgPolyAngle += angle;
}

//===============================================================
//アクション
//===============================================================
//背景用の更新処理
void CTriPolygonRendInfo::notesFadeBackground()
{
	if (_bgPolyColor.w > 10.0f)
		_bgPolyColor.w -= 5.0f;

	if (_bgPolyVert.z > _bgPolyDefaultVert)
	{
		_bgPolyVert.z -= _beatUpSize * 0.1f;
		//下向き三角
		if (_bgPolyVert.w < 0)
			_bgPolyVert.w += _beatUpSize * 0.1f;
		else
			_bgPolyVert.w -= _beatUpSize * 0.1f;
	}

}



//背景用のランダム初期化
void CTriPolygonRendInfo::notesRandomFadeInit()
{
	if (rand() % 3 == 1)
	{
		_bgPolyColor.w = 100.0f;
		_bgPolyVert.z += _beatUpSize;
		//下向き三角
		if (_bgPolyVert.w < 0)
		{
			_bgPolyVert.w -= _beatUpSize;
		}
		else
		{
			_bgPolyVert.w += _beatUpSize;
		}
	}


}

//背景用アクションの初期化(mode)
void CTriPolygonRendInfo::notesUpFadeInit(int mode)
{
	switch (mode)
	{
	case 0:
		if (_bgPolyLine == upfadeCount)
		{
			_bgPolyColor.w = 100.0f;
			_bgPolyVert.z += _beatUpSize;
			//下向き三角
			if (_bgPolyVert.w < 0)
				_bgPolyVert.w -= _beatUpSize;
			else
				_bgPolyVert.w += _beatUpSize;
		}
		upfadeCount++;
		if (upfadeCount > _bgPolyMaxLine)
		{
			upfadeCount = 0;
		}
		break;
	case 1:
		if (_bgPolyLine == upfadeCount || _bgPolyLine == upfadeCount + 1)
		{
			_bgPolyColor.w = 100.0f;
			_bgPolyVert.z += _beatUpSize;
			//下向き三角
			if (_bgPolyVert.w < 0)
				_bgPolyVert.w -= _beatUpSize;
			else
				_bgPolyVert.w += _beatUpSize;
		}
		upfadeCount += 2;
		if (upfadeCount > _bgPolyMaxLine)
		{
			upfadeCount = 0;
		}
		break;
	default:
		break;
	}

}