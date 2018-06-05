#pragma once

#include "../../Character/EnemyBulletCharacter/EnemyBulletCharacter.h"
#include "../../Character/PlayerCharacter/PlayerCharacter.h"
#include <map>



class CEnemyBulletPartsFactory : public CCharacterPartsFactory
{
public:
	//�A�j���[�V�����擾
	std::vector<CAnimation*>* getAnimations()override;

	//�s���擾
	CMove* getMove()override;

	//�d�͎擾
	std::vector<CPhysical*>* getPhysicals()override;

	//�A�N�V�����擾
	std::vector<CAction*>* getActions()override;


	//���ɍ��킹�ē����A�N�V�����擾
	std::vector<CNotes*>* getNotes() override;

	//���̎擾
	CBody* getBody()override;

	//�Փ˔�����
	std::vector<CCollisionArea*>* getCollisionAreas()
	{
		return new std::vector<CCollisionArea*>();
	}
};


//===================
//�G�H��
//===================
class CEnemyBulletFactory
{
public:
	virtual ~CEnemyBulletFactory() {};

protected:

	virtual CEnemyBulletCharacter* createEnemyBullet() = 0;

	virtual void settingMove(CEnemyBulletCharacter* pChara, float posX, float posY) = 0;

	virtual void settingTexture(CEnemyBulletCharacter* pChara) = 0;

	virtual void settingAnimations(CEnemyBulletCharacter* pChara) = 0;

	virtual void settingPhysicals(CEnemyBulletCharacter* pChara) = 0;

	virtual void settingActions(CEnemyBulletCharacter* pChara, CVec2) = 0;

	virtual void settingNotes(CEnemyBulletCharacter* pChara) = 0;

	virtual void settingBody(CEnemyBulletCharacter* pChara) = 0;

	//�Փ˔����Ԃ̐ݒ�
	virtual void settingCollisionAreas(CEnemyBulletCharacter* pChara) = 0;

	virtual void settingInitialize(CEnemyBulletCharacter* pChara) = 0;

	virtual void settingState(CEnemyBulletCharacter* pChara) = 0;

public:

	virtual CCharacter* create(float posX, float posY, CVec2 vec);

};

class CEnemyBulletCreateFactory : public CEnemyBulletFactory
{
public:
	virtual ~CEnemyBulletCreateFactory() {};




	CEnemyBulletCharacter* createEnemyBullet()override
	{
		CEnemyBulletCharacter* pChara = CEnemyBulletCharacter::create();

		CEnemyBulletPartsFactory pFactory;

		pChara->m_pAnimations = pFactory.getAnimations();

		pChara->m_pMove = pFactory.getMove();

		pChara->m_pPhysicals = pFactory.getPhysicals();

		pChara->m_pActions = pFactory.getActions();

		pChara->m_pNotes = pFactory.getNotes();

		pChara->m_pBody = pFactory.getBody();

		//�Փ˔����Ԃ̐����Ǝ��t��
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

class CNormalEnemyBulletFactory : public CEnemyBulletCreateFactory
{
protected:
	void settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyBulletCharacter* pChara)override;

	void settingAnimations(CEnemyBulletCharacter* pChara)override;

	void settingPhysicals(CEnemyBulletCharacter* pChara)override;

	void settingActions(CEnemyBulletCharacter* pChara ,CVec2)override;

	void settingNotes(CEnemyBulletCharacter* pChara)override;

	void settingBody(CEnemyBulletCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyBulletCharacter* pChara)override;

	void settingInitialize(CEnemyBulletCharacter* pChara)override;

	void settingState(CEnemyBulletCharacter* pChara) override;
};


class CCustomEnemyBulletFactory : public CEnemyBulletCreateFactory
{
protected:
	void settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyBulletCharacter* pChara)override;

	void settingAnimations(CEnemyBulletCharacter* pChara)override;

	void settingPhysicals(CEnemyBulletCharacter* pChara)override;

	void settingActions(CEnemyBulletCharacter* pChara, CVec2)override;

