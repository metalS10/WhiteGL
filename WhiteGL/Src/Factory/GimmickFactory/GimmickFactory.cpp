#include "GimmickFactory.h"

//==================================================
//プレイヤー工場
//==================================================


std::vector<CAnimation*>* CGimmickPartsFactory::getAnimations()
{
	//アニメーションデータ群の生成
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//アニメーションデータ群の作成
	return new std::vector<CAnimation*>;

}

CMove* CGimmickPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CGimmickPartsFactory::getPhysicals()
{
	//適用させる物理演算作成
	return new std::vector<CPhysical*>;
}
std::vector<CAction*>* CGimmickPartsFactory::getActions()
{
	//行えるアクション群を作成
	return new std::vector<CAction*>;
}

CBody* CGimmickPartsFactory::getBody()
{
	return new CBody();
}


CCharacter* CGimmickFactory::create(float posX, float posY)
{
	CGimmickCharacter* pChara = this->createGimmick();

	//==============================================
	//インスタンスに値を設定していく
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara);

	this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//初期化
	this->settingInitialize(pChara);

	return pChara;
}

//========================================
//
//左棘ブロックの生成工場
//
//========================================
//移動データの設定
void CDamageBlockLeftFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CDamageBlockLeftFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//アニメーションの設定
void CDamageBlockLeftFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
}

//物理演算の設定
void CDamageBlockLeftFactory::settingPhysicals(CGimmickCharacter* pChara)
{
	
}

//アクションの設定
void CDamageBlockLeftFactory::settingActions(CGimmickCharacter* pChara)
{

}

//実体の設定
void CDamageBlockLeftFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CDamageBlockLeftFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterLeft();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionLeftCallback);

	//下のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//上のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(pCharacterTerritory);



	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CDamageBlockLeftFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//上棘ブロックの生成工場
//
//========================================
//移動データの設定
void CDamageBlockTopFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CDamageBlockTopFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//アニメーションの設定
void CDamageBlockTopFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
}

//物理演算の設定
void CDamageBlockTopFactory::settingPhysicals(CGimmickCharacter* pChara)
{
	
}

//アクションの設定
void CDamageBlockTopFactory::settingActions(CGimmickCharacter* pChara)
{

}

//実体の設定
void CDamageBlockTopFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CDamageBlockTopFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterTop();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionTopCallback);

	//下のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritory);



	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CDamageBlockTopFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//右棘ブロックの生成工場
//
//========================================
//移動データの設定
void CDamageBlockRightFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CDamageBlockRightFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//アニメーションの設定
void CDamageBlockRightFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
}

//物理演算の設定
void CDamageBlockRightFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CDamageBlockRightFactory::settingActions(CGimmickCharacter* pChara)
{

}

//実体の設定
void CDamageBlockRightFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CDamageBlockRightFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterRight();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionRightCallback);

	//下のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//上のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//イベントトリガー呼び出すやつ
	pCharacterArea->addTerritory(pCharacterTerritory);



	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CDamageBlockRightFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//下棘ブロックの生成工場
//
//========================================
//移動データの設定
void CDamageBlockBottomFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CDamageBlockBottomFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_DAMAGEBLOCK);
}

//アニメーションの設定
void CDamageBlockBottomFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());



	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));
}

//物理演算の設定
void CDamageBlockBottomFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CDamageBlockBottomFactory::settingActions(CGimmickCharacter* pChara)
{

}

//実体の設定
void CDamageBlockBottomFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CDamageBlockBottomFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterBottom();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionBottomCallback);

	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//上のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritory);

	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CDamageBlockBottomFactory::settingInitialize(CGimmickCharacter* pChara)
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



//========================================
//
//回転ブロックの生成工場
//
//========================================
//移動データの設定
void CRollBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CRollBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_ROLLBLOCK);
}

//アニメーションの設定
void CRollBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());
	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));

	//回るアニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[1]->addChipData(new CChip(96, 0, 32, 32));
}

//物理演算の設定
void CRollBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CRollBlockFactory::settingActions(CGimmickCharacter* pChara)
{
	pChara->m_pActions->push_back(new CActionRoll());
}

//実体の設定
void CRollBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CRollBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterBottom();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//上のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritory);
	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CRollBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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

//========================================
//
//ちくわブロックの生成工場
//
//========================================
//移動データの設定
void CTikuwaBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CTikuwaBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_TIKUWABLOCK);
}

//アニメーションの設定
void CTikuwaBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());
	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
}

//物理演算の設定
void CTikuwaBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CTikuwaBlockFactory::settingActions(CGimmickCharacter* pChara)
{
	pChara->m_pActions->push_back(new CActionDown());
}

//実体の設定
void CTikuwaBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CTikuwaBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterTop();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionTopCallback);
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//下のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritory);
	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CTikuwaBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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

