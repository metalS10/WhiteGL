#pragma once
#include "../../Character/NotesCharacter/NotesCharacter.h"
#include "../../Data/Map/Map.h"
#include <map>

class CNotesPartsFactory : public CCharacterPartsFactory
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
//�e�ƂȂ�H��
//===================
class CNotesFactory
{
public:

	virtual ~CNotesFactory() {};

protected:
	virtual CNotesCharacter* createNotes() = 0;
	virtual void settingMove(CNotesCharacter* pChara, float posX, float posY) = 0;
	virtual void settingTexture(CNotesCharacter* pChara) = 0;
	virtual void settingAnimations(CNotesCharacter* pChara) = 0;
	virtual void settingPhysicals(CNotesCharacter* pChara) = 0;
	virtual void settingActions(CNotesCharacter* pChara) = 0;
	//virtual void settingBody(CNotesCharacter* pChara) = 0;
	virtual void settingNotes(CNotesCharacter* pChara) = 0;
	virtual void settingCollisionAreas(CNotesCharacter* pChara) = 0;
	virtual void settingInitialize(CNotesCharacter* pChara) = 0;

public:

	virtual CCharacter* create(float posX, float posY);

};

class CNotesCreateFactory : public CNotesFactory
{
public:
	virtual ~CNotesCreateFactory() {};

	CNotesCharacter* createNotes()override
	{
		CNotesCharacter* pChara = CNotesCharacter::create();
		CNotesPartsFactory pFactory;
		pChara->m_pAnimations = pFactory.getAnimations();
		pChara->m_pMove = pFactory.getMove();
		pChara->m_pPhysicals = pFactory.getPhysicals();
		pChara->m_pActions = pFactory.getActions();
		pChara->m_pNotes = pFactory.getNotes();
		//pChara->m_pBody = pFactory.getBody();
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		return pChara;
	}

};

//�A�j���[�V����
class CNotesAnimationFactory : public CNotesCreateFactory
{
protected:
	void settingMove(CNotesCharacter* pChara, float posX, float posY)override;
	void settingTexture(CNotesCharacter* pChara)override;
	void settingAnimations(CNotesCharacter* pChara)override;
	void settingPhysicals(CNotesCharacter* pChara)override;
	void settingActions(CNotesCharacter* pChara)override;
	//void settingBody(CNotesCharacter* pChara)override;
	void settingNotes(CNotesCharacter* pChara)override;
	void settingCollisionAreas(CNotesCharacter* pChara)override;
	void settingInitialize(CNotesCharacter* pChara)override;
};

//=====================================
//�v���C���[�H��Ǘ�
//=====================================
class CNotesFactoryManager
{
private:
	//���L�C���X�^���X
	static CNotesFactoryManager* m_pSharedMgr;

	//�R���X�g���N�^
	CNotesFactoryManager()
	{
		//�G�H��Q�̐���
		this->m_pFactories = new std::map<NOTES_TYPE, CNotesFactory*>();

		//�H������t���Ă���
		//�����H��̎��t��
		(*this->m_pFactories)[NOTES_TYPE::ANIMATION] = new CNotesAnimationFactory();

	}
public:
	//�f�X�g���N�^
	~CNotesFactoryManager()
	{
		//�G�H��Q�̔j��
		std::map<NOTES_TYPE, CNotesFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//�G�����H��Q�̔j��
		SAFE_DELETE(this->m_pFactories);
	}

	//���L�C���X�^���X�̎擾
	static CNotesFactoryManager* getInstance()
	{
		if (CNotesFactoryManager::m_pSharedMgr == NULL)
		{
			CNotesFactoryManager::m_pSharedMgr = new CNotesFactoryManager();
		}
		return CNotesFactoryManager::m_pSharedMgr;
	}

	//���L�C���X�^���X�̔j��
	static void removeInstance()
	{
		SAFE_DELETE(CNotesFactoryManager::m_pSharedMgr);
	}

private:
	//�G�����H��Q
	std::map<NOTES_TYPE, CNotesFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	�G�̐���
	*@param	�G�^�C�v(�}�b�v�`�b�vID)
	*@param	�����ʒuX
	*@param	�����ʒuY
	*/
	CCharacter* create(NOTES_TYPE type, float posX, float posY)
	{
		return (*this->m_pFactories)[type]->create(posX, posY);
	}
};
