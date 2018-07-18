#pragma once
#include "../Character.h"
#include "../../Scene/Scene.h"

//=====================================================
//
//�G�L�����N�^�[�̊��N���X�ƂȂ�N���X
//
//=====================================================
class CEnemyCharacter : public CCharacter
{
public:
	//�R���X�g���N�^
	CEnemyCharacter();

	//�f�X�g���N�^
	~CEnemyCharacter();

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
	//CREATE_FUNC(CEnemyCharacter);
	static CEnemyCharacter* create()
	{
		CEnemyCharacter* pRet = new(std::nothrow)CEnemyCharacter();
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
	static CEnemyCharacter* create(float posX, float posY)
	{
		CEnemyCharacter* pRet = new(std::nothrow)CEnemyCharacter();

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

	//4�������X�V
	void quarterUpdate() override;

	void hitsPlayerCharacter(CCharacter* pChara);

	void hitsBulletCharacter(CCharacter* pChara);

	void DamageInterval();


	//===========================================
	//������ł����g���Ă��Ȃ������o�ϐ�
	//===========================================
	//�v���C���[
	CCharacter* pPlayerChara;

	//�v���C���[���̍��̓G���������߂�1�t���[���̂��߂̕ϐ�
	int m_enemyDeadOneFrame = 0;

	void isDeath();

	bool Troi = false;

	int beatsCounter = 0;
};