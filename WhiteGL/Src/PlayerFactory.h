#pragma once
#include "PlayerCharacter.h"

class CPlayerPartsFactory : public CCharacterPartsFactory
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
};



class CPlayerFactory
{
public:

	virtual ~CPlayerFactory() {};

protected:

	virtual CPlayerCharacter* createPlayer() = 0;

	virtual void settingMove(CPlayerCharacter* pPlayerCharacter,float posX,float posY) = 0;

	virtual void settingTexture(CPlayerCharacter* pPlayerCharacter) = 0;

	virtual void settingAnimations(CPlayerCharacter* pPlayerCharacter) = 0;

	virtual void settingPhysicals(CPlayerCharacter* pPlayerCharacter) = 0;

	virtual void settingActions(CPlayerCharacter* pPlayerCharacter) = 0;

	virtual void settingBody(CPlayerCharacter* pPlayerCharacter) = 0;

	virtual void settingInitialize(CPlayerCharacter* pPlayerCharacter) = 0;

public:

	virtual CCharacter* create(float posX, float posY,CGameEngine& gm);

};

class CPlayerCreateFactory : public CPlayerFactory
{
public:
	virtual ~CPlayerCreateFactory() {};

	CPlayerCharacter* createPlayer()override
	{
		CPlayerCharacter* pChara = new CPlayerCharacter();

		CPlayerPartsFactory pFactory;

		pChara->m_pAnimations = pFactory.getAnimations();

		pChara->m_pMove = pFactory.getMove();

		pChara->m_pPhysicals = pFactory.getPhysicals();

		//pChara->m_pActions = pFactory.getActions();

		pChara->m_pBody = pFactory.getBody();

		return pChara;
	}

};

class CBasePlayerFactory : public CPlayerCreateFactory
{
protected:
	void settingMove(CPlayerCharacter* pPlayerCharacter, float posX, float posY)override;

	void settingTexture(CPlayerCharacter* pPlayerCharacter)override;

	void settingAnimations(CPlayerCharacter* pPlayerCharacter)override;

	void settingPhysicals(CPlayerCharacter* pPlayerCharacter)override;

	void settingActions(CPlayerCharacter* pPlayerCharacter)override;

	void settingBody(CPlayerCharacter* pPlayerCharacter)override;

	void settingInitialize(CPlayerCharacter* pPlayerCharacter)override;
};

//=====================================
//�v���C���[�H��Ǘ�
//=====================================
class CPlayerFactoryManager
{
private:
	//���L�C���X�^���X
	static CPlayerFactoryManager* m_pSharedInstance;

	//�R���X�g���N�^
	CPlayerFactoryManager();

public:
	//�f�X�g���N�^
	~CPlayerFactoryManager();

	//���L�C���X�^���X�̎擾
	static CPlayerFactoryManager* getInstance();

	//���L�C���X�^���X�̔j��
	static void removeInstance();

	//�v���C���[�H��Q
	std::vector<CPlayerFactory*> m_factories;

	/**
	*@desc	�v���C���[�̐���
	*@param	�����ʒux
	*@param	�����ʒuy
	*@return �v���C���[
	*/
	CCharacter* create(float x, float y,CGameEngine& gm);
};

