#pragma once
#include "../../Character/GimmickCharacter/GimmickCharacter.h"
#include "../../Data/Map/Map.h"
#include <map>

class CGimmickPartsFactory : public CCharacterPartsFactory
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

	//衝突判定空間の設定
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

	//衝突判定空間の設定
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

	//衝突判定空間の設定
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

	//衝突判定空間の設定
	void settingCollisionAreas(CGimmickCharacter* pChara)override;

	void settingInitialize(CGimmickCharacter* pChara)override;
};





//ワープ
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
//プレイヤー工場管理
//=====================================
class CGimmickFactoryManager
{
private:
	//共有インスタンス
	static CGimmickFactoryManager* m_pSharedMgr;

	//コンストラクタ
	CGimmickFactoryManager()
	{
		//敵工場群の生成
		this->m_pFactories = new std::map<GIMMICK_TYPE, CGimmickFactory*>();

		//工場を取り付けていく
		//左棘工場の取り付け
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_L] = new CDamageBlockLeftFactory();
		//上棘工場の取り付け
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_T] = new CDamageBlockTopFactory();
		//右棘工場の取り付け
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_R] = new CDamageBlockRightFactory();
		//下棘工場の取り付け
		(*this->m_pFactories)[GIMMICK_TYPE::TOGE_B] = new CDamageBlockBottomFactory();
		//ワープ工場の取り付け
		(*this->m_pFactories)[GIMMICK_TYPE::WORP] = new CWorpFactory();

	}
public:
	//デストラクタ
	~CGimmickFactoryManager()
	{
		//敵工場群の破棄
		std::map<GIMMICK_TYPE, CGimmickFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//敵生成工場群の破棄
		SAFE_DELETE(this->m_pFactories);
	}

	//共有インスタンスの取得
	static CGimmickFactoryManager* getInstance()
	{
		if (CGimmickFactoryManager::m_pSharedMgr == NULL)
		{
			CGimmickFactoryManager::m_pSharedMgr = new CGimmickFactoryManager();
		}
		return CGimmickFactoryManager::m_pSharedMgr;
	}

	//共有インスタンスの破棄
	static void removeInstance()
	{
		SAFE_DELETE(CGimmickFactoryManager::m_pSharedMgr);
	}

private:
	//敵生成工場群
	std::map<GIMMICK_TYPE, CGimmickFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	敵の生成
	*@param	敵タイプ(マップチップID)
	*@param	初期位置X
	*@param	初期位置Y
	*/
	CCharacter* create(GIMMICK_TYPE type, float posX, float posY)
	{
		return (*this->m_pFactories)[type]->create(posX, posY);
	}
};