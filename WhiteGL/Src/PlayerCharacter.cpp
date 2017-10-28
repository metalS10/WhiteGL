//================================================
//追加のインクルードはここから
//================================================
#include "PlayerCharacter.h"
//#include "Model/Map/Map.h"
//#include "Data/LaunchData/LaunchData.h"
//#include "Data/LaunchTrigger/LaunchTrigger.h"

//================================================
//プレイヤーキャラクターのメンバ関数のコード追加はここから
//================================================

//コンストラクタ
CPlayerCharacter::CPlayerCharacter() {
	//キャラクタータイプをプレイヤーキャラクターに設定
	this->m_charaType = CHARACTER_TYPE::PLAYER;

	this->m_CharaLaunchVector.x = 1.0f;

	this->m_tag = TAG_PLAYER_1;

	this->m_denkiPoint = 100.0f;

	this->m_hitPoint = 100.0f;

}

//デストラクタ
CPlayerCharacter::~CPlayerCharacter() {
}

//初期化処理
bool CPlayerCharacter::init()
{
	//キャラクタークラスの初期化
	if (CCharacter::init() == false)
	{
		printf("プレイヤーキャラクター初期化に失敗");
		return false;
	}


	return true;
}

void CPlayerCharacter::update()
{
	//x軸の加速度の初期化
	this->m_pMove->m_accele.x = 0.0f;

	//ダメージインターバル処理
	this->DamageInterval();

	//ジャスト回避インターバル
	this->DodgeInterval();

	//キャラクターの更新処理呼び出し
	CCharacter::update();
}

/**
*	@desc入力処理
*	@tip	移動処理で呼び出す
*/
void CPlayerCharacter::inputFunc()
{
	/*
	//ダメージ中じゃなければ && 回避中じゃなければ
	if (!this->m_isDamage && !this-> m_isAvoidance)
	{
		if (pGamepadInput->isPressed((int)XButtonType::LEFT) == true || pKeybordInput->isPressed((int)KeyType::LEFT) == true)
		{

			this->m_pMove->m_accele.x = -0.7f;
			this->Allfalse();
		}

		if (pGamepadInput->isPressed((int)XButtonType::RIGHT) == true || pKeybordInput->isPressed((int)KeyType::RIGHT) == true)
		{
			this->m_pMove->m_accele.x = 0.7f;
			this->Allfalse();
		}

		if (pGamepadInput->isPressed((int)XButtonType::A) == true || pKeybordInput->isPressed((int)KeyType::UP) == true)
		{
			//地面についてたら
			if (this->m_isGround)
			{
				//ジャンプを開始させる
				(*this->m_pActions)[(int)ACTION::JUMP]->start();

				this->Allfalse();
			}
		}
		if (pGamepadInput->isPressed((int)XButtonType::X) == true || pKeybordInput->isPressed((int)KeyType::Z) == true)
		{
			//アニメーションの初期化
			(*this->m_pAnimations)[(int)STATE::ATTACK]->start();
			//弾発射(playerFactoryのgetActionsにも注意)
			(*this->m_pActions)[(int)ACTION::ATTACK]->start();

			this->Allfalse();
			m_isAttack1 = true;
		}
		if (pGamepadInput->isPressed((int)XButtonType::Y) == true || pKeybordInput->isPressed((int)KeyType::X) == true)
		{
			//弾発射(playerFactoryのgetActionsにも注意)
			(*this->m_pActions)[(int)ACTION::ATTACK_NOR]->start();

			(*this->m_pAnimations)[(int)STATE::NOR]->start();

			m_denkiPoint -= 1;

			this->Allfalse();
			m_isAttack2 = true;
		}
		if (pGamepadInput->isPressed((int)XButtonType::B) == true || pKeybordInput->isPressed((int)KeyType::C) == true)
		{

		}
		//DPがあれば(0より上なら)
		if (this->m_denkiPoint > 0)
		{
			if (pGamepadInput->isPressed((int)XButtonType::R_SHOULDER) == true || pKeybordInput->isPressed((int)KeyType::L_SHIFT) == true)
			{
				//ジャスト回避受付時間
				this->m_DodgeTime = 30;
				//回避状態にする
				this->m_isAvoidance = true;
				this->m_denkiPoint -= 5;
				//最大速度の変更
				(*m_pPhysicals)[1]->SetMaxSpeed(20, 5);
			}
		}
		//デバッグ用
		if (pKeybordInput->isPressed((int)KeyType::SPACE) == true)
		{
			this->DPHeal(100);
			this->m_hitPoint = 100;
		}
	}
	//回避中なら
	else if (m_isAvoidance)
	{
		if (pGamepadInput->isPressed((int)XButtonType::LEFT) == true || pKeybordInput->isPressed((int)KeyType::LEFT) == true)
		{
			//不思議な動きになるので空中での移動を制限
			if (this->m_isGround)
			{
				(*m_pPhysicals)[1]->SetMaxSpeed(20, 5);
			}
			else
			{
				(*m_pPhysicals)[1]->SetMaxSpeed(10, 0.5f);
			}
			this->m_pMove->m_accele.x = -20;
			this->Allfalse();
		}

		if (pGamepadInput->isPressed((int)XButtonType::RIGHT) == true || pKeybordInput->isPressed((int)KeyType::RIGHT) == true)
		{
			//不思議な動きになるので空中での移動を制限
			if (this->m_isGround)
			{
				(*m_pPhysicals)[1]->SetMaxSpeed(20, 5);
			}
			else
			{
				(*m_pPhysicals)[1]->SetMaxSpeed(10, 0.5f);
			}
			this->m_pMove->m_accele.x = 20;
			this->Allfalse();
		}
		if (pGamepadInput->isPressed((int)XButtonType::A) == true || pKeybordInput->isPressed((int)KeyType::UP) == true)
		{
			//地面についてたら
			if (this->m_isGround)
			{
				//ジャンプを開始させる
				(*this->m_pActions)[(int)ACTION::SUPERJUMP]->start();

				this->Allfalse();
			}
		}
		//DPがあれば(0より上なら)
		if (this->m_denkiPoint > 0)
		{
			if (pGamepadInput->isPressed((int)XButtonType::R_SHOULDER) == true || pKeybordInput->isPressed((int)KeyType::L_SHIFT) == true)
			{
				//徐々に減っていく
				this->m_denkiPoint -= 0.1;
			}
			else
			{
				//回避状態終わり
				m_isAvoidance = false;
				//最大速度の変更
				(*m_pPhysicals)[1]->SetMaxSpeed(10, 0.5f);
			}
		}
		else
		{
			//回避状態終わり
			m_isAvoidance = false;
			//最大速度の変更
			(*m_pPhysicals)[1]->SetMaxSpeed(10, 0.5f);
		}

	}
	*/
}

