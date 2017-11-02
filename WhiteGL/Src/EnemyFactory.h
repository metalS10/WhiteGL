#pragma once
#include "EnemyCharacter.h"
#include "Map.h"
#include <map>

class CEnemyPartsFactory : public CCharacterPartsFactory
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
class CEnemyFactory
{
public:

	virtual ~CEnemyFactory() {};

protected:

	virtual CEnemyCharacter* createEnemy() = 0;

	virtual void settingMove(CEnemyCharacter* pChara, float posX, float posY) = 0;

	virtual void settingTexture(CEnemyCharacter* pChara) = 0;

	virtual void settingAnimations(CEnemyCharacter* pChara) = 0;

	virtual void settingPhysicals(CEnemyCharacter* pChara) = 0;

	virtual void settingActions(CEnemyCharacter* pChara) = 0;

	virtual void settingBody(CEnemyCharacter* pChara) = 0;

	//�Փ˔����Ԃ̐ݒ�
	virtual void settingCollisionAreas(CEnemyCharacter* pChara) = 0;

	virtual void settingInitialize(CEnemyCharacter* pChara) = 0;

	virtual void settingState(CEnemyCharacter* pChara) = 0;

public:

	virtual CCharacter* create(float posX, float posY);

};

class CEnemyCreateFactory : public CEnemyFactory
{
public:
	virtual ~CEnemyCreateFactory() {};

	CEnemyCharacter* createEnemy()override
	{
		CEnemyCharacter* pChara = CEnemyCharacter::create();

		CEnemyPartsFactory pFactory;

		pChara->m_pAnimations = pFactory.getAnimations();

		pChara->m_pMove = pFactory.getMove();

		pChara->m_pPhysicals = pFactory.getPhysicals();

		//pChara->m_pActions = pFactory.getActions();

		pChara->m_pBody = pFactory.getBody();

		//�Փ˔����Ԃ̐����Ǝ��t��
		pChara->m_pCollisionAreas = pFactory.getCollisionAreas();

		pChara->m_hitPoint = pFactory.getState();

		return pChara;
	}

};

class CKuriboFactory : public CEnemyCreateFactory
{
protected:
	void settingMove(CEnemyCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyCharacter* pChara)override;

	void settingAnimations(CEnemyCharacter* pChara)override;

	void settingPhysicals(CEnemyCharacter* pChara)override;

	void settingActions(CEnemyCharacter* pChara)override;

	void settingBody(CEnemyCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//�G�̗̑͂̐ݒ�
	void settingState(CEnemyCharacter* pChara)override;
};

class CGreenNokoNokoFactory : public CEnemyCreateFactory
{
protected:
	void settingMove(CEnemyCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyCharacter* pChara)override;

	void settingAnimations(CEnemyCharacter* pChara)override;

	void settingPhysicals(CEnemyCharacter* pChara)override;

	void settingActions(CEnemyCharacter* pChara)override;

	void settingBody(CEnemyCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//�G�̗̑͂̐ݒ�
	void settingState(CEnemyCharacter* pChara)override;
};

class CGreenPataPataFactory : public CEnemyCreateFactory
{
protected:
	void settingMove(CEnemyCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyCharacter* pChara)override;

	void settingAnimations(CEnemyCharacter* pChara)override;

	void settingPhysicals(CEnemyCharacter* pChara)override;

	void settingActions(CEnemyCharacter* pChara)override;

	void settingBody(CEnemyCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//�G�̗̑͂̐ݒ�
	void settingState(CEnemyCharacter* pChara)override;
};

class CKillerHoudaiFactory : public CEnemyCreateFactory
{
protected:
	void settingMove(CEnemyCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyCharacter* pChara)override;

	void settingAnimations(CEnemyCharacter* pChara)override;

	void settingPhysicals(CEnemyCharacter* pChara)override;

	void settingActions(CEnemyCharacter* pChara)override;

