#pragma once

#include  <iostream>
#include "Texture\Texture.h"
#include "Node.h"
#include "Rect.h"

//========================================
//
//1���̉摜���Ǘ����`�����������N���X
//
//========================================
class CSprite : public CNode
{
public:
	//�e�N�X�`��
	CTexture2D* m_pTexture = NULL;

	/**
	*@desc ����������
	*@param	fileName	�t�@�C����
	*@return true...����
	*/
	bool init(const std::string&fileName);

	/**
	*@desc	�`��
	*/
	void draw()override;

	CRect* m_pTextureRect;
};