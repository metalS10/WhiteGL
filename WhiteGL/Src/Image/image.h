#pragma once

#include<iostream>
#include "GL/glew.h"

#include "../png/png.h"
#include "../Constants.h"

#pragma comment(lib, "Src/png/zlib.lib")
#pragma comment(lib, "Src/png/libpng.lib")

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


//============================================================
//
//外部画像ファイル読み込みクラス
//
//============================================================
class CImage
{
public:
	//ピクセル情報を保存するための配列
	GLubyte* m_bits;

	//テクスチャの幅
	unsigned long m_width = 0;
	//テクスチャの高さ
	unsigned long m_height = 0;


	//ファイル名
	std::string m_name;
	//ピクセル数
	GLuint m_bpp;
	//フォーマットタイプ
	GLenum m_format;
	//内部フォーマットタイプ
	GLuint m_internalFormat;


	//コンストラクタ
	CImage(){}

	//デストラクタ
	~CImage()
	{
		SAFE_DELETE(this->m_bits);
	}

	/*
	*@desc	ファイルの読み込み
	*@param	fileNameファイル名
	*@return true...成功
	*/
	virtual bool load(const std::string& fileName) = 0;



};


//======================================================
//BMPファイル読み込みクラス
//=====================================================
class CBmpImage : public CImage
{
public:
	/**
	*@desc	BMPファイルの読み込み
	*@param	fileName BMPファイル名
	*@return true...成功
	*/
	bool load(const std::string& fileName)override;

};

//=====================================================
//TGAファイル読み込みクラス
//=====================================================
class CTgaImage : public CImage
{
public:
	/**
	*@desc	TGAファイルの読み込み
	*@param	fileName TGAファイル名
	*@return true...成功
	*/
	bool load(const std::string& fileName)override;

};

//======================================================
//PNGファイル読み込みクラス
//=====================================================
class CPngImage : public CImage
{
public:
	/**
	*@desc	BMPファイルの読み込み
	*@param	fileName BMPファイル名
	*@return true...成功
	*/
	bool load(const std::string& fileName)override;

	
};