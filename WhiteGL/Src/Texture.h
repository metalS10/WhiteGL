#pragma once
#include<iostream>
#include "image.h"

#include <map>

//====================================================
//
//1���̃e�N�X�`���𐶐����Ǘ�����N���X
//
//====================================================
class CTexture2D
{
public:
	//OpenGL���犄�蓖�Ă���e�N�X�`���̖��O
	GLuint m_texName;

	//�摜�f�[�^
	CImage* m_pImage;

	//�R���X�g���N�^
	CTexture2D(){}

	//�f�X�g���N�^
	~CTexture2D()
	{
		//�e�N�X�`���̔j��
		this->remove();
	}

	/**
	* @desc	�e�N�X�`���̐���
	* @param	fileName �t�@�C����
	* @return	true...����
	*/
	bool create(const std::string & fileName);

	/**
	* @desc	�e�N�X�`���̔j��
	*/
	void remove();
};

//====================================================
//
//�����̃e�N�X�`�����Ǘ�����N���X
//
//====================================================
class CTextureManager
{
private:
	//�R���X�g���N�^
	CTextureManager();

	//�e�N�X�`���Q<�t�@�C�����A�e�N�X�`��>
	std::map<std::string, CTexture2D*>m_textures;

public:
	//get instance
	static CTextureManager* getInstance();

	//�f�X�g���N�^
	~CTextureManager();

	/**
	*@desc	�e�N�X�`���̎擾
	*@param	fileName �t�@�C����
	*@return �e�N�X�`��
	*@tips	���݂��Ă��Ȃ���ΐ������ĕԂ�
	*/
	CTexture2D* get(const std::string & fileName);

	/**
	*@desc	�e�N�X�`���̍폜
	*@param	fileName�t�@�C����
	*/
	void remove(const std::string&fileName);

	/**
	*@desc	�S�Ẵe�N�X�`���̍폜
	*/
	void clear();

};