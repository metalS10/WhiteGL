#pragma once
#include<iostream>
#include "image.h"

#include <map>

//====================================================
//
//1枚のテクスチャを生成し管理するクラス
//
//====================================================
class CTexture2D
{
public:
	//OpenGLから割り当てられるテクスチャの名前
	GLuint m_texName;

	//画像データ
	CImage* m_pImage;

	//コンストラクタ
	CTexture2D(){}

	//デストラクタ
	~CTexture2D()
	{
		//テクスチャの破棄
		this->remove();
	}

	/**
	* @desc	テクスチャの生成
	* @param	fileName ファイル名
	* @return	true...成功
	*/
	bool create(const std::string & fileName);

	/**
	* @desc	テクスチャの破棄
	*/
	void remove();
};

//====================================================
//
//複数のテクスチャを管理するクラス
//
//====================================================
class CTextureManager
{
private:
	//コンストラクタ
	CTextureManager();

	//テクスチャ群<ファイル名、テクスチャ>
	std::map<std::string, CTexture2D*>m_textures;

public:
	//get instance
	static CTextureManager* getInstance();

	//デストラクタ
	~CTextureManager();

	/**
	*@desc	テクスチャの取得
	*@param	fileName ファイル名
	*@return テクスチャ
	*@tips	存在していなければ生成して返す
	*/
	CTexture2D* get(const std::string & fileName);

	/**
	*@desc	テクスチャの削除
	*@param	fileNameファイル名
	*/
	void remove(const std::string&fileName);

	/**
	*@desc	全てのテクスチャの削除
	*/
	void clear();

};