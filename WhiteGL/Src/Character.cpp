#include "Character.h"
#include "PlayerCharacter.h"

//コンストラクタ
CCharacter::CCharacter()
{
}

//デストラクタ
CCharacter::~CCharacter()
{
	SAFE_DELETE(this->m_pBody);
	
	for (CAction* pAction : (*m_pActions))
	{
		SAFE_DELETE(pAction);
	}
	SAFE_DELETE(this->m_pActions);
	
	for (CPhysical* pPhysical : (*m_pPhysicals))
	{
		SAFE_DELETE(pPhysical);
	}
	SAFE_DELETE(this->m_pPhysicals);
	SAFE_DELETE(this->m_pMove);
	for (CAnimation* pAnimation : (*m_pAnimations))
	{
		SAFE_DELETE(pAnimation);
	}
	SAFE_DELETE(this->m_pAnimations);
}

//初期化処理
bool CCharacter::init()
{
	/*
	if (cocos2d::Sprite::init() == false)
	{
		CCLOG("Characterの初期化に失敗");
		return false;
	}

	//update()メンバ関数呼び出し
	this->scheduleUpdate();
	*/
	return true;
}

//更新処理
void CCharacter::update()
{
	//移動処理
	this->moveFunc();
	
	//アニメーション処理
	this->animationFunc();

	/*
	//画面範囲外判定処理
	this->endOfScreen();

	//ｍっぷチップとの衝突判定
	this->collisionMap();
	*/
	//衝突判定処理
	this->collision();

	//状態チェック
	this->checkState();

	//反映処理
	this->applyFunc();

	
}

void CCharacter::setScale(CVec2 scale)
{
	this->m_scale = scale;
}
void CCharacter::setScale(float scaleX,float scaleY)
{
	this->m_scale.x = scaleX;
	this->m_scale.y = scaleY;
}
void CCharacter::setColor(CVec4 color)
{
	this->m_color = color;
}
void CCharacter::setColor(float r, float g, float b, float a)
{
	this->m_color.x = r;
	this->m_color.y = g;
	this->m_color.z = b;
	this->m_color.w = a;
}
void CCharacter::setColor(float opacity)
{
	this->m_color.w = opacity;
}


/**
*@desc	DP回復処理
*@param	回復値
*/
void CCharacter::DPHeal(float dp_value)
{
	this->m_denkiPoint += dp_value;
	if (this->m_denkiPoint >= 100)
	{
		this->m_denkiPoint = 100;
	}
}


//==================================================
//キャラクターの集合体
//	シングルトン化させて他のファイルで扱えるようにしておく
//==================================================
//共有インスタンス本体
CCharacterAggregate* CCharacterAggregate::m_pSharedAggre = NULL;

//コンストラクタ
CCharacterAggregate::CCharacterAggregate()
{

}

//デストラクタ
CCharacterAggregate::~CCharacterAggregate()
{

}

//共有インスタンスの取得
CCharacterAggregate* CCharacterAggregate::getInstance()
{
	if (CCharacterAggregate::m_pSharedAggre == NULL)
	{
		CCharacterAggregate::m_pSharedAggre = new CCharacterAggregate();
	}
	return CCharacterAggregate::m_pSharedAggre;
}

//共有インスタンスの破棄
void CCharacterAggregate::removeInstance()
{
	SAFE_DELETE(CCharacterAggregate::m_pSharedAggre);
}

/**
*@desc	キャラクターの集まりの参照を設定
*@param	設定するキャラクターの集まりのアドレス
*/
void CCharacterAggregate::set(std::vector<CCharacter*>* pCharacters)
{
	//すでに設定されていたら設定しないようにしておく
	if (this->m_pCharacters != NULL)
		return;

	this->m_pCharacters = pCharacters;
}

/**
*@desc	キャラクターの集まりを取得
*@return キャラクターの集まり
*/
std::vector<CCharacter*>* CCharacterAggregate::get()
{
	return this->m_pCharacters;
}

/**
*@desc	キャラクター一体を取得
*@param	添字番号
*@return キャラクター
*/
CCharacter* CCharacterAggregate::getAt(int index)
{
	//最大数以上ならNULLを返すように設定しておく
	if (this->m_pCharacters->size() <= index)
		return NULL;

	return(*this->m_pCharacters)[index];
}

/**
*@desc	タグを特定してキャラクター一体を取得
*@param	タグ
*@return キャラクター
*		存在しなければNULLを返す
*/
CCharacter* CCharacterAggregate::getAtTag(int tag)
{
	for (CCharacter* pChara : (*this -> m_pCharacters))
	{
		if (pChara->m_tag == tag)
		{
			return pChara;
		}
	}
}

/**
*@desc	キャラクターの追加
*@param	追加するキャラクター
*/
void CCharacterAggregate::add(CCharacter* pChara)
{
	this->m_pCharacters->push_back(pChara);
}

/**
*@desc	キャラクターの集まりの取り付けられている数を取得
*@return 取り付けられている数
*/
int CCharacterAggregate::getSize()
{
	return (int)this->m_pCharacters->size();
}