	void settingNotes(CEnemyBulletCharacter* pChara)override;

	void settingBody(CEnemyBulletCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyBulletCharacter* pChara)override;

	void settingInitialize(CEnemyBulletCharacter* pChara)override;

	void settingState(CEnemyBulletCharacter* pChara) override;
};

class CFireBallCreateFactory : public CEnemyBulletFactory
{
public:
	virtual ~CFireBallCreateFactory() {};




	CFireBallEnemyBulletCharacter* createEnemyBullet()override
	{
		CFireBallEnemyBulletCharacter* pChara = CFireBallEnemyBulletCharacter::create();

		CEnemyBulletPartsFactory pFactory;

		pChara->m_pAnimations = pFactory.getAnimations();

		pChara->m_pMove = pFactory.getMove();

		pChara->m_pPhysicals = pFactory.getPhysicals();

		pChara->m_pActions = pFactory.getActions();

		pChara->m_pNotes = pFactory.getNotes();

		pChara->m_pBody = pFactory.getBody();

		//�Փ˔����Ԃ̐����Ǝ��t��
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

class CFireBallEnemyBulletFactory : public CFireBallCreateFactory
{
protected:
	void settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyBulletCharacter* pChara)override;

	void settingAnimations(CEnemyBulletCharacter* pChara)override;

	void settingPhysicals(CEnemyBulletCharacter* pChara)override;

	void settingActions(CEnemyBulletCharacter* pChara, CVec2)override;

	void settingNotes(CEnemyBulletCharacter* pChara)override;

	void settingBody(CEnemyBulletCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyBulletCharacter* pChara)override;

	void settingInitialize(CEnemyBulletCharacter* pChara)override;

	void settingState(CEnemyBulletCharacter* pChara) override;
};



//=====================================
//�v���C���[�H��Ǘ�
//=====================================
class CEnemyBulletFactoryManager
{
private:
	//���L�C���X�^���X
	static CEnemyBulletFactoryManager* m_pSharedMgr;

	//�R���X�g���N�^
	CEnemyBulletFactoryManager()
	{
		//�G�H��Q�̐���
		this->m_pFactories = new std::map<BULLET_TYPE, CEnemyBulletFactory*>();

		//�H������t���Ă���
		//�N���{�[�H��̎��t��
		(*this->m_pFactories)[BULLET_TYPE::NORMAL] = new CNormalEnemyBulletFactory();

		(*this->m_pFactories)[BULLET_TYPE::CUSTOM] = new CCustomEnemyBulletFactory();

		(*this->m_pFactories)[BULLET_TYPE::FIREBALL] = new CFireBallEnemyBulletFactory();

	}
public:
	//�f�X�g���N�^
	~CEnemyBulletFactoryManager()
	{
		//�e�H��Q�̔j��
		std::map<BULLET_TYPE, CEnemyBulletFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//�G�����H��Q�̔j��
		SAFE_DELETE(this->m_pFactories);
	}

	//���L�C���X�^���X�̎擾
	static CEnemyBulletFactoryManager* getInstance()
	{
		if (CEnemyBulletFactoryManager::m_pSharedMgr == NULL)
		{
			CEnemyBulletFactoryManager::m_pSharedMgr = new CEnemyBulletFactoryManager();
		}
		return CEnemyBulletFactoryManager::m_pSharedMgr;
	}

	//���L�C���X�^���X�̔j��
	static void removeInstance()
	{
		SAFE_DELETE(CEnemyBulletFactoryManager::m_pSharedMgr);
	}

private:
	//�G�����H��Q
	std::map<BULLET_TYPE, CEnemyBulletFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	�G�̐���
	*@param	�G�^�C�v(�}�b�v�`�b�vID)
	*@param	�����ʒuX
	*@param	�����ʒuY
	*/
	CCharacter* create(BULLET_TYPE type, float posX, float posY,CVec2 vec)
	{
		return (*this->m_pFactories)[type]->create(posX, posY,vec);
	}
};