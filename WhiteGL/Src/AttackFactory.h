#pragma once

#include "AttackCharacter.h"
#include "PlayerCharacter.h"
#include <map>



class CAttackPartsFactory : public CCharacterPartsFactory
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

	//衝突判定空間
	std::vector<CCollisionArea*>* getCollisionAreas()
	{
		return new std::vector<CCollisionArea*>();
	}

	int getState();
};


//===================
//敵工場
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

	//衝突判定空間の設定
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

		//衝突判定空間の生成と取り付け
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

	//衝突判定空間の設定
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

	//衝突判定空間の設定
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

		//衝突判定空間の生成と取り付け
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

	//衝突判定空間の設定
	void settingCollisionAreas(CAttackCharacter* pChara)override;

	void settingInitialize(CAttackCharacter* pChara)override;
};
*/
//=====================================
//攻撃工場管理
//=====================================
class CAttackFactoryManager
{
private:
	//共有インスタンス
	static CAttackFactoryManager* m_pSharedMgr;

	//コンストラクタ
	CAttackFactoryManager()
	{
		//敵工場群の生成
		this->m_pFactories = new std::map<ATTACK_TYPE, CAttackFactory*>();

		//工場を取り付けていく
		//クリボー工場の取り付け
		(*this->m_pFactories)[ATTACK_TYPE::NORMAL] = new CNormalAttackFactory();

		(*this->m_pFactories)[ATTACK_TYPE::NOR] = new CNorAttackFactory();

		//(*this->m_pFactories)[ATTACK_TYPE::FIREBALL] = new CFireBallAttackFactory();

	}
public:
	//デストラクタ
	~CAttackFactoryManager()
	{
		//弾工場群の破棄
		std::map<ATTACK_TYPE, CAttackFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//敵生成工場群の破棄
		SAFE_DELETE(this->m_pFactories);
	}

	//共有インスタンスの取得
	static CAttackFactoryManager* getInstance()
	{
		if (CAttackFactoryManager::m_pSharedMgr == NULL)
		{
			CAttackFactoryManager::m_pSharedMgr = new CAttackFactoryManager();
		}
		return CAttackFactoryManager::m_pSharedMgr;
	}

	//共有インスタンスの破棄
	static void removeInstance()
	{
		SAFE_DELETE(CAttackFactoryManager::m_pSharedMgr);
	}

private:
	//敵生成工場群
	std::map<ATTACK_TYPE, CAttackFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	敵の生成
	*@param	敵タイプ(マップチップID)
	*@param	初期位置X
	*@param	初期位置Y
	*/
	CCharacter* create(ATTACK_TYPE type, float posX, float posY, CVec2 vec)
	{
		return (*this->m_pFactories)[type]->create(posX, posY, vec);
	}
};