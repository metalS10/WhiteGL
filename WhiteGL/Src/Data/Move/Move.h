#pragma once
//==================================================================
//追加のインクルードはここから
//==================================================================
#include "Vec2.h"
#include "Constants.h"

//==================================================================
//移動データ
//==================================================================
class CMove
{
public:
	//位置
	CVec2 m_pos;
	//速度
	CVec2 m_vel;
	//加速度
	CVec2 m_accele;
	//速さ
	float m_speed;

	/**
	*	@desc移動
	*/
	virtual void moveBy()
	{
		//速度による移動
		m_pos += m_vel;
	}

};