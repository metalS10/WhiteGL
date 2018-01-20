#include "EnemyFactory.h"
#include "EnemyBulletCharacter.h"

//文字コードをUTF-8にする(敵の名前)
#pragma execution_character_set("utf-8")

//==================================================
//プレイヤー工場
//==================================================


std::vector<CAnimation*>* CEnemyPartsFactory::getAnimations()
{
	//アニメーションデータ群の生成
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//アニメーションデータ群の作成
	return new std::vector<CAnimation*>;

}

CMove* CEnemyPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CEnemyPartsFactory::getPhysicals()
{
	//適用させる物理演算作成
	return new std::vector<CPhysical*>;
}


std::vector<CAction*>* CEnemyPartsFactory::getActions()
{
	//行えるアクション群を作成
	return new std::vector<CAction*>;
}

CBody* CEnemyPartsFactory::getBody()
{
	return new CBody();
}

int CEnemyPartsFactory::getState()
{
	return int();
}


CCharacter* CEnemyFactory::create(float posX, float posY)
{
	CEnemyCharacter* pChara = this->createEnemy();

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

	this->settingState(pChara);

	return pChara;
}

//========================================
//
//クリボーの生成工場
//
//========================================
//移動データの設定
void CKuriboFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//移動速度の設定
	pChara->m_moveVector.set(-1.0f, 0.0f);
	pChara->m_CharaLaunchVector.set(-1.0f, 0.0f);
}

//テクスチャの設定
void CKuriboFactory::settingTexture(CEnemyCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_ENEMY);
}

//アニメーションの設定
void CKuriboFactory::settingAnimations(CEnemyCharacter* pChara)
{

	CAnimation* pAnimation = new CChipListAnimation(10, true);
	pAnimation->addChipData(new CChip(37 * 0, 0, 37, 54));
	pAnimation->addChipData(new CChip(37 * 1, 0, 37, 54));
	pAnimation->addChipData(new CChip(37 * 2, 0, 37, 54));
	pAnimation->addChipData(new CChip(37 * 3, 0, 37, 54));
	pChara->m_pAnimations->push_back(pAnimation);

}

//物理演算の設定
void CKuriboFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//重力演算の設定
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//アクションの設定
void CKuriboFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//敵死亡アクションを0番で設定(順番に気を付ける)
	pChara->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));

	//敵ダメージアクション設定
	pChara->m_pActions->push_back(new CActionEnemyDamage(5, 1, 3));

	//弾発射アクションを設定
	pChara->m_pActions->push_back(new CActionShotEnemyBullet((int)BULLET_TYPE::NORMAL, 60));
	
}

//実体の設定
void CKuriboFactory::settingBody(CEnemyCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-18.5, 27, 18.5, -27);
}

//衝突判定空間の設定
void CKuriboFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//画面左端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定
	
	//下のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//右のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//左のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	


	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CKuriboFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//攻撃力の設定
	pChara->m_attackPoint = 1;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	pChara->m_eneType = ENEMY_TYPE::KURIBO;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//体力の設定
void CKuriboFactory::settingState(CEnemyCharacter* pChara)
{
	//名前の設定
	pChara->m_name = "YMD";		//sorce「山田ウィルス」

	pChara->m_maxHitPoint = 3;

	pChara->m_hitPoint = 3;


}

//========================================
//
//緑のノコノコの生成工場
//
//========================================
//移動データの設定
void CGreenNokoNokoFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	pChara->m_moveVector.set(-1.0f, 0.0f);

}

//テクスチャの設定
void CGreenNokoNokoFactory::settingTexture(CEnemyCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_NOKONOKO);

	//左向きに設定
	pChara->setScale(-1.0f, 1.0f);
}

//アニメーションの設定
void CGreenNokoNokoFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 54));
	//歩行アニメーション
	CAnimation* pAnimation = new CChipListAnimation(10, true);
	pAnimation->addChipData(new CChip(0, 0, 32, 54));
	pAnimation->addChipData(new CChip(32, 0, 32, 54));
	pChara->m_pAnimations->push_back(pAnimation);

}

//物理演算の設定
void CGreenNokoNokoFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//重力演算の設定
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//アクションの設定
void CGreenNokoNokoFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//敵死亡アクションを0番で設定
	pChara->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));

	//敵ダメージアクション設定
	pChara->m_pActions->push_back(new CActionEnemyDamage(5, 1, 3));
	

}

//実体の設定
void CGreenNokoNokoFactory::settingBody(CEnemyCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 27, 16, -27);
}