/**
*	@desc 移動処理
*/
void CPlayerCharacter::moveFunc()
{
	/*
	*入力処理
	*	今回入力は入力による移動というカテゴリで扱う
	*/
	/*
	this->inputFunc();

	//ジャンプ移動計算
	(*this->m_pActions)[(int)ACTION::JUMP]->update(this);
	

	//弾発射update
	(*this->m_pActions)[(int)ACTION::ATTACK]->update(this);


	(*this->m_pActions)[(int)ACTION::ATTACK_NOR]->update(this);

	(*this->m_pActions)[(int)ACTION::DAMAGE]->update(this);

	(*this->m_pActions)[(int)ACTION::SUPERJUMP]->update(this);


	*/
	//物理計算
	for (CPhysical* pPhysical : (*m_pPhysicals))
	{
		pPhysical->update(this->m_pMove);
	}
	
	//移動計算
	this->m_pMove->moveBy();
}

//アニメーション処理
void CPlayerCharacter::animationFunc()
{
	//アニメーション
	(*this->m_pAnimations)[m_state]->animUpdate();

}

/**
* @desc	画面範囲外判定処理
* @tips	こういった実装の仕方はこれからは少なくしていくように
*		心がけよう。
*		どのようにすれば汎用的に、つまり他のキャラクターでも使い回しできるかを
*		考えて実行していこう。
*/
/*
void CPlayerCharacter::endOfScreen()
{
	//左に移動している場合は画面左で止めるようにする
	if (this->m_pMove->m_vel.x < 0.0f&&this->m_pMove->m_pos.x + m_pBody->m_left < WINDOW_LEFT)
	{
		//設定　修正値
		float boundary = (this->m_pMove->m_pos.x + this->m_pBody->m_left) - WINDOW_LEFT;
		this->m_pMove->m_pos.x -= boundary;

		//速度と加速度を0にするかどうかはゲームによって変わる
		this->m_pMove->m_vel.x = 0.0f;
		this->m_pMove->m_accele.x = 0.0f;
	}
	//右に移動している場合は画面右で止めるようにする
	if (this->m_pMove->m_vel.x > 0.0f&&this->m_pMove->m_pos.x + m_pBody->m_right > WINDOW_RIGHT)
	{
		//設定　修正値
		float boundary = (this->m_pMove->m_pos.x + this->m_pBody->m_right) - WINDOW_RIGHT;
		this->m_pMove->m_pos.x -= boundary;

		//速度と加速度を0にするかどうかはゲームによって変わる
		this->m_pMove->m_vel.x = 0.0f;
		this->m_pMove->m_accele.x = 0.0f;
	}
	//画面下で止めるようにする
	if (this->m_pMove->m_pos.y + this->m_pBody->m_bottom < WINDOW_BOTTOM)
	{
		//設定　修正値
		float boundary = (this->m_pMove->m_pos.y + this->m_pBody->m_bottom) - WINDOW_BOTTOM;
		this->m_pMove->m_pos.y -= boundary;

		//速度と加速度を0にする
		this->m_pMove->m_vel.y = 0.0f;
		this->m_pMove->m_accele.y = 0.0f;

		//ジャンプを停止させる
		(*this->m_pActions)[(int)ACTION::JUMP]->stop();
	}
}
*/

