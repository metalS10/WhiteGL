#include "NotesCharacter.h"

//=======================================================
//ギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CNotesCharacter::CNotesCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::NOTES;

	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::NOTES);

	if (m_texID >= START_NOTES_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_NOTES_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::NOTES);
}
//デストラクタ
CNotesCharacter::~CNotesCharacter()
{
}

//初期化処理
bool CNotesCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "音に合わせて動くキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc 初期化処理
* @param 初期位置X
* @param 初期位置Y
*/
bool CNotesCharacter::init(float posX, float posY)
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "音に合わせて動くキャラクター初期化に失敗" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc 移動処理
*/
void CNotesCharacter::moveFunc()
{
	//取り付けられているアクションの更新
	for (CAction* pAction : (*m_pActions))
	{
		pAction->update(this);
	}


	//物理計算
	for (CPhysical* pPhysical : (*m_pPhysicals))
	{
		pPhysical->update(this->m_pMove);
	}

	//移動計算
	this->m_pMove->moveBy();
}

//アニメーション処理
void CNotesCharacter::animationFunc()
{
	//アニメーション
	(*this->m_pAnimations)[m_state]->update();
}

/**
*@desc	空間との衝突判定処理
*/
void CNotesCharacter::collision()
{
	//死んでいたら飛ばす
	if (this->m_isAlive == false)
		return;

	//空間との衝突判定を行う
	for (CCollisionArea* pArea : (*this->m_pCollisionAreas))
	{
		pArea->collision(this);
	}
}

/**
* @desc 状態チェック
* @tips 値をチェックして現在の状態を変更する
*/
void CNotesCharacter::checkState()
{

}
//4分音符更新
void CNotesCharacter::quarterUpdate()
{

}

/**
* @desc 反映処理
*/
void CNotesCharacter::applyFunc()
{
	//位置データを反映
	//this->setPosition(this->m_pMove->m_pos);

	//チップデータを反映
	//this->setTextureRect((*this->m_pAnimations)[m_state]->getCurrentChip());
}

/**
* @desc キャラクター1体との衝突判定処理
* @param キャラクターのアドレス
* @return true...衝突した
*/
bool CNotesCharacter::collision(CCharacter* pChara)
{
	return true;
}

/**
*@desc	衝突判定後の処理
*@param	衝突してきたキャラクター
*/
void CNotesCharacter::hits(CCharacter* pChara)
{
	//死んでいたら飛ばす
	if (this->m_isAlive == false)
		return;
	if (this->m_isAction == true)
		return;


	for (CCollisionArea* pCollisionArea : (*this->m_pCollisionAreas))
	{
		pCollisionArea->collision(pChara, this);
	}
}