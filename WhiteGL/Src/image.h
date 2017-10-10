#pragma once

#include<iostream>
#include "GL/glew.h"

#include "png/png.h"
#pragma comment(lib, "Src/png/zlib.lib")
#pragma comment(lib, "Src/png/libpng.lib")

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#define SAFE_DELETE(p_)if(p_){delete p_;p_ = NULL;}

//============================================================
//
//�O���摜�t�@�C���ǂݍ��݃N���X
//
//============================================================
class CImage
{
public:
	//�s�N�Z������ۑ����邽�߂̔z��
	GLubyte* m_bits;

	//�e�N�X�`���̕�
	unsigned long m_width = 0;
	//�e�N�X�`���̍���
	unsigned long m_height = 0;


	//�t�@�C����
	std::string m_name;
	//�s�N�Z����
	GLuint m_bpp;
	//�t�H�[�}�b�g�^�C�v
	GLenum m_format;
	//�����t�H�[�}�b�g�^�C�v
	GLuint m_internalFormat;


	//�R���X�g���N�^
	CImage(){}

	//�f�X�g���N�^
	~CImage()
	{
		SAFE_DELETE(this->m_bits);
	}

	/*
	*@desc	�t�@�C���̓ǂݍ���
	*@param	fileName�t�@�C����
	*@return true...����
	*/
	virtual bool load(const std::string& fileName) = 0;

	virtual bool loadchara(const char* fileName) = 0;


};


//======================================================
//BMP�t�@�C���ǂݍ��݃N���X
//=====================================================
class CBmpImage : public CImage
{
public:
	/**
	*@desc	BMP�t�@�C���̓ǂݍ���
	*@param	fileName BMP�t�@�C����
	*@return true...����
	*/
	bool load(const std::string& fileName)override;

	bool loadchara(const char* fileName)override { return false; }

};

//=====================================================
//TGA�t�@�C���ǂݍ��݃N���X
//=====================================================
class CTgaImage : public CImage
{
public:
	/**
	*@desc	TGA�t�@�C���̓ǂݍ���
	*@param	fileName TGA�t�@�C����
	*@return true...����
	*/
	bool load(const std::string& fileName)override;

	bool loadchara(const char* fileName)override { return false; }
};

//======================================================
//PNG�t�@�C���ǂݍ��݃N���X
//=====================================================
class CPngImage : public CImage
{
public:
	/**
	*@desc	BMP�t�@�C���̓ǂݍ���
	*@param	fileName BMP�t�@�C����
	*@return true...����
	*/
	bool load(const std::string& fileName)override;

	bool loadchara(const char* fileName)override;

	
};