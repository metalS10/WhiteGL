#pragma once

#include <iostream>
#include <math.h>
#include <memory>

//==============================================
//
//3Dベクトルを扱うクラス
//
//==============================================
class CVec3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//コンストラクタ
	CVec3(){}
	CVec3(float x_, float y_, float z_) { this->x = x_;this->y = y_;this->z = z_; }
	CVec3(const CVec3&v_) { this->x = v_.x;this->y = v_.y;this->z = v_.z; }
	CVec3(const float a_[]) { this->x = a_[0];this->y = a_[1];this->z = a_[2]; }

	//セット
	void set(float x_, float y_, float z_) { this->x = x_;this->y = y_;this->z = z_; }
	void set(CVec3 v_) { this->x = v_.x;this->y = v_.y;this->z = v_.z; }
	void set(float a_[]) { this->x = a_[0];this->y = a_[1];this->z = a_[2]; }

	//ゼロ
	void zero() { this->x = 0.0f;this->y = 0.0f;this->z = 0.0f; }

	//配列に変換して取得
	std::shared_ptr<float> toArray()
	{
		return std::shared_ptr<float>(new float[3]{ this->x,this->y,this->z });
	}

	//長さを調べる
	float length()
	{
		return (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	//長さを調べる(平方根は求めない)
	float lengthSq()
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	//加算
	CVec3 add(CVec3 v_)
	{
		return{ x + v_.x,y + v_.y,z + v_.z };
	}

	//減算
	CVec3 sub(CVec3 v_)
	{
		return{ x - v_.x,y - v_.y,z - v_.z };
	}

	//積算
	CVec3 multiply(float val_)
	{
		return{ x*val_,y*val_,z*val_ };
	}

	//除算
	CVec3 div(float val_)
	{
		return{ x / val_,y / val_,z / val_ };
	}

	//等価演算
	bool equals(CVec3 v_)
	{
		return (x == v_.x) && (y == v_.y) && (z == v_.z);
	}

	//非等価演算
	bool notEquals(CVec3 v_)
	{
		return !equals(v_);
	}

	//距離を調べる
	float distance(CVec3 v_)
	{
		return this->sub(v_).length();
	}

	//距離を調べる(平方根は求めない)
	float distanceSq(CVec3 v_)
	{
		return this->sub(v_).lengthSq();
	}

	//正規化
	CVec3 normalize()
	{
		float sq = (float)sqrt(x * x + y * y + z * z);
		if (sq == 0)
		{
			return{ 1.0f,0.0f,0.0f };
		}
		return{ x / sq,y / sq,z / sq };
	}

	//各要素をそれぞれ積算(MultiplyEach)
	CVec3 multiplyEach(CVec3 v_)
	{
		return{ x * v_.x,y * v_.y,z * v_.z };
	}

	//内積
	float dot(CVec3 v_)
	{
		return (z * v_.x + y * v_.y + z * v_.z);
	}

	//外積
	CVec3 cross(CVec3 v_)
	{
		return
		{
			y * v_.z - z * v_.y,
			z * v_.x - x * v_.z,
			x * v_.y - y * v_.x
		};
	}
};