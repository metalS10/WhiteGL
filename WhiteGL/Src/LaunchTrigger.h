#pragma once

#include <stdio.h>
#include <memory>
#include "Constants.h"
#include "LaunchData.h"
#include "Map.h"


//==================================================
//�O���錾
//==================================================
class CCharacter;

//==================================================
//
//�o���g���K�[
//
//==================================================
class CLaunchTrigger
{
public:
	//�L���t���O	false...�o���X�P�W���[��������O��
	bool m_activeFlag = false;

	//�R���X�g���N�^
	CLaunchTrigger()
	{
		this->m_activeFlag = true;
	}

	//�f�X�g���N�^
	virtual ~CLaunchTrigger(){}

	/**
	*@desc	���˂��I��������ǂ���
	*@return true...���˂����@false...���˂��Ă��Ȃ�
	*@tips	���˂��I��������ǂ����͔h���N���X�ɂ����
	*		�t���O���ω�����ꍇ�����݂���
	*/
	virtual bool isLaunched()
	{
		return this->m_activeFlag;
	}

	/**
	*@desc	�ݒ肳��Ă���g���K�[���C�x���g���s���邩�ǂ���
	*@param	true...�C�x���g�̎��s���\
	*@tips	�C�x���g�̎��s�\�����͔h���N���X�ɂ���ĕω�����
	*/
	virtual bool isTrigger() = 0;

	/**
	*@desc	�g���K�[�̃C�x���g�̎��s
	*		�����ł̃g���K�[�C�x���g�̓L�����N�^�[�̐���
	*/
	virtual CCharacter* action() = 0;
};