	void settingBody(CEnemyCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//�G�̗̑͂̐ݒ�
	void settingState(CEnemyCharacter* pChara)override;
};


class CKillerFactory : public CEnemyCreateFactory
{
protected:
	void settingMove(CEnemyCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyCharacter* pChara)override;

	void settingAnimations(CEnemyCharacter* pChara)override;

	void settingPhysicals(CEnemyCharacter* pChara)override;

	void settingActions(CEnemyCharacter* pChara)override;

	void settingBody(CEnemyCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//�G�̗̑͂̐ݒ�
	void settingState(CEnemyCharacter* pChara)override;
};

class CTRoiFactory : public CEnemyCreateFactory
{
protected:
	void settingMove(CEnemyCharacter* pChara, float posX, float posY)override;

	void settingTexture(CEnemyCharacter* pChara)override;

	void settingAnimations(CEnemyCharacter* pChara)override;

	void settingPhysicals(CEnemyCharacter* pChara)override;

	void settingActions(CEnemyCharacter* pChara)override;

	void settingBody(CEnemyCharacter* pChara)override;

	//�Փ˔����Ԃ̐ݒ�
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//�G�̗̑͂̐ݒ�
	void settingState(CEnemyCharacter* pChara)override;
};

//=====================================
//�v���C���[�H��Ǘ�
//=====================================
class CEnemyFactoryManager
{
private:
	//���L�C���X�^���X
	static CEnemyFactoryManager* m_pSharedMgr;

	//�R���X�g���N�^
	CEnemyFactoryManager()
	{
		//�G�H��Q�̐���
		this->m_pFactories = new std::map<ENEMY_TYPE, CEnemyFactory*>();

		//�H������t���Ă���
		//�N���{�[�H��̎��t��
		(*this->m_pFactories)[ENEMY_TYPE::KURIBO] = new CKuriboFactory();
		//�m�R�m�R�H��̎��t��
		(*this->m_pFactories)[ENEMY_TYPE::NOKONOKO] = new CGreenNokoNokoFactory();
		//�p�^�p�^�H��̎��t��
		(*this->m_pFactories)[ENEMY_TYPE::PATAPATA] = new CGreenPataPataFactory();
		//�L���[�C��H��̎��t��
		(*this->m_pFactories)[ENEMY_TYPE::KILLERHODAI] = new CKillerHoudaiFactory();
		//�L���[�H��̎��t��
		(*this->m_pFactories)[ENEMY_TYPE::KILLER] = new CKillerFactory();
		//�g�����Ȃ��ؔn�H��̎��t��
		(*this->m_pFactories)[ENEMY_TYPE::TROI] = new CTRoiFactory();
	}

public:
	//�f�X�g���N�^
	~CEnemyFactoryManager()
	{
		//�G�H��Q�̔j��
		std::map<ENEMY_TYPE, CEnemyFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//�G�����H��Q�̔j��
		SAFE_DELETE(this->m_pFactories);
	}

	//���L�C���X�^���X�̎擾
	static CEnemyFactoryManager* getInstance()
	{
		if (CEnemyFactoryManager::m_pSharedMgr == NULL)
		{
			CEnemyFactoryManager::m_pSharedMgr = new CEnemyFactoryManager();
		}
		return CEnemyFactoryManager::m_pSharedMgr;
	}

	//���L�C���X�^���X�̔j��
	static void removeInstance()
	{
		SAFE_DELETE(CEnemyFactoryManager::m_pSharedMgr);
	}

private:
	//�G�����H��Q
	std::map<ENEMY_TYPE, CEnemyFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	�G�̐���
	*@param	�G�^�C�v(�}�b�v�`�b�vID)
	*@param	�����ʒuX
	*@param	�����ʒuY
	*/
	CCharacter* create(ENEMY_TYPE type, float posX, float posY)
	{
		return (*this->m_pFactories)[type]->create(posX, posY);
	}
};