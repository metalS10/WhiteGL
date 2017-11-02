#pragma once

#include "AttackCharacter.h"
#include "PlayerCharacter.h"
#include <map>



class CAttackPartsFactory : public CCharacterPartsFactory
{
public:
	//�A�j���[�V�����擾
	std::vector<CAnimation*>* getAnimations()override;

	//�s���擾
	CMove* getMove()override;

	//�d�͎擾
	std::vector<CPhysical*>* getPhysicals()override;

	//�A�N�V�����擾
	//std::vector<CAction*>* getActions()override;

	//���̎擾
	CBody* getBody()override;

	//�Փ˔�����
	std::vector<CCollisionArea*>* getCollisionAreas()
	{
		return new std::vector<CCollisionArea*>();
	}

	int getState();
};


//===================
//�G�H��
//===================
class CAttackFactory
{
public:
	virtual ~CAttackFactory() {};

protected:

	virtual CAttackCharacter* createAttack() = 0;

	virtual void settingMove(CAttackCharacter* pChara, float posX, float posY) = 0;

	virtual void settingTexture(CAttackCharacter* pChara) = 0;

	virtual void settingAnimations(CAttackCharacter* pChara) = 0;

	virtual void settingPhysicals(CAttackCharacter* pChara) = 0;

	//virtual void settingActions(CAttackCharacter* pChara, CVec2) = 0;

	virtual void settingBody(CAttackCharacter* pChara) = 0;

	//�Փ˔����Ԃ̐ݒ�
	virtual void settingCollisionAreas(CAttackCharacter* pChara) = 0;

	virtual void settingInitialize(CAttackCharacter* pChara) = 0;

	virtual void settingState(CAttackCharacter* pChara) = 0;

public:

	virtual CCharacter* create(float posX, float posY, CVec2 vec);

};

class CAttackCreateFactory : public CAttackFactory
{
public:
	virtual ~CAttackCreateFactory() {};




	CAttackCharacter* createAttack()override
	{
		CAttackCharacter* pChara = CAttackCharacter::create();

		CAttackPartsFactory pFactory;

		pChara->m_pAnimations = pFactory.getAnimations();

		pChara->m_pMove = pFactory.getMove();

		pChara->m_pPhysicals = pFactory.getPhysicals();

		//pChara->m_pActions = pFactory.getActions();

		pChara->m_pBody = pFactory.getBody();

		//�Փ˔����Ԃ̐����Ǝ��t��
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		pChara->m_DeleteTime = pFactory.getState();

		return pChara;
	}

};

class CNormalAttackFactory : public CAttackCreateFactory
{
protected:
	void settingMove(CAttackCharacter* pChara, float posX, float posY)override;

	void settingTexture(CAttackCharacter* pChara)override;

	void settingAnimations(CAttackCharacter* pChara)override;

	void settingPhysicals(CAttackCharacter* pChara)override;

	//void settingActions(CAttackCharacter* pChara, CVec2)override;

	void settingBody(CAttackCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CAttackCharacter* pChara)override;

	void settingInitialize(CAttackCharacter* pChara)override;

	void settingState(CAttackCharacter* pChara) override;
};


class CNorAttackFactory : public CAttackCreateFactory
{
protected:
	void settingMove(CAttackCharacter* pChara, float posX, float posY)override;

	void settingTexture(CAttackCharacter* pChara)override;

	void settingAnimations(CAttackCharacter* pChara)override;

	void settingPhysicals(CAttackCharacter* pChara)override;

	//void settingActions(CAttackCharacter* pChara, cocos2d::Vec2)override;

	void settingBody(CAttackCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CAttackCharacter* pChara)override;

	void settingInitialize(CAttackCharacter* pChara)override;

	void settingState(CAttackCharacter* pChara) override;
};

/*
class CFireBallCreateFactory : public CAttackFactory
{
public:
	virtual ~CFireBallCreateFactory() {};




	CFireBallAttackCharacter* createAttack()override
	{
		CFireBallAttackCharacter* pChara = CFireBallAttackCharacter::create();

		CAttackPartsFactory pFactory;

		pChara->m_pAnimations = pFactory.getAnimations();

		pChara->m_pMove = pFactory.getMove();

		pChara->m_pPhysicals = pFactory.getPhysicals();

		pChara->m_pActions = pFactory.getActions();

		pChara->m_pBody = pFactory.getBody();

		//�Փ˔����Ԃ̐����Ǝ��t��
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

class CFireBallAttackFactory : public CFireBallCreateFactory
{
protected:
	void settingMove(CAttackCharacter* pChara, float posX, float posY)override;

	void settingTexture(CAttackCharacter* pChara)override;

	void settingAnimations(CAttackCharacter* pChara)override;

	void settingPhysicals(CAttackCharacter* pChara)override;

	void settingActions(CAttackCharacter* pChara, cocos2d::Vec2)override;

	void settingBody(CAttackCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CAttackCharacter* pChara)override;

	void settingInitialize(CAttackCharacter* pChara)override;
};
*/
//=====================================
//�U���H��Ǘ�
//=====================================
class CAttackFactoryManager
{
private:
	//���L�C���X�^���X
	static CAttackFactoryManager* m_pSharedMgr;

	//�R���X�g���N�^
	CAttackFactoryManager()
	{
		//�G�H��Q�̐���
		this->m_pFactories = new std::map<ATTACK_TYPE, CAttackFactory*>();

		//�H������t���Ă���
		//�N���{�[�H��̎��t��
		(*this->m_pFactories)[ATTACK_TYPE::NORMAL] = new CNormalAttackFactory();

		(*this->m_pFactories)[ATTACK_TYPE::NOR] = new CNorAttackFactory();

		//(*this->m_pFactories)[ATTACK_TYPE::FIREBALL] = new CFireBallAttackFactory();

	}
public:
	//�f�X�g���N�^
	~CAttackFactoryManager()
	{
		//�e�H��Q�̔j��
		std::map<ATTACK_TYPE, CAttackFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//�G�����H��Q�̔j��
		SAFE_DELETE(this->m_pFactories);
	}

	//���L�C���X�^���X�̎擾
	static CAttackFactoryManager* getInstance()
	{
		if (CAttackFactoryManager::m_pSharedMgr == NULL)
		{
			CAttackFactoryManager::m_pSharedMgr = new CAttackFactoryManager();
		}
		return CAttackFactoryManager::m_pSharedMgr;
	}

	//���L�C���X�^���X�̔j��
	static void removeInstance()
	{
		SAFE_DELETE(CAttackFactoryManager::m_pSharedMgr);
	}

private:
	//�G�����H��Q
	std::map<ATTACK_TYPE, CAttackFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	�G�̐���
	*@param	�G�^�C�v(�}�b�v�`�b�vID)
	*@param	�����ʒuX
	*@param	�����ʒuY
	*/
	CCharacter* create(ATTACK_TYPE type, float posX, float posY, CVec2 vec)
	{
		return (*this->m_pFactories)[type]->create(posX, posY, vec);
	}
};