//====================================================================
//
//�G�o���g���K�[
//	�G�o���f�[�^���g���K�[�Ƃ��ēG�o���Ƃ����C�x���g������������
//
//====================================================================
class CEnemyLaunchTrigger : public CLaunchTrigger
{
private:
	//�G�o���f�[�^
	CEnemyLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�G�o���f�[�^
	*@tips	�G�o���f�[�^���g���K�[�Ƃ��Đݒ肷��
	*/
	CEnemyLaunchTrigger(CEnemyLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData){}

	//�f�X�g���N�^
	~CEnemyLaunchTrigger();

	/**
	*@desc	�C�x���g�����s�ł��邩�ǂ���
	*@return	true...���s�\
	*/
	bool isTrigger() override;

	/**
	*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
	*		�g���K�[�����ɃC�x���g�����s
	*/
	CCharacter* action() override;
};

//====================================================================
//
//�e�o���g���K�[
//	�e�o���f�[�^���g���K�[�Ƃ��Ēe�o���Ƃ����C�x���g������������
//
//====================================================================
class CAttackLaunchTrigger : public CLaunchTrigger
{
private:
	//�G�o���f�[�^
	CAttackLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�G�o���f�[�^
	*@tips	�G�o���f�[�^���g���K�[�Ƃ��Đݒ肷��
	*/
	CAttackLaunchTrigger(CAttackLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData) {}

	//�f�X�g���N�^
	~CAttackLaunchTrigger();

	/**
	*@desc	�C�x���g�����s�ł��邩�ǂ���
	*@return	true...���s�\
	*/
	bool isTrigger() override;

	/**
	*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
	*		�g���K�[�����ɃC�x���g�����s
	*/
	CCharacter* action() override;
};

//====================================================================
//
//�M�~�b�N�o���g���K�[
//	�M�~�b�N�o���f�[�^���g���K�[�Ƃ��ăM�~�b�N�o���Ƃ����C�x���g������������
//
//====================================================================
class CGimmickLaunchTrigger : public CLaunchTrigger
{
private:
	//�G�o���f�[�^
	CGimmickLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�G�o���f�[�^
	*@tips	�G�o���f�[�^���g���K�[�Ƃ��Đݒ肷��
	*/
	CGimmickLaunchTrigger(CGimmickLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData) {}

	//�f�X�g���N�^
	~CGimmickLaunchTrigger();

	/**
	*@desc	�C�x���g�����s�ł��邩�ǂ���
	*@return	true...���s�\
	*/
	bool isTrigger() override;

	/**
	*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
	*		�g���K�[�����ɃC�x���g�����s
	*/
	CCharacter* action() override;
};

//===========================================================
//���ˑ�
//	�o���X�P�W���[���̎Q�Ƃ�ݒ肵��
//	�o���X�P�W���[���Ɏ��t�����Ă���o���g���K�[�̏��Ԓʂ��
//	�C�x���g�����s���Ă���
//	�܂���t����ꂽ���Ԓʂ�ɏo�����s���Ă���
//
//	Aggregate
//
//===========================================================
class CLauncher
{
public:
	//�o���X�P�W���[���̎Q��(�܂肱�̃N���X�Ő�����j�����s��Ȃ�)
	//1�t���[���ɏo��������g���K�[�C�x���g�̏W�܂�
	std::vector<CLaunchTrigger*>* m_pLaunchSchedule = NULL;

	/**
	*@desc	�R���X�g���N�^
	*@param	�o���X�P�W���[���̃A�h���X
	*/
	CLauncher(std::vector<CLaunchTrigger*>* pLaunchSchedule)
		:m_pLaunchSchedule(pLaunchSchedule){}

	//�f�X�g���N�^
	~CLauncher(){}

	/**
	*@desc	�o���g���K�[���o���X�P�W���[���ɒǉ�����
	*/
	void add(CLaunchTrigger* pTrigger)
	{
		this->m_pLaunchSchedule->push_back(pTrigger);
	}
	
	/**
	*@desc	�o���X�P�W���[���̃T�C�Y�̎擾
	*/
	int getSize()
	{
		return (int)this->m_pLaunchSchedule->size();
	}

	/**
	*@desc	�o���g���K�[�̎擾
	*@param	�Y�����ԍ�
	*/
	CLaunchTrigger* getAt(int index)
	{
		//�ő�v�f�ȏ�̍ۂ�NULL��Ԃ�
		if (this->getSize() <= index)
		{
			return NULL;
		}
		return (*this->m_pLaunchSchedule)[index];
	}

	//==============================================================
	//
	//�o���g���K�[�C�e���[�^�[
	//	���ˑ�Ɏ��t�����Ă���g���K�[�𔭎ˉ\�����ׂāA
	//	���ˉ\�Ȃ�1�Âo�������邽�߂̑{�����s���N���X
	//	Aggregate�̒��Ɏ���
	//		Iterator
	//
	//==============================================================
	class CLaunchTriggerIterator
	{
	public:
		//���ˑ�
		CLauncher* m_pLauncher = NULL;

		//���ݎQ�ƒ��̔ԍ�
		int m_triggerCount = 0;

		//�R���X�g���N�^
		CLaunchTriggerIterator(CLauncher* pLauncher)
			:m_pLauncher(pLauncher){}

		/**
		*@desc	�o���g���K�[�̎������邩�ǂ����𒲂ׂ�
		*		�������͏o���g���K�[���N���\���ǂ����𒲂ׂ�
		*/
		bool hasNext()
		{
			//�g���K�[�C�x���g�̏W�܂�̃T�C�Y�𒲂ׂ�
			if (this->m_pLauncher->getSize() <= this->m_triggerCount)
			{
				return false;
			}

			//�o���g���K�[���N���\���ǂ����𒲂ׂ�
			if (this->m_pLauncher->getAt(this->m_triggerCount)->isTrigger() == false)
			{
				//�N���\�łȂ��ꍇ�͓Y�����ԍ������ɐi�߂�
				this->m_triggerCount++;
				//�����`�F�b�N
				return this->hasNext();
			}
			return true;
		}

		/**
		*@desc	���݂̏o���g���K�[���擾���Y�����ԍ������ɐi�߂�
		*/
		CLaunchTrigger* next()
		{
			CLaunchTrigger* pTrigger = this->m_pLauncher->getAt(this->m_triggerCount);
			this->m_triggerCount++;
			return pTrigger;
		}
	};

	/**
	*@desc	�o���g���K�[�C�e���[�^�[�̐���
	*@param	�o���g���K�[�C�e���[�^�[
	*/
	std::shared_ptr<CLaunchTriggerIterator>iterator()
	{
		return std::shared_ptr<CLaunchTriggerIterator>(new CLaunchTriggerIterator(this));
	}
};

//======================================================
//
//�o���X�P�W���[���[
//	Singleton
//
//======================================================
class CLaunchScheduler
{
	//=========================================================
	//��������Singleton�ݒ�
	//=========================================================

private:
	//���L�C���X�^���X
	static CLaunchScheduler* m_pSharedScheduler;

	//�R���X�g���N�^
	CLaunchScheduler();

public:
	//���L�C���X�^���X�̎擾
	static CLaunchScheduler* getInstance();

	//���L�C���X�^���X�̔j��
	static void removeInstance();

	//�f�X�g���N�^
	~CLaunchScheduler();

	//=========================================================
	//�����܂�Singleton�ݒ�
	//=========================================================

public:
	//���ˑ�
	CLauncher* m_pLauncher = NULL;

	/**
	*@desc	���ˑ�
	*@param	���ˑ�ɐݒ肷��o���X�P�W���[���̃A�h���X
	*/
	void createLauncher(std::vector<CLaunchTrigger*>* pLaunchSchedule);

	/**
	*@desc	�L�����N�^�[�̏o��
	*@param	���t���郌�C���[
	*/
	void launchCharacters();
};


//====================================================================
//
//�G�̒e�o���g���K�[
//	�e�o���f�[�^���g���K�[�Ƃ��Ēe�o���Ƃ����C�x���g������������
//
//====================================================================
class CEnemyBulletLaunchTrigger : public CLaunchTrigger
{
private:
	//�G�o���f�[�^
	CEnemyBulletLaunchData* m_pLaunchData = NULL;

public:
	/**
	*@desc	�R���X�g���N�^
	*@param	�G�o���f�[�^
	*@tips	�G�o���f�[�^���g���K�[�Ƃ��Đݒ肷��
	*/
	CEnemyBulletLaunchTrigger(CEnemyBulletLaunchData* pLaunchData)
		:m_pLaunchData(pLaunchData) {}

	//�f�X�g���N�^
	~CEnemyBulletLaunchTrigger();

	/**
	*@desc	�C�x���g�����s�ł��邩�ǂ���
	*@return	true...���s�\
	*/
	bool isTrigger() override;

	/**
	*@desc	�ݒ肳��Ă���G�o���f�[�^�����ƂɓG�𐶐�����
	*		�g���K�[�����ɃC�x���g�����s
	*/
	CCharacter* action() override;
};