//衝突判定空間の設定
void CGreenNokoNokoFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//画面左端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定
	
	//下のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//右のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//左のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CGreenNokoNokoFactory::settingInitialize(CEnemyCharacter* pChara)
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

//体力の設定
void CGreenNokoNokoFactory::settingState(CEnemyCharacter* pChara)
{
	//名前の設定
	pChara->m_name = "ノコノコ";
	pChara->m_maxHitPoint = 5;

	pChara->m_hitPoint = 5;
}

//========================================
//
//緑のパタパタの生成工場
//
//========================================
//移動データの設定
void CGreenPataPataFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//移動速度の設定
	pChara->m_moveVector.set(-1.0f, 0.0f);
}

//テクスチャの設定
void CGreenPataPataFactory::settingTexture(CEnemyCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_PATAPATA);

	//テクスチャのデフォルトの向きを左向きに設定
	pChara->setScale(-1.0f, 1.0f);

}

//アニメーションの設定
void CGreenPataPataFactory::settingAnimations(CEnemyCharacter* pChara)
{
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));

	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 56, 56));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(56, 0, 56, 56));

}

//物理演算の設定
void CGreenPataPataFactory::settingPhysicals(CEnemyCharacter* pChara)
{

}

//アクションの設定
void CGreenPataPataFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//敵死亡アクションを0番で設定
	pChara->m_pActions->push_back(new CActionEnemyDeadAndCreateEnemy((int)ENEMY_TYPE::NOKONOKO));

	//上下運動アクションの取り付け
	//基準点を初期位置に設定する
	pChara->m_pActions->push_back(new CActionUpAndDownMove(pChara->m_pMove->m_pos, 100, 0.02f));

	//弾発射アクションを設定
	pChara->m_pActions->push_back(new CActionShotEnemyBullet((int)BULLET_TYPE::CUSTOM, 60));
	
}

//実体の設定
void CGreenPataPataFactory::settingBody(CEnemyCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-28, 28, 28, -28);
}

//衝突判定空間の設定
void CGreenPataPataFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{

}

//初期化設定
void CGreenPataPataFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	pChara->m_eneType = ENEMY_TYPE::PATAPATA;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//体力の設定
void CGreenPataPataFactory::settingState(CEnemyCharacter* pChara)
{
	//名前の設定
	pChara->m_name = "パタパタ";

	pChara->m_maxHitPoint = 5;

	pChara->m_hitPoint = 5;
}

//========================================
//
//キラー砲台の生成工場
//
//========================================
//移動データの設定
void CKillerHoudaiFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	pChara->m_moveVector.set(0.0f, 0.0f);
}

//テクスチャの設定
void CKillerHoudaiFactory::settingTexture(CEnemyCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_KILLER);

	//左向きに設定
	pChara->setScale(-1.0f, 1.0f);
}

//アニメーションの設定
void CKillerHoudaiFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());

	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));

}

//物理演算の設定
void CKillerHoudaiFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//重力演算の設定
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//アクションの設定
void CKillerHoudaiFactory::settingActions(CEnemyCharacter* pChara)
{
	pChara->m_pActions->push_back(new CActionCreateEnemy((int)ENEMY_TYPE::KILLER));
}

//実体の設定
void CKillerHoudaiFactory::settingBody(CEnemyCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CKillerHoudaiFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//画面左端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定
	
	//下のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//右のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//左のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CKillerHoudaiFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	pChara->m_eneType = ENEMY_TYPE::KILLERHODAI;

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//体力の設定
void CKillerHoudaiFactory::settingState(CEnemyCharacter* pChara)
{
	//名前の設定
	pChara->m_name = "キラー砲台";

	pChara->m_hitPoint = 1;
}

//========================================
//
//キラーの生成工場
//
//========================================
//移動データの設定
void CKillerFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	pChara->m_moveVector.set(-2.0f, 0.0f);
}

//テクスチャの設定
void CKillerFactory::settingTexture(CEnemyCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_KILLER);

	//左向きに設定
	pChara->setScale(-1.0f, 1.0f);
}

//アニメーションの設定
void CKillerFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipNotAnimation());

	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));

}

//物理演算の設定
void CKillerFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//重力演算の設定
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//アクションの設定
void CKillerFactory::settingActions(CEnemyCharacter* pChara)
{

	pChara->m_pActions->push_back(new CActionEnemyDead(1.0f, -6.0f));
}

//実体の設定
void CKillerFactory::settingBody(CEnemyCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-16, 16, 16, -16);
}

