#pragma once
#include "Data/Move/Move.h"

//=========================================================
//�������Z�N���X
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
//�d�͂Ɋ�Â������x�v�Z�Ɋւ���R�[�h�̒ǉ��͂�������
//=========================================================
class CPhysicalGravity :public CPhysical
{
public:
	float GRAVITY = -1.5f;
	//�f�t�H���g�R���X�g���N�^
	CPhysicalGravity()
	{
		
	}

	//�R���X�g���N�^
	CPhysicalGravity(float gravity)
	{
		GRAVITY = gravity;
	}

	
public:
	void update(CMove* pMove)override
	{
		//y���̑��x���v�Z(�d�͌v�Z)
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
//���C�W���Ɋ�Â������x�v�Z�Ɋւ���R�[�h�̒ǉ��͂�������
//==========================================================
class CPhysicalFriction : public CPhysical
{
public:
	//���C�W��
	float FRICTION = 0.5f;

protected:

	//�ő呬�x
	float m_maxSpeed = 0.0f;

public:
	CPhysicalFriction(float maxSpeed):m_maxSpeed(maxSpeed){}

	/**
	*	@desc�X�V����(���C�̌v�Z)
	*/
	void update(CMove* pMove)override
	{
		//���C
		float friction = 0.0f;

		//�E�Ɉړ����Ă�����
		if (pMove->m_vel.x > CPhysicalFriction::FRICTION)
		{
			friction = -CPhysicalFriction::FRICTION;
		}
		else if (pMove->m_vel.x > 0)
		{
			//���x�����C�W���ȉ��ɂȂ�����
			//���C-���x=0
			//�ɂȂ�悤�ɂ���
			friction = -pMove->m_vel.x;
		}
		//���Ɉړ�������
		if (pMove->m_vel.x < -CPhysicalFriction::FRICTION)
		{
			friction = CPhysicalFriction::FRICTION;
		}
		else if (pMove->m_vel.x < 0)
		{
			//���C-���x=0
			friction = -pMove->m_vel.x;
		}
		//x���̑��x���v�Z(���C�v�Z)
		pMove->m_vel.x += pMove->m_accele.x + friction;

		//x���̍ō����x���v�Z
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