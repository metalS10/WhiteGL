#include "Sprite.h"

/**
*@desc	初期化処理
*@param	fileName	ファイル名
*@return true...成功
*/
bool CSprite::init(const std::string&fileName)
{
	this->m_pTexture = CTextureManager::getInstance()->get(fileName);
	if (this->m_pTexture == NULL)
	{
		printf("テクスチャの生成に失敗\n");
		return false;
	}
	return true;
}

/**
*@desc	描画
*/
void CSprite::draw()
{
	float width = this->m_pTexture->m_pImage->m_width;
	float height = this->m_pTexture->m_pImage->m_height;

	float left = 0;
	float top = 0;
	float right = width;
	float bottom = height;

	float half_width = this->m_pTexture->m_pImage->m_width * 0.5f;
	float half_height = this->m_pTexture->m_pImage->m_height * 0.5f;

	if (this->m_pTextureRect)
	{
		//画像空間の左の点
		left = this->m_pTextureRect->m_origin.x;
		//画像空間の上の点
		top = this->m_pTextureRect->m_origin.y;
		//画像空間の右の点
		right = this->m_pTextureRect->m_origin.x + this->m_pTextureRect->m_size.width;
		//画像空間の下の点
		bottom = this->m_pTextureRect->m_origin.y + this->m_pTextureRect->m_size.height;

		half_width = this->m_pTextureRect->m_size.width * 0.5f;
		half_height = this->m_pTextureRect->m_size.height * 0.5f;
	}


	//頂点座標データ
	GLfloat vertecies[] = {
		-half_width,-half_height,0.0f,	//左下
		half_width,half_height,0.0f,	//右上
		-half_width,half_height,0.0f,	//左上
		half_width,-half_height,0.0f,	//右下
	};

	//色データ
	GLfloat color[] = {
		//R,G,B,A
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,1.0f,
	};

	//テクスチャ座標
	GLfloat texcoords[] = {
		left/width,(height-bottom)/height,	//テクスチャ空間の左下の点を画像空間の左上の点に
		right/width,(height-top)/height,	//テクスチャ空間の右上の点を画像空間の右下の点に
		left/width,(height-top)/height,		//テクスチャ空間の左上の点を画像空間の左下の点に
		right/width,(height-bottom)/height,	//テクスチャ空間の右下の点を画像空間の右上の点に
	};

	//添字データ
	GLubyte indeices[] = {
		0,1,2,
		0,3,1
	};

	//登録してあるテクスチャを有効化
	glBindTexture(GL_TEXTURE_2D, this->m_pTexture->m_texName);

	//頂点座標データをメモリに登録するための許可を得る
	glEnableClientState(GL_VERTEX_ARRAY);
	//頂点座標データをメモリに登録する(頂点データの次元,頂点データの型,オフセット,頂点データ)
	glVertexPointer(3, GL_FLOAT, 0, vertecies);

	//色データをメモリに登録するための許可を得る
	glEnableClientState(GL_COLOR_ARRAY);
	//色データをメモリに登録する(色データの色数、色データの型,オフセット,色データ)
	glColorPointer(4, GL_FLOAT, 0, color);

	//テクスチャ座標データをメモリに登録するための許可を得る
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//テクスチャ座標データをメモリに登録する
	//(テクスチャ座標データの次元数、テクスチャ座標データの型、オフセット、テクスチャ座標データ)
	
	
	
	
	(2, GL_FLOAT, 0, texcoords);

	//ポリゴンを描画(形状,添字データの数,添字データの型,添字データ)
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, indeices);

	//描画するテクスチャを解除する
	glBindTexture(GL_TEXTURE_2D, 0);

}