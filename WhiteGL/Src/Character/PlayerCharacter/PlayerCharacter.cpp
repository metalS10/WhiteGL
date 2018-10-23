
#include "PlayerCharacter.h"
#include "../../AllController/AllController.h"

//================================================
//プレイヤーキャラクターのメンバ関数のコード追加はここから
//================================================

//コンストラクタ
CPlayerCharacter::CPlayerCharacter() {

	//キャラクタータイプをプレイヤーキャラクターに設定
	this->m_charaType = CHARACTER_TYPE::PLAYER;

	this->m_CharaLaunchVector.x = 1.0f;

	this->m_tag = TAG_PLAYER_1;

	this->m_denkiPoint = 100;

	this->m_hitPoint = 100;

	this->m_texID = NULL;

	this->init();


}

//デストラクタ
CPlayerCharacter::~CPlayerCharacter() {
	SAFE_DELETE(m_pSounds);
	this->deletePoly();
	SAFE_DELETE(m_playerEffect[0])
	SAFE_DELETE(m_playerEffect[1])
	SAFE_DELETE(m_playerEffect[2])
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

	//攻撃音読み込み
	this->m_pSounds = new std::vector<CSound*>();
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_AVOIDANCE_MISS	, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_AVOIDANCE		, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_ATTACK_MISS	, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_DRUM_ATTACK			, 16,100));
	this->m_pSounds->push_back(new CSound(SOUND_QUARTER_BEATS		, 16,80));

	//ポリゴンを設定
	this->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 100.0f), rendInfo::LAYER::MAIN);

	//PlayerEffect
	m_playerEffect[0] = new rendInfo::CPolygonRendInfo();
	m_playerEffect[1] = new rendInfo::CPolygonRendInfo();
	m_playerEffect[2] = new rendInfo::CPolygonRendInfo();
	m_playerEffect[0]->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 40.0f), rendInfo::LAYER::MAIN);
	m_playerEffect[1]->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 60.0f), rendInfo::LAYER::MAIN);
	m_playerEffect[2]->setupPoly(CVec4(0.0f, 0.0f, 64.0f, 64.0f), CVec4(100.0f, 100.0f, 100.0f, 80.0f), rendInfo::LAYER::MAIN);


	for (CSound* sound : (*m_pSounds))
	{
		sound->LoadChunk();
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

	//ポリゴンの拍子アクション
	this->polygonBeatsAction();

	//キャラクターの更新処理呼び出し
	CCharacter::update();
}

