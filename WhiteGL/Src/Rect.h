#pragma once
#include "Vec3.h"

//===========================================
//
//サイズ
//
//===========================================
class CSize
{
public:
	float width = 0.0f;		//幅
	float height = 0.0f;	//高さ

	CSize(){}
	CSize( const CSize& size )
		:width( size.width ),height( size.height ){}

	CSize( float w,float h )
		:width(w),height(h){}
};


//===========================================
//
//矩形
//
//===========================================
class CRect
{
public:
	CVec3 m_origin;		//原点位置
	CSize m_size;		//サイズ

	CRect() {}

	CRect(const CRect& rect)
		:m_origin(rect.m_origin), m_size(rect.m_size) {}
	CRect(float x, float y, float w, float h)
		:m_origin({x, y, 0.0f}), m_size({ w,h }) {}

	/**
	*	@desc	テクスチャの切り取り
	*	@param	切り取る部分
	*
	void setTextureRect(CRect rect);
	*/
};