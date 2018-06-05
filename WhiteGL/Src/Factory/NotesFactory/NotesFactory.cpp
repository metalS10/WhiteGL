#include "NotesFactory.h"

//==================================================
//音合わせ工場
//==================================================


std::vector<CAnimation*>* CNotesPartsFactory::getAnimations()
{
	//アニメーションデータ群の生成
	std::vector<CAnimation*>* m_pAnimations = new std::vector<CAnimation*>();

	//アニメーションデータ群の作成
	return new std::vector<CAnimation*>;

}

CMove* CNotesPartsFactory::getMove()
{
	return new CMove();
}



std::vector<CPhysical*>* CNotesPartsFactory::getPhysicals()
{
	//適用させる物理演算作成
	return new std::vector<CPhysical*>;
}
std::vector<CAction*>* CNotesPartsFactory::getActions()
{
	//行えるアクション群を作成
	return new std::vector<CAction*>;
}

std::vector<CNotes*>* CNotesPartsFactory::getNotes()
{
	//行える音アクション群を作成
	return new std::vector<CNotes*>;
}

CBody* CNotesPartsFactory::getBody()
{
	return new CBody();
}


CCharacter* CNotesFactory::create(float posX, float posY)
{
	CNotesCharacter* pChara = this->createNotes();

	//==============================================
	//インスタンスに値を設定していく
	//==============================================
	this->settingMove(pChara, posX, posY);

	this->settingTexture(pChara);

	this->settingAnimations(pChara);

	this->settingPhysicals(pChara);

	this->settingActions(pChara);

	//this->settingBody(pChara);

	this->settingCollisionAreas(pChara);

	//初期化
	this->settingInitialize(pChara);

	return pChara;
}


//========================================
//
//音アニメーションの生成工場
//
//========================================
//移動データの設定
void CNotesAnimationFactory::settingMove(CNotesCharacter* pChara, float posX, float posY)
{
	//初期位置の設定
	//pChara->m_pMove->m_pos.set(posX + 14, posY);

	//速度の設定
	pChara->m_pMove->m_vel.set(0.0f, 0.0f);
}

//テクスチャの設定
void CNotesAnimationFactory::settingTexture(CNotesCharacter* pChara)
{
	//テクスチャの設定
	pChara->setTexture(IMAGE_HATENABLOCK);
}

//アニメーションの設定
void CNotesAnimationFactory::settingAnimations(CNotesCharacter* pChara)
{
	//直立アニメーションの設定
	pChara->m_pAnimations->push_back(new CChipListAnimation(10, true));
	//直立アニメーションに設定するためのチップデータの設定
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(0, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(32, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(64, 0, 32, 32));
	(*pChara->m_pAnimations)[0]->addChipData(new CChip(96, 0, 32, 32));

	pChara->m_pAnimations->push_back(new CChipNotAnimation());
}

//物理演算の設定
void CNotesAnimationFactory::settingPhysicals(CNotesCharacter* pChara)
{

}

//アクションの設定
void CNotesAnimationFactory::settingActions(CNotesCharacter* pChara)
{

}

//音アクションの設定
void CNotesAnimationFactory::settingNotes(CNotesCharacter* pChara)
{

}



//衝突判定空間の設定
void CNotesAnimationFactory::settingCollisionAreas(CNotesCharacter* pChara)
{
	
}

//初期化設定
void CNotesAnimationFactory::settingInitialize(CNotesCharacter* pChara)
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