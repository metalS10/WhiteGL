#pragma once
#include "../../Character/GimmickCharacter/GimmickCharacter.h"
#include "../../Data/Map/Map.h"
#include <map>

class CGimmickPartsFactory : public CCharacterPartsFactory
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
class CGimmickFactory
{
public:

	virtual ~CGimmickFactory() {};

protected:

	virtual CGimmickCharacter* createGimmick() = 0;
	virtual void settingMove(CGimmickCharacter* pChara, float posX, float posY) = 0;
	virtual void settingTexture(CGimmickCharacter* pChara) = 0;
	virtual void settingAnimations(CGimmickCharacter* pChara) = 0;
	virtual void settingPhysicals(CGimmickCharacter* pChara) = 0;
	virtual void settingActions(CGimmickCharacter* pChara) = 0;
	virtual void settingNotes(CGimmickCharacter* pChara) = 0;
	virtual void settingBody(CGimmickCharacter* pChara) = 0;
	virtual void settingCollisionAreas(CGimmickCharacter* pChara) = 0;
	virtual void settingInitialize(CGimmickCharacter* pChara) = 0;

public:

	virtual CCharacter* create(float posX, float posY);

};

class CGimmickCreateFactory : public CGimmickFactory
{
public:
	virtual ~CGimmickCreateFactory() {};

