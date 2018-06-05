#pragma once

#include "../../Character/EnemyBulletCharacter/EnemyBulletCharacter.h"
#include "../../Character/PlayerCharacter/PlayerCharacter.h"
#include <map>



class CEnemyBulletPartsFactory : public CCharacterPartsFactory
{
public:
	//アニメーション取得
	std::vector<CAnimation*>* getAnimations()override;

	//行動取得
	CMove* getMove()override;

	//重力取得
	std::vector<CPhysical*>* getPhysicals()override;

	//アクション取得
	std::vector<CAction*>* getActions()override;


	//音に合わせて動くアクション取得
	std::vector<CNotes*>* getNotes() override;

	//実体取得
	CBody* getBody()override;

	//衝突判定空間
	std::vector<CCollisionArea*>* getCollisionAreas()
	{
		return new std::vector<CCollisionArea*>();
	}
};


//===================
//敵工場
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

	//衝突判定空間の設定
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

		//衝突判定空間の生成と取り付け
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

	//衝突判定空間の設定
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

	//衝突判定空間の設定
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

		//衝突判定空間の生成と取り付け
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyBulletCharacter* pChara)override;

	void settingInitialize(CEnemyBulletCharacter* pChara)override;

	void settingState(CEnemyBulletCharacter* pChara) override;
};



//=====================================
//プレイヤー工場管理
//=====================================
class CEnemyBulletFactoryManager
{
private:
	//共有インスタンス
	static CEnemyBulletFactoryManager* m_pSharedMgr;

	//コンストラクタ
	CEnemyBulletFactoryManager()
	{
		//敵工場群の生成
		this->m_pFactories = new std::map<BULLET_TYPE, CEnemyBulletFactory*>();

		//工場を取り付けていく
		//クリボー工場の取り付け
		(*this->m_pFactories)[BULLET_TYPE::NORMAL] = new CNormalEnemyBulletFactory();

		(*this->m_pFactories)[BULLET_TYPE::CUSTOM] = new CCustomEnemyBulletFactory();

		(*this->m_pFactories)[BULLET_TYPE::FIREBALL] = new CFireBallEnemyBulletFactory();

	}
public:
	//デストラクタ
	~CEnemyBulletFactoryManager()
	{
		//弾工場群の破棄
		std::map<BULLET_TYPE, CEnemyBulletFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//敵生成工場群の破棄
		SAFE_DELETE(this->m_pFactories);
	}

	//共有インスタンスの取得
	static CEnemyBulletFactoryManager* getInstance()
	{
		if (CEnemyBulletFactoryManager::m_pSharedMgr == NULL)
		{
			CEnemyBulletFactoryManager::m_pSharedMgr = new CEnemyBulletFactoryManager();
		}
		return CEnemyBulletFactoryManager::m_pSharedMgr;
	}

	//共有インスタンスの破棄
	static void removeInstance()
	{
		SAFE_DELETE(CEnemyBulletFactoryManager::m_pSharedMgr);
	}

private:
	//敵生成工場群
	std::map<BULLET_TYPE, CEnemyBulletFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	敵の生成
	*@param	敵タイプ(マップチップID)
	*@param	初期位置X
	*@param	初期位置Y
	*/
	CCharacter* create(BULLET_TYPE type, float posX, float posY,CVec2 vec)
	{
		return (*this->m_pFactories)[type]->create(posX, posY,vec);
	}
};