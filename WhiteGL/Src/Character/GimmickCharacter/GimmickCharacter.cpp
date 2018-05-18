//=======================================================
//追加のインクルードはここから
//=======================================================
#include "GimmickCharacter.h"
#include "../../Data/Map/Map.h"

//=======================================================
//ギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CGimmickCharacter::CGimmickCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::GIMMICK;

	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::GIMMICK);

	if (m_texID >= START_GIMMICK_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_GIMMICK_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::GIMMICK);
}
//デストラクタ
CGimmickCharacter::~CGimmickCharacter()
{
}

//初期化処理
bool CGimmickCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc 初期化処理
* @param 初期位置X
* @param 初期位置Y
*/
bool CGimmickCharacter::init(float posX, float posY)
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc 移動処理
*/
void CGimmickCharacter::moveFunc()
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
void CGimmickCharacter::animationFunc()
{
	//アニメーション
	(*this->m_pAnimations)[m_state]->update();
}

/**
*@desc	空間との衝突判定処理
*/
void CGimmickCharacter::collision()
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
void CGimmickCharacter::checkState()
{
	
}

/**
* @desc 反映処理
*/
void CGimmickCharacter::applyFunc()
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
bool CGimmickCharacter::collision(CCharacter* pChara)
{
	return true;
}

/**
*@desc	衝突判定後の処理
*@param	衝突してきたキャラクター
*/
void CGimmickCharacter::hits(CCharacter* pChara)
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


//=======================================================
//回るギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CRollGimmickCharacter::CRollGimmickCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CRollGimmickCharacter::~CRollGimmickCharacter()
{

}
//初期化処理
bool CRollGimmickCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}

//=======================================================
//ちくわギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CTikuwaGimmickCharacter::CTikuwaGimmickCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CTikuwaGimmickCharacter::~CTikuwaGimmickCharacter()
{

}
//初期化処理
bool CTikuwaGimmickCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}


//=======================================================
//音符ギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CNoteGimmickCharacter::CNoteGimmickCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CNoteGimmickCharacter::~CNoteGimmickCharacter()
{

}
//初期化処理
bool CNoteGimmickCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}


//=======================================================
//はてなブロックギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CHatenaGimmickCharacter::CHatenaGimmickCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CHatenaGimmickCharacter::~CHatenaGimmickCharacter()
{

}
//初期化処理
bool CHatenaGimmickCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}

//=======================================================
//はてなブロックギミックのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CWorpGimmickCharacter::CWorpGimmickCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::GIMMICK;
}
CWorpGimmickCharacter::~CWorpGimmickCharacter()
{

}
//初期化処理
bool CWorpGimmickCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "ギミックキャラクター初期化に失敗" << std::endl;
		return false;
	}
	return true;
}