	CGimmickCharacter* createGimmick()override
	{
		CGimmickCharacter* pChara = CGimmickCharacter::create();
		CGimmickPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

class CRollGimmickCreateFactory : public CGimmickFactory
{
public:
	virtual ~CRollGimmickCreateFactory() {};

	CRollGimmickCharacter* createGimmick()override
	{
		CRollGimmickCharacter* pChara = CRollGimmickCharacter::create();
		CGimmickPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

class CTikuwaGimmickCreateFactory : public CGimmickFactory
{
public:
	virtual ~CTikuwaGimmickCreateFactory() {};

	CTikuwaGimmickCharacter* createGimmick()override
	{
		CTikuwaGimmickCharacter* pChara = CTikuwaGimmickCharacter::create();
		CGimmickPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

class CNoteGimmickCreateFactory : public CGimmickFactory
{
public:
	virtual ~CNoteGimmickCreateFactory() {};

	CNoteGimmickCharacter* createGimmick()override
	{
		CNoteGimmickCharacter* pChara = CNoteGimmickCharacter::create();
		CGimmickPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}
};

class CHatenaGimmickCreateFactory : public CGimmickFactory
{
public:
	virtual ~CHatenaGimmickCreateFactory() {};

	CHatenaGimmickCharacter* createGimmick()override
	{
		CHatenaGimmickCharacter* pChara = CHatenaGimmickCharacter::create();
		CGimmickPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}
};

class CWorpGimmickCreateFactory : public CGimmickFactory
{
public:
	virtual ~CWorpGimmickCreateFactory() {};

	CWorpGimmickCharacter* createGimmick()override
	{
		CWorpGimmickCharacter* pChara = CWorpGimmickCharacter::create();
		CGimmickPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}
};



class CDamageBlockLeftFactory : public CGimmickCreateFactory
{
protected:
	void settingMove(CGimmickCharacter* pChara, float posX, float posY)override;

	void settingTexture(CGimmickCharacter* pChara)override;

	void settingAnimations(CGimmickCharacter* pChara)override;

	void settingPhysicals(CGimmickCharacter* pChara)override;

	void settingActions(CGimmickCharacter* pChara)override;

	void settingNotes(CGimmickCharacter* pChara)override;

	void settingBody(CGimmickCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CGimmickCharacter* pChara)override;

	void settingInitialize(CGimmickCharacter* pChara)override;
};

class CDamageBlockTopFactory : public CGimmickCreateFactory
{
protected:
	void settingMove(CGimmickCharacter* pChara, float posX, float posY)override;

	void settingTexture(CGimmickCharacter* pChara)override;

	void settingAnimations(CGimmickCharacter* pChara)override;

	void settingPhysicals(CGimmickCharacter* pChara)override;

	void settingActions(CGimmickCharacter* pChara)override;

	void settingNotes(CGimmickCharacter* pChara)override;

	void settingBody(CGimmickCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CGimmickCharacter* pChara)override;

	void settingInitialize(CGimmickCharacter* pChara)override;
};

class CDamageBlockRightFactory : public CGimmickCreateFactory
{
protected:
	void settingMove(CGimmickCharacter* pChara, float posX, float posY)override;

	void settingTexture(CGimmickCharacter* pChara)override;

	void settingAnimations(CGimmickCharacter* pChara)override;

	void settingPhysicals(CGimmickCharacter* pChara)override;

	void settingActions(CGimmickCharacter* pChara)override;

	void settingNotes(CGimmickCharacter* pChara)override;

	void settingBody(CGimmickCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CGimmickCharacter* pChara)override;

	void settingInitialize(CGimmickCharacter* pChara)override;
};

class CDamageBlockBottomFactory : public CGimmickCreateFactory
{
protected:
	void settingMove(CGimmickCharacter* pChara, float posX, float posY)override;

	void settingTexture(CGimmickCharacter* pChara)override;

	void settingAnimations(CGimmickCharacter* pChara)override;

	void settingPhysicals(CGimmickCharacter* pChara)override;

	void settingActions(CGimmickCharacter* pChara)override;

	void settingNotes(CGimmickCharacter* pChara)override;

	void settingBody(CGimmickCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CGimmickCharacter* pChara)override;

	void settingInitialize(CGimmickCharacter* pChara)override;
};





//���[�v
class CWorpFactory : public CWorpGimmickCreateFactory
{
protected:
	void settingMove(CGimmickCharacter* pChara, float posX, float posY)override;
	void settingTexture(CGimmickCharacter* pChara)override;
	void settingAnimations(CGimmickCharacter* pChara)override;
	void settingPhysicals(CGimmickCharacter* pChara)override;
	void settingActions(CGimmickCharacter* pChara)override;
	void settingNotes(CGimmickCharacter* pChara)override;
	void settingBody(CGimmickCharacter* pChara)override;
	void settingCollisionAreas(CGimmickCharacter* pChara)override;
	void settingInitialize(CGimmickCharacter* pChara)override;
};


//=====================================
//�v���C���[�H��Ǘ�
//=====================================
class CGimmickFactoryManager
{
private:
	//���L�C���X�^���X
	static CGimmickFactoryManager* m_pSharedMgr;

	//�R���X�g���N�^
	CGimmickFactoryManager()
	{
		//�G�H��Q�̐���
		this->m_pFactories = new std::map<GIMMICK_TYPE, CGimmickFactory*>();

		//�H������t���Ă���
		//�����H��̎��t��
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_L] = new CDamageBlockLeftFactory();
		//�㞙�H��̎��t��
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_T] = new CDamageBlockTopFactory();
		//�E���H��̎��t��
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_R] = new CDamageBlockRightFactory();
		//�����H��̎��t��
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_B] = new CDamageBlockBottomFactory();
		//���[�v�H��̎��t��
		(*this->m_pFactories)[GIMMICK_TYPE::WORP] = new CWorpFactory();

	}
public:
	//�f�X�g���N�^
	~CGimmickFactoryManager()
	{
		//�G�H��Q�̔j��
		std::map<GIMMICK_TYPE, CGimmickFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//�G�����H��Q�̔j��
		SAFE_DELETE(this->m_pFactories);
	}

	//���L�C���X�^���X�̎擾
	static CGimmickFactoryManager* getInstance()
	{
		if (CGimmickFactoryManager::m_pSharedMgr == NULL)
		{
			CGimmickFactoryManager::m_pSharedMgr = new CGimmickFactoryManager();
		}
		return CGimmickFactoryManager::m_pSharedMgr;
	}

	//���L�C���X�^���X�̔j��
	static void removeInstance()
	{
		SAFE_DELETE(CGimmickFactoryManager::m_pSharedMgr);
	}

private:
	//�G�����H��Q
	std::map<GIMMICK_TYPE, CGimmickFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	�G�̐���
	*@param	�G�^�C�v(�}�b�v�`�b�vID)
	*@param	�����ʒuX
	*@param	�����ʒuY
	*/
	CCharacter* create(GIMMICK_TYPE type, float posX, float posY)
	{
		return (*this->m_pFactories)[type]->create(posX, posY);
	}
};