/**
*@desc	空間との衝突判定処理
*/
void CPlayerCharacter::collision()
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
*	@desc 状態チェック
*	@tips 値をチェックして現在の状態を変更する
*/
void CPlayerCharacter::checkState()
{
	/*
	//向きの判定
	if (this->m_pMove->m_vel.x != 0)
	{
		if (this->m_pMove->m_vel.x > 0)
		{
			//右向きに設定
			this->setScale(1.0f, 1.0f);

			this->m_CharaLaunchVector.set(1.0f, 0.0f);
		}
		else
		{
			//左向きに設定
			this->setScale(-1.0f, 1.0f);

			this->m_CharaLaunchVector.set(-1.0f, 0.0f);
		}
	}
	*/

	//y移動速度が0なら
	if (this->m_pMove->m_vel.y == 0.0f)
	{
		//地面についている
		this->m_isGround = true;
	}
	//ダメージ中じゃなければ && 回避中じゃなければ
	if (!this->m_isDamage && !this->m_isAvoidance)
	{
		//状態の判定
		if (this->m_isAttack1 == true)
		{
			m_state = (int)STATE::ATTACK;
		}
		else if (this->m_pMove->m_vel.y > 0.0f)
		{
			//y軸の速度がプラスということはジャンプしている状態
			m_state = (int)STATE::JUMPING;
		}
		else if (this->m_pMove->m_vel.y < 0.0f)
		{
			//y軸の速度がマイナスということは落ちている状態
			m_state = (int)STATE::FALING;
			//地面についていない
			this->m_isGround = false;
		}
		else if (this->m_pMove->m_vel.x != 0)
		{
			//歩いている
			m_state = (int)STATE::WALK;
		}
		
		else if (this->m_isAttack2 == true)
		{
			m_state = (int)STATE::NOR;
		}
		else
		{
			//立っている
			m_state = (int)STATE::STAND;
		}
	}
	//回避中なら
	else if (this->m_isAvoidance)
	{
		if (this->m_pMove->m_vel.y > 0.0f)
		{
			//y軸の速度がプラスということはジャンプしている状態
			m_state = (int)STATE::SUPERJUMP;
		}
		else if (this->m_pMove->m_vel.y < 0.0f)
		{
			//y軸の速度がマイナスということは落ちている状態
			m_state = (int)STATE::SUPERFALING;
			//地面についていない
			this->m_isGround = false;
		}
		else if (this->m_pMove->m_vel.x != 0)
		{
			//歩いている
			m_state = (int)STATE::DASH;
		}
		else
		{
			//回避中立っている状態
			m_state = (int)STATE::AVOIDANCE;
		}
	}
	//ダメージ中なら
	else
	{
		//ダメージ中で地面についていなければ
		if (this->m_isDamage == true && this->m_pMove->m_vel.y != 0)
		{
			m_state = (int)STATE::DAMAGE;
		}
	}
}

