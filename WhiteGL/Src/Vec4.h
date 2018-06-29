#pragma once

#include <iostream>
#include <math.h>
#include <memory>

//==============================================
//
//3Dベクトルを扱うクラス
//
//==============================================
class CVec4
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	//コンストラクタ
	CVec4() {}
	CVec4(float x_, float y_, float z_, float w_) { this->x = x_;this->y = y_;this->z = z_;this->w = w_; }
	CVec4(const CVec4&v_) { this->x = v_.x;this->y = v_.y;this->z = v_.z;this->w = v_.w; }
	CVec4(const float a_[]) { this->x = a_[0];this->y = a_[1];this->z = a_[2];this->w = a_[3]; }

	//セット
	void set(float x_, float y_, float z_, float w_) { this->x = x_;this->y = y_;this->z = z_;this->w = w_; }
	void set(CVec4 v_) { this->x = v_.x;this->y = v_.y;this->z = v_.z;this->w = v_.w; }
	void set(float a_[]) { this->x = a_[0];this->y = a_[1];this->z = a_[2];this->w = a_[3]; }

	//ゼロ
	void zero() { this->x = 0.0f;this->y = 0.0f;this->z = 0.0f;this->w = 0.0f; }

	bool isEnpty()
	{
		if (this->x == 0.0f && this->y == 0.0f && this->z == 0.0f && this->w == 0.0f)
			return false;
		else
			return true;
	}

	inline CVec4& CVec4::operator-=(const CVec4& v)
	{
		minus(v);
		return *this;
	}
	inline CVec4& CVec4::operator-=(const float& v)
	{
		minus(v);
		return *this;
	}
	inline CVec4 CVec4::operator*(const float& v) const
	{
		CVec4 result(*this);
		result.multi(v);
		return result;
	}
	inline CVec4& CVec4::operator*=(const float& v)
	{
		multi(v);
		return *this;
	}

	inline void CVec4::add(const CVec4& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}
	inline void CVec4::minus(const CVec4& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.x;
		y -= v.z;
		w -= v.w;
	}
	inline void CVec4::minus(const float& v)
	{
		x -= v;
		y -= v;
		z -= v;
		y -= v;
		w -= v;
	}

	inline void CVec4::multi(const float& v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
	}

};