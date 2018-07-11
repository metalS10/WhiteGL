
#include "EnemyCharacter.h"
#include "../../Data/Map/Map.h"

//=======================================================
//敵キャラクターのメンバ関数のコードの追加はここから
//=======================================================
//コンストラクタ
CEnemyCharacter::CEnemyCharacter()
{
	//キャラクタータイプを敵キャラクターに設定
	this->m_charaType = CHARACTER_TYPE::ENEMY;
	this->m_texID = MS::CMS::getInstance()->getTexID((int)ID_TYPE::ENEMY);

	if (m_texID >= START_ENEMY_TEXTURE_NUMBER + 1000)
	{
		m_texID = START_ENEMY_TEXTURE_NUMBER;
	}

	MS::CMS::getInstance()->setTexID(m_texID + 1, (int)ID_TYPE::ENEMY);
}
//デストラクタ
CEnemyCharacter::~CEnemyCharacter()
{
}

//初期化処理
bool CEnemyCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "エネミ―キャラクター初期化に失敗" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc 初期化処理
* @param 初期位置X
* @param 初期位置Y
*/
bool CEnemyCharacter::init(float posX, float posY)
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		std::cerr << "エネミ―キャラクター初期化に失敗" << std::endl;
		return false;
	}

	return true;
}

/**
* @desc 移動処理
*/
void CEnemyCharacter::moveFunc()
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

	//多重ダメージ防止
	this->DamageInterval();

	if (this->m_eneType == ENEMY_TYPE::TROI && !Troi)
	{
		//this->runAction(cocos2d::TintTo::create(0.01f, 0, 0, 0));
		Troi = true;
	}
	if (this->m_enemyDeadOneFrame == 1)
	{
		pPlayerChara->m_pNowEnemy = NULL;
	}
}

//アニメーション処理
void CEnemyCharacter::animationFunc()
{
	//アニメーション
	(*this->m_pAnimations)[m_state]->update();
}

/**
*@desc	空間との衝突判定処理
*/
void CEnemyCharacter::collision()
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
void CEnemyCharacter::checkState()
{
	if (!this->m_isDamage)
	{
		//向きの判定
		if (this->m_pMove->m_vel.x != 0)
		{
			if (this->m_pMove->m_vel.x > 0)
			{
				//右向きに設定
				this->setScale(1.0f, 1.0f);
				if(this->m_moveVector.x >= 0)
					this->m_CharaLaunchVector.set(1.0f,0.0f);
				else
					this->m_CharaLaunchVector.set(-1.0f, 0.0f);
			}
			else
			{
				//左向きに設定
				this->setScale(-1.0f, 1.0f);
				if (this->m_moveVector.x >= 0)
					this->m_CharaLaunchVector.set(1.0f, 0.0f);
				else
					this->m_CharaLaunchVector.set(-1.0f, 0.0f);
			}
		}
	}

	//y移動速度が0なら
	if (this->m_pMove->m_vel.y == 0.0f)
	{
		Groundcount++;
		if (Groundcount == 2)
		{
			if (!this->m_isGround)
			{
				this->m_pMove->m_vel.set(this->m_moveVector);
				this->m_isDamage = false;
			}
			//地面についている
			this->m_isGround = true;
			Groundcount = 0;
		}
	}
	else if (this->m_pMove->m_vel.y > 0.0f)
	{
		//地面についていない
		this->m_isGround = false;
		Groundcount = 0;
	}
	else if (this->m_pMove->m_vel.y < 0.0f)
	{
		//地面についていない
		this->m_isGround = false;
		Groundcount = 0;
	}
}

/**
* @desc 反映処理
*/
void CEnemyCharacter::applyFunc()
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
bool CEnemyCharacter::collision(CCharacter* pChara)
{
	return true;
}

/**
*@desc	衝突判定後の処理
*@param	衝突してきたキャラクター
*/
void CEnemyCharacter::hits(CCharacter* pChara)
{
	//死んでいたら飛ばす
	if (this->m_isAlive == false)
		return;


	if (pChara->m_charaType == CHARACTER_TYPE::PLAYER)
	{

		this->hitsPlayerCharacter(pChara);
	}
	if(pChara->m_charaType == CHARACTER_TYPE::ATTACK)
	{
		this->hitsBulletCharacter(pChara);
	}
}

