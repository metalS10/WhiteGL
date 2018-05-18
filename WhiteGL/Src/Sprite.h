#pragma once

#include  <iostream>
#include "Texture\Texture.h"
#include "Node.h"
#include "Rect.h"

//========================================
//
//1枚の画像を管理し描画を処理するクラス
//
//========================================
class CSprite : public CNode
{
public:
	//テクスチャ
	CTexture2D* m_pTexture = NULL;

	/**
	*@desc 初期化処理
	*@param	fileName	ファイル名
	*@return true...成功
	*/
	bool init(const std::string&fileName);

	/**
	*@desc	描画
	*/
	void draw()override;

	CRect* m_pTextureRect;
};