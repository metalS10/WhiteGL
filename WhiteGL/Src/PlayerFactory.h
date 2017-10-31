#pragma once
#include "PlayerCharacter.h"

class CPlayerPartsFactory : public CCharacterPartsFactory
{
public:
	//アニメーション取得
	 std::vector<CAnimation*>* getAnimations()override;

	//行動取得
	 CMove* getMove()override;

	//重力取得
	 std::vector<CPhysical*>* getPhysicals()override;

	//アクション取得
	 //std::vector<CAction*>* getActions()override;

	//実体取得
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
//プレイヤー工場管理
//=====================================
class CPlayerFactoryManager
{
private:
	//共有インスタンス
	static CPlayerFactoryManager* m_pSharedInstance;

	//コンストラクタ
	CPlayerFactoryManager();

public:
	//デストラクタ
	~CPlayerFactoryManager();

	//共有インスタンスの取得
	static CPlayerFactoryManager* getInstance();

	//共有インスタンスの破棄
	static void removeInstance();

	//プレイヤー工場群
	std::vector<CPlayerFactory*> m_factories;

	/**
	*@desc	プレイヤーの生成
	*@param	初期位置x
	*@param	初期位置y
	*@return プレイヤー
	*/
	CCharacter* create(float x, float y,CGameEngine& gm);
};

