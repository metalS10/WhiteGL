#include "EnemyBulletFactory.h"

std::vector<CAnimation*>* CEnemyBulletPartsFactory::getAnimations()
{
	//アニメーションデータ群の生成
	//std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//アニメーションデータ群の作成
	return new std::vector<CAnimation*>;

}

CMove* CEnemyBulletPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CEnemyBulletPartsFactory::getPhysicals()
{
	//適用させる物理演算作成
	return new std::vector<CPhysical*>;
}

std::vector<CAction*>* CEnemyBulletPartsFactory::getActions()
{
	//行えるアクション群を作成
	return new std::vector<CAction*>;
}

CBody* CEnemyBulletPartsFactory::getBody()
{
	return new CBody();
}


CCharacter* CEnemyBulletFactory::create(float posX, float posY, CVec2 vec)
{
	CEnemyBulletCharacter* pChara = this->createEnemyBullet();

	//==============================================
	//インスタンスに値を設定していく
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara,vec);

	this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//初期化
	this->settingInitialize(pChara);

	this->settingState(pChara);

	return pChara;
}

//========================================
//
//ノーマル弾の生成工場
//
//========================================
//移動データの設定
void CNormalEnemyBulletFactory::settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//テクスチャの設定
void CNormalEnemyBulletFactory::settingTexture(CEnemyBulletCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_NORMAL_FIRE);
}

//アニメーションの設定
void CNormalEnemyBulletFactory::settingAnimations(CEnemyBulletCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 16, 16));
}

//物理演算の設定
void CNormalEnemyBulletFactory::settingPhysicals(CEnemyBulletCharacter* pChara)
{
	
}

//アクションの設定
void CNormalEnemyBulletFactory::settingActions(CEnemyBulletCharacter* pChara, CVec2 vec)
{
	//敵死亡アクションを0番で設定
	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos, vec.x,vec.y));

}

//実体の設定
void CNormalEnemyBulletFactory::settingBody(CEnemyBulletCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//衝突判定空間の設定
void CNormalEnemyBulletFactory::settingCollisionAreas(CEnemyBulletCharacter* pChara)
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

	/*
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
	*/


	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CNormalEnemyBulletFactory::settingInitialize(CEnemyBulletCharacter* pChara)
{

	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());

}

void CNormalEnemyBulletFactory::settingState(CEnemyBulletCharacter* pChara)
{
	//自然消滅する時間
	pChara->m_DeleteTime = 180;

	//攻撃力
	pChara->m_attackPoint = 10;
}

//========================================
//
//ノーマル弾改の生成工場
//
//========================================
//移動データの設定
void CCustomEnemyBulletFactory::settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//テクスチャの設定
void CCustomEnemyBulletFactory::settingTexture(CEnemyBulletCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_NORMAL_FIRE);
}

//アニメーションの設定
void CCustomEnemyBulletFactory::settingAnimations(CEnemyBulletCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0.0f, 0.0f, 16.0f, 16.0f));
}

//物理演算の設定
void CCustomEnemyBulletFactory::settingPhysicals(CEnemyBulletCharacter* pChara)
{
	pChara->m_pPhysicals->push_back(new CPhysicalGravity(-0.15f));
}

//アクションの設定
void CCustomEnemyBulletFactory::settingActions(CEnemyBulletCharacter* pChara, CVec2 vec)
{
	//敵死亡アクションを0番で設定
	pChara->m_pActions->push_back(new CActionCurve(pChara->m_pMove->m_pos, vec.x,vec.y));

}

//実体の設定
void CCustomEnemyBulletFactory::settingBody(CEnemyBulletCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//衝突判定空間の設定
void CCustomEnemyBulletFactory::settingCollisionAreas(CEnemyBulletCharacter* pChara)
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
	/*
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
	*/


	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CCustomEnemyBulletFactory::settingInitialize(CEnemyBulletCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

void CCustomEnemyBulletFactory::settingState(CEnemyBulletCharacter* pChara)
{
	//自然消滅する時間
	pChara->m_DeleteTime = 180;

	//攻撃力
	pChara->m_attackPoint = 10;
}



//========================================
//
//ファイアボールの生成工場
//
//========================================
//移動データの設定
void CFireBallEnemyBulletFactory::settingMove(CEnemyBulletCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	//pChara->m_pMove->m_vel.set(0.0f, 0.0f);

}

//テクスチャの設定
void CFireBallEnemyBulletFactory::settingTexture(CEnemyBulletCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_FIREBALL);
}

//アニメーションの設定
void CFireBallEnemyBulletFactory::settingAnimations(CEnemyBulletCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(5, true));



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0.0f, 0.0f, 16.0f, 16.0f));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(16.0f, 0.0f, 16.0f, 16.0f));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32.0f, 0.0f, 16.0f, 16.0f));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(48.0f, 0.0f, 16.0f, 16.0f));

}

//物理演算の設定
void CFireBallEnemyBulletFactory::settingPhysicals(CEnemyBulletCharacter* pChara)
{
	pChara->m_pPhysicals->push_back(new CPhysicalGravity(-0.15f));
}

//アクションの設定
void CFireBallEnemyBulletFactory::settingActions(CEnemyBulletCharacter* pChara, CVec2 vec)
{
	float velX = 3.0f * vec.x;
	pChara->m_pActions->push_back(new CActionJump(4.0f,3.0f));

	pChara->m_pActions->push_back(new CActionMoveStraight(pChara->m_pMove->m_pos, velX));
}

//実体の設定
void CFireBallEnemyBulletFactory::settingBody(CEnemyBulletCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-8, 8, 8, -8);
}

//衝突判定空間の設定
void CFireBallEnemyBulletFactory::settingCollisionAreas(CEnemyBulletCharacter* pChara)
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

	/*
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
	*/


	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CFireBallEnemyBulletFactory::settingInitialize(CEnemyBulletCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

void CFireBallEnemyBulletFactory::settingState(CEnemyBulletCharacter* pChara)
{
	//自然消滅する時間
	pChara->m_DeleteTime = 180;

	//攻撃力
	pChara->m_attackPoint = 1;
}



//=======================================================
//敵生成工場管理
//=======================================================
//共有インスタンス本体の宣言
CEnemyBulletFactoryManager* CEnemyBulletFactoryManager::m_pSharedMgr = NULL;