/**
*	@desc反映処理
*/
void CPlayerCharacter::applyFunc()
{
	/*
	//位置データを反映
	this->setPosition(this->m_pMove->m_pos);

	//チップデータを反映
	this->setTextureRect((*this->m_pAnimations)[m_state]->getCurrentChip());
	*/
}

/**
*	@desc キャラクター１体との衝突判定処理
*	@param キャラクターのアドレス
*	@return ture....衝突した
*/
bool CPlayerCharacter::collision(CCharacter* pChara)
{
	//敵かギミックだったら
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMY || pChara->m_charaType == CHARACTER_TYPE::GIMMICK)
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
void CPlayerCharacter::hits(CCharacter* pChara)
{
	//敵だったら
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMY)
	{
		//インビジブル状態じゃないなら && 回避状態じゃないなら
		if (!this->m_isInvisible && !this->m_isAvoidance && !pChara->m_isInvisible)
		{
			//(*this->m_pActions)[4]->restart(this);

			//x軸移動の設定(向きに同期)
			this->m_Nockback.x = -this->m_CharaLaunchVector.x * 5;

			//ノックバック
			this->m_pMove->m_vel = this->m_Nockback;

			//ダメージのフラグをtrueにする
			this->m_isDamage = true;
			
			//インビジブルのフラグをtrueにする
			this->m_isInvisible = true;

			//点滅アニメーション(速さ,回数)-----------------------
			//cocos2d::Blink* blink = cocos2d::Blink::create(DamageTime / 60, DamageTime / 3);
			//this->runAction(blink);
			//-------------------------------------------------
			//インビジブル時間
			this->InvisibleFrame = DamageTime;

			//自分とプレイヤーとの衝突判定(上じゃない場合)
			//体力を減らす
			this->m_hitPoint -= pChara->m_attackPoint;
		}
		//ジャスト回避可能なら
		else if (this->m_DodgeTime > 0)
		{
			printf("JustAvoidance!");
		}
	}

	//敵の攻撃だったら
	if (pChara->m_charaType == CHARACTER_TYPE::ENEMYBULLET)
	{
		//インビジブル状態じゃないなら && 回避状態じゃないなら
		if (!this->m_isInvisible && !this->m_isAvoidance)
		{
			//(*this->m_pActions)[4]->restart(this);

			//x軸移動の設定(向きに同期)
			this->m_Nockback.x = -this->m_CharaLaunchVector.x * 5;

			//ノックバック
			this->m_pMove->m_vel = this->m_Nockback;

			//ダメージのフラグをtrueにする
			this->m_isDamage = true;

			//インビジブルのフラグをtrueにする
			this->m_isInvisible = true;

			//点滅アニメーション(速さ,回数)-----------------------
			//cocos2d::Blink* blink = cocos2d::Blink::create(DamageTime / 60, DamageTime / 3);
			//this->runAction(blink);
			//-------------------------------------------------
			//インビジブル時間
			this->InvisibleFrame = DamageTime;

			//自分とプレイヤーとの衝突判定(上じゃない場合)
			//体力を減らす
			this->m_hitPoint -= pChara->m_attackPoint;

			//敵の弾を消す
			pChara->m_activeFlag = false;
		}
	}
	if (this->m_hitPoint <= 0)
	{
		this->m_gameOver = true;
	}
}

void CPlayerCharacter::Allfalse()
{
	this->m_isAttack1 = false;
	this->m_isAttack2 = false;
	this->m_isAttack3 = false;
}

//多重ダメージ防止用(ダメージ判定)
void CPlayerCharacter::DamageInterval()
{
	//ダメージ間隔
	if (!this->InvisibleFrame <= 0)
	{
		this->InvisibleFrame--;
	}
	//ダメージを受けた後の操作無効時間
	if (this->InvisibleFrame <= this->DamageTime * 0.5 && this->m_isDamage)
	{
		this->m_isDamage = false;
	}
	//無敵時間(インビジブル)
	else if (this->InvisibleFrame <= 0 && this->m_isInvisible)
	{
		this->m_isInvisible = false;
	}
}

//ジャスト回避
void CPlayerCharacter::DodgeInterval()
{
	if (!this->m_DodgeTime <= 0)
	{
		this->m_DodgeTime--;
	}
}