void CEnemyCharacter::hitsPlayerCharacter( CCharacter* pChara )
{
	//プレイヤーの足下の位置
	float playerFeetPosY = pChara->m_pMove->m_pos.y + pChara->m_pBody->m_bottom;

	//敵の中心位置
	float enePosY = this->m_pMove->m_pos.y;

	//敵より上かどうか
	float posY = playerFeetPosY - enePosY;

	if (posY > 0.0f)
	{
		/*
		//上だった
		std::cerr << u8"勝利" << std::endl;

		//敵の死亡フラグを立てる
		//つまり生きているか死んでいるかのフラグにfalseを入れる
		this->m_isAlive = false;

		//敵キャラクターのアクションに適死亡アクションを取り付ける
		//this->m_pActions->push_back(new CActionEnemyDead(2.0f, 6.0f));
		//↓
		(*this->m_pActions)[0]->start();


		//==============================================================
		//めり込んだ分戻す
		//==============================================================
		//めり込んだ分の計算
		float boundary = (this->m_pMove->m_pos.y + this->m_pBody->m_top) - playerFeetPosY;

		//最終的に戻す値
		pChara->m_pMove->m_pos.y -= boundary;

		//==============================================================
		//ジャンプアクションの再起動
		//==============================================================
		//ジャンプアクションの再起動
		(*pChara->m_pActions)[0]->restart(pChara);
		*/
		
	}
	else
	{
		if(this->m_isAlive)
			pChara->hits(this);
	}
}

void CEnemyCharacter::hitsBulletCharacter(CCharacter* pChara)
{
	//プレイヤーをゲット
	pPlayerChara = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);

	//プレイヤーの今の敵に自身をセット
	pPlayerChara->m_pNowEnemy = this;

	if (this->InvisibleFrame <= 0)
	{
		//ダメージのフラグをtrueにする
		this->m_isDamage = true;
		//体力を減らす
		this->m_hitPoint -= pChara->m_attackPoint;

		//キラーにダメージアクションはないので
		if (this->m_eneType != ENEMY_TYPE::TROI)
		{
			//ダメージアクション
			(*this->m_pActions)[1]->restart(this);
		}
		else if (this->m_eneType == ENEMY_TYPE::TROI && !pPlayerChara->m_stageClear)
		{
			/*
			//赤く点滅
			cocos2d::Sequence* sequence = cocos2d::Sequence::create(cocos2d::TintTo::create(0.05f, 255, 0, 0), cocos2d::TintTo::create(0.1f, 0, 0, 0),NULL);
			this->runAction(sequence);
			*/
			//多重ダメージ防止
			this->InvisibleFrame = 10;

		}
		//敵の体力可視化
		//CCLOG("%i", m_hitPoint);


	//HPが0以下なら死
		if (this->m_hitPoint <= 0)
		{
			//ダメージのフラグをtrueにする
			this->m_isDamage = true;

			if (this->m_eneType == ENEMY_TYPE::TROI)
			{
				this->m_pMove->m_vel = CVec2(0, 0);

				/*
				//黒くなる、消える、殺す
				cocos2d::Sequence* sequence = cocos2d::Sequence::create(cocos2d::TintTo::create(0.5f, 255,0,0),cocos2d::FadeOut::create(0.3),cocos2d::CallFunc::create(this,callfunc_selector(CEnemyCharacter::isDeath)), NULL);
				this->runAction(sequence);
				*/
				this->isDeath();
				//ステージクリアをtrue
				pPlayerChara->m_stageClear = true;

				this->InvisibleFrame = 60;
			}
			else
			{
				//敵の死亡フラグを立てる
				//つまり生きているか死んでいるかのフラグにfalseを入れる
				this->m_isAlive = false;
				(*this->m_pActions)[0]->start();
			}
			this->m_enemyDeadOneFrame++;

		}
		CGameEngine& game = MS::CMS::getInstance()->getGame();
		game.HitStop(3.0f);
		CScene* scene = MS::CMS::getInstance()->getScene();
		scene->SetCameraShake(10.0f,5,2);
	}

	//弾も死ぬ
	//pChara->m_activeFlag = false;

}

void CEnemyCharacter::isDeath()
{
	this->m_isAlive = false;
}


//多重ダメージ防止用
void CEnemyCharacter::DamageInterval()
{
	if (this->InvisibleFrame <= 0)
	{
		this->InvisibleFrame = 0;
		//インビジブルfalse
		this->m_isInvisible = false;
	}
	//以下じゃなければ
	else if (!this->InvisibleFrame <= 0)
	{
		this->InvisibleFrame--;
	}
}