//衝突判定空間の設定
void CKillerFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//画面左端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定
	
	
	//下のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//右のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//左のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CKillerFactory::settingInitialize(CEnemyCharacter* pChara)
{
	//状態の設定
	pChara->m_state = 0;

	//有効フラグを立てる
	pChara->m_activeFlag = true;

	//生きているフラグを立てる
	pChara->m_isAlive = true;

	pChara->m_eneType = ENEMY_TYPE::KILLER;

	//生きているフラグを立てる
	//pChara->setPosition(pChara->m_pMove->m_pos);

	//チップデータを反映
	//pChara->setTextureRect((*pChara->m_pAnimations)[pChara->m_state]->getCurrentChip());
}

//体力の設定
void CKillerFactory::settingState(CEnemyCharacter* pChara)
{
	//名前の設定
	pChara->m_name = "キラー";

	pChara->m_maxHitPoint = 1;

	pChara->m_hitPoint = 1;
}

//========================================
//
//トロくない木馬の生成工場
//
//========================================
//移動データの設定
void CTRoiFactory::settingMove(CEnemyCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	pChara->m_pMove->m_pos.set(posX, posY);

	//速度の設定
	pChara->m_moveVector.set(-1.0f, 0.0f);

}

//テクスチャの設定
void CTRoiFactory::settingTexture(CEnemyCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_TROI);

	//左向きに設定
	pChara->setScale(-1.0f, 1.0f);
}

//アニメーションの設定
void CTRoiFactory::settingAnimations(CEnemyCharacter* pChara)
{
	//(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 54));
	//歩行アニメーション
	CAnimation* pAnimation = new CChipNotAnimation();
	pAnimation->addChipData(new CChip(0, 0, 200, 160));
	pChara->m_pAnimations->push_back(pAnimation);

}

//物理演算の設定
void CTRoiFactory::settingPhysicals(CEnemyCharacter* pChara)
{
	//重力演算の設定
	pChara->m_pPhysicals->push_back(new CPhysicalGravity());
}

//アクションの設定
void CTRoiFactory::settingActions(CEnemyCharacter* pChara)
{
	
	//敵死亡アクションを0番で設定(順番に気を付ける)
	pChara->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));

	//敵ダメージアクション設定
	pChara->m_pActions->push_back(new CActionEnemyDamage(5, 1, 3));

	//弾発射アクションを設定
	pChara->m_pActions->push_back(new CActionShotEnemySphereBullet((int)BULLET_TYPE::NORMAL, 120));

	//TRoi専用アクションを設定
	pChara->m_pActions->push_back(new CActionTRoi(3, false, 300));

}

//実体の設定
void CTRoiFactory::settingBody(CEnemyCharacter* pChara)
{
	//実体データの設定
	pChara->m_pBody->set(-100, 80, 100, -80);
}

//衝突判定空間の設定
void CTRoiFactory::settingCollisionAreas(CEnemyCharacter* pChara)
{
	//==========================================================
	//画面端衝突空間の生成
	//==========================================================
	CCollisionArea* pEndOfScreenArea = new CCollisionAreaEndOfScreen(pChara->m_pBody);

	//画面端の衝突判定空間に領域を設定
	//画面下端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenBottom());
	//画面左端の領域を設定
	pEndOfScreenArea->addTerritory(new CCollisionTerritoryEndOfScreenLeft());
	//画面端の衝突空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pEndOfScreenArea);

	//==========================================================
	//マップ衝突空間の生成
	//==========================================================
	CCollisionArea* pMapArea = new CCollisionAreaMap(pChara->m_pBody);

	//マップチップ衝突空間に領域を設定

	
	//下のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipBottom());
	//右のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipRight());
	//左のマップチップ領域を設定
	pMapArea->addTerritory(new CCollisionTerritoryMapChipLeft());
	

	//画面端の衝突判定空間を取り付ける
	pChara->m_pCollisionAreas->push_back(pMapArea);
}

//初期化設定
void CTRoiFactory::settingInitialize(CEnemyCharacter* pChara)
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

//体力の設定
void CTRoiFactory::settingState(CEnemyCharacter* pChara)
{
	//名前の設定
	pChara->m_name = "トロくない木馬";
	pChara->m_maxHitPoint = 10;

	pChara->m_hitPoint = pChara->m_maxHitPoint;

	pChara->m_eneType = ENEMY_TYPE::TROI;
}

//=======================================================
//敵生成工場管理
//=======================================================
//共有インスタンス本体の宣言
CEnemyFactoryManager* CEnemyFactoryManager::m_pSharedMgr = NULL;