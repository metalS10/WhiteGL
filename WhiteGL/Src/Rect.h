#pragma once
#include "Vec3.h"

//===========================================
//
//�T�C�Y
//
//===========================================
class CSize
{
public:
	float width = 0.0f;		//��
	float height = 0.0f;	//����

	CSize(){}
	CSize( const CSize& size )
		:width( size.width ),height( size.height ){}

	CSize( float w,float h )
		:width(w),height(h){}
};


//===========================================
//
//��`
//
//===========================================
class CRect
{
public:
	CVec3 m_origin;		//���_�ʒu
	CSize m_size;		//�T�C�Y

	CRect() {}

	CRect(const CRect& rect)
		:m_origin(rect.m_origin), m_size(rect.m_size) {}
	CRect(float x, float y, float w, float h)
		:m_origin({x, y, 0.0f}), m_size({ w,h }) {}

	/**
	*	@desc	�e�N�X�`���̐؂���
	*	@param	�؂��镔��
	*
	void setTextureRect(CRect rect);
	*/
};