#pragma once

//=====================================
//
//2D�x�N�g���������N���X
//
//=====================================
class CVec2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	CVec2(){}
	CVec2(float x,float y)
		:x(x),y(y){}
	CVec2(const CVec2& v)
		:x(v.x),y(v.y){}
};