#pragma once
//=====================================================
//�ǉ��̃C���N���[�h�͂�������
//=====================================================
#include "../Character.h"

//=====================================================
//
//�M�~�b�N�L�����N�^�[�̊��N���X�ƂȂ�N���X
//
//=====================================================
class CGimmickCharacter : public CCharacter
{
public:
	//�R���X�g���N�^
	CGimmickCharacter();

	//�f�X�g���N�^
	~CGimmickCharacter();

	//����������
	bool init() override;


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
	* @tips �O��̓M�~�b�N�o���f�[�^�Ƃ����M�~�b�N��p�̃N���X�����݂���Ă����̂�
	*		���̃N���X�ɒ��������Ă����͐����Ȃ�������
	*		����̓}�b�v�̏��ɂ��o���ʒu�̌���Ƃ������ڂ��K�v�ɂȂ�
	*		�}�b�v���V���O���g���������̂Œ��������Ă����Ȃ��悤�Ɏv���邪
	*		���̃^�C�~���O�ł̂��̏ꏊ�̃}�b�v�̃^�C���̈ʒu�̏�񂪕K�v�ɂȂ�
	*		�ŏI�I�ɕK�v�ɂȂ�͈̂ʒu������
	*		�Ȃ̂Ő����Ɠ����Ɉʒu���擾������
	*		�����������Acocos2dx�̋@�\�ł��鎩����delete�̋@�\���g������
	*		�Ȃ̂�create�ÓI�����o�֐����J�X�^�}�C�Y����B
	*/
	//CREATE_FUNC(CGimmickCharacter);
	static CGimmickCharacter* create()
	{
		CGimmickCharacter* pRet = new(std::nothrow)CGimmickCharacter();
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
	static CGimmickCharacter* create(float posX, float posY)
	{
		CGimmickCharacter* pRet = new(std::nothrow)CGimmickCharacter();

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
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}
	void collisionTopCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}
	void collisionRightCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}
	void collisionLeftCallback(int event)override
	{
		CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		pPlayerCharacter->m_isDamage = true;
		pPlayerCharacter->m_hitPoint = 0;
		pPlayerCharacter->m_gameOver = true;
	}

};



//==================================================================================
//�M�~�b�N���p���������u���b�N
//==================================================================================
class CRollGimmickCharacter : public CGimmickCharacter
{
public:
	//�R���X�g���N�^
	CRollGimmickCharacter();

	//�f�X�g���N�^
	~CRollGimmickCharacter()override;

	//����������
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CRollGimmickCharacter* create()
	{
		CRollGimmickCharacter* pRet = new(std::nothrow)CRollGimmickCharacter();
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
	
	void collisionBottomCallback(int event)override
	{
		(*this->m_pActions)[0]->start();
	}
	void collisionTopCallback(int event)override
	{
		
	}
	void collisionRightCallback(int event)override
	{
		
	}
	void collisionLeftCallback(int event)override
	{
		
	}


};


//==================================================================================
//�M�~�b�N���p������������u���b�N
//==================================================================================
class CTikuwaGimmickCharacter : public CGimmickCharacter
{
public:
	//�R���X�g���N�^
	CTikuwaGimmickCharacter();

	//�f�X�g���N�^
	~CTikuwaGimmickCharacter()override;

	//����������
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CTikuwaGimmickCharacter* create()
	{
		CTikuwaGimmickCharacter* pRet = new(std::nothrow)CTikuwaGimmickCharacter();
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

	void collisionBottomCallback(int event)override
	{

	}
	void collisionTopCallback(int event)override
	{
		(*this->m_pActions)[0]->start();
	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};

//==================================================================================
//�M�~�b�N���p�����������u���b�N
//==================================================================================
class CNoteGimmickCharacter : public CGimmickCharacter
{
public:
	//�R���X�g���N�^
	CNoteGimmickCharacter();

	//�f�X�g���N�^
	~CNoteGimmickCharacter()override;

	//����������
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CNoteGimmickCharacter* create()
	{
		CNoteGimmickCharacter* pRet = new(std::nothrow)CNoteGimmickCharacter();
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

	void collisionBottomCallback(int event)override
	{

	}
	void collisionTopCallback(int event)override
	{
		CCharacter* pPlayer = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
		(*pPlayer->m_pActions)[0]->restart(pPlayer);
	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};

//==================================================================================
//�M�~�b�N���p�����������u���b�N
//==================================================================================
class CHatenaGimmickCharacter : public CGimmickCharacter
{
public:
	//�R���X�g���N�^
	CHatenaGimmickCharacter();

	//�f�X�g���N�^
	~CHatenaGimmickCharacter()override;

	//����������
	bool init() override;

	//CREATE_FUNC(CGimmickCharacter);
	static CHatenaGimmickCharacter* create()
	{
		CHatenaGimmickCharacter* pRet = new(std::nothrow)CHatenaGimmickCharacter();
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

	void collisionBottomCallback(int event)override
	{
		(*this->m_pActions)[0]->start();
	}
	void collisionTopCallback(int event)override
	{

	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};

//==================================================================================
//�M�~�b�N���p���������[�v
//==================================================================================
class CWorpGimmickCharacter : public CGimmickCharacter
{
public:
	//�R���X�g���N�^
	CWorpGimmickCharacter();

	//�f�X�g���N�^
	~CWorpGimmickCharacter()override;

	//����������
	bool init() override;

	//���d���[�v�h�~
	int i = 0;

	//CREATE_FUNC(CGimmickCharacter);
	static CWorpGimmickCharacter* create()
	{
		CWorpGimmickCharacter* pRet = new(std::nothrow)CWorpGimmickCharacter();
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

	void collisionBottomCallback(int event)override
	{
		if (i == 0)
		{
			CCharacter* pPlayerCharacter = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
			pPlayerCharacter->m_nextStage = true;
			i++;
		}
	}
	void collisionTopCallback(int event)override
	{

	}
	void collisionRightCallback(int event)override
	{

	}
	void collisionLeftCallback(int event)override
	{

	}


};