//========================================
//
//音符ブロックの生成工場
//
//========================================
//移動データの設定
void CNoteBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CNoteBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_NOTEBLOCK);
}

//アニメーションの設定
void CNoteBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(10,true));
	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));

}

//物理演算の設定
void CNoteBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CNoteBlockFactory::settingActions(CGimmickCharacter* pChara)
{

}

//実体の設定
void CNoteBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(0, 0, 0, 0);
}

//衝突判定空間の設定
void CNoteBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterTop();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionTopCallback);
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//下のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterBottom());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritory);
	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CNoteBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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


//========================================
//
//はてなブロックの生成工場
//
//========================================
//移動データの設定
void CHatenaBlockFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CHatenaBlockFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_HATENABLOCK);
}

//アニメーションの設定
void CHatenaBlockFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));

	pChara->m_pAnimations->push_back(new CChipNotAnimation());

	(*pChara->m_pAnimations)[1]->addChipData(new CChip(128, 0, 32, 32));
}

//物理演算の設定
void CHatenaBlockFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CHatenaBlockFactory::settingActions(CGimmickCharacter* pChara)
{
	int enemy = rand() % 4;
	switch (enemy)
	{
	case 0:
		enemy = (int)ENEMY_TYPE::KURIBO;
		break;
	case 1:
		enemy = (int)ENEMY_TYPE::NOKONOKO;
		break;
	case 2:
		enemy = (int)ENEMY_TYPE::PATAPATA;
		break;
	case 3:
		enemy = (int)ENEMY_TYPE::KILLERHODAI;
		break;
	default:
		break;
	}
	pChara->m_pActions->push_back(new CActionCreateCharacter(enemy));
}

//実体の設定
void CHatenaBlockFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CHatenaBlockFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritory = new CCollisionTerritoryCharacterBottom();

	pCharacterTerritory->setEventCallback(&CCharacter::collisionBottomCallback);
	//左のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterLeft());
	//上のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterTop());
	//右のマップチップ領域を設定
	pCharacterArea->addTerritory(new CCollisionTerritoryCharacterRight());
	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritory);
	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CHatenaBlockFactory::settingInitialize(CGimmickCharacter* pChara)
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

//========================================
//
//ワープの生成工場
//
//========================================
//移動データの設定
void CWorpFactory::settingMove(CGimmickCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX + 14, posY + 10);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CWorpFactory::settingTexture(CGimmickCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_WORP);
}

//アニメーションの設定
void CWorpFactory::settingAnimations(CGimmickCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 54, 54));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(54, 0, 54, 54));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(108, 0, 54, 54));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(162, 0, 54, 54));

}

//物理演算の設定
void CWorpFactory::settingPhysicals(CGimmickCharacter* pChara)
{

}

//アクションの設定
void CWorpFactory::settingActions(CGimmickCharacter* pChara)
{
	
}

//実体の設定
void CWorpFactory::settingBody(CGimmickCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CWorpFactory::settingCollisionAreas(CGimmickCharacter* pChara)
{
	pChara->m_pCollisionAreas = new std::vector<CCollisionArea*>();

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pCharacterArea = new CCollisionAreaCharacter(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	CCollisionTerritory* pCharacterTerritoryB = new CCollisionTerritoryCharacterBottom();
	pCharacterTerritoryB->setEventCallback(&CCharacter::collisionBottomCallback);

	//左のマップチップ領域を設定
	CCollisionTerritory* pCharacterTerritoryL = new CCollisionTerritoryCharacterLeft();
	pCharacterTerritoryL->setEventCallback(&CCharacter::collisionBottomCallback);

	//上のマップチップ領域を設定
	CCollisionTerritory* pCharacterTerritoryT = new CCollisionTerritoryCharacterTop();
	pCharacterTerritoryT->setEventCallback(&CCharacter::collisionBottomCallback);

	//右のマップチップ領域を設定
	CCollisionTerritory* pCharacterTerritoryR = new CCollisionTerritoryCharacterRight();
	pCharacterTerritoryR->setEventCallback(&CCharacter::collisionBottomCallback);

	//イベントトリガーを呼ぶやつ
	pCharacterArea->addTerritory(pCharacterTerritoryB);
	pCharacterArea->addTerritory(pCharacterTerritoryL);
	pCharacterArea->addTerritory(pCharacterTerritoryT);
	pCharacterArea->addTerritory(pCharacterTerritoryR);
	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pCharacterArea);
}

//初期化設定
void CWorpFactory::settingInitialize(CGimmickCharacter* pChara)
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





//=======================================================
//敵生成工場管理
//=======================================================
//共有インスタンス本体の宣言
CGimmickFactoryManager* CGimmickFactoryManager::m_pSharedMgr = NULL;