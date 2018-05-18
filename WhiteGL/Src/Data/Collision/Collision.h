#pragma once
//=====================================================
//�ǉ��̃C���N���[�h�͂�������
//=====================================================
#include "../../Constants.h"
#include "../../Vec2.h"

//=====================================================
//���̃f�[�^�͂������珑��
//=====================================================
class CBody
{
public:
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;

	CBody(){}
	CBody(float left,float top,float right,float bottom)
		:m_left(left),m_top(top),m_right(right),m_bottom(bottom){}

	void set(float left, float top, float right, float bottom)
	{
		this->m_left = left;
		this->m_top = top;
		this->m_right = right;
		this->m_bottom = bottom;
	}
};

//=====================================================
//�O���錾�Ɋւ���R�[�h�͂������珑��
//=====================================================
//�_
class CCollisionPoint;

//��`
class CCollisionRect;

//=====================================================
//�Փ˔���p�̃R�[�h�͂������珑��
//=====================================================
class CCollision
{
public:
	virtual ~CCollision() {}

	//======================================================
	//�Փ˔���̃����o�֐��̐錾�͂�������ǉ����Ă���
	//======================================================
	//�_���Փ˂��Ă����Ƃ��̏Փ˔���
	virtual bool  collision(CCollisionPoint*) = 0;
	//��`���Փ˂��Ă����Ƃ��̏Փ˔���
	virtual bool  collision(CCollisionRect*) = 0;
};

//====================================================
//�_
//====================================================
class CCollisionPoint :public CCollision
{
public:
	//�_�̈ʒu
	CVec2 m_pos;

	//�ʒu�����̂܂܏Փ˔���p�̓_�ɂȂ�
	CCollisionPoint(CVec2 pos):m_pos(pos){}

	/**
	*	@desc �_�Ɠ_�̏Փ˔���
	*	@param �_
	*/
	bool collision(CCollisionPoint* pPt)override;

	/**
	*	@desc �_�Ƌ�`�̏Փ˔���
	*	@param ��`
	*/
	bool collision(CCollisionRect* pRect)override;
};

//====================================================
//�Փ˔���p��`
//====================================================
class CCollisionRect :public CCollision
{
public:
	CBody m_body;

	/**
	*	@desc���̂����̂܂܏Փ˔���p�̋�`�ɂȂ�
	*/
	CCollisionRect(CBody body):m_body(body){}

	/**
	*	@desc ���݈ʒu�Ǝ��̂���Փ˔���p�̋�`��ݒ�
	*	@param ����
	*	@param �ʒu
	*/
	CCollisionRect(CBody body, CVec2 pos);

	/**
	*	@desc ��`�Ɠ_�̏Փ˔���
	*	@param �_
	*	@tips CPoint��CRect�̏Փ˔����CPoint�N���X�Ɏ������Ă���̂�
	*		�����Ƃ��Ď󂯎����pPt����collision���Ăяo��
	*/
	bool collision(CCollisionPoint*)override;

	/**
	*	@desc ��`�Ƌ�`�̏Փ˔���
	*	@param ��`
	*/
	bool collision(CCollisionRect*)override;
};