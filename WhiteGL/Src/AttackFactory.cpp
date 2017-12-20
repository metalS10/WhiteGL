#include "AttackFactory.h"

std::vector<CAnimation*>* CAttackPartsFactory::getAnimations()
{
	//アニメーションデータ群の生成
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//アニメーションデータ群の作成
	return new std::vector<CAnimation*>;

}

CMove* CAttackPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CAttackPartsFactory::getPhysicals()
{
	//適用させる物理演算作成
	return new std::vector<CPhysical*>;
}

std::vector<CAction*>* CAttackPartsFactory::getActions()
{
	//行えるアクション群を作成
	return new std::vector<CAction*>;
}


CBody* CAttackPartsFactory::getBody()
{
	return new CBody();
}

int CAttackPartsFactory::getState()
{
	return int();
}


CCharacter* CAttackFactory::create(float posX, float posY, CVec2 vec)
{
	CAttackCharacter* pChara = this->createAttack();

	//==============================================
	//インスタンスに値を設定していく
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara, vec);

	this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//初期化
	this->settingInitialize(pChara);

	this->settingState(pChara);

	return pChara;
}

//========================================
//
//通常攻撃の生成工場
//
//========================================
//移動データの設定
void CNormalAttackFactory::settingMove(CAttackCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//テクスチャの設定
void CNormalAttackFactory::settingTexture(CAttackCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_NORMALATTACK);
}

//アニメーションの設定
void CNormalAttackFactory::settingAnimations(CAttackCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(5, false));



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 48, 16));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(48, 0, 48, 16));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 48, 16));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(144, 0, 48, 16));

}

//物理演算の設定
void CNormalAttackFactory::settingPhysicals(CAttackCharacter* pChara)
{

}

//アクションの設定

void CNormalAttackFactory::settingActions(CAttackCharacter* pChara, CVec2 vec)
{
	//攻撃の移動速度
	float velX = 0 * vec.x;
	//敵死亡アクションを0番で設定
	//posに向きを兼ね備えたplayerの先を渡している
	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos + (vec * 60.0f), velX));
}


//実体の設定
void CNormalAttackFactory::settingBody(CAttackCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//衝突判定空間の設定
void CNormalAttackFactory::settingCollisionAreas(CAttackCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pOutOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	CCollisionTerritory* pOutOfScreenBttomTerritory = new CCollisionTerritoryOutOfScreenBottom();
	pOutOfScreenBttomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenBttomTerritory);


	//画面上端の領域を設定
	pOutOfScreenArea->addTerritory(new CCollisionTerritoryOutOfScreenTop());

	//画面右端の領域を設定
	CCollisionTerritory* pOutOfScreenRightTerritory = new CCollisionTerritoryOutOfScreenRight();
	pOutOfScreenRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenRightTerritory);

	//画面左端の領域を設定
	CCollisionTerritory* pOutOfScreenLeftTerritory = new CCollisionTerritoryOutOfScreenLeft();
	pOutOfScreenLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenLeftTerritory);

	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pOutOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	
	//下のマップチップ領域を設定
	CCollisionTerritory* pMapChipBottomTerritory = new CCollisionTerritoryMapChipBottom();
	pMapChipBottomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pMapArea->addTerritory(pMapChipBottomTerritory);

	//右のマップチップ領域を設定
	CCollisionTerritory* pMapChipRightTerritory = new CCollisionTerritoryMapChipRight();
	pMapChipRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pMapArea->addTerritory(pMapChipRightTerritory);

	//左のマップチップ領域を設定
	CCollisionTerritory* pMapChipLeftTerritory = new CCollisionTerritoryMapChipLeft();
	pMapChipLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pMapArea->addTerritory(pMapChipLeftTerritory);



	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
	
}

//初期化設定
void CNormalAttackFactory::settingInitialize(CAttackCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//位置を設定
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());

}

void CNormalAttackFactory::settingState(CAttackCharacter* pChara)
{
	//自然消滅する時間
	pChara->m_DeleteTime = 20;

	//攻撃力
	pChara->m_attackPoint = 1;
}


//========================================
//
//nor攻撃の生成工場
//
//========================================
//移動データの設定
void CNorAttackFactory::settingMove(CAttackCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	//pChara->m_pMove->m_vel.set(5.0f, 0.0f);

}

//テクスチャの設定
void CNorAttackFactory::settingTexture(CAttackCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_GETSUGATENSHO);
}

//アニメーションの設定
void CNorAttackFactory::settingAnimations(CAttackCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(3, false));



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(42, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(84, 0, 42, 100));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(126, 0, 42, 100));

}

//物理演算の設定
void CNorAttackFactory::settingPhysicals(CAttackCharacter* pChara)
{

}

//アクションの設定
void CNorAttackFactory::settingActions(CAttackCharacter* pChara, CVec2 vec)
{
	//攻撃の移動速度
	float velX = 20 * vec.x;
	//敵死亡アクションを0番で設定
	//posに向きを兼ね備えたplayerの先を渡している
	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos + (vec * 30.0f), velX));

}


//実体の設定
void CNorAttackFactory::settingBody(CAttackCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-21, 50, 21, -50);
}

//衝突判定空間の設定
void CNorAttackFactory::settingCollisionAreas(CAttackCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pOutOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	CCollisionTerritory* pOutOfScreenBttomTerritory = new CCollisionTerritoryOutOfScreenBottom();
	pOutOfScreenBttomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenBttomTerritory);


	//画面上端の領域を設定
	pOutOfScreenArea->addTerritory(new CCollisionTerritoryOutOfScreenTop());

	//画面右端の領域を設定
	CCollisionTerritory* pOutOfScreenRightTerritory = new CCollisionTerritoryOutOfScreenRight();
	pOutOfScreenRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenRightTerritory);

	//画面左端の領域を設定
	CCollisionTerritory* pOutOfScreenLeftTerritory = new CCollisionTerritoryOutOfScreenLeft();
	pOutOfScreenLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pOutOfScreenArea->addTerritory(pOutOfScreenLeftTerritory);

	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pOutOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	
	//下のマップチップ領域を設定
	CCollisionTerritory* pMapChipBottomTerritory = new CCollisionTerritoryMapChipBottom();
	pMapChipBottomTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	pMapArea->addTerritory(pMapChipBottomTerritory);

	//右のマップチップ領域を設定
	CCollisionTerritory* pMapChipRightTerritory = new CCollisionTerritoryMapChipRight();
	pMapChipRightTerritory->setEventCallback(&CCharacter::collisionRightCallback);
	pMapArea->addTerritory(pMapChipRightTerritory);

	//左のマップチップ領域を設定
	CCollisionTerritory* pMapChipLeftTerritory = new CCollisionTerritoryMapChipLeft();
	pMapChipLeftTerritory->setEventCallback(&CCharacter::collisionLeftCallback);
	pMapArea->addTerritory(pMapChipLeftTerritory);



	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
	
}

//初期化設定
void CNorAttackFactory::settingInitialize(CAttackCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//位置を設定
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());

}

void CNorAttackFactory::settingState(CAttackCharacter* pChara)
{
	//自然消滅する時間
	pChara->m_DeleteTime = 30;

	//攻撃力
	pChara->m_attackPoint = 10;
}


//=======================================================
//攻撃生成工場管理
//=======================================================
//共有インスタンス本体の宣言
CAttackFactoryManager* CAttackFactoryManager::m_pSharedMgr = NULL;