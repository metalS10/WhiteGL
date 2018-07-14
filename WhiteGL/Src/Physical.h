#pragma once
#include "Data/Move/Move.h"

//=========================================================
//物理演算クラス
//=========================================================
class CPhysical
{
public:
	virtual ~CPhysical() {}
	virtual void update(CMove* pMove) = 0;
	virtual void SetMaxSpeed(float maxspeed, float friction) = 0;
	virtual void setGravity(float gravity) = 0;
};

//=========================================================
//重力に基づいた速度計算に関するコードの追加はここから
//=========================================================
class CPhysicalGravity :public CPhysical
{
public:
	float GRAVITY = -1.5f;
	//デフォルトコンストラクタ
	CPhysicalGravity()
	{
		
	}

	//コンストラクタ
	CPhysicalGravity(float gravity)
	{
		GRAVITY = gravity;
	}

	
public:
	void update(CMove* pMove)override
	{
		//y軸の速度を計算(重力計算)
		pMove->m_vel.y += pMove->m_accele.y + CPhysicalGravity::GRAVITY;
	}

	void SetMaxSpeed(float maxspeed, float friction)override
	{

	}
	void setGravity(float gravity) override
	{
		GRAVITY = gravity;
	}
};

//==========================================================
//摩擦係数に基づいた速度計算に関するコードの追加はここから
//==========================================================
class CPhysicalFriction : public CPhysical
{
public:
	//摩擦係数
	float FRICTION = 0.5f;

protected:

	//最大速度
	float m_maxSpeed = 0.0f;

public:
	CPhysicalFriction(float maxSpeed):m_maxSpeed(maxSpeed){}

	/**
	*	@desc更新処理(摩擦の計算)
	*/
	void update(CMove* pMove)override
	{
		//摩擦
		float friction = 0.0f;

		//右に移動していたら
		if (pMove->m_vel.x > CPhysicalFriction::FRICTION)
		{
			friction = -CPhysicalFriction::FRICTION;
		}
		else if (pMove->m_vel.x > 0)
		{
			//速度が摩擦係数以下になったら
			//摩擦-速度=0
			//になるようにする
			friction = -pMove->m_vel.x;
		}
		//左に移動したら
		if (pMove->m_vel.x < -CPhysicalFriction::FRICTION)
		{
			friction = CPhysicalFriction::FRICTION;
		}
		else if (pMove->m_vel.x < 0)
		{
			//摩擦-速度=0
			friction = -pMove->m_vel.x;
		}
		//x軸の速度を計算(摩擦計算)
		pMove->m_vel.x += pMove->m_accele.x + friction;

		//x軸の最高速度を計算
		if (pMove->m_vel.x < -this->m_maxSpeed)
		{
			pMove->m_vel.x = -this->m_maxSpeed;
		}
		else if (pMove->m_vel.x > this->m_maxSpeed)
		{
			pMove->m_vel.x = this->m_maxSpeed;
		}
	}

	void SetMaxSpeed(float maxspeed,float friction) override
	{
		this->m_maxSpeed = maxspeed;
		this->FRICTION = friction;
	}

	void setGravity(float gravity) override
	{

	}
};