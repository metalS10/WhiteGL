#include "ActionController.h"
#include "../Character.h"
#include "../LaunchData.h"
#include "../LaunchTrigger.h"



/*
*	@desc 更新処理(ジャンプ移動計算)
*	@param ジャンプする対象のキャラクター
*	@tips 上キーが押されたらこの関数を呼び出す
*/
void CActionJump::update(CCharacter* pChara)
{
	if (this->m_isJumping == true)
	{
		//ジャンプ中

		//ジャンプブーストを減らしていく
		this->m_currentBoost--;

		//ジャンプブーストが0より小さい場合
		if ((this->m_isJumpStart == false) || (this->m_currentBoost < 0))
		{
			//加速度を0にする
			pChara->m_pMove->m_accele.y = 0.0f;

			pChara->m_isGround = false;
		}
	}
	else if (this->m_isJumpStart == true)
	{
		//ジャンプ開始

		//y軸の加速度に値を設定
		pChara->m_pMove->m_accele.y = this->m_accele;
		//何フレーム、加速度を適用させるかを設定
		this->m_currentBoost = this->m_boost;
		//ジャンプフラグをtrueにする
		this->m_isJumping = true;
	}
	this->m_isJumpStart = false;
}

/**
*@desc	アクションの再起動
*@param	再起動するキャラクター
*@tips	キャラクターのY成分のリセットも行う
*/
void CActionJump::restart(CCharacter* pChara)
{
	//Y成分の速度濾過速度のリセット
	pChara->m_pMove->m_vel.y = 0.0f;
	pChara->m_pMove->m_accele.y = 0.0f;

	//アクションの停止
	this->stop();

	//アクションの開始
	this->start();
}


/*
*	@desc 更新処理(回避移動計算)
*	@param 回避する対象のキャラクター
*	@tips 回避キーが押されたらこの関数を呼び出す
*/
void CActionAvoidance::update(CCharacter* pChara)
{
	if (this->m_isAvoidanceStart == true && m_isAvoidance == false)
	{

		//最大速度の変更
		(*pChara->m_pPhysicals)[1]->SetMaxSpeed(m_accele, 5.0f);
		//x軸の移動速度に値を設定
		pChara->m_pMove->m_vel.x = this->m_accele * pChara->m_CharaLaunchVector.x;
		pChara->m_pMove->m_vel.y = 0;
		pChara->m_isAvoidance = true;
		//回避フラグをtrueにする
		this->m_isAvoidance = true;
	}
	else if(m_isAvoidance)
	{
		//カウンターがインターバルに到達したら
		m_counter++;
		//回避行動のインターバル
		if (m_counter >= m_avoidanceIntarval)
		{
			pChara->m_pMove->m_vel.x = 0;
			pChara->m_isAvoidance = false;
			(*pChara->m_pPhysicals)[1]->SetMaxSpeed(10.0f, 0.5f);
			//次発動可能インターバル
			if (m_counter >= m_intarval)
			{

				m_counter = 0;
				//アクション停止
				m_isAvoidance = false;
			}
		}
		else
		{
			//横に回避行動中
			pChara->m_pMove->m_vel.x = this->m_accele * pChara->m_CharaLaunchVector.x;
			pChara->m_pMove->m_vel.y = 0;

		}
	}
	this->m_isAvoidanceStart = false;
}

/**
*@desc	アクションの再起動
*@param	再起動するキャラクター
*@tips	キャラクターのY成分のリセットも行う
*/
void CActionAvoidance::restart(CCharacter* pChara)
{
	//Y成分の速度濾過速度のリセット
	pChara->m_pMove->m_vel.x = 0.0f;
	pChara->m_pMove->m_accele.x = 0.0f;

	//アクションの停止
	this->stop();

	//アクションの開始
	this->start();
}



//=====================================================
//敵死亡アクション
//=====================================================
/**
*@desc	コンストラクタ
*@param	横移動速度
*@param	跳ねる速度
*/
CActionEnemyDead::CActionEnemyDead(float velX,float leapVelY)
	:m_velX(velX), m_leapVelY(leapVelY)
{
	//コンストラクタ
	//this->start();
}

/**
*@desc	アクション開始
*/
void CActionEnemyDead::start()
{
	//アクション開始
	this->m_isStart = true;
}

