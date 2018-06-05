#pragma once
#include "../../Character/NotesCharacter/NotesCharacter.h"
#include "../../Data/Map/Map.h"
#include <map>

class CNotesPartsFactory : public CCharacterPartsFactory
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
//親となる工場
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

//アニメーション
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
//プレイヤー工場管理
//=====================================
class CNotesFactoryManager
{
private:
	//共有インスタンス
	static CNotesFactoryManager* m_pSharedMgr;

	//コンストラクタ
	CNotesFactoryManager()
	{
		//敵工場群の生成
		this->m_pFactories = new std::map<NOTES_TYPE, CNotesFactory*>();

		//工場を取り付けていく
		//左棘工場の取り付け
		(*this->m_pFactories)[NOTES_TYPE::ANIMATION] = new CNotesAnimationFactory();

	}
public:
	//デストラクタ
	~CNotesFactoryManager()
	{
		//敵工場群の破棄
		std::map<NOTES_TYPE, CNotesFactory*>::iterator itr = this->m_pFactories->begin();
		while (itr != this->m_pFactories->end())
		{
			SAFE_DELETE(itr->second);
			itr++;
		}
		//敵生成工場群の破棄
		SAFE_DELETE(this->m_pFactories);
	}

	//共有インスタンスの取得
	static CNotesFactoryManager* getInstance()
	{
		if (CNotesFactoryManager::m_pSharedMgr == NULL)
		{
			CNotesFactoryManager::m_pSharedMgr = new CNotesFactoryManager();
		}
		return CNotesFactoryManager::m_pSharedMgr;
	}

	//共有インスタンスの破棄
	static void removeInstance()
	{
		SAFE_DELETE(CNotesFactoryManager::m_pSharedMgr);
	}

private:
	//敵生成工場群
	std::map<NOTES_TYPE, CNotesFactory*>* m_pFactories = NULL;

public:
	/**
	*@desc	敵の生成
	*@param	敵タイプ(マップチップID)
	*@param	初期位置X
	*@param	初期位置Y
	*/
	CCharacter* create(NOTES_TYPE type, float posX, float posY)
	{
		return (*this->m_pFactories)[type]->create(posX, posY);
	}
};
