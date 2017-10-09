#pragma once

#include <iostream>
#include <math.h>
#include <memory>

//==============================================
//
//3D�x�N�g���������N���X
//
//==============================================
class CVec3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	//�R���X�g���N�^
	CVec3(){}
	CVec3(float x_, float y_, float z_) { this->x = x_;this->y = y_;this->z = z_; }
	CVec3(const CVec3&v_) { this->x = v_.x;this->y = v_.y;this->z = v_.z; }
	CVec3(const float a_[]) { this->x = a_[0];this->y = a_[1];this->z = a_[2]; }

	//�Z�b�g
	void set(float x_, float y_, float z_) { this->x = x_;this->y = y_;this->z = z_; }
	void set(CVec3 v_) { this->x = v_.x;this->y = v_.y;this->z = v_.z; }
	void set(float a_[]) { this->x = a_[0];this->y = a_[1];this->z = a_[2]; }

	//�[��
	void zero() { this->x = 0.0f;this->y = 0.0f;this->z = 0.0f; }

	//�z��ɕϊ����Ď擾
	std::shared_ptr<float> toArray()
	{
		return std::shared_ptr<float>(new float[3]{ this->x,this->y,this->z });
	}

	//�����𒲂ׂ�
	float length()
	{
		return (float)sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}

	//�����𒲂ׂ�(�������͋��߂Ȃ�)
	float lengthSq()
	{
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	//���Z
	CVec3 add(CVec3 v_)
	{
		return{ x + v_.x,y + v_.y,z + v_.z };
	}

	//���Z
	CVec3 sub(CVec3 v_)
	{
		return{ x - v_.x,y - v_.y,z - v_.z };
	}

	//�ώZ
	CVec3 multiply(float val_)
	{
		return{ x*val_,y*val_,z*val_ };
	}

	//���Z
	CVec3 div(float val_)
	{
		return{ x / val_,y / val_,z / val_ };
	}

	//�������Z
	bool equals(CVec3 v_)
	{
		return (x == v_.x) && (y == v_.y) && (z == v_.z);
	}

	//�񓙉����Z
	bool notEquals(CVec3 v_)
	{
		return !equals(v_);
	}

	//�����𒲂ׂ�
	float distance(CVec3 v_)
	{
		return this->sub(v_).length();
	}

	//�����𒲂ׂ�(�������͋��߂Ȃ�)
	float distanceSq(CVec3 v_)
	{
		return this->sub(v_).lengthSq();
	}

	//���K��
	CVec3 normalize()
	{
		float sq = (float)sqrt(x * x + y * y + z * z);
		if (sq == 0)
		{
			return{ 1.0f,0.0f,0.0f };
		}
		return{ x / sq,y / sq,z / sq };
	}

	//�e�v�f�����ꂼ��ώZ(MultiplyEach)
	CVec3 multiplyEach(CVec3 v_)
	{
		return{ x * v_.x,y * v_.y,z * v_.z };
	}

	//����
	float dot(CVec3 v_)
	{
		return (z * v_.x + y * v_.y + z * v_.z);
	}

	//�O��
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