/**
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionEnemyDead::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//アクション中

		//画面の外に出たら
		if (pChara->m_pMove->m_pos.y + pChara->m_pBody->m_top < WINDOW_BOTTOM)
		{
			//アクションを停止
			this->stop();

			//有効フラグを下げる
			pChara->m_activeFlag = false;
		}
	}
	else if (this->m_isStart == true)
	{
		//アクションの開始

		//アクション中のフラグを立てる
		this->m_inAction = true;

		//跳ねる速度と横移動速度を設定する
		pChara->m_pMove->m_vel.set(this->m_velX * - pChara->m_moveVector.x, this->m_leapVelY);

		//アクション開始フラグは下げる
		this->m_isStart = false;
	}
}

/**
*@desc	アクション終了
*/
void CActionEnemyDead::stop()
{
	//アクション中フラグを下ろす
	this->m_inAction = false;
}

//========================================================
//上下移動アクション
//========================================================
/**
*@desc	コンストラクタ
*@param	基準位置
*@param	半径
*@param	速度
*/
CActionUpAndDownMove::CActionUpAndDownMove(Point basePos, float radius, float vel)
	:m_basePos(basePos), m_radius(radius), m_vel(vel)
{
	this->start();
}

/**
*@desc	アクション開始
*/
void CActionUpAndDownMove::start()
{
	this->m_inAction = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionUpAndDownMove::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//X位置は基準点のまま
		pChara->m_pMove->m_pos.x = this->m_basePos.x;
		//Y位置はsinカーブ運動
		pChara->m_pMove->m_pos.y = sinf(this->m_counter)* this->m_radius + this->m_basePos.y;

		//カウンターを速度分更新
		this->m_counter += this->m_vel;
	}
}

/**
*@desc	アクション終了
*/
void CActionUpAndDownMove::stop()
{
	this->m_inAction = false;
}

//===================================================
//敵死亡アクション後に死亡位置から敵を出現させる
//===================================================
/**
*@desc	コンストラクタ
*@param	出現させる敵のタイプ
*/
CActionEnemyDeadAndCreateEnemy::CActionEnemyDeadAndCreateEnemy(int type)
	:m_type(type){}

/**
*@desc	アクション開始
*/
void CActionEnemyDeadAndCreateEnemy::start()
{
	this->m_inAction = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionEnemyDeadAndCreateEnemy::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//有効フラグを下ろす
		pChara->m_activeFlag = false;

		//非表示にする
		pChara->setColor(0);


		//==============================
		//ここでは出撃の情報を出撃トリガーとして
		//出撃スケジュールに取り付けるだけ
		//==============================
		
		
		//敵出撃データ(出撃の情報)の生成
		CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(
			(ENEMY_TYPE)this->m_type,
			pChara->m_pMove->m_pos
		);

		//出撃トリガーを生成し、敵出撃データを設定
		CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

		//出撃トリガーを出撃スケジュールとして追加する
		CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);


		//アクション中にフラグを下ろす
		this->m_inAction = false;
		
	}
}

/**
*@desc	アクション終了
*/
void CActionEnemyDeadAndCreateEnemy::stop()
{
	this->m_inAction = false;
}

//===================================================
//敵生成アクション
//===================================================
/**
*@desc	コンストラクタ
*@param	出現させる敵のタイプ
*/
CActionCreateEnemy::CActionCreateEnemy(int type)
	:m_type(type) {}

/**
*@desc	アクション開始
*/
void CActionCreateEnemy::start()
{
	this->m_inAction = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionCreateEnemy::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//==============================
		//ここでは出撃の情報を出撃トリガーとして
		//出撃スケジュールに取り付けるだけ
		//==============================

		this->m_ShotCount++;

		if (this->m_ShotCount == 60)
		{
			//敵出撃データ(出撃の情報)の生成
			CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(
				(ENEMY_TYPE)this->m_type,
				pChara->m_pMove->m_pos
			);

			//出撃トリガーを生成し、敵出撃データを設定
			CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

			//出撃トリガーを出撃スケジュールとして追加する
			CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

			this->m_ShotCount = 0;
		}
	}
}

/**
*@desc	アクション終了
*/
void CActionCreateEnemy::stop()
{
	this->m_inAction = false;
}


//========================================================
//まっすぐ移動アクション
//========================================================
/**
*@desc	コンストラクタ
*@param	基準位置
*@param	速度
*/
CActionMoveStraight::CActionMoveStraight(Point basePos, float vel)
	:m_basePos(basePos), m_vel(vel)
{
	this->start();
}

CActionMoveStraight::CActionMoveStraight(Point basePos, float velX,float velY)
	: m_basePos(basePos), m_vel(velX),m_velY(velY)
{
	this->start();
}

