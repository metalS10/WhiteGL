//=======================================================
//追加のインクルードはここから
//=======================================================
#include "AttackCharacter.h"
#include "Map.h"

//=======================================================
//弾のメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CAttackCharacter::CAttackCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::ATTACK;


}
//デストラクタ
CAttackCharacter::~CAttackCharacter()
{
	//CCLOG("unko");
}

//初期化処理
bool CAttackCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr<<"攻撃の初期化に失敗"<<std::endl;
		return false;
	}
	return true;
}

/**
* @desc 初期化処理
* @param 初期位置X
* @param 初期位置Y
*/
bool CAttackCharacter::init(float posX, float posY)
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "攻撃初期化に失敗"<<std::endl;
		return false;
	}

	return true;
}

/**
* @desc 移動処理
*/
void CAttackCharacter::moveFunc()
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
void CAttackCharacter::animationFunc()
{
	//アニメーション
	(*this->m_pAnimations)[m_state]->update();
}
/**
* @desc	画面判定処理
* @tips	まだ削除の処理を作成していないので画面下で止める処理のみ実装しておく
*/
/*
void CEnemyCharacter::endOfScreen()
{
cocos2d::Vec2* pPos = &this->m_pMove->m_pos;
cocos2d::Vec2* pVel = &this->m_pMove->m_vel;
cocos2d::Vec2* pAccele = &this->m_pMove->m_accele;

//画面下で止めるようにする
if (pVel->y < 0.0f&&pPos->y + this->m_pBody->m_bottom < WINDOW_BOTTOM)
{
//設定 修正値
float boundary = (pPos->y + this->m_pBody->m_bottom) - WINDOW_BOTTOM;
pPos->y -= boundary;

//速度と加速度を0にする
pVel->y = 0.0f;
pAccele->y = 0.0f;
}
}
*/

/**
*@desc	空間との衝突判定処理
*/
void CAttackCharacter::collision()
{
	//空間との衝突判定を行う
	for (CCollisionArea* pArea : (*this->m_pCollisionAreas))
	{
		pArea->collision(this);
	}
	//すべてのキャラクターとの衝突判定
	std::vector<CCharacter*>* pCharacters = CCharacterAggregate::getInstance()->get();
	for (CCharacter* pChara : (*pCharacters))
	{
		//キャラクター1体との衝突判定
		this->collision(pChara);
	}
}

/**
* @desc 状態チェック
* @tips 値をチェックして現在の状態を変更する
*/
void CAttackCharacter::checkState()
{
	//向きの判定
	if (this->m_pMove->m_vel.x != 0)
	{
		if (this->m_pMove->m_vel.x > 0)
		{
			//右向きに設定
			this->setScale(1.0f, 1.0f);
		}
		else
		{
			//左向きに設定
			this->setScale(-1.0f, 1.0f);
		}
	}
}

/**
* @desc 反映処理
*/
void CAttackCharacter::applyFunc()
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
bool CAttackCharacter::collision(CCharacter* pChara)
{
	//敵だったら
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
	{
		//自身の衝突判定矩形
		CCollisionRect myRect(*this->m_pBody, this->m_pMove->m_pos);

		//敵の衝突判定矩形
		CCollisionRect eneRect(*pChara->m_pBody, pChara->m_pMove->m_pos);

		//衝突判定
		if (myRect.collision(&eneRect) == true)
		{
			//衝突した後の判定


			//衝突判定後の処理
			pChara->hits(this);

			return true;
		}
	}
	return false;
}

/**
*@desc	衝突判定後の処理
*@param	衝突してきたキャラクター
*/
void CAttackCharacter::hits(CCharacter* pChara)
{

}


//コンストラクタ
CFireBallAttackCharacter::CFireBallAttackCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::ATTACK;
}
//デストラクタ
CFireBallAttackCharacter::~CFireBallAttackCharacter()
{
}

//初期化処理
bool CFireBallAttackCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "弾の初期化に失敗" << std::endl;
		return false;
	}
	return true;
}

/**
* @desc 初期化処理
* @param 初期位置X
* @param 初期位置Y
*/
bool CFireBallAttackCharacter::init(float posX, float posY)
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "プレイヤーキャラクター初期化に失敗" << std::endl;
		return false;
	}

	return true;
}