#pragma once

#include <iostream>
#include "Vec3.h"

//==============================================
//
//�s��ϊ����Ǘ�����N���X
//
//==============================================
class CNode
{
private:
	//�ʒu
	CVec3 m_position = { 0.0f,0.0f,0.0f };
	//��]
	CVec3 m_rotate = { 0.0f,0.0f,0.0f };
	//�g�嗦
	CVec3 m_scale = { 1.0f,1.0f,1.0f };

public:
	//�R���X�g���N�^
	CNode(){}
	//�f�X�g���N�^
	virtual ~CNode(){}
	
	/**
	*@desc �ʒu�̐ݒ�
	*/
	void setPosition(float x, float y, float z)
	{
		this->m_position.set(x, y, z);
	}

	/**
	*@desc	��]�̐ݒ�
	*/
	void setRotate(float x, float y, float z)
	{
		this->m_rotate.set(x, y, z);
	}

	/**
	*@desc	�g�嗦�̐ݒ�
	*/
	void setScale(float x, float y, float z)
	{
		this->m_scale.set(x, y, z);
	}

	/**
	*@desc �s��ϊ�
	*/
	void transform();

	/**
	*@desc	�`��
	*/
	virtual void draw() = 0;

	/**
	*@desc	�e�N�X�`���̐؂���
	*@param	�؂��镔��
	*/
};