/**
*@desc	アクション開始
*/
void CActionMoveStraight::start()
{
	this->m_inAction = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionMoveStraight::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		
		//位置は基準点のまま
		pChara->m_pMove->m_pos.y = this->m_basePos.y;
		pChara->m_pMove->m_pos.x = this->m_basePos.x;

		//X位置はまっすぐ移動
		pChara->m_pMove->m_vel.set(this->m_vel, this->m_velY);


	}
	this->m_inAction = false;

	//攻撃判定が自動で消えるためのコード
	if (pChara->m_DeleteTime != -1)
	{
		
		deleteCount++;
		if (deleteCount >= pChara->m_DeleteTime)
		{
			pChara->m_activeFlag = false;
			deleteCount = 0;
		}
	}

}

/**
*@desc	アクション終了
*/
void CActionMoveStraight::stop()
{
	this->m_inAction = false;
}


/**
*弾発射アクション
*/
void CActionShotBullet::update(CCharacter* pChara)
{
	if (this->m_inAction== true)
	{
		//アクションがtrueになると
		
		/**
		*弾を発射
		*/
		//間隔が「撃てる状態」なら
		if (this->m_shotCount == 0)
		{
			//まっすぐ弾を打つ
			//CCharacter* bulletChara = (CBulletCharacter*)CBulletFactoryManager::getInstance()->create(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos.x, pChara->m_pMove->m_pos.y, pChara->m_shotLaunchVector);

			//CCharacterAggregateにプレイヤーを追加
			//敵出撃データを作成
			//CBulletLaunchData* pLaunchData = new CBulletLaunchData(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos, pChara->m_shotLaunchVector);


			CAttackLaunchData* pLaunchData = new CAttackLaunchData(
				(ATTACK_TYPE)this->m_bulletType,
				pChara->m_pMove->m_pos,
				pChara->m_CharaLaunchVector
			);


			CAttackLaunchTrigger* pTrigger = new CAttackLaunchTrigger(pLaunchData);

			CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

			this->m_shotCount = this->m_interval;

		}
		//打てないなら
		else
		{
			//間隔を引いていく(0になるまで)
			this->m_shotCount--;

			if (this->m_shotCount == 0)
			{
				pChara->m_isAttack1 = false;
				this->m_inAction = false;
			}
		}


	}
}

//========================================================
//上にあがって落ちるアクション(重力)
//========================================================
/**
*@desc	コンストラクタ
*@param	基準位置
*@param	速度
*/
CActionCurve::CActionCurve(Point basePos, float vel)
	:m_basePos(basePos), m_vel(vel)
{
	this->start();
}
CActionCurve::CActionCurve(Point basePos, float velX,float velY)
	: m_basePos(basePos), m_vel(velX),m_velY(velY)
{
	this->start();
}

/**
*@desc	アクション開始
*/
void CActionCurve::start()
{
	this->m_inAction = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionCurve::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{

		//位置は基準点のまま
		pChara->m_pMove->m_pos.y = this->m_basePos.y;
		pChara->m_pMove->m_pos.x = this->m_basePos.x;

		//ポーンと移動
		pChara->m_pMove->m_vel.set(this->m_vel, this->m_velY);


	}
	this->m_inAction = false;

}

/**
*@desc	アクション終了
*/
void CActionCurve::stop()
{
	this->m_inAction = false;
}


