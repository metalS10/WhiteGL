#pragma once
#include "EnemyCharacter.h"
#include "Map.h"
#include <map>

class CEnemyPartsFactory : public CCharacterPartsFactory
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

	//衝突判定空間の設定
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

		//衝突判定空間の生成と取り付け
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//敵の体力の設定
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//敵の体力の設定
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//敵の体力の設定
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//敵の体力の設定
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//敵の体力の設定
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

	//衝突判定空間の設定
	void settingCollisionAreas(CEnemyCharacter* pChara)override;

	void settingInitialize(CEnemyCharacter* pChara)override;

	//敵の体力の設定
	void settingState(CEnemyCharacter* pChara)override;
};

//=====================================
//プレイヤー工場管理
//=====================================
class CEnemyFactoryManager
{
private:
	//共有インスタンス
	static CEnemyFactoryManager* m_pSharedMgr;

	//コンストラクタ
	CEnemyFactoryManager()
	{
		//敵工場群の生成
		this->m_pFactories = new std::map<ENEMY_TYPE, CEnemyFactory*>();

		//工場を取り付けていく
		//クリボー工場の取り付け
		(*this->m_pFactories)[ENEMY_TYPE::KURIBO] = new CKuriboFactory();
		//ノコノコ工場の取り付け
		(*this->m_pFactories)[ENEMY_TYPE::NOKONOKO] = new CGreenNokoNokoFactory();
		//パタパタ工場の取り付け
		(*this->m_pFactories)[ENEMY_TYPE::PATAPATA] = new CGreenPataPataFactory();
		//キラー砲台工場の取り付け
		(*this->m_pFactories)[ENEMY_TYPE::KILLERHODAI] = new CKillerHoudaiFactory();
		//キラー工場の取り付け
		(*this->m_pFactories)[ENEMY_TYPE::KILLER] = new CKillerFactory();
		//トロくない木馬工場の取り付け
		(*this->m_pFactories)[ENEMY_TYPE::TROI] = new CTRoiFactory();
	}

public:
	//デストラクタ
	~CEnemyFactoryManager()
	{
		//敵工場群の破棄
		std::map<ENEMY_TYPE, CEnemyFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//敵生成工場群の破棄
		SAFE_DELETE(this->m_pFactories);
	}

	//共有インスタンスの取得
	static CEnemyFactoryManager* getInstance()
	{
		if (CEnemyFactoryManager::m_pSharedMgr == NULL)
		{
			CEnemyFactoryManager::m_pSharedMgr = new CEnemyFactoryManager();
		}
		return CEnemyFactoryManager::m_pSharedMgr;
	}

	//共有インスタンスの破棄
	static void removeInstance()
	{
		SAFE_DELETE(CEnemyFactoryManager::m_pSharedMgr);
	}

private:
	//敵生成工場群
	std::map<ENEMY_TYPE, CEnemyFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	敵の生成
	*@param	敵タイプ(マップチップID)
	*@param	初期位置X
	*@param	初期位置Y
	*/
	CCharacter* create(ENEMY_TYPE type, float posX, float posY)
	{
		return (*this->m_pFactories)[type]->create(posX, posY);
	}
};