/**
*	@desc入力処理
*	@tip	移動処理で呼び出す
*/
void CPlayerCharacter::inputFunc()
{
	
	//ダメージ中じゃなければ && 回避中じゃなければ
	if (!this->m_isDamage && !this-> m_isAvoidance)
	{
		if (input->getOnKey(Input::Key::DPAD_LEFT) == true)
		{
			inputArrow.x = -1;
			this->m_pMove->m_accele.x = -0.7f;
			this->Allfalse();
		}

		else if (input->getOnKey(Input::Key::DPAD_RIGHT) == true)
		{
			inputArrow.x =1;
			this->m_pMove->m_accele.x = 0.7f;
			this->Allfalse();
		}
		else
		{
			inputArrow.x = 0;
		}
		if (input->getOnKey(Input::Key::DPAD_UP) == true)
		{

			//現在の方向キー入力情報
			inputArrow.y = 1;
			/*
			//地面についてたら
			if (this->m_isGround)
			{
				//ジャンプを開始させる
				(*this->m_pActions)[(int)ACTION::JUMP]->start();
				this->Allfalse();
			}
			*/
		}
		else if (input->getOnKey(Input::Key::DPAD_DOWN) == true)
		{

			//現在の方向キー入力情報
			inputArrow.y = -1;
		}
		else
		{
			//現在の方向キー入力情報
			inputArrow.y = 0;
		}
		if (input->getOnKey(Input::Key::Z) == true)
		{
			if (m_denkiPoint >= 5.0f)
			{
				//弾発射(playerFactoryのgetActionsにも注意)
				(*this->m_pActions)[(int)ACTION::ATTACK]->start();
				//アニメーションの初期化
				//(*this->m_pAnimations)[(int)STATE::ATTACK]->start();
				this->Allfalse();
				m_isAttack1 = true;
			}

		}
		if (input->getOnKey(Input::Key::X) == true)
		{

			//回避開始
			(*this->m_pActions)[(int)ACTION::AVOIDANCE]->start();

			//(*this->m_pAnimations)[(int)STATE::AVOIDANCE]->start();
		}
		if (input->getOnKey(Input::Key::D) == true)
		{

		}
		//デバッグ用
		if (input->getOnKey(Input::Key::SPACE) == true)
		{
			this->DPHeal(100);
			this->m_hitPoint = 100;
		}
	}
	
	
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
	
	this->inputFunc();
	
	//ジャンプ移動計算
	(*this->m_pActions)[(int)ACTION::JUMP]->update(this);
	

	//弾発射update
	(*this->m_pActions)[(int)ACTION::ATTACK]->update(this);

	//回避アクション更新処理
	(*this->m_pActions)[(int)ACTION::AVOIDANCE]->update(this);

	(*this->m_pActions)[(int)ACTION::DAMAGE]->update(this);



	
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
	//(*this->m_pAnimations)[m_state]->update();

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
	
	//ダメージ中に色を変える
	if (m_isDamage)
	{
		setPolyColor(CVec4(100.0f, 0.0f, 0.0f, 100.0f));
	}
	else if (musicNotesMiss > 0)
	{
		//beatsのミスはピンク
		setPolyColor(CVec4(100.0f, 50.0f, 50.0f, 100.0f));
	}
	else if (m_isAvoidance)
	{
		//回避成功中の回避行動は黄色
		setPolyColor(CVec4(100.0f, 100.0f, 0.0f, 100.0f));
	}
	else
	{
		//何もなければ戻す
		setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 100.0f));
	}
	//回転情報
	if (playerRolling)
	{
		playerAngle -= m_CharaLaunchVector.x*50.0f;
		if (playerAngle >= 600 || playerAngle <= -600)
		{
			playerAngle = 0;
			playerRolling = false;
		}
		setPolyAngle(playerAngle);
	}
	//Playerのエフェクト処理
	this->playerEffect();

	//位置データを反映
	//rendTex->setPosition(this->m_pMove->m_pos,5);
	//頂点座標の更新
	setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));

	//チップデータを反映
	//game.setTextureRect((*this->m_pAnimations)[1]->getCurrentChip());

}
void CPlayerCharacter::playerEffect()
{
	//動いてたらエフェクト表示
	if (m_state == (int)STATE::WALK)
	{
		playerEffectCount[0]++;
		playerEffectCount[1]++;
		playerEffectCount[2]++;
		if (playerEffectCount[0] >= 2)
		{
			playerEffectCount[0] = 0;
			m_playerEffect[0]->setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));
			m_playerEffect[0]->setPolyScale(getPolyScale());
			m_playerEffect[0]->setPolyAngle(getPolyAngle());
			CVec4 playerColor = getPolyColor();
			playerColor.w = 80.0f;
			m_playerEffect[0]->setPolyColor(playerColor);
		}
		if (playerEffectCount[1] >= 4)
		{
			playerEffectCount[1] = 0;
			m_playerEffect[1]->setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));
			m_playerEffect[1]->setPolyScale(getPolyScale());
			m_playerEffect[1]->setPolyAngle(getPolyAngle());
			CVec4 playerColor = getPolyColor();
			playerColor.w = 60.0f;
			m_playerEffect[1]->setPolyColor(playerColor);
		}
		if (playerEffectCount[2] >= 6)
		{
			playerEffectCount[2] = 0;
			m_playerEffect[2]->setPolyPos(CVec2(m_pMove->m_pos.x, m_pMove->m_pos.y));
			m_playerEffect[2]->setPolyScale(getPolyScale());
			m_playerEffect[2]->setPolyAngle(getPolyAngle());
			CVec4 playerColor = getPolyColor();
			playerColor.w = 40.0f;
			m_playerEffect[2]->setPolyColor(playerColor);
		}
	}
	//動いていなければエフェクト非表示
	else
	{
		//前回の処理が「動いている状態」なら
		if (m_state != (int)STATE::WALK)
		{
			m_playerEffect[0]->setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f));
			m_playerEffect[1]->setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f));
			m_playerEffect[2]->setPolyColor(CVec4(100.0f, 100.0f, 100.0f, 0.0f));
		}
	}
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

//拍子間隔セット
void CPlayerCharacter::setBeat(int beat)
{
	m_beatInterval = beat;
	m_beatInterval -= BEAT_INTERVAL;
}

//ジャスト回避
void CPlayerCharacter::DodgeInterval()
{
	m_beatCounter++;

	//音に合わせるタイミングが来たら
	if (!this->musicNotesCounter <= 0)
	{
		//徐々に合わなくなる
		this->musicNotesCounter--;
	}
	//ミスしたら
	if(this->musicNotesMiss > 0)
	{
		this->musicNotesMiss--;
	}
}

void CPlayerCharacter::quarterUpdate()
{
	if (m_beatInterval == 0)
	{
		setBeat(m_beatCounter);
	}
	//回避行動中じゃなければ
	if (!m_isAvoidance)
	{
		//重力を戻す
		(*this->m_pPhysicals)[0]->setGravity(-1.5f);
	}
	m_beatCounter = 0;
	//playerのカウンター
	musicNotesCounter = BEAT_INTERVAL;
	DPHeal(0.5f);
}