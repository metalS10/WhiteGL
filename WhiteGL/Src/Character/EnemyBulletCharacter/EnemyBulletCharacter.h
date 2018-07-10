#pragma once
#include "../Character.h"
#include "../../Data/CollisionArea/CollisionArea.h"



//�e�^�C�v
enum class BULLET_TYPE : int
{
	NORMAL		=	0,
	CUSTOM		=	1,
	FIREBALL	=	2,
};

class CEnemyBulletCharacter : public CCharacter
{
public:
	//�R���X�g���N�^
	CEnemyBulletCharacter();

	//�f�X�g���N�^
	~CEnemyBulletCharacter();

	//����������
	bool init();

	CCollisionTerritory* m_pCollisionTerritory;

	/*
	* @desc ����������
	* @param �����ʒuX
	* @param �����ʒuY
	* @tips create() �����o�֐��̒���init()�����o�֐����Ăяo���Ă��邪
	*		����A����create()�����o�֐����I�[�o�[���[�h����
	*		�������󂯎���Ă���̂�init()�����o�֐���
	*		�I�[�o�[���[�h����K�v������B
	*/
	bool init(float posX, float posY);

	/**
	* @desc CREATE_FUNC�}�N���̒��g�����̂܂܎����Ă�������
	* @tips �O��͓G�o���f�[�^�Ƃ����G��p�̃N���X�����݂���Ă����̂�
	*		���̃N���X�ɒ��������Ă����͐����Ȃ�������
	*		����̓}�b�v�̏��ɂ��o���ʒu�̌���Ƃ������ڂ��K�v�ɂȂ�
	*		�}�b�v���V���O���g���������̂Œ��������Ă����Ȃ��悤�Ɏv���邪
	*		���̃^�C�~���O�ł̂��̏ꏊ�̃}�b�v�̃^�C���̈ʒu�̏�񂪕K�v�ɂȂ�
	*		�ŏI�I�ɕK�v�ɂȂ�͈̂ʒu������
	*		�Ȃ̂Ő����Ɠ����Ɉʒu���擾������
	*		�����������Acocos2dx�̋@�\�ł��鎩����delete�̋@�\���g������
	*		�Ȃ̂�create�ÓI�����o�֐����J�X�^�}�C�Y����B
	*/
	//CREATE_FUNC(CEnemyBulletCharacter);
	static CEnemyBulletCharacter* create()
	{
		CEnemyBulletCharacter* pRet = new(std::nothrow)CEnemyBulletCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	/*
	* @desc CREATE_FUNC�}�N�����I�[�o�[���C�h
	* @param �����ʒuX
	* @param �����ʒuY
	* @tips �����ʒu��K�v�Ƃ���̂͐����̒i�K�ł͂Ȃ�
	*		init�̒i�K�ł���
	*/
	static CEnemyBulletCharacter* create(float posX, float posY)
	{
		CEnemyBulletCharacter* pRet = new(std::nothrow)CEnemyBulletCharacter();

		//�����������ɏ����ʒu��n��
		if (pRet && pRet->init(posX, posY))
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	//===============================================
	//
	//�����o�Ɋւ���R�[�h�̒ǉ��͂�������
	//
	//===============================================

	//�ړ�����
	void moveFunc() override;

	//�A�j���[�V��������
	void animationFunc() override;

	/*
	//��ʒ[���菈��
	void endOfScreen() override;
	*/
	//��ԃ`�F�b�N
	void checkState() override;

	//���f����
	void applyFunc() override;


	void collision() override;


	/**
	* @desc �L�����N�^�[1�̂Ƃ̏Փ˔��菈��
	* @param �L�����N�^�[�̃A�h���X
	* @return true...�Փ˂���
	*/
	bool collision(CCharacter* pChara)override;

	/**
	* @desc �}�b�v�Ƃ̏Փ˔���
	* @return true...�Փ˂���
	*/
	//bool collisionMap() override;

	/**
	*@desc	�Փ˔����̏���
	*@param	�Փ˂��Ă����L�����N�^�[
	*/
	virtual void hits(CCharacter* pChara) override;





	void collisionBottomCallback(int event)override
	{
		this->m_activeFlag = false;
	}
	void collisionTopCallback(int event)override 
	{
		this->m_activeFlag = false;
	}
	void collisionRightCallback(int event)override 
	{
		this->m_activeFlag = false;
	}
	void collisionLeftCallback(int event)override 
	{
		this->m_activeFlag = false;
	}
};

class CFireBallEnemyBulletCharacter : public CEnemyBulletCharacter
{
public:
	//�R���X�g���N�^
	CFireBallEnemyBulletCharacter();
	//�f�X�g���N�^
	~CFireBallEnemyBulletCharacter();

	bool init();

	bool init(float posX, float posY);

	/**
	* @desc CREATE_FUNC�}�N���̒��g�����̂܂܎����Ă�������
	* @tips �O��͓G�o���f�[�^�Ƃ����G��p�̃N���X�����݂���Ă����̂�
	*		���̃N���X�ɒ��������Ă����͐����Ȃ�������
	*		����̓}�b�v�̏��ɂ��o���ʒu�̌���Ƃ������ڂ��K�v�ɂȂ�
	*		�}�b�v���V���O���g���������̂Œ��������Ă����Ȃ��悤�Ɏv���邪
	*		���̃^�C�~���O�ł̂��̏ꏊ�̃}�b�v�̃^�C���̈ʒu�̏�񂪕K�v�ɂȂ�
	*		�ŏI�I�ɕK�v�ɂȂ�͈̂ʒu������
	*		�Ȃ̂Ő����Ɠ����Ɉʒu���擾������
	*		�����������Acocos2dx�̋@�\�ł��鎩����delete�̋@�\���g������
	*		�Ȃ̂�create�ÓI�����o�֐����J�X�^�}�C�Y����B
	*/
	//CREATE_FUNC(CEnemyBulletCharacter);
	static CFireBallEnemyBulletCharacter* create()
	{
		CFireBallEnemyBulletCharacter* pRet = new(std::nothrow)CFireBallEnemyBulletCharacter();
		if (pRet && pRet->init())
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	/*
	* @desc CREATE_FUNC�}�N�����I�[�o�[���C�h
	* @param �����ʒuX
	* @param �����ʒuY
	* @tips �����ʒu��K�v�Ƃ���̂͐����̒i�K�ł͂Ȃ�
	*		init�̒i�K�ł���
	*/
	static CFireBallEnemyBulletCharacter* create(float posX, float posY)
	{
		CFireBallEnemyBulletCharacter* pRet = new(std::nothrow)CFireBallEnemyBulletCharacter();

		//�����������ɏ����ʒu��n��
		if (pRet && pRet->init(posX, posY))
		{
			//pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	void collisionBottomCallback(int event)override
	{
		(*this->m_pActions)[0]->restart(this);
	}

};