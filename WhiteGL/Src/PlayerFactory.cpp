#include "PlayerFactory.h"
//#include "Model/Character/AttackCharacter/AttackCharacter.h"

//==================================================
//プレイヤー工場
//==================================================


std::vector<CAnimation*>* CPlayerPartsFactory::getAnimations()
{
	//アニメーションデータ群の生成
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//直立アニメーションの設定
	//m_pAnimations->push_back(new CChipListAnimation(10,true));
	m_pAnimations->push_back(new CNotAnimation());

	//歩行アニメーションの設定
	m_pAnimations->push_back(new CListAnimation(10, true));
	//ダメージを受けた時のアニメーションの設定
	m_pAnimations->push_back(new CNotAnimation());
	//落ちている時のアニメーションの設定
	m_pAnimations->push_back(new CNotAnimation());
	//攻撃アニメーション
	m_pAnimations->push_back(new CListAnimation(10,false));
	m_pAnimations->push_back(new CListAnimation(10, false));
	//回避状態
	m_pAnimations->push_back(new CNotAnimation());
	//ダッシュアニメーションの設定
	m_pAnimations->push_back(new CListAnimation(10, true));
	//回避中ジャンプアニメーションの設定
	m_pAnimations->push_back(new CNotAnimation());
	//回避落ちている時のアニメーションの設定
	m_pAnimations->push_back(new CNotAnimation());

	return m_pAnimations;
}

CMove* CPlayerPartsFactory::getMove()
{
	return new CMove();
}

std::vector<CPhysical*>* CPlayerPartsFactory::getPhysicals()
{
	std::vector<CPhysical*>* m_pPhysicals;

	//適応させる物理演算作成
	m_pPhysicals = new std::vector<CPhysical*>();
	//重力演算の設定
	m_pPhysicals->push_back(new CPhysicalGravity());
	//摩擦演算の設定
	//maxspeed
	m_pPhysicals->push_back(new CPhysicalFriction(10));

	return m_pPhysicals;
}
/*
std::vector<CAction*>* CPlayerPartsFactory::getActions()
{
	std::vector<CAction*>* m_pActions;

	//行えるアクション軍を作成
	m_pActions = new std::vector<CAction*>();
	//ジャンプアクションを設定
	m_pActions->push_back(new CActionJump(4.0f, 3));
	//弾発射アクションを設定
	m_pActions->push_back(new CActionShotBullet((int)ATTACK_TYPE::NORMAL, 20));

	m_pActions->push_back(new CActionShotBullet((int)ATTACK_TYPE::NOR, 20));

	m_pActions->push_back(new CActionShotBullet((int)ATTACK_TYPE::FIREBALL, 20));
	//SuperJump
	m_pActions->push_back(new CActionJump(12.0f, 1));

	return m_pActions;
}
*/
CBody* CPlayerPartsFactory::getBody()
{
	return new CBody();
}



CCharacter* CPlayerFactory::create(float posX,float posY)
{
	CPlayerCharacter* pChara = this->createPlayer();

	//==============================================
	//インスタンスに値を設定していく
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara);

	this->settingBody(pChara);

	//初期化
	this->settingInitialize(pChara);

	return pChara;
}


//============================
//基本プレイヤー工場
//============================

void CBasePlayerFactory::settingMove(CPlayerCharacter* pPlayerCharacter, float posX, float posY)
{
	pPlayerCharacter->m_pMove->m_pos.set(posX, posY);
}

void CBasePlayerFactory::settingTexture(CPlayerCharacter* pPlayerCharacter)
{
	pPlayerCharacter->setTexture(IMAGE_PLAYER);
}

void CBasePlayerFactory::settingAnimations(CPlayerCharacter* pPlayerCharacter)
{
	//直立アニメーションに設定するためのチップデータの設定
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(0, 0, 64, 64));
	/*
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64 * 2, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64 * 3, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::STAND]->addChipData(new CChip(64 * 4, 0, 64, 64));
	*/


	//歩行アニメーションに設定する1枚目のチップデータの作成
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::WALK]->addChipData(new CChip(64, 0, 64, 64));
	//歩行アニメーションに設定する2枚目のチップデータの作成
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::WALK]->addChipData(new CChip(128, 0, 64, 64));


	//ダメージを受けたときのアニメーションに設定するためのチップデータの設定
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::DAMAGE]->addChipData(new CChip(192, 0, 64, 64));

	//落ちているときのアニメーションに設定するためのチップデータの設定
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::FALING]->addChipData(new CChip(256, 0, 64, 64));

	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::ATTACK]->addChipData(new CChip(192, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::ATTACK]->addChipData(new CChip(256, 0, 64, 64));

	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::NOR]->addChipData(new CChip(192, 0, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::NOR]->addChipData(new CChip(256, 0, 64, 64));
	
	//回避中のチップデータ
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::AVOIDANCE]->addChipData(new CChip(0, 64, 64, 64));

	//ダッシュアニメーションに設定する1枚目のチップデータの作成
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::DASH]->addChipData(new CChip(64, 64, 64, 64));
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::DASH]->addChipData(new CChip(128, 64, 64, 64));

	//回避中ジャンプ
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::SUPERJUMP]->addChipData(new CChip(0, 64, 64, 64));

	//回避中落ちるチップデータ
	(*pPlayerCharacter->m_pAnimations)[(int)CPlayerCharacter::STATE::SUPERFALING]->addChipData(new CChip(192, 64, 64, 64));


}