/**
*@desc	アクション開始
*/
void CActionRoll::start()
{
	this->m_isStart = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionRoll::update(CCharacter* pChara)
{
	if (this->m_counter > 0 && this->m_isStart == true)
	{
		this->m_counter--;

		//trueにすることでhitsのcollisionAreaを設定する部分をreturnする
		pChara->m_isAction = true;
		//1にすることでアニメーションする
		pChara->m_state = 1;

		if (this->m_counter <= 0)
		{
			pChara->m_isAction = false;
			pChara->m_state = 0;
			this->stop();
		}
		

	}

}

/**
*@desc	アクション終了
*/
void CActionRoll::stop()
{
	this->m_isStart = false;
	this->m_counter = this->m_interval;
}


//=======================================================
//落ちるアクション
//=======================================================
/**
*@desc	アクション開始
*/
void CActionDown::start()
{
	this->m_isStart = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionDown::update(CCharacter* pChara)
{
	if (this->m_isStart == true)
	{
		this->m_counter--;

		if (this->m_counter <= 0)
		{
			//重力を取り付ける
			pChara->m_pPhysicals->push_back(new CPhysicalGravity());
			this->stop();
		}


	}

}

/**
*@desc	アクション終了
*/
void CActionDown::stop()
{
	this->m_isStart = false;
}


//===============================================================
//敵生成ブロック用アクション
//===============================================================
/**
*@desc	コンストラクタ
*@param	出現させる敵のタイプ
*/
CActionCreateCharacter::CActionCreateCharacter(int type)
	:m_type(type) {}

/**
*@desc	アクション開始
*/
void CActionCreateCharacter::start()
{
	this->m_inAction = true;
}

/*
*@desc	更新処理
*@param	アクションを行う対象のキャラクター
*/
void CActionCreateCharacter::update(CCharacter* pChara)
{
	if (this->m_inAction == true && this->count == 0)
	{

		//敵出撃データ(出撃の情報)の生成
		CEnemyLaunchData* pLaunchData = new CEnemyLaunchData(
			(ENEMY_TYPE)this->m_type,
			pChara->m_pMove->m_pos
		);

		pChara->m_state = 1;

		pLaunchData->m_pos.y += pChara->m_pBody->m_top * 2;

		//出撃トリガーを生成し、敵出撃データを設定
		CEnemyLaunchTrigger* pTrigger = new CEnemyLaunchTrigger(pLaunchData);

		//出撃トリガーを出撃スケジュールとして追加する
		CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

		this->count++;
	}
}

/**
*@desc	アクション終了
*/
void CActionCreateCharacter::stop()
{
	this->m_inAction = false;
}


/*
*	@desc 更新処理(ジャンプ移動計算)
*	@param ジャンプする対象のキャラクター
*	@tips 上キーが押されたらこの関数を呼び出す
*/
void CActionEnemyDamage::update(CCharacter* pChara)
{
	if (this->m_isJumping == true)
	{
		//ジャンプ中
		
		//ジャンプブーストを減らしていく
		this->m_currentBoost--;

		//ジャンプブーストが0より小さい場合
		if ((this->m_isJumpStart == false) || (this->m_currentBoost < 0))
		{
			//加速度を0にする
			pChara->m_pMove->m_accele.y = 0.0f;
			pChara->m_pMove->m_accele.x = 0.0f;
		}
	}
	else if (this->m_isJumpStart == true)
	{
		//ジャンプ開始

		//y軸の加速度に値を設定
		pChara->m_pMove->m_vel.y = this->m_accele;

		//向きに合わせてノックバックのxを変える

		//横移動速度を設定する
		pChara->m_pMove->m_vel.x = this->m_backstep * -pChara->m_moveVector.x;
		
		//何フレーム、加速度を適用させるかを設定
		//this->m_currentBoost = this->m_boost;
		//ジャンプフラグをtrueにする
		this->m_isJumping = true;

		/*
		//点滅アニメーション(速さ,回数)-----------------------
		cocos2d::Blink* blink = cocos2d::Blink::create(1, 20);
		pChara->runAction(blink);
		//-------------------------------------------------
		*/
		//インビジブル時間
		pChara->InvisibleFrame = 60;

		pChara->m_isInvisible = true;

	}
	this->m_isJumpStart = false;
}

/**
*@desc	アクションの再起動
*@param	再起動するキャラクター
*@tips	キャラクターのY成分のリセットも行う
*/
void CActionEnemyDamage::restart(CCharacter* pChara)
{
	//Y成分の速度濾過速度のリセット
	pChara->m_pMove->m_vel.y = 0.0f;
	pChara->m_pMove->m_accele.y = 0.0f;

	//アクションの停止
	this->stop();

	//アクションの開始
	this->start();
}


/**
*弾発射アクション
*/
void CActionShotEnemyBullet::update(CCharacter* pChara)
{
	if (pChara->m_isAlive)
	{
		/**
		*弾を発射
		*/
		//間隔が「撃てる状態」なら
		if (this->m_shotCount == 0)
		{
			//まっすぐ弾を打つ
			//CCharacter* bulletChara = (CBulletCharacter*)CBulletFactoryManager::getInstance()->create(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos.x, pChara->m_pMove->m_pos.y, pChara->m_shotLaunchVector);

			//CCharacterAggregateにプレイヤーを追加
			//敵出撃データを作成
			//CBulletLaunchData* pLaunchData = new CBulletLaunchData(BULLET_TYPE::NORMAL, pChara->m_pMove->m_pos, pChara->m_shotLaunchVector);
			CVec2 vec = CVec2(pChara->m_moveVector.x * 3, pChara->m_moveVector.y);

			CEnemyBulletLaunchData* pLaunchData = new CEnemyBulletLaunchData(
				(BULLET_TYPE)this->m_bulletType,
				pChara->m_pMove->m_pos,
				vec
			);


			CEnemyBulletLaunchTrigger* pTrigger = new CEnemyBulletLaunchTrigger(pLaunchData);

			CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);

			this->m_shotCount = this->m_interval;

		}
		//打てないなら
		else
		{
			//間隔を引いていく(0になるまで)
			this->m_shotCount--;

			if (this->m_shotCount == 0)
			{
				pChara->m_isAttack1 = false;

			}
		}
	}
}


/**
*円状弾発射アクション
*/
void CActionShotEnemySphereBullet::update(CCharacter* pChara)
{
	if (this->m_inAction == true)
	{
		//アクションがtrueになると

		/**
		*弾を発射
		*/
		if (this->m_interval <= 0)
		{
			for (int i = 0;i <= 17;i++)
			{
				//角度
				float angle = i * 20.0f - 10.0f;

				//角度分に２次元ベクトルを取得
				float velX = cos(angle * M_PI / 180.0f) * 6.0f;
				float velY = sin(angle * M_PI / 180.0f) * 6.0f;


				CEnemyBulletLaunchData* pLaunchData = new CEnemyBulletLaunchData(
					(BULLET_TYPE)this->m_bulletType,
					pChara->m_pMove->m_pos,
					CVec2(velX, velY)
				);
				CEnemyBulletLaunchTrigger* pTrigger = new CEnemyBulletLaunchTrigger(pLaunchData);

				CLaunchScheduler::getInstance()->m_pLauncher->add(pTrigger);
			}


			this->m_interval = 60;
		}
		else
		{
			m_interval--;
			if (this->m_interval <= 0)
			{
				this->m_interval = 0;
				this->stop();
			}
		}

	}


}

/**
*ボスアクション
*/
void CActionTRoi::update(CCharacter* pChara)
{
	if (pChara->m_isAlive)
	{
		switch (step)
		{
		case 0:
			if (this->counter <= 0)
			{
				m_pPlayer = CCharacterAggregate::getInstance()->getAtTag(TAG_PLAYER_1);
				if (pChara->m_pMove->m_pos.x < m_pPlayer->m_pMove->m_pos.x - 10)
				{
					(*pChara->m_pActions)[2]->start();
					pChara->setScale(1.0f, 1.0f);
					pChara->m_moveVector = CVec2(20, 0);
					pChara->m_pMove->m_vel = pChara->m_moveVector;

				}
				else if (pChara->m_pMove->m_pos.x > m_pPlayer->m_pMove->m_pos.x + 10)
				{
					(*pChara->m_pActions)[2]->start();
					pChara->setScale(-1.0f, 1.0f);
					pChara->m_moveVector = CVec2(-20, 0);
					pChara->m_pMove->m_vel = pChara->m_moveVector;
				}
				this->counter = this->m_intervalTime;

				step++;
			}
			break;

		//飛ぶ
		case 1:
			if (pChara->m_pMove->m_pos.x < m_pPlayer->m_pMove->m_pos.x - 300 && pChara->m_pMove->m_vel.x < 0)
			{
				(*pChara->m_pPhysicals)[0]->setGravity(0.0f);
				pChara->setScale(1.0f, 1.0f);

				pChara->m_moveVector = CVec2(0, 0);
				step++;

			}
			else if (pChara->m_pMove->m_pos.x > m_pPlayer->m_pMove->m_pos.x + 300 && pChara->m_pMove->m_vel.x > 0)
			{
				(*pChara->m_pPhysicals)[0]->setGravity(0.0f);
				pChara->setScale(-1.0f, 1.0f);

				pChara->m_moveVector = CVec2(0, 0);
				step++;

			}


			pChara->m_pMove->m_vel = pChara->m_moveVector;
			break;

		case 2:
			//空中停止
			if (pChara->m_pMove->m_pos.y >= 300.0f)
			{
				(*pChara->m_pActions)[2]->start();
				this->nowHeight = pChara->m_pMove->m_pos.y;
				step++;
			}
			else
			{
				pChara->m_pMove->m_pos.y += 1;
			}
			break;
		//浮く
		case 3:
			if (up)
			{
				upheight += 0.1f;
				if (upheight >= 1)
				{
					up = false;
				}
			}
			else
			{
				upheight -= 0.1f;
				if (upheight <=  -1)
				{
					up = true;
				}
			}
			pChara->m_pMove->m_pos.y += upheight;
			this->counter--;
			if (this->counter <= 0)
			{
				step = 0;
				(*pChara->m_pPhysicals)[0]->setGravity(0.0f);

			}

			break;
		default:
			break;
		}

	}
}