void CBasePlayerFactory::settingPhysicals(CPlayerCharacter* pPlayerCharacter)
{

}


void CBasePlayerFactory::settingActions(CPlayerCharacter* pPlayerCharacter)
{

}

void CBasePlayerFactory::settingBody(CPlayerCharacter* pPlayerCharacter)
{
	pPlayerCharacter->m_pBody->set(-32, 32, 32, -32);
}

void CBasePlayerFactory::settingInitialize(CPlayerCharacter* pPlayerCharacter)
{
	//状態の設定
	pPlayerCharacter->m_state = (int)CPlayerCharacter::STATE::FALING;

	//有効フラグを立てる
	pPlayerCharacter->m_activeFlag = true;

	/*
	*計算データのままで起動すると1フレームズレが発生するので
	*初期化時の最後に値をSpriteに反映する
	*/
	pPlayerCharacter->applyFunc();

	//=================================================
	//衝突判定空間の生成
	//=================================================
	pPlayerCharacter->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//=================================================
	//画面端衝突空間の生成
	//=================================================
	//Bodyを送る
	CCollisionArea* pEndOfScreeArea = new CCollisionAreaEndOfScreen(pPlayerCharacter->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	CCollisionTerritory* pEndOfScreenBttomTerritory = new CCollisionTerritoryEndOfScreenBottom();

	//画面下端と衝突した際のイベントを設定
	pEndOfScreenBttomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);


	//画面下端の領域を設定
	pEndOfScreeArea->addTerritory(pEndOfScreenBttomTerritory);

	CCollisionTerritory* pEndOfScreenLeftTerritory = new CCollisionTerritoryEndOfScreenLeft();

	//画面下端の領域を設定
	pEndOfScreeArea->addTerritory(pEndOfScreenLeftTerritory);


	//画面端の衝突空間に衝突を行う下の基準点を設定		CollisionArea.h
	//pEndOfScreeArea->addBasePoint(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, cocos2d::Point(0, -32)));


	//画面端の衝突空間を取り付ける
	pPlayerCharacter->m_pCollisionAreas->push_back(pEndOfScreeArea);

	//==================================================
	//マップ衝突空間の生成
	//==================================================
	//Bodyを送る
	CCollisionArea* pMapArea = new CCollisionAreaMap(pPlayerCharacter->m_pBody);



	
	/*		CollisionArea.h
	//基準点の設定
	//下のマップチップ衝突空間に衝突を行う下の基準点を設定(下に落ちないようにxをちょっとずらす)
	pMapArea->addBasePoint(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, cocos2d::Point(16, -32)));
	//下のマップチップ衝突空間に衝突を行う下の基準点を設定(下に落ちないようにxをちょっとずらす)
	pMapArea->addBasePoint(new CCollisionBasePoint(TERRITORY_TYPE::BOTTOM, cocos2d::Point(-16, -32)));
	*/
	//画面端の衝突空間を取り付ける
	pPlayerCharacter->m_pCollisionAreas->push_back(pMapArea);

	
}


//享有インスタンス
CPlayerFactoryManager* CPlayerFactoryManager::m_pSharedInstance = NULL;

//コンストラクタ
CPlayerFactoryManager::CPlayerFactoryManager()
{
	//基本的なプレイヤー工場の生成と取り付け
	this->m_factories.push_back(new CBasePlayerFactory());
}

//デストラクタ
CPlayerFactoryManager::~CPlayerFactoryManager()
{
	for (CPlayerFactory* pFactory : this->m_factories)
	{
		SAFE_DELETE(pFactory);
	}
}

//共有インスタンスの取得
CPlayerFactoryManager* CPlayerFactoryManager::getInstance()
{
	if (CPlayerFactoryManager::m_pSharedInstance == NULL)
	{
		CPlayerFactoryManager::m_pSharedInstance = new CPlayerFactoryManager();
	}
	return CPlayerFactoryManager::m_pSharedInstance;
}

//共有インスタンスの破棄
void CPlayerFactoryManager::removeInstance()
{
	SAFE_DELETE(CPlayerFactoryManager::m_pSharedInstance);
}

/**
*@desc	プレイヤーの生成
*@param	初期位置x
*@param	初期位置y
*@return プレイヤー
*/
CCharacter* CPlayerFactoryManager::create(float x, float y)
{
	return this->m_factories[0]->